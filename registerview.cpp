#include "registerview.h"
#include "ui_registerview.h"
#include <QMessageBox>

RegisterView::RegisterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterView)
{
    ui->setupUi(this);
}

RegisterView::~RegisterView()
{
    delete ui;
}

void RegisterView::on_btnRegister_clicked()
{
    // 获取输入
    QString username = ui->leUsername->text().trimmed();
    QString password = ui->lePassword->text().trimmed();
    QString confirmPwd = ui->leConfirmPwd->text().trimmed();

    // 输入校验
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名/密码不能为空！");
        return;
    }
    if (password != confirmPwd) {
        QMessageBox::warning(this, "提示", "两次密码不一致！");
        return;
    }

    // 调用注册接口
    bool success = IDatabase::getInstance().userRegister(username, password, "reader");
    if (success) {
        QMessageBox::information(this, "成功", "注册成功！");
        emit registerSuccess();
    } else {
        QMessageBox::warning(this, "失败", "用户名已存在！");
    }
    emit backToLogin();
}


void RegisterView::on_btnBack_clicked()
{
    emit backToLogin();
}

