#include "readereditview.h"
#include "ui_readereditview.h"
#include <QSqlTableModel>
#include "idatabase.h"

ReaderEditView::ReaderEditView(QWidget *parent, int readerRow)
    : QWidget(parent)
    , ui(new Ui::ReaderEditView)
{
    ui->setupUi(this);
    if (readerRow < 0) {
        readerRow = IDatabase::getInstance().addNewReader();
    }

    // 初始化DataMapper（完全匹配你的UI控件名）
    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = IDatabase::getInstance().getReaderModel();
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // 和你的BookEditView一致

    // 字段映射：严格匹配你的UI控件名+readers表字段
    dataMapper->addMapping(ui->leReaderId, tabModel->fieldIndex("reader_id"));       // 读者ID：leReaderId
    dataMapper->addMapping(ui->leReaderName, tabModel->fieldIndex("reader_name"));   // 姓名：leReaderName
    dataMapper->addMapping(ui->cbGender, tabModel->fieldIndex("gender"));            // 性别：cbGender（QComboBox）
    dataMapper->addMapping(ui->lePhone, tabModel->fieldIndex("phone"));              // 联系方式：lePhone
    dataMapper->addMapping(ui->leUsername, tabModel->fieldIndex("username"));        // 关联账号：leUsername

    dataMapper->setCurrentIndex(readerRow);
    ui->leReaderId->setReadOnly(true); // 读者ID只读（和你的BookId逻辑一致）
}

ReaderEditView::~ReaderEditView()
{
    delete ui;
    delete dataMapper;
}

void ReaderEditView::on_btnConfirm_clicked()
{
    bool submitOk = IDatabase::getInstance().submitReaderEdit(); // 换 submitBookEdit→submitReaderEdit
    if (submitOk) {
        qDebug() << "读者修改提交成功";
        IDatabase::getInstance().getReaderModel()->select(); // 换 getBookModel→getReaderModel
    } else {
        qDebug() << "提交失败：" << IDatabase::getInstance().getReaderModel()->lastError().text();
    }
    emit goPreviousView(); // 和你的 BookEditView 一致，发射返回信号
}



void ReaderEditView::on_btnCancel_clicked()
{
    IDatabase::getInstance().revertReaderEdit(); // 换 revertBookEdit→revertReaderEdit
    emit goPreviousView();
}

