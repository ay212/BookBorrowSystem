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
    explicit PersonalBorrowView(QWidget *parent = nullptr);
    ~PersonalBorrowView();

private:
    Ui::PersonalBorrowView *ui;
};

#endif // PERSONALBORROWVIEW_H
