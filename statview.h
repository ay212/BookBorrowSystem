#ifndef STATVIEW_H
#define STATVIEW_H

#include <QWidget>

namespace Ui {
class StatView;
}

class StatView : public QWidget
{
    Q_OBJECT

public:
    explicit StatView(QWidget *parent = nullptr);
    ~StatView();

private:
    Ui::StatView *ui;
};

#endif // STATVIEW_H
