#include "adminmainview.h"
#include "ui_adminmainview.h"

AdminMainView::AdminMainView(QWidget *parent, QString username)
    : QWidget(parent)
    , ui(new Ui::AdminMainView),m_username(username)
{
    ui->setupUi(this);
}

AdminMainView::~AdminMainView()
{
    delete ui;
}

void AdminMainView::on_btnBookManage_clicked()
{

}


void AdminMainView::on_btnReaderManage_clicked()
{

}


void AdminMainView::on_btnBorrowReturn_clicked()
{

}


void AdminMainView::on_btnStat_clicked()
{

}

