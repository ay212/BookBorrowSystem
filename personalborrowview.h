#ifndef PERSONALBORROWVIEW_H
#define PERSONALBORROWVIEW_H

#include <QWidget>
#include <QSqlTableModel>
#include "idatabase.h"
#include <QDate>

namespace Ui {
class PersonalBorrowView;
}

class PersonalBorrowView : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalBorrowView(QWidget *parent = nullptr, const QString username = "");
    ~PersonalBorrowView();
signals:
    void goPreviousView();
private:
    Ui::PersonalBorrowView *ui;
    QSqlTableModel* borrowModel;
    // 新增：定义逾期阈值（借阅30天未还即逾期，可根据需求修改）
    static const int OVERDUE_THRESHOLD = 1;
    // 内部方法：通过username查reader_id
    int getReaderIdByUsername(const QString &username);
    // 新增：检查逾期记录并返回逾期图书名称列表
    QStringList checkOverdueRecords(int readerId);
    // 新增：高亮表格中的逾期行
    void highlightOverdueRows();
    bool isRecordOverdue(const QString &borrowDateStr, const QString &returnDateStr);
    bool isBookReturned(const QString &returnDateStr);
};

#endif // PERSONALBORROWVIEW_H
