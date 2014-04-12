#include <boost/make_shared.hpp>
#include "chat_session.hpp"

class chat_server
{
public:
  chat_server(int portNumber)
: endpoint_( boost::asio::ip::tcp::v4(), portNumber),
  acceptor_(service_, endpoint_)
  {
    do_accept();
  }

private:
  void handle_accept(socket_ptr& sock, const error_code& ec){
    if (!ec)
    {
    	boost::shared_ptr<chat_session> session(new chat_session(sock, room_));
    	session->start();
    }
    do_accept();
	}

  void do_accept()
  {
	  socket_ptr sock(new tcp_socket(service_));
	  acceptor_.async_accept(*sock, boost::bind(&chat_server::handle_accept,this,sock, _1));
	  service_.run();
  }
  io_service service_;
  tcp_endpoint endpoint_;
  tcp_acceptor acceptor_;
  chat_room room_;
};


int main(int argc, char* argv[])
{
	  try
	  {
	    if (argc < 2)
	    {
	      std::cerr << "Usage: chat_server <port> [<port> ...]\n";
	      return 1;
	    }
	    //std::list<chat_server> servers;
	    for (int i = 1; i < argc; ++i)
	    {
	      	std::cout << argv[i] << std::endl;
	    	chat_server newChatServer(std::atoi(argv[i]));
	    	//servers.push_back(newChatServer);
	    }

	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }

	  return 0;
}
