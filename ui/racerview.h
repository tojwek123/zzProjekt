#ifndef RACERVIEW_H
#define RACERVIEW_H

#include <QWidget>

namespace Ui {
class RacerView;
}

class RacerView : public QWidget
{
    Q_OBJECT

public:
    explicit RacerView(QWidget *parent = 0);
    ~RacerView();

private:
    Ui::RacerView *ui;
};

#endif // RACERVIEW_H
