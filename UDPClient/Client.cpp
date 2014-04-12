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

class Client{
public:
	Client(char* host, int port)
:ep_(boost::asio::ip::address::from_string(host), port)
{
}

	void sync_echo(std::string msg){
		udp::socket sock(service_, udp::endpoint(udp::v4(), 0));
		sock.send_to(boost::asio::buffer(msg),ep_);
		char buff[1024];
		udp::endpoint sender_ep;
		int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);
		std::string copy(buff, bytes);
		std::cout << "server echoed our " << msg << ": " << (copy == msg ? "OK" : "FAIL") << std::endl;
		sock.close();
	}

private:
	udp::endpoint ep_;
	io_service service_;
};

int main(int argc, char* argv[]){

	try
	{
	    if (argc != 3)
	    {
	      std::cerr << "Usage: Client <host> <port>\n";
	      return 1;
	    }

	    char* messages[] = {"Shailesh says hi", "So does Jigar", "Here we go..",0};
		Client client(argv[1],std::atoi(argv[2]));
		boost::thread_group threads;
		for(char ** message = messages; *message; ++message){
			//std::cout << "Message : " << *message;
			std::string testStr(*message);
			void (Client::*fn)(std::string) = &Client::sync_echo;
			threads.create_thread(boost::bind(fn, boost::ref(client), *message));
			boost::this_thread::sleep(boost::posix_time::millisec(100));
		}
		//threads.join_all();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
