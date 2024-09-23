#include "VerifyGrpcClient.h"
#include "ConfigMgr.h"

GetVerifyRsp VerifyGrpcClient::GetVerifyCode(std::string email)
{
    ClientContext context;
    GetVerifyRsp reply;
    GetVerifyReq request;
    request.set_email(email);
    auto stub = pool_->getConnection();
    Status status = stub->GetVerifyCode(&context, request, &reply);

    if (status.ok()) {
        pool_->returnConnection(std::move(stub));
        return reply;
    }
    else {
        pool_->returnConnection(std::move(stub));
        reply.set_error(ErrorCodes::RPCFailed);
        return reply;
    }
}

VerifyGrpcClient::VerifyGrpcClient()
{
    auto& gCfgMgr = ConfigMgr::Inst();
    std::string host = gCfgMgr["VerifyServer"]["Host"];
    std::string port = gCfgMgr["VerifyServer"]["Port"];
    pool_.reset(new RPCConPool(5, host, port));
}

RPCConPool::RPCConPool(size_t poolsize, std::string host, std::string port) 
    : poolSize_(poolsize), host_(host), port_(port), b_stop_(false)
{
    for (size_t i = 0; i < poolSize_; ++i) {
        std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
        connections_.push(VerifyService::NewStub(channel));
    }
}

RPCConPool::~RPCConPool()
{
    std::lock_guard<std::mutex> lock(mutex_);
    Close();
    while (!connections_.empty()) {
        connections_.pop();
    }
}

void RPCConPool::Close()
{
    b_stop_ = true;
    cond_.notify_all();
}

std::unique_ptr<VerifyService::Stub> RPCConPool::getConnection()
{
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this]() {
        if (b_stop_) {
            return true;
        }
        return !connections_.empty();
    });
    if (b_stop_) {
        return nullptr;
    }
    auto context = std::move(connections_.front());
    connections_.pop();
    return context;
}

void RPCConPool::returnConnection(std::unique_ptr<VerifyService::Stub> context)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (b_stop_) {
        return;
    }
    connections_.push(std::move(context));
    cond_.notify_one();
}
