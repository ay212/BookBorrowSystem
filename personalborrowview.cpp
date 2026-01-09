#include "personalborrowview.h"
#include "ui_personalborrowview.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QHeaderView>
#include <QTableWidget>
#include <QBrush>
#include <QLabel>
#include <QColor>
#include <QDebug>

PersonalBorrowView::PersonalBorrowView(QWidget *parent, QString username)
    : QWidget(parent)
    , ui(new Ui::PersonalBorrowView)
{
    ui->setupUi(this);
    int readerId = getReaderIdByUsername(username);
    if (readerId == -1) {
        QMessageBox::warning(this, "错误", "未查询到该账号对应的读者信息！");
        emit goPreviousView();
        return;
    }

    // 1. 初始化借阅模型（原有逻辑不变）
    borrowModel = new QSqlTableModel(this, IDatabase::getInstance().getDatabase());
    borrowModel->setQuery(QString(R"(
        SELECT borrows.borrow_id, books.book_name, borrows.borrow_date, borrows.return_date
        FROM borrows
        LEFT JOIN books ON borrows.book_id = books.book_id
        WHERE borrows.reader_id = %1
    )").arg(readerId));

    if (borrowModel->lastError().isValid()) {
        QMessageBox::warning(this, "数据库错误", borrowModel->lastError().text());
        return;
    }

    // 2. 设置表格基础样式（原有逻辑不变）
    borrowModel->setHeaderData(0, Qt::Horizontal, "借阅ID");
    borrowModel->setHeaderData(1, Qt::Horizontal, "图书名称");
    borrowModel->setHeaderData(2, Qt::Horizontal, "借阅日期");
    borrowModel->setHeaderData(3, Qt::Horizontal, "归还日期");

    ui->tablePersonal->setModel(borrowModel);
    ui->tablePersonal->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePersonal->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablePersonal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePersonal->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 3. 关键：先查逾期记录，再执行高亮（顺序不能反）
    QStringList overdueBooks = checkOverdueRecords(readerId);
    highlightOverdueRows(); // 执行高亮逻辑

    // 4. 弹窗提醒（原有逻辑不变）
    if (!overdueBooks.isEmpty()) {
        QString tipMsg = QString("⚠️ 你有 %1 本图书已逾期未归还（借阅超%2天算逾期）：\n")
                             .arg(overdueBooks.size())
                             .arg(OVERDUE_THRESHOLD);
        tipMsg += overdueBooks.join("\n");
        QMessageBox::warning(this, "逾期提醒", tipMsg);
    }
}

PersonalBorrowView::~PersonalBorrowView()
{
    delete ui;
}

int PersonalBorrowView::getReaderIdByUsername(const QString &username)
{
    QSqlQuery query(IDatabase::getInstance().getDatabase());
    query.prepare(R"(
        SELECT readers.reader_id
        FROM users
        INNER JOIN readers ON users.username = readers.username
        WHERE users.username = :username
    )");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

QStringList PersonalBorrowView::checkOverdueRecords(int readerId)
{
    QStringList overdueBooks;
    QSqlQuery query(IDatabase::getInstance().getDatabase());
    // SQL查询：获取图书名、借阅时间、归还时间
    query.prepare(R"(
        SELECT books.book_name, borrows.borrow_date, borrows.return_date
        FROM borrows
        LEFT JOIN books ON borrows.book_id = books.book_id
        WHERE borrows.reader_id = :readerId
    )");
    query.bindValue(":readerId", readerId);

    if (query.exec()) {
        while (query.next()) {
            QString bookName = query.value(0).toString();
            QString borrowDateStr = query.value(1).toString();
            QString returnDateStr = query.value(2).toString(); // 获取归还时间

            // 调用工具函数，判定是否逾期
            if (isRecordOverdue(borrowDateStr, returnDateStr)) {
                overdueBooks.append(bookName);
            }
        }
    } else {
        qDebug() << "逾期记录查询失败：" << query.lastError().text();
    }
    return overdueBooks;
}

// ========== 新增：高亮逾期行方法 ==========
void PersonalBorrowView::highlightOverdueRows()
{
    QDate currentDate = QDate::currentDate();
    // 清空旧样式
    for (int row = 0; row < borrowModel->rowCount(); ++row) {
        for (int col = 0; col < borrowModel->columnCount(); ++col) {
            ui->tablePersonal->setStyleSheet("");
            QModelIndex idx = borrowModel->index(row, col);
            ui->tablePersonal->setIndexWidget(idx, nullptr);
        }
    }

    for (int row = 0; row < borrowModel->rowCount(); ++row) {
        // 获取：借阅时间（索引2）、归还时间（索引3）
        QModelIndex borrowDateIndex = borrowModel->index(row, 2);
        QModelIndex returnDateIndex = borrowModel->index(row, 3);
        QString borrowDateStr = borrowDateIndex.data().toString();
        QString returnDateStr = returnDateIndex.data().toString();

        // 第一步：判断是否已归还 → 已归还则跳过
        if (isBookReturned(returnDateStr)) {
            continue;
        }

        // 第二步：未归还，判断是否逾期
        if (isRecordOverdue(borrowDateStr, returnDateStr)) {
            // 高亮逾期行（原有逻辑不变）
            for (int col = 0; col < borrowModel->columnCount(); ++col) {
                QModelIndex cellIndex = borrowModel->index(row, col);
                QLabel *label = new QLabel(borrowModel->data(cellIndex).toString());
                label->setStyleSheet("background-color: #ffe6e6; color: red; padding: 2px;");
                label->setAlignment(Qt::AlignCenter);
                ui->tablePersonal->setIndexWidget(cellIndex, label);

                // 归还日期列显示逾期天数
                if (col == 3) {
                    QDateTime borrowDT = QDateTime::fromString(borrowDateStr, "yyyy-MM-dd HH:mm:ss");
                    int totalDays = borrowDT.daysTo(QDateTime::currentDateTime());
                    int overdueDays = totalDays - OVERDUE_THRESHOLD;
                    label->setText(QString("逾期%1天").arg(overdueDays));
                }
            }
        }
    }
    ui->tablePersonal->viewport()->update();
}
// 工具函数：判断单条记录是否逾期（当前时间-借书时间 > 逾期天数）
bool PersonalBorrowView::isRecordOverdue(const QString &borrowDateStr, const QString &returnDateStr)
{
    // 第一步：先判断是否已归还（核心！已归还直接排除）
    if (isBookReturned(returnDateStr)) {
        qDebug() << "图书已归还，不判定逾期";
        return false;
    }

    // 第二步：未归还，解析借阅时间并计算是否逾期
    QDateTime borrowDT = QDateTime::fromString(borrowDateStr, "yyyy-MM-dd HH:mm:ss");
    if (!borrowDT.isValid()) {
        borrowDT = QDateTime::fromString(borrowDateStr, "yyyy-MM-dd");
    }
    if (!borrowDT.isValid()) {
        qDebug() << "借阅日期解析失败，不判定逾期";
        return false;
    }

    // 计算借阅天数（当前时间 - 借阅时间）
    QDateTime currentDT = QDateTime::currentDateTime();
    int totalBorrowDays = borrowDT.daysTo(currentDT);
    int actualOverdueDays = totalBorrowDays - OVERDUE_THRESHOLD; // 逾期阈值（如30天）

    // 第三步：未归还且借阅天数超阈值 → 逾期
    bool isOverdue = actualOverdueDays > 0;
    qDebug() << "未归还图书，借阅天数：" << totalBorrowDays << "，逾期天数：" << actualOverdueDays << "，是否逾期：" << isOverdue;
    return isOverdue;
}

bool PersonalBorrowView::isBookReturned(const QString &returnDateStr)
{
    // 情况1：归还时间为空/NULL → 未归还
    if (returnDateStr.isEmpty() || returnDateStr == "NULL" || returnDateStr == "0000-00-00") {
        return false;
    }
    // 情况2：归还时间非空，解析验证格式 → 格式有效=已归还，无效=未归还
    QDateTime returnDT = QDateTime::fromString(returnDateStr, "yyyy-MM-dd HH:mm:ss");
    if (!returnDT.isValid()) {
        returnDT = QDateTime::fromString(returnDateStr, "yyyy-MM-dd"); // 兼容纯日期格式
    }
    return returnDT.isValid();
}
