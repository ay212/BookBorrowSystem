#include "readermainview.h"
#include "ui_readermainview.h"

ReaderMainView::ReaderMainView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderMainView)
{
    ui->setupUi(this);
}

ReaderMainView::~ReaderMainView()
{
    delete ui;
}
