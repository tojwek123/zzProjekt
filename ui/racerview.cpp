#include "racerview.h"
#include "ui_racerview.h"

RacerView::RacerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RacerView)
{
    ui->setupUi(this);
}

RacerView::~RacerView()
{
    delete ui;
}
