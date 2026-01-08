#ifndef BORROWRETURNVIEW_H
#define BORROWRETURNVIEW_H

#include <QWidget>
#include "idatabase.h"

namespace Ui {
class BorrowReturnView;
}

class BorrowReturnView : public QWidget
{
    Q_OBJECT
signals:
    // 仅保留返回信号（对齐前面模块）
    void goPreviousView();
public:
    explicit BorrowReturnView(QWidget *parent = nullptr);
    ~BorrowReturnView();

private slots:
    void on_btnBorrow_clicked();

    void on_btnReturn_clicked();

    void on_btnSearch_clicked();

private:
    Ui::BorrowReturnView *ui;
};

#endif // BORROWRETURNVIEW_H
