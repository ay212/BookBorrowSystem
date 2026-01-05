#ifndef BOOKMANAGEVIEW_H
#define BOOKMANAGEVIEW_H

#include <QWidget>

namespace Ui {
class BookManageView;
}

class BookManageView : public QWidget
{
    Q_OBJECT

public:
    explicit BookManageView(QWidget *parent = nullptr);
    ~BookManageView();

private:
    Ui::BookManageView *ui;
};

#endif // BOOKMANAGEVIEW_H
