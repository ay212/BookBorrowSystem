#include "readermanageview.h"
#include "ui_readermanageview.h"

ReaderManageView::ReaderManageView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderManageView)
{
    ui->setupUi(this);
}

ReaderManageView::~ReaderManageView()
{
    delete ui;
}
