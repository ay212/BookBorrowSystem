#include "readermanageview.h"
#include "ui_readermanageview.h"
#include "idatabase.h"

ReaderManageView::ReaderManageView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderManageView)
{
    ui->setupUi(this);


    // 完全抄你的 BookManageView 构造函数，只换图书模型→读者模型
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase = IDatabase::getInstance();
    if(iDatabase.initReaderModel()){ // 换 initBookModel→initReaderModel
        ui->tableView->setModel(iDatabase.getReaderModel()); // 换 getBookModel→getReaderModel
        ui->tableView->setSelectionModel(iDatabase.getReaderSelectionModel()); // 换 getBookSelectionModel→getReaderSelectionModel
    }
}

ReaderManageView::~ReaderManageView()
{
    delete ui;
}

void ReaderManageView::on_btnSearch_clicked()
{
    QString filter = QString("reader_name like '%%1%' OR gender like '%%1%' OR phone like '%%1%' OR username like '%%1%'").arg(ui->leSearch->text().trimmed());
    IDatabase::getInstance().searchReader(filter);
}


void ReaderManageView::on_btnAdd_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    int newRow = iDatabase.addNewReader(); // 换 addNewBook→addNewReader
    emit goReaderEditView(newRow); // 换 goBookEditView→goReaderEditView
}


void ReaderManageView::on_btnDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentReader();
}


void ReaderManageView::on_btnEdit_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();
    QModelIndex curIndex = iDatabase.getReaderSelectionModel()->currentIndex(); // 换 getBookSelectionModel→getReaderSelectionModel
    emit goReaderEditView(curIndex.row()); // 换 goBookEditView→goReaderEditView
}

