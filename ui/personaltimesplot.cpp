#include "personaltimesplot.h"
#include "ui_personaltimesplot.h"

PersonalTimesPlot::PersonalTimesPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalTimesPlot)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    QFont font;
    font.setBold(true);
    ui->plot->xAxis->setLabelFont(font);
    ui->plot->yAxis->setLabelFont(font);

    ui->plot->xAxis->setLabel("Date");
    ui->plot->yAxis->setLabel("Lap time");
}

PersonalTimesPlot::~PersonalTimesPlot()
{
    delete ui;
}

void PersonalTimesPlot::plotTimes(const QMap<QDateTime, QTime> &times)
{
    ui->plot->clearGraphs();
    QSharedPointer<QCPAxisTickerText> xTicker(new QCPAxisTickerText);
    QSharedPointer<QCPAxisTickerText> yTicker(new QCPAxisTickerText);

    ui->plot->xAxis->setTicker(xTicker);
    ui->plot->yAxis->setTicker(yTicker);

    auto graph = ui->plot->addGraph();
    graph->setScatterStyle(QCPScatterStyle::ssCircle);

    QList<QTime> timeValues = times.values();
    QList<QDateTime> dates = times.keys();

    QVector<double> x(timeValues.length());
    QVector<double> y(timeValues.length());

    for (int i = 0; i < timeValues.length(); ++i)
    {
        x[i] = i;//dates[i].toMSecsSinceEpoch();
        y[i] = QTime(0, 0, 0).secsTo(timeValues[i]);

        xTicker->addTick(x[i], dates[i].toString("yyyy-MM-dd\nhh:mm:ss"));
        yTicker->addTick(y[i], timeValues[i].toString("mm:ss.zzz"));
    }

    graph->setData(x, y);
    graph->rescaleAxes();
    ui->plot->xAxis->scaleRange(1.1, ui->plot->xAxis->range().center());
    ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
    ui->plot->replot();

    this->show();
}
