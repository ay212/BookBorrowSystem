#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QUuid>
#include <QDebug>
#include <QDateTime>

class IDatabase : public QObject
{
    Q_OBJECT
public:
    static IDatabase& getInstance()
    {
        static IDatabase instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }


    // ===================== 登录相关=====================
    QString userLogin(QString userName, QString password, QString& role);
    bool userRegister(QString username, QString password, QString role);
    bool initUserModel();

    // ===================== 读者管理=====================
    bool initReaderModel();          // 初始化读者模型
    int addNewReader();              // 新增读者
    bool searchReader(QString filter); // 搜索读者
    void deleteCurrentReader();      // 删除当前读者
    bool submitReaderEdit();         // 提交读者修改
    void revertReaderEdit();         // 回滚读者修改
    QSqlTableModel* getReaderModel() { return readerTabModel; }
    QItemSelectionModel* getReaderSelectionModel() { return readerSelectionModel; }

    // ===================== 图书管理=====================
    bool initBookModel();            // 初始化图书模型
    int addNewBook();                // 新增图书
    bool searchBook(QString filter); // 搜索图书
    void deleteCurrentBook();        // 删除当前图书
    bool submitBookEdit();           // 提交图书修改
    void revertBookEdit();           // 回滚图书修改
    QSqlTableModel* getBookModel() { return bookTabModel; }
    QItemSelectionModel* getBookSelectionModel() { return bookSelectionModel; }

    // ===================== 借阅记录管理=====================
    bool initBorrowModel();              // 初始化借阅模型
    int addNewBorrow();                  // 新增借阅记录
    bool searchBorrow(QString filter);   // 搜索借阅记录
    void deleteCurrentBorrow();          // 删除当前借阅记录
    bool submitBorrowEdit();             // 提交借阅修改
    void revertBorrowEdit();             // 回滚借阅修改
    QSqlTableModel* getBorrowModel() { return borrowTabModel; }
    QItemSelectionModel* getBorrowSelectionModel() { return borrowSelectionModel; }

private:
        explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const&)               = delete;
    void operator=(IDatabase const&)  = delete;

    QSqlDatabase database;
    void initDatabase();
    // 读者相关模型
    QSqlTableModel *readerTabModel;
    QItemSelectionModel *readerSelectionModel;
    // 图书相关模型
    QSqlTableModel *bookTabModel;
    QItemSelectionModel *bookSelectionModel;
    // 借阅相关模型
    QSqlTableModel *borrowTabModel;
    QItemSelectionModel *borrowSelectionModel;
    QSqlTableModel *userTabModel;       // 新增：users表模型
    QItemSelectionModel *theUserSelection; // 新增：users表选择模型

signals:
};

#endif // IDATABASE_H
