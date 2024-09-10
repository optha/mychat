#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _login_dlg = new LoginDialog(this);
    setCentralWidget(_login_dlg);
    // 已经嵌入，不需要show了
    // _login_dlg->show();

    // 使用信号和槽，实现点击按钮进行跳转
    connect(_login_dlg, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchReg);
    _reg_dlg = new RegisterDialog(this);

    // 将dlg嵌入主窗口中
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _reg_dlg->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    // 没有指定父节点，qt就不会回收new出来的对象
    // 此时某个dlg在qt底层的事件循环中，直接delete会强制退出，所以程序会崩溃
    // if(_login_dlg) {
    //     delete _login_dlg;
    //     _login_dlg = nullptr;
    // }
    // if(_reg_dlg) {
    //     delete _reg_dlg;
    //     _reg_dlg = nullptr;
    // }
}

void MainWindow::slotSwitchReg()
{
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}
