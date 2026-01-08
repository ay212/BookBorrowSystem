#ifndef STATVIEW_H
#define STATVIEW_H

#include <QWidget>
#include "idatabase.h"

namespace Ui {
class StatView;
}

class StatView : public QWidget
{
    Q_OBJECT

public:
    explicit StatView(QWidget *parent = nullptr);
    ~StatView();
signals:
    void goPreviousView(); // 统一返回信号

private slots:
    void on_btnExport_clicked();

private:
    Ui::StatView *ui;
    QSqlTableModel* overdueModel; // 逾期记录模型
    // 导出为CSV文件（通用格式）
    void exportToCsv(const QString& filePath);
};

#endif // STATVIEW_H
