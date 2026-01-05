#include "adminmainview.h"
#include "ui_adminmainview.h"

AdminMainView::AdminMainView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminMainView)
{
    ui->setupUi(this);
}

AdminMainView::~AdminMainView()
{
    delete ui;
}
