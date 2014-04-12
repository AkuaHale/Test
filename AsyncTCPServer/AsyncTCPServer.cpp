#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
typedef boost::asio::io_service io_service;
typedef boost::asio::ip::tcp::socket tcp_socket;
typedef boost::asio::ip::tcp::endpoint tcp_endpoint;
typedef boost::asio::ip::tcp::acceptor tcp_acceptor;
typedef boost::system::error_code error_code;
typedef boost::system::system_error system_error;

class asynctcpserver{
public:
	asynctcpserver(int portNumber)
		:_ep( boost::asio::ip::tcp::v4(), portNumber),_acc(_service, _ep)/*,_sock(new tcp_socket(_service))*/{
	}

	void start_accept(){
    	std::cout << "Start Accept Start" << std::endl;
		socket_ptr sock(new tcp_socket(_service));
		_acc.async_accept(*sock, boost::bind(&asynctcpserver::handle_accept,this,sock, _1));
		_service.run();
    	std::cout << "Start Accept Finish" << std::endl;
	}

	void handle_accept(socket_ptr sock, const error_code& err){
    	std::cout << "Handle Accept Start" << std::endl;
		if(err){
			return;
		}
		//Work Start
		try{
			char newdata[1024]="";
			sock->async_read_some(boost::asio::buffer(newdata), boost::bind(&asynctcpserver::handle_read,this,sock, newdata, boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
		}catch(system_error e){
			std::cout << e.code() << std::endl;
			//break;
		}
		//Work Finish
		start_accept();
    	std::cout << "Handle Accept Finish" << std::endl;
	}

	void handle_write(socket_ptr sock, const boost::system::error_code& e) {
		std::cout << "Handle Write Start" << std::endl;
		std::cout << "Handle Write Finish" << std::endl;
	}

	void handle_read(socket_ptr sock, char* newdata, std::size_t bytes_transferred, const boost::system::error_code& e) {
    	std::cout << "Handle Read Start" << std::endl;
		if (!e && bytes_transferred)    {
	                std::cout << " " << bytes_transferred <<"b" << std::endl;
	                std::cout << " " << newdata  << std::endl;
	                char newerdata[1024]="";
	    			sock->async_read_some(boost::asio::buffer(newerdata), boost::bind(&asynctcpserver::handle_read,this,sock,newerdata, boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
	            }
	            else
	            {
	                std::cout << "In Else" << std::endl;
	                std::cout << newdata << std::endl;
	            }
    	std::cout << "Handle Read Finish" << std::endl;
		std::cout << "Before Writing Back" << std::endl;
		sock->async_write_some(boost::asio::buffer("Received!!!!"), boost::bind(&asynctcpserver::handle_write,this,sock, boost::asio::placeholders::error));
		std::cout << "After Writing Back" << std::endl;
	        }

private:
	io_service _service;
	tcp_endpoint _ep;
	tcp_acceptor _acc;
	//char _data[1024];
};


int main()
{
	asynctcpserver server(2001);
	server.start_accept();
	/*
	io_service service;
	tcp_endpoint ep( boost::asio::ip::tcp::v4(), 2001); // listen on 2001
	tcp_acceptor acc(service, ep);
	socket_ptr sock(new tcp_socket(service));
	start_accept(service, acc, sock);
	service.run();
	*/
}
