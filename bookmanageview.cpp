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
