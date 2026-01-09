#include "bookqueryview.h"
#include "ui_bookqueryview.h"
#include <QMessageBox>

BookQueryView::BookQueryView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookQueryView)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true); // 隔行变色（和BookManageView一致）

    // 复用数据库层的BookModel（和BookManageView完全一致）
    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initBookModel()){
        ui->tableView->setModel(iDatabase.getBookModel());
        ui->tableView->setSelectionModel(iDatabase.getBookSelectionModel());
    }
}

BookQueryView::~BookQueryView()
{
    delete ui;
}

void BookQueryView::on_btnSearch_clicked()
{
    QString keyword = ui->leSearch->text().trimmed();
    QString filter;
    // 按“书名/作者”模糊搜索（复用图书查询的筛选逻辑）
    if (!keyword.isEmpty()) {
        filter = QString("book_name LIKE '%%1%' OR author LIKE '%%1%'").arg(keyword);
    }
    // 调用数据库层的searchBook接口（复用已有逻辑）
    IDatabase::getInstance().searchBook(filter);
}

