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

    connect(loginView, &LoginView::goAdminMainView, this, &MasterView::goAdminMainView);
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
}

void MasterView::goReaderMainView(QString username)
{
    qDebug()<<"goReaderMainView";
    readerMainView = new ReaderMainView(this, username);
    pushWidgetToStackView(readerMainView);
}

void MasterView::goBookManageView()
{
    qDebug()<<"goBookManageView";
    bookManageView = new BookManageView(this);
    pushWidgetToStackView(bookManageView);
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

