#ifndef ADMINMAINVIEW_H
#define ADMINMAINVIEW_H

#include <QWidget>

namespace Ui {
class AdminMainView;
}

class AdminMainView : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMainView(QWidget *parent = nullptr);
    ~AdminMainView();

private:
    Ui::AdminMainView *ui;
};

#endif // ADMINMAINVIEW_H
