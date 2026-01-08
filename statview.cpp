#include "statview.h"
#include "ui_statview.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QSqlTableModel>

StatView::StatView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatView)
{
    ui->setupUi(this);
    overdueModel = IDatabase::getInstance().getOverdueBorrowModel();
    ui->tableOverdue->setModel(overdueModel);
    // 强制刷新表格
    overdueModel->select();
}

StatView::~StatView()
{
    delete ui;
}

void StatView::on_btnExport_clicked()
{// 弹出保存对话框（匹配你的样式，类型为CSV）
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "导出文件",   // 对话框标题
        "",          // 不设默认地址
        "CSV文件 (*.csv);;Text files(*.txt);;All files(*)"  // 优先显示CSV
        );

    if (filePath.isEmpty()) return;

    // 导出CSV
    exportToCsv(filePath);
    QMessageBox::information(this, "成功", "逾期记录已导出为CSV文件！");
}

void StatView::exportToCsv(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "失败", "无法打开文件！");
        return;
    }

    QTextStream out(&file);
    // 写列名（逗号分隔）
    for (int col = 0; col < overdueModel->columnCount(); ++col) {
        out << "\"" << overdueModel->headerData(col, Qt::Horizontal).toString() << "\"";
        if (col < overdueModel->columnCount() - 1) out << ",";
    }
    out << "\n";

    // 写数据行（逗号分隔，内容用引号包裹避免特殊字符干扰）
    for (int row = 0; row < overdueModel->rowCount(); ++row) {
        for (int col = 0; col < overdueModel->columnCount(); ++col) {
            out << "\"" << overdueModel->index(row, col).data().toString() << "\"";
            if (col < overdueModel->columnCount() - 1) out << ",";
        }
        out << "\n";
    }

    file.close();
}

