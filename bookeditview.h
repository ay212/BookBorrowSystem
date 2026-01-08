#ifndef BOOKEDITVIEW_H
#define BOOKEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "idatabase.h"

namespace Ui {
class BookEditView;
}

class BookEditView : public QWidget
{
    Q_OBJECT

public:
    explicit BookEditView(QWidget *parent = nullptr, int bookId = -1);
    ~BookEditView();

signals:
    void goPreviousView();

private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

private:
    Ui::BookEditView *ui;
    QDataWidgetMapper *dataMapper;

};

#endif // BOOKEDITVIEW_H
