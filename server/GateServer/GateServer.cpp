#include <json/json.h>
#include <iostream>
#include <json/reader.h>
#include <json/value.h>
#include "CServer.h"
using namespace std;


int main(int argc, char* argv[])
{
	try
	{
		// 设置端口
		unsigned short port = static_cast<unsigned short>(8080);
		// 初始化上下文，默认1个线程
		net::io_context ioc{ 1 };
		// 信号集
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
			if (error) {
				return;
			}
			ioc.stop();
		});
		// 启动Server
		std::make_shared<CServer>(ioc, port)->Start();
		std::cout << "GateServer listen on Port: " << port << std::endl;
		ioc.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}