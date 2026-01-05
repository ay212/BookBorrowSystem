#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

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
private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
