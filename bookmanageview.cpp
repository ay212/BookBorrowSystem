#include "bookmanageview.h"
#include "ui_bookmanageview.h"

BookManageView::BookManageView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookManageView)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true); // 对齐PatientView的隔行变色


    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initBookModel()){
        ui->tableView->setModel(iDatabase.getBookModel());
        ui->tableView->setSelectionModel(iDatabase.getBookSelectionModel());
    }
}

BookManageView::~BookManageView()
{
    delete ui;
}



void BookManageView::on_btnAdd_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    int newRow = iDatabase.addNewBook();
    emit goBookEditView(newRow);
}

void BookManageView::on_btnSearch_clicked()
{
    QString filter = QString("book_name like '%%1%' OR author like '%%1%' OR category like '%%1%'").arg(ui->leSearch->text().trimmed());
    IDatabase::getInstance().searchBook(filter);
}

void BookManageView::on_btnDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentBook();
}

void BookManageView::on_btnEdit_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    QModelIndex curIndex = iDatabase.getBookSelectionModel()->currentIndex();
    emit goBookEditView(curIndex.row());
}


