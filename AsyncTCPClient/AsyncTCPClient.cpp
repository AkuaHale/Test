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

class asynctcpclient{
public:
	asynctcpclient(/*const char* ipAddress,*/ int portNumber)
		:_ep( boost::asio::ip::address::from_string("127.0.0.1"), portNumber), _sock(new tcp_socket(_service)){
	}

	void connect(){
		_sock->async_connect(_ep, boost::bind(&asynctcpclient::connect_handler,this, _1));
		_service.run();
	}

	void connect_handler(const error_code & ec) {
	  // here we know we connected successfully
	  // if ec indicates success
	    std::cout << "Client Connected" << std::endl;

		try{
			char newdata[1024]="";
			_sock->async_read_some(boost::asio::buffer(newdata), boost::bind(&asynctcpclient::handle_read,this,_sock, newdata, boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
		}catch(system_error e){
			std::cout << e.code() << std::endl;
		}

	    while (std::cin)
	    {
			_sock->async_write_some(boost::asio::buffer(getNextLine()), boost::bind(&asynctcpclient::handle_write,this,_sock, boost::asio::placeholders::error));
	    }
	}

	std::string getNextLine(){
	    std::string line;
	    std::getline(std::cin, line);
	    return line;
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
	    			sock->async_read_some(boost::asio::buffer(newerdata), boost::bind(&asynctcpclient::handle_read,this,sock,newerdata, boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
	            }
	            else
	            {
	                std::cout << "In Else" << std::endl;
	                std::cout << newdata << std::endl;
	            }
    	std::cout << "Handle Read Finish" << std::endl;
	        }

private:
	io_service _service;
	tcp_endpoint _ep;
	socket_ptr _sock;
};


int main()
{
	asynctcpclient client(/*"127.0.0.1",*/ 2001);
	client.connect();
}
