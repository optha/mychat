#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
// 信号传递、槽
#include <QObject>
// .pro 文件里 QT += network Qt原生的http管理类
#include <QNetworkAccessManager>
// 数据序列化
#include <QJsonObject>
// 数据反序列化
#include <QJsonDocument>
#include "global.h"

// CRTP 实例化自己 在运行时才生成
class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private:
    // 基类可以访问子类的构造函数
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
