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

private slots:
    void on_btnAdd_clicked();

    void on_btnSearch_clicked();

    void on_btnDelete_clicked();

    void on_btnEdit_clicked();
signals:
    // 唯一信号：跳转图书编辑界面（bookId=-1=新增，bookId>0=修改）
    void goBookEditView(int bookId);
private:
    Ui::BookManageView *ui;
};

#endif // BOOKMANAGEVIEW_H
