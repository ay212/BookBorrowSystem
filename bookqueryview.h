#ifndef BOOKQUERYVIEW_H
#define BOOKQUERYVIEW_H

#include <QWidget>

namespace Ui {
class BookQueryView;
}

class BookQueryView : public QWidget
{
    Q_OBJECT

public:
    explicit BookQueryView(QWidget *parent = nullptr);
    ~BookQueryView();

private:
    Ui::BookQueryView *ui;
};

#endif // BOOKQUERYVIEW_H
