#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::udp;

typedef boost::asio::io_service io_service;

class Server
{
public:
void handle_connections(){
	char buff[1024];
	udp::socket sock(service_, udp::endpoint(udp::v4(),8001));
	while(true){
		udp::endpoint sender_ep;
		int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);
		std::string msg(buff, bytes);
		sock.send_to(boost::asio::buffer(msg), sender_ep);
	}
}

private:
	io_service service_;
};

int main(int argc, char* argv[]){
	Server newServer;
	newServer.handle_connections();
}
