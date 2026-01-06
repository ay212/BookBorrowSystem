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
    // 关键：精准查询users表的username/password/role字段（适配图片表结构）
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
    readerTabModel->setTable("readers"); // 绑定readers表
    readerTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit); // 手动提交
    readerTabModel->setSort(readerTabModel->fieldIndex("readerName"), Qt::AscendingOrder); // 按姓名排序
    if (!(readerTabModel->select())) return false;

    readerSelectionModel = new QItemSelectionModel(readerTabModel);
    return true;
}



IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    // 初始化所有业务模型
    initDatabase();
    initReaderModel();
    // initBookModel();
    // initBorrowModel();
}

void IDatabase::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    // 替换为你的BookBorrowSystem数据库路径（绝对/相对路径均可）
    QString aFile = "D:/qtcode/BookBorrowSystem.db";
    database.setDatabaseName(aFile);

    if (!database.open()) {
        qDebug() << "failed to open database";
    } else {
        qDebug() << "open database is ok" << database.connectionName();
    }
}
