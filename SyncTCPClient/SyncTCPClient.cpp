#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

void connect_handler(const boost::system::error_code & ec) {
  // here we know we connected successfully
  // if ec indicates success
    std::cout << "Client Connected" << std::endl;
}


int main()
{
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 2001);
	boost::asio::ip::tcp::socket sock(service);
	bool isConnected = false;
	try{
	sock.connect(ep);
	isConnected = true;
	}catch(boost::system::system_error e){
	std::cout << e.code() << std::endl;
	isConnected = false;
	}
	if(isConnected){
	
    std::string line;
    while (std::cin)
    {
        std::getline(std::cin, line);
        sock.write_some(boost::asio::buffer(line));  	
    }
	
	//char data[512];
	//std::cout << "Before Read" << std::endl;        	
    //size_t len = sock.read_some(boost::asio::buffer(data));
    //if ( len > 0){
	//    std::cout << data << std::endl;        	
    //    }
	//std::cout << "Before Read" << std::endl;        	
    }
}
