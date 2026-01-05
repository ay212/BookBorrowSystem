#include "bookeditview.h"
#include "ui_bookeditview.h"

BookEditView::BookEditView(QWidget *parent, int bookId)
    : QWidget(parent)
    , ui(new Ui::BookEditView)
    ,m_bookId(bookId),
    m_isEdit(bookId != -1) // ID!=-1=修改模式
{
    ui->setupUi(this);
}

BookEditView::~BookEditView()
{
    delete ui;
}
