#include "personalborrowview.h"
#include "ui_personalborrowview.h"

PersonalBorrowView::PersonalBorrowView(QWidget *parent, QString username)
    : QWidget(parent)
    , ui(new Ui::PersonalBorrowView),m_username(username)
{
    ui->setupUi(this);
}

PersonalBorrowView::~PersonalBorrowView()
{
    delete ui;
}
