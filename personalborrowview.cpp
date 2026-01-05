#include "personalborrowview.h"
#include "ui_personalborrowview.h"

PersonalBorrowView::PersonalBorrowView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PersonalBorrowView)
{
    ui->setupUi(this);
}

PersonalBorrowView::~PersonalBorrowView()
{
    delete ui;
}
