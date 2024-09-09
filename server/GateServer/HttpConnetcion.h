#pragma once
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(tcp::socket socket);
	void Start();

private:
	// ��ʱ���
	void CheckDeadline();
	// �յ����ݵ�Ӧ��
	void WriteResponse();
	// ��������
	void HandleReq();
	// ����get����
	void PreParseGetParam();

	tcp::socket _socket;
	// ��������
	beast::flat_buffer _buffer{ 8192 };
	// ��������
	http::request<http::dynamic_body> _request;
	// ��Ӧ�ͻ���
	http::response<http::dynamic_body> _response;
	// ��ʱ���ж������Ƿ�ʱ
	net::steady_timer deadline_{
		_socket.get_executor(),
		std::chrono::seconds(60)
	};

	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

