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
    // 注册成功后返回登录
    connect(registerView, &RegisterView::registerSuccess, this, &MasterView::goLoginView);
    // 返回登录
    connect(registerView, &RegisterView::backToLogin, this, &MasterView::goLoginView);
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

    bookManageView = new BookManageView(this);
    pushWidgetToStackView(bookManageView); // 替换直接addWidget

    // 绑定编辑跳转信号
    connect(bookManageView, &BookManageView::goBookEditView, this, &MasterView::goBookEditView);
}

void MasterView::goBookEditView(int row)
{
    bookEditView = new BookEditView(this, row);
    pushWidgetToStackView(bookEditView); // 复用项目一的统一栈管理函数

    // 绑定统一回退信号
    connect(bookEditView, &BookEditView::goPreviousView, this, &MasterView::goPreviousView);
}

void MasterView::goReaderManageView()
{
    qDebug()<<"goReaderManageView";
    readerManageView = new ReaderManageView(this);
    pushWidgetToStackView(readerManageView); // 和你的图书模块一致，用统一栈管理
    // 绑定编辑跳转信号（抄你的图书模块绑定逻辑）
    connect(readerManageView, &ReaderManageView::goReaderEditView, this, &MasterView::goReaderEditView);
}

void MasterView::goReaderEditView(int row)
{
    qDebug()<<"goReaderEditView";
    readerEditView = new ReaderEditView(this, row);
    pushWidgetToStackView(readerEditView); // 和你的图书模块一致，用统一栈管理
    // 绑定返回信号（抄你的图书模块，绑定 goPreviousView）
    connect(readerEditView, &ReaderEditView::goPreviousView, this, &MasterView::goPreviousView);
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
    connect(bookQueryView, &BookQueryView::goPreviousView, this, &MasterView::goPreviousView);
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
    if (!widget) return;
    // 先检查是否已存在，避免重复添加
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == widget) {
            ui->stackedWidget->setCurrentWidget(widget);
            ui->labelTitle->setText(widget->windowTitle());
            return;
        }
    }
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    ui->labelTitle->setText(widget->windowTitle());
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if (count>1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);

    QString title =ui->stackedWidget->currentWidget()->windowTitle();

    if(title=="管理员主界面"||title=="读者主界面"){

        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    }else if(title=="登录"){
        ui->btLogout->setEnabled(false);
        ui->btBack->setEnabled(false);
    }else
        ui->btLogout->setEnabled(false);
}

void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

