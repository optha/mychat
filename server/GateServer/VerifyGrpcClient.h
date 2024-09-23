#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

// ioc³Ø
class RPCConPool
{
public:
    RPCConPool(size_t poolsize, std::string host, std::string port);
    ~RPCConPool();
    void Close();
    std::unique_ptr<VerifyService::Stub> getConnection();
    void returnConnection(std::unique_ptr<VerifyService::Stub> context);

private:
    std::atomic<bool> b_stop_;
    size_t poolSize_;
    std::string host_;
    std::string port_;
    std::queue<std::unique_ptr<VerifyService::Stub>> connections_;
    std::condition_variable cond_;
    std::mutex mutex_;
};

class VerifyGrpcClient : public Singleton<VerifyGrpcClient>
{
    friend class Singleton<VerifyGrpcClient>;
public:

    GetVerifyRsp GetVerifyCode(std::string email);

private:
    VerifyGrpcClient();
        //std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials());
        //stub_ = VerifyService::NewStub(channel);


    //std::unique_ptr<VerifyService::Stub> stub_;
    std::unique_ptr<RPCConPool> pool_;
};