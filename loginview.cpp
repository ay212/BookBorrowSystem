#include "loginview.h"
#include "ui_loginview.h"
#include <QMessageBox>
#include <QDebug>

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
    , m_db(IDatabase::getInstance())
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btnLogin_clicked()
{
    // 1. 获取并校验输入（去空格，避免无效值）
    QString username = ui->leUsername->text().trimmed();
    QString password = ui->lePassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名/密码不能为空！");
        emit loginFailed("空输入");
        return;
    }

    // 2. 调用数据库登录接口
    QString role;
    QString loginResult = m_db.userLogin(username, password, role);

    // 3. 根据结果发送对应信号
    if (loginResult == "LoginOK") {
        QMessageBox::information(this, "登录成功", QString("欢迎！角色：%1").arg(role));
        if (role == "admin") {
            emit goAdminMainView(username); // 管理员→管理员主界面
        } else {
            emit goReaderMainView(username); // 读者→读者主界面
        }
        // 清空输入框
        ui->leUsername->clear();
        ui->lePassword->clear();
    } else if (loginResult == "wrongPassword") {
        QMessageBox::critical(this, "登录失败", "密码错误！");
        emit loginFailed("密码错误");
        ui->lePassword->clear();
        ui->lePassword->setFocus();
    } else if (loginResult == "wrongUsername") {
        QMessageBox::critical(this, "登录失败", "用户名不存在！");
        emit loginFailed("用户名不存在");
        ui->leUsername->clear();
        ui->leUsername->setFocus();
    } else {
        QMessageBox::critical(this, "登录失败", "数据库异常！");
        emit loginFailed("数据库错误");
    }
}

