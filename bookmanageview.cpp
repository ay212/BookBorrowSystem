#include "bookmanageview.h"
#include "ui_bookmanageview.h"

BookManageView::BookManageView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookManageView)
{
    ui->setupUi(this);
}

BookManageView::~BookManageView()
{
    delete ui;
}

void BookManageView::on_btnAdd_clicked()
{
    emit goBookEditView(-1);
}


void BookManageView::on_btnSearch_clicked()
{

}


void BookManageView::on_btnDelete_clicked()
{

}


void BookManageView::on_btnEdit_clicked()
{

}

