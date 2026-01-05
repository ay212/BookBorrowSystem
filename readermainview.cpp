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
