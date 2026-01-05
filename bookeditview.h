#ifndef BOOKEDITVIEW_H
#define BOOKEDITVIEW_H

#include <QWidget>

namespace Ui {
class BookEditView;
}

class BookEditView : public QWidget
{
    Q_OBJECT

public:
    explicit BookEditView(QWidget *parent = nullptr, int bookId = -1);
    ~BookEditView();

private:
    Ui::BookEditView *ui;
    int m_bookId;                  // 图书ID（-1=新增，>0=修改）
    bool m_isEdit;                 // 模式标记：true=修改，false=新增（自动判断）
};

#endif // BOOKEDITVIEW_H
