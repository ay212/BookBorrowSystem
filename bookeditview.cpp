#include "bookeditview.h"
#include "ui_bookeditview.h"

BookEditView::BookEditView(QWidget *parent, int bookRow)
    : QWidget(parent)
    , ui(new Ui::BookEditView)
    , dataMapper(nullptr)
{
    ui->setupUi(this);
    if (bookRow < 0) {
        bookRow = IDatabase::getInstance().addNewBook();
    }

    // 1:1复刻PatientEditView的DataMapper初始化逻辑
    dataMapper = new QDataWidgetMapper(); // 无父对象
    QSqlTableModel *tabModel = IDatabase::getInstance().getBookModel();
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 字段映射
    dataMapper->addMapping(ui->leBookId, tabModel->fieldIndex("book_id"));
    dataMapper->addMapping(ui->leBookName, tabModel->fieldIndex("book_name"));
    dataMapper->addMapping(ui->leAuthor, tabModel->fieldIndex("author"));
    dataMapper->addMapping(ui->leCategory, tabModel->fieldIndex("category"));
    dataMapper->addMapping(ui->sbStock, tabModel->fieldIndex("stock"));

    dataMapper->setCurrentIndex(bookRow);
    ui->leBookId->setReadOnly(true); // 图书ID只读
}

BookEditView::~BookEditView()
{
    delete ui;
    delete dataMapper;
}

void BookEditView::on_btnConfirm_clicked()
{

    bool submitOk = IDatabase::getInstance().submitBookEdit();
    if (submitOk) {
        qDebug() << "图书修改提交成功";
        // 强制刷新模型，消除*标记
        IDatabase::getInstance().getBookModel()->select();
    } else {
        qDebug() << "提交失败：" << IDatabase::getInstance().getBookModel()->lastError().text();
    }
    emit goPreviousView();

}

void BookEditView::on_btnCancel_clicked()
{
    IDatabase::getInstance().revertBookEdit();
    emit goPreviousView(); // 触发统一回退信号

}

