#include "borrowreturnview.h"
#include "ui_borrowreturnview.h"

BorrowReturnView::BorrowReturnView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowReturnView)
{
    ui->setupUi(this);
}

BorrowReturnView::~BorrowReturnView()
{
    delete ui;
}
