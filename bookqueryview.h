#ifndef BOOKQUERYVIEW_H
#define BOOKQUERYVIEW_H

#include <QWidget>
#include "idatabase.h"

namespace Ui {
class BookQueryView;
}

class BookQueryView : public QWidget
{
    Q_OBJECT

public:
    explicit BookQueryView(QWidget *parent = nullptr);
    ~BookQueryView();
signals:
    void goPreviousView(); // 统一返回信号
private slots:
    void on_btnSearch_clicked();

private:
    Ui::BookQueryView *ui;
};

#endif // BOOKQUERYVIEW_H
