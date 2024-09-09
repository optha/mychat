#pragma once
#include "const.h"

class CServer : public std::enable_shared_from_this<CServer>
{
public :
	// һ���������ܹ������Զ˵���Ϣ����Ҫһ�������ģ������¼��Ļ������൱��һ�����������ڵײ㲻����ѯ��
	CServer(boost::asio::io_context& ioc, unsigned short& port);
	void Start();

private:
	// �����������նԶ�����
	tcp::acceptor _acceptor;
	net::io_context& _ioc;
	// ���ã����Ͻ��նԶ����ӵ���Ϣ
	tcp::socket _socket;
};

