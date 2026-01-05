#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "registerview.h"
#include "adminmainview.h"
#include "readermainview.h"
#include "bookmanageview.h"
#include "readermanageview.h"
#include "borrowreturnview.h"
#include "statview.h"
#include "bookqueryview.h"
#include "personalborrowview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();
public slots:
    // 视图切换槽函数（接收子视图信号）
    void goLoginView();
    void goRegisterView();
    void goAdminMainView(QString username);
    void goReaderMainView(QString username);
    void goBookManageView();
    void goReaderManageView();
    void goBorrowReturnView();
    void goStatView();
    void goBookQueryView();
    void goPersonalBorrowView(QString username);
    void goPreviousView();

private slots:
    void on_btBack_clicked();

private:
    void pushWidgetToStackView(QWidget *widget);
    Ui::MasterView *ui;

    LoginView *loginView;
    RegisterView *registerView;
    AdminMainView *adminMainView;
    ReaderMainView *readerMainView;
    BookManageView *bookManageView;
    ReaderManageView *readerManageView;
    BorrowReturnView *borrowReturnView;
    StatView *statView;
    BookQueryView *bookQueryView;
    PersonalBorrowView *personalBorrowView;

};
#endif // MASTERVIEW_H
