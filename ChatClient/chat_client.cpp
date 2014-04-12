#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
  chat_client(boost::asio::io_service& io_service,
      tcp::resolver::iterator endpoint_iterator)
    : io_service_(io_service),
      socket_(io_service)
  {
    do_connect(endpoint_iterator);
  }


  void run_service()
  {
	  io_service_.run();
  }

  void start()
  {
	  boost::thread t(boost::bind(&chat_client::run_service,this));
	  svcThread_ = boost::move(t);
  }

  void wait()
  {
	  svcThread_.join();
  }

  void handle_write_msg(const chat_message& msg){
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
	}

  void write(const chat_message& msg)
  {
    io_service_.post(boost::bind(&chat_client::handle_write_msg, this, msg));
  }

  void handle_close(){
  	socket_.close();
	}

  void close()
  {
    io_service_.post(boost::bind(&chat_client::handle_close, this));
  }

private:
  void do_connect(tcp::resolver::iterator endpoint_iterator)
  {
    boost::asio::async_connect(socket_, endpoint_iterator,boost::bind(&chat_client::handle_connect, this,_1,endpoint_iterator));
  }

  void handle_connect(const boost::system::error_code & ec, tcp::resolver::iterator endpoint_iterator) {
	    std::cout << "Client Connected" << std::endl;
        if (!ec)
        {
          do_read_header();
        }
	}

  void do_read_header()
  {
	  boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), chat_message::header_length),boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

  void handle_read_header(const boost::system::error_code & ec, std::size_t bytes_transferred) {
	  if (!ec && read_msg_.decode_header())
      {
        do_read_body();
      }
      else
      {
        socket_.close();
      }
	}

  void do_read_body()
  {
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),boost::bind(&chat_client::handle_read_body, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

  void handle_read_body(const boost::system::error_code & ec, std::size_t bytes_transferred) {
      if (!ec)
      {
        std::cout.write(read_msg_.body(), read_msg_.body_length());
        std::cout << "\n";
        do_read_header();
      }
      else
      {
        socket_.close();
      }
	}

  void do_write()
  {
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
          write_msgs_.front().length()),boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

  void handle_write(const boost::system::error_code & ec, std::size_t bytes_transferred) {
      if (!ec)
      {
        write_msgs_.pop_front();
        if (!write_msgs_.empty())
        {
          do_write();
        }
      }
      else
      {
        socket_.close();
      }
	}

private:
  boost::asio::io_service& io_service_;
  boost::thread svcThread_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    //auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
    chat_client c(io_service, resolver.resolve({ argv[1], argv[2] }));

    c.start();
    //boost::thread t(c.start());

    char line[chat_message::max_body_length + 1];
    while (std::cin.getline(line, chat_message::max_body_length + 1))
    {
      chat_message msg;
      msg.body_length(std::strlen(line));
      std::memcpy(msg.body(), line, msg.body_length());
      msg.encode_header();
      c.write(msg);
    }

    c.close();
    c.wait();
    //t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
