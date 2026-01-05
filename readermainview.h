#ifndef READERMAINVIEW_H
#define READERMAINVIEW_H

#include <QWidget>

namespace Ui {
class ReaderMainView;
}

class ReaderMainView : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderMainView(QWidget *parent = nullptr, QString username = "");
    ~ReaderMainView();
signals:
    // 子视图仅发信号，由 MasterView 处理栈切换
    void goBookQueryView(); // 跳转图书查询视图
    void goPersonalBorrowView(QString username); // 跳转个人借阅记录（传当前用户名）
private slots:
    void on_btnBookQuery_clicked();

    void on_btnPersonalBorrow_clicked();

private:
    Ui::ReaderMainView *ui;
    QString m_username;
};

#endif // READERMAINVIEW_H
