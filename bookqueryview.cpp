#include "bookqueryview.h"
#include "ui_bookqueryview.h"

BookQueryView::BookQueryView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookQueryView)
{
    ui->setupUi(this);
}

BookQueryView::~BookQueryView()
{
    delete ui;
}
