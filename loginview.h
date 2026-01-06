#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include "idatabase.h"

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();
signals:
    //子视图发信号，MasterView处理切换
    void goRegisterView();
    void goAdminMainView(QString username);
    void goReaderMainView(QString username);
    void loginFailed(QString reason);
private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginView *ui;

    IDatabase& m_db;
};

#endif // LOGINVIEW_H
