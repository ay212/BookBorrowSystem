#ifndef READERMANAGEVIEW_H
#define READERMANAGEVIEW_H

#include <QWidget>
#include <QHeaderView>
#include <QMessageBox>
#include "idatabase.h"

namespace Ui {
class ReaderManageView;
}

class ReaderManageView : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderManageView(QWidget *parent = nullptr);
    ~ReaderManageView();
signals:
    void goReaderEditView(int row);

private slots:
    void on_btnSearch_clicked();

    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_btnEdit_clicked();

private:
    Ui::ReaderManageView *ui;
};

#endif // READERMANAGEVIEW_H
