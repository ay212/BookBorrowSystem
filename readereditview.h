#ifndef READEREDITVIEW_H
#define READEREDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "idatabase.h"

namespace Ui {
class ReaderEditView;
}

class ReaderEditView : public QWidget
{
    Q_OBJECT
signals:
    void goPreviousView();

public:
    explicit ReaderEditView(QWidget *parent = nullptr, int readerRow = -1);
    ~ReaderEditView();

private slots:
    void on_btnConfirm_clicked();



    void on_btnCancel_clicked();

private:
    Ui::ReaderEditView *ui;
    QDataWidgetMapper *dataMapper;
};

#endif // READEREDITVIEW_H
