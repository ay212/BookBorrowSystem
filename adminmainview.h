#ifndef ADMINMAINVIEW_H
#define ADMINMAINVIEW_H

#include <QWidget>

namespace Ui {
class AdminMainView;
}

class AdminMainView : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainView(QWidget *parent = nullptr, QString username = "");
    ~AdminMainView();

private slots:
    void on_btnBookManage_clicked();

    void on_btnReaderManage_clicked();

    void on_btnBorrowReturn_clicked();

    void on_btnStat_clicked();

private:
    Ui::AdminMainView *ui;
    QString m_username; // 存储当前登录读者账号（用于个人借阅记录查询）
};

#endif // ADMINMAINVIEW_H
