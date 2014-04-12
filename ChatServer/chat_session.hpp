#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>
#include "chat_message.hpp"
#include "chat_room.hpp"

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
typedef boost::asio::io_service io_service;
typedef boost::asio::ip::tcp::socket tcp_socket;
typedef boost::asio::ip::tcp::endpoint tcp_endpoint;
typedef boost::asio::ip::tcp::acceptor tcp_acceptor;
typedef boost::system::error_code error_code;
typedef boost::system::system_error system_error;

class chat_session
		: public chat_participant,
		  public boost::enable_shared_from_this<chat_session>
{
public:
  chat_session(socket_ptr& socket, chat_room& room)
	:socket_(socket),room_(room)
  {
  }

  void start()
  {
	  boost::shared_ptr<chat_session> sessionCopy = shared_from_this();
	  room_.join(sessionCopy);
	  do_read_header();
  }

  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      do_write();
    }
  }

private:
	void handle_read_header(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (!ec && read_msg_.decode_header())
    {
      do_read_body();
    }
    else
    {
      room_.leave((boost::shared_ptr<chat_participant>)shared_from_this());
    }
	}

  void do_read_header()
  {
	  socket_->async_read_some(boost::asio::buffer(read_msg_.data(), chat_message::header_length),boost::bind(&chat_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

	void handle_read_body(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (!ec)
    {
        room_.deliver(read_msg_);
        do_read_header();
    }
    else
    {
      room_.leave((boost::shared_ptr<chat_participant>)shared_from_this());
    }
	}

  void do_read_body()
  {
	  socket_->async_read_some(boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),boost::bind(&chat_session::handle_read_body, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

	void handle_write(const boost::system::error_code& ec, std::size_t bytes_transferred) {
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
      room_.leave((boost::shared_ptr<chat_participant>)shared_from_this());
    }
	}


  void do_write()
  {
      chat_message msg;
      chat_message frontMsg = write_msgs_.front();
      msg.body_length(frontMsg.body_length());
      std::memcpy(msg.body(), frontMsg.body(), msg.body_length());
      msg.encode_header();

      socket_->async_write_some(boost::asio::buffer(msg.data(),msg.length()),boost::bind(&chat_session::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

  socket_ptr socket_;
  chat_room& room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};
