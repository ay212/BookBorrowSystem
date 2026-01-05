#ifndef READERMAINVIEW_H
#define READERMAINVIEW_H

#include <QWidget>

namespace Ui {
class ReaderMainView;
}

class ReaderMainView : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderMainView(QWidget *parent = nullptr);
    ~ReaderMainView();

private:
    Ui::ReaderMainView *ui;
};

#endif // READERMAINVIEW_H
