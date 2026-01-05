#ifndef PERSONALBORROWVIEW_H
#define PERSONALBORROWVIEW_H

#include <QWidget>

namespace Ui {
class PersonalBorrowView;
}

class PersonalBorrowView : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalBorrowView(QWidget *parent = nullptr, QString username = "");
    ~PersonalBorrowView();

private:
    Ui::PersonalBorrowView *ui;
    QString m_username; // 存储当前登录读者账号（用于个人借阅记录查询）
};

#endif // PERSONALBORROWVIEW_H
