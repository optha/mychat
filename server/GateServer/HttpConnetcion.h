#pragma once
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(tcp::socket socket);
	void Start();

private:
	// 超时检测
	void CheckDeadline();
	// 收到数据的应答
	void WriteResponse();
	// 处理请求
	void HandleReq();
	// 解析get参数
	void PreParseGetParam();

	tcp::socket _socket;
	// 接收数据
	beast::flat_buffer _buffer{ 8192 };
	// 解析请求
	http::request<http::dynamic_body> _request;
	// 回应客户端
	http::response<http::dynamic_body> _response;
	// 定时器判断请求是否超时
	net::steady_timer deadline_{
		_socket.get_executor(),
		std::chrono::seconds(60)
	};

	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

