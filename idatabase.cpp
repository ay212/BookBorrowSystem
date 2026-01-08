#include "idatabase.h"
#include <QUuid>
#include <QDebug>
#include <QDir>

QString IDatabase::userLogin(QString username, QString password, QString &role)
{
    // 强制初始化user模型（确保查询前模型就绪）
    if (!userTabModel || !theUserSelection) {
        if (!initUserModel()) {
            role = "";
            return "dbError";
        }
    }

    QSqlQuery query(database);
    // 关键：精准查询users表的username/password/role字段
    query.prepare("SELECT username, password, role FROM users WHERE username = :USER");
    query.bindValue(":USER", username);

    // 执行查询并校验结果
    if (!query.exec()) {
        qCritical() << "登录查询失败：" << query.lastError().text();
        role = "";
        return "dbError";
    }

    if (query.first() && query.value("username").isValid()) {
        QString dbPwd = query.value("password").toString().trimmed();
        QString dbRole = query.value("role").toString().trimmed(); // 去空格，避免格式问题

        // 密码校验
        if (dbPwd != password.trimmed()) {
            role = "";
            return "wrongPassword";
        }

        // 角色规范化（确保仅返回admin/reader，适配业务逻辑）
        if (dbRole == "admin" || dbRole == "Admin" || dbRole == "ADMIN") {
            role = "admin"; // 统一为小写
        } else if (dbRole == "reader" || dbRole == "Reader" || dbRole == "READER") {
            role = "reader"; // 统一为小写
        } else {
            role = "reader"; // 默认角色（防止数据库中角色值异常）
        }

        qInfo() << "登录成功：用户名=" << username << "，角色=" << role;
        return "LoginOK";
    } else {
        qInfo() << "登录失败：用户名不存在=" << username;
        role = "";
        return "wrongUsername";
    }
}

bool IDatabase::initUserModel()
{
    userTabModel = new QSqlTableModel(this, database);
    userTabModel->setTable("users"); // 绑定图片中的users表
    userTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    userTabModel->setSort(userTabModel->fieldIndex("username"), Qt::AscendingOrder); // 按用户名排序
    if (!(userTabModel->select())) {
        qCritical() << "users表模型初始化失败：" << userTabModel->lastError().text();
        return false;
    }

    theUserSelection = new QItemSelectionModel(userTabModel);
    return true;
}

bool IDatabase::initReaderModel()
{
    readerTabModel = new QSqlTableModel(this, database);
    readerTabModel->setTable("readers"); // 换表名books→readers
    readerTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    readerTabModel->setSort(readerTabModel->fieldIndex("reader_name"), Qt::AscendingOrder); // 换排序字段book_name→reader_name
    if (!(readerTabModel->select())) {
        qCritical() << "readers表模型初始化失败：" << readerTabModel->lastError().text();
        return false;
    }
    readerSelectionModel = new QItemSelectionModel(readerTabModel);
    return true;
}

int IDatabase::addNewReader()
{
    readerTabModel->insertRow(readerTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = readerTabModel->index(readerTabModel->rowCount()-1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = readerTabModel->record(curRecNo);
    // 换字段名book_id→reader_id，其他字段对应替换
    curRec.setValue("reader_id", QUuid::createUuid().toString(QUuid::WithoutBraces));
    curRec.setValue("reader_name", ""); // 换book_name→reader_name
    curRec.setValue("gender", ""); // 新增读者字段
    curRec.setValue("phone", ""); // 新增读者字段
    curRec.setValue("username", ""); // 新增读者字段

    readerTabModel->setRecord(curRecNo, curRec);
    return curIndex.row();
}

// 复刻searchBook → searchReader（只换表名相关）
bool IDatabase::searchReader(QString filter)
{
    readerTabModel->setFilter(filter);
    return readerTabModel->select();
}

void IDatabase::deleteCurrentReader()
{
    QModelIndex curIndex = readerSelectionModel->currentIndex();
    readerTabModel->removeRow(curIndex.row());
    readerTabModel->submitAll();
    readerTabModel->select();
}

bool IDatabase::submitReaderEdit()
{
    bool result = readerTabModel->submitAll();
    if (result) readerTabModel->select();
    return result;
}

void IDatabase::revertReaderEdit()
{
    if (readerTabModel) readerTabModel->revertAll();
}

bool IDatabase::initBookModel()
{
    bookTabModel = new QSqlTableModel(this, database);
    bookTabModel->setTable("books");
    bookTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 新增：按book_name排序
    bookTabModel->setSort(bookTabModel->fieldIndex("book_name"), Qt::AscendingOrder);
    // 新增：校验select结果
    if (!(bookTabModel->select())) {
        qCritical() << "books表模型初始化失败：" << bookTabModel->lastError().text();
        return false;
    }
    bookSelectionModel = new QItemSelectionModel(bookTabModel);
    return true;

}

int IDatabase::addNewBook()
{
    // 第一步：查询当前books表中最大的book_id
    QSqlQuery query;
    query.exec("SELECT MAX(book_id) FROM books");
    int maxId = 0;
    if (query.next()) {
        maxId = query.value(0).toInt(); // 获取最大ID
    }
    int newBookId = maxId + 1; // 新ID = 最大ID + 1（保证连续）

    // 第二步：插入新行并赋值
    bookTabModel->insertRow(bookTabModel->rowCount(), QModelIndex());
    QModelIndex curIndex = bookTabModel->index(bookTabModel->rowCount()-1, 1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = bookTabModel->record(curRecNo);

    // 项目1步骤4：设置字段值
    curRec.setValue("book_id", newBookId);
    curRec.setValue("book_name", ""); // 空值兜底
    curRec.setValue("author", "");
    curRec.setValue("category", "");
    curRec.setValue("stock", 0);


    // 项目1步骤5：设置记录（完全复刻）
    bookTabModel->setRecord(curRecNo, curRec);

    // 项目1步骤6：返回行号（完全复刻）
    return curIndex.row();
}

bool IDatabase::searchBook(QString filter)
{
    bookTabModel->setFilter(filter);
    return bookTabModel->select();
}

void IDatabase::deleteCurrentBook()
{
    QModelIndex curIndex = bookSelectionModel->currentIndex();
    bookTabModel->removeRow(curIndex.row());
    bookTabModel->submitAll();
    bookTabModel->select();
}

bool IDatabase::submitBookEdit()
{
    bool result = bookTabModel->submitAll();
    if (result) bookTabModel->select();
    return result;
}

void IDatabase::revertBookEdit()
{
    if (bookTabModel) bookTabModel->revertAll();
}



IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    // 初始化所有业务模型
    initDatabase();
    initReaderModel();
    initBookModel();
    // initBorrowModel();
}

void IDatabase::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "D:/qtcode/BookBorrowSystem.db";
    database.setDatabaseName(aFile);

    if (!database.open()) {
        qDebug() << "failed to open database";
    } else {
        qDebug() << "open database is ok" << database.connectionName();
    }
}
