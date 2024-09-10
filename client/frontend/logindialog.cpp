#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include "httpmgr.h"
// #include <QRegExp>
#include <QRegularExpression>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->reg_btn, &QPushButton::clicked, this, &LoginDialog::switchRegister);
    // // 连接登录回包信号
    // connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this,
    //         &LoginDialog::slot_login_mod_finish);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->err_tip->setProperty("state","normal");
    }else{
        ui->err_tip->setProperty("state","err");
    }

    ui->err_tip->setText(str);

    repolish(ui->err_tip);
}

// void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
// {
//     if(err != ErrorCodes::SUCCESS){
//         showTip(tr("网络请求错误"),false);
//         return;
//     }

//     // 解析 JSON 字符串,res需转化为QByteArray
//     QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
//     // json解析错误
//     if(jsonDoc.isNull()){
//         showTip(tr("json解析错误"),false);
//         return;
//     }

//     // json解析错误
//     if(!jsonDoc.isObject()){
//         showTip(tr("json解析错误"),false);
//         return;
//     }


//     // 调用对应的逻辑,根据id回调。
//     _handlers[id](jsonDoc.object());

//     return;
// }
