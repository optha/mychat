#pragma once
#include "const.h"

class CServer : public std::enable_shared_from_this<CServer>
{
public :
	// 一个服务器能够监听对端的消息，需要一个上下文（所有事件的基础，相当于一个调度器，在底层不断轮询）
	CServer(boost::asio::io_context& ioc, unsigned short& port);
	void Start();

private:
	// 接收器，接收对端连接
	tcp::acceptor _acceptor;
	net::io_context& _ioc;
	// 复用，不断接收对端连接的信息
	tcp::socket _socket;
};

