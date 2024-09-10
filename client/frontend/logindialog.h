#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    void showTip(QString str,bool b_ok);
    // void initHttpHandlers();

private slots:
    // void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);

signals:
    void switchRegister();
};

#endif // LOGINDIALOG_H
