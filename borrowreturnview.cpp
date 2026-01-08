#include "borrowreturnview.h"
#include "ui_borrowreturnview.h"
#include <QMessageBox>
#include <QSqlQuery>

BorrowReturnView::BorrowReturnView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BorrowReturnView)
{
    ui->setupUi(this);
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initBorrowModel()) {
        ui->tableView->setModel(iDatabase.getBorrowModel());
        ui->tableView->setSelectionModel(iDatabase.getBorrowSelectionModel());
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

BorrowReturnView::~BorrowReturnView()
{
    delete ui;
}

void BorrowReturnView::on_btnBorrow_clicked()
{
    int readerId = ui->leReaderId->text().trimmed().toInt();
    int bookId = ui->leBookId->text().trimmed().toInt();
    if (readerId <= 0 || bookId <= 0) {
        QMessageBox::warning(this, "提示", "读者ID/图书ID不能为空且需为正整数！");
        return;
    }

    // 2. 检查读者是否存在（复用注册模块的查询逻辑）
    QSqlQuery checkReaderQuery;
    checkReaderQuery.exec(QString("SELECT * FROM readers WHERE reader_id = %1").arg(readerId));
    if (!checkReaderQuery.next()) {
        QMessageBox::warning(this, "失败", "读者ID不存在！");
        return;
    }

    // 3. 检查图书库存（复用借书模块的库存逻辑）
    QSqlQuery checkStockQuery;
    checkStockQuery.exec(QString("SELECT stock FROM books WHERE book_id = %1").arg(bookId));
    if (!checkStockQuery.next() || checkStockQuery.value(0).toInt() <= 0) {
        QMessageBox::warning(this, "失败", "图书库存不足或图书ID不存在！");
        return;
    }

    // 4. 调用数据库层的借书接口（完全复用前面写的borrowBook逻辑）
    bool borrowOk = IDatabase::getInstance().borrowBook(readerId, bookId);
    if (borrowOk) {
        QMessageBox::information(this, "成功", "借书成功！");
        // 清空输入框+刷新表格（复用前面模块的刷新逻辑）
        ui->leReaderId->clear();
        ui->leBookId->clear();
        IDatabase::getInstance().getBorrowModel()->select();
    } else {
        QMessageBox::warning(this, "失败", "借书失败！");
    }
}


void BorrowReturnView::on_btnReturn_clicked()
{
    // 1. 获取选中的借阅记录ID（复用表格选择逻辑）
    QModelIndex curIndex = IDatabase::getInstance().getBorrowSelectionModel()->currentIndex();
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, "提示", "请选择要还的借阅记录！");
        return;
    }
    int borrowId = curIndex.siblingAtColumn(0).data().toInt(); // borrow_id是第0列

    // 2. 调用数据库层的还书接口（完全复用前面写的returnBook逻辑）
    bool returnOk = IDatabase::getInstance().returnBook(borrowId);
    if (returnOk) {
        QMessageBox::information(this, "成功", "还书成功！");
        // 刷新表格（复用前面模块的刷新逻辑）
        IDatabase::getInstance().getBorrowModel()->select();
    } else {
        QMessageBox::warning(this, "失败", "该记录已归还或不存在！");
    }
}


void BorrowReturnView::on_btnSearch_clicked()
{
    // 1. 获取两个输入框的内容（复用前面搜索拼接逻辑）
    QString readerId = ui->leReaderId->text().trimmed();
    QString bookId = ui->leBookId->text().trimmed();
    QString filter;

    // 2. 拼接搜索条件（同时匹配读者ID和图书ID）
    if (!readerId.isEmpty() && !bookId.isEmpty()) {
        filter = QString("reader_id = %1 AND book_id = %2").arg(readerId).arg(bookId);
    } else if (!readerId.isEmpty()) {
        filter = QString("reader_id = %1").arg(readerId);
    } else if (!bookId.isEmpty()) {
        filter = QString("book_id = %1").arg(bookId);
    }

    // 3. 调用搜索接口（复用前面searchBorrow逻辑）
    IDatabase::getInstance().searchBorrow(filter);
}

