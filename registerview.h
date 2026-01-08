#ifndef REGISTERVIEW_H
#define REGISTERVIEW_H

#include <QWidget>
#include "idatabase.h"

namespace Ui {
class RegisterView;
}

class RegisterView : public QWidget
{
    Q_OBJECT
signals:
    void registerSuccess(); // 注册成功信号
    void backToLogin();     // 返回登录信号
public:
    explicit RegisterView(QWidget *parent = nullptr);
    ~RegisterView();

private slots:
    void on_btnRegister_clicked();

    void on_btnBack_clicked();

private:
    Ui::RegisterView *ui;
};

#endif // REGISTERVIEW_H
