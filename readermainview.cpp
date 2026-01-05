#include "readermainview.h"
#include "ui_readermainview.h"

ReaderMainView::ReaderMainView(QWidget *parent, QString username)
    : QWidget(parent)
    , ui(new Ui::ReaderMainView),m_username(username)
{
    ui->setupUi(this);
}

ReaderMainView::~ReaderMainView()
{
    delete ui;
}

void ReaderMainView::on_btnBookQuery_clicked()
{
    emit goBookQueryView(); // 信号无参数，仅通知切换
}


void ReaderMainView::on_btnPersonalBorrow_clicked()
{
    emit goPersonalBorrowView(m_username); // 传递用户名，用于查询个人记录
}

