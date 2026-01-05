#ifndef BORROWRETURNVIEW_H
#define BORROWRETURNVIEW_H

#include <QWidget>

namespace Ui {
class BorrowReturnView;
}

class BorrowReturnView : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowReturnView(QWidget *parent = nullptr);
    ~BorrowReturnView();

private:
    Ui::BorrowReturnView *ui;
};

#endif // BORROWRETURNVIEW_H
