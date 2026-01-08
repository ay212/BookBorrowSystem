#ifndef BOOKMANAGEVIEW_H
#define BOOKMANAGEVIEW_H

#include <QWidget>
#include <QHeaderView>
#include <QMessageBox>
#include "idatabase.h"

namespace Ui {
class BookManageView;
}

class BookManageView : public QWidget
{
    Q_OBJECT

public:
    explicit BookManageView(QWidget *parent = nullptr);
    ~BookManageView();




private slots:
    void on_btnAdd_clicked();

    void on_btnSearch_clicked();

    void on_btnDelete_clicked();

    void on_btnEdit_clicked();
signals:
    // 唯一信号：跳转图书编辑界面
    void goBookEditView(int row);
private:
    Ui::BookManageView *ui;

};

#endif // BOOKMANAGEVIEW_H
