#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    goLoginView();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug()<<"goLoginView";
    loginView =new LoginView(this);
    pushWidgetToStackView(loginView);

    // 绑定登录页信号
    connect(loginView, &LoginView::goRegisterView, this, &MasterView::goRegisterView);
    connect(loginView, &LoginView::goAdminMainView, this, &MasterView::goAdminMainView);
    connect(loginView, &LoginView::goReaderMainView, this, &MasterView::goReaderMainView);
    connect(loginView, &LoginView::loginFailed, this, [=](QString reason) {
        qWarning() << "Login failed:" << reason;
    });
}

void MasterView::goRegisterView()
{
    qDebug()<<"goRegisterView";
    registerView = new RegisterView(this);
    pushWidgetToStackView(registerView);
}

void MasterView::goAdminMainView(QString username)
{
    qDebug()<<"goAdminMainView";
    adminMainView = new AdminMainView(this, username);
    pushWidgetToStackView(adminMainView);

    // 绑定管理员主界面信号
    connect(adminMainView, &AdminMainView::goBookManageView, this, &MasterView::goBookManageView);
    connect(adminMainView, &AdminMainView::goReaderManageView, this, &MasterView::goReaderManageView);
    connect(adminMainView, &AdminMainView::goBorrowReturnView, this, &MasterView::goBorrowReturnView);
    connect(adminMainView, &AdminMainView::goStatView, this, &MasterView::goStatView);
}

void MasterView::goReaderMainView(QString username)
{
    qDebug()<<"goReaderMainView";
    readerMainView = new ReaderMainView(this, username);
    pushWidgetToStackView(readerMainView);

    // 绑定读者主界面信号
    connect(readerMainView, &ReaderMainView::goBookQueryView, this, &MasterView::goBookQueryView);
    connect(readerMainView, &ReaderMainView::goPersonalBorrowView, this, &MasterView::goPersonalBorrowView);
}

void MasterView::goBookManageView()
{
    qDebug()<<"goBookManageView";
    bookManageView = new BookManageView(this);
    pushWidgetToStackView(bookManageView);

    // 绑定唯一信号：处理图书新增/修改跳转
    connect(bookManageView, &BookManageView::goBookEditView, this, [=](int bookId) {
        // 创建编辑界面并入栈
        BookEditView *editView = new BookEditView(this, bookId);
        pushWidgetToStackView(editView);

        // 绑定编辑完成信号：回退并刷新表格
        /*connect(editView, &BookEditView::editFinished, this, [=](bool success) {
            goPreviousView(); // 编辑窗口出栈销毁
            bookManageView->onEditFinished(success); // 通知图书管理界面刷新
        });*/
    });
}

void MasterView::goReaderManageView()
{
    qDebug()<<"goReaderManageView";
    readerManageView = new ReaderManageView(this);
    pushWidgetToStackView(readerManageView);
}

void MasterView::goBorrowReturnView()
{
    qDebug()<<"goBorrowReturnView";
    borrowReturnView = new BorrowReturnView(this);
    pushWidgetToStackView(borrowReturnView);
}

void MasterView::goStatView()
{
    qDebug()<<"goStatView";
    statView = new StatView(this);
    pushWidgetToStackView(statView);
}

void MasterView::goBookQueryView()
{
    qDebug()<<"goBookQueryView";
    bookQueryView = new BookQueryView(this);
    pushWidgetToStackView(bookQueryView);
}

void MasterView::goPersonalBorrowView(QString username)
{
    qDebug()<<"goPersonalBorrowView";
    personalBorrowView = new PersonalBorrowView(this,username);
    pushWidgetToStackView(personalBorrowView);
}

void MasterView::goPreviousView()
{
    int count =ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count =ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);//总是显示最新加入的View
    ui->labelTitle->setText(widget->windowTitle());
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();
}

