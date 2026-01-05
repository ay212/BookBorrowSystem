#ifndef READERMANAGEVIEW_H
#define READERMANAGEVIEW_H

#include <QWidget>

namespace Ui {
class ReaderManageView;
}

class ReaderManageView : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderManageView(QWidget *parent = nullptr);
    ~ReaderManageView();

private:
    Ui::ReaderManageView *ui;
};

#endif // READERMANAGEVIEW_H
