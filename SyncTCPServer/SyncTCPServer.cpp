#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

void client_session(socket_ptr sock) {
    while ( true) {
    try{
        char data[1024];
        size_t len = sock->read_some(boost::asio::buffer(data));
        if ( len > 0){
        std::cout << data << std::endl;        	
		    //std::cout << "Writing Back!!!" << std::endl;      
		    //sock->write_some(boost::asio::buffer("ok", 2));  	
            //write(*sock, boost::asio::buffer("ok", 2));
            }
	    }
	    catch(boost::system::system_error e){
	    std::cout << e.code() << std::endl;
	    break;
	    }
    }
}

int main()
{
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint ep( boost::asio::ip::tcp::v4(), 2001); // listen on 2001
	boost::asio::ip::tcp::acceptor acc(service, ep);
	while ( true) {
	    socket_ptr sock(new boost::asio::ip::tcp::socket(service));
        std::cout << "Here we go" << std::endl;
	    acc.accept(*sock);
	    boost::thread(boost::bind(client_session, sock));
	}
}
