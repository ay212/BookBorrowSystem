#include "statview.h"
#include "ui_statview.h"

StatView::StatView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatView)
{
    ui->setupUi(this);
}

StatView::~StatView()
{
    delete ui;
}
