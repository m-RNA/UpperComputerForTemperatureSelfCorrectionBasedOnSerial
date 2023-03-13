#include "collectpanel.h"
#include "ui_collectpanel.h"

CollectPanel::CollectPanel(QWidget *parent) : QWidget(parent),
                                              ui(new Ui::CollectPanel)
{
    ui->setupUi(this);
    ui->chart->setXAxisToTimelineState(true);
}

CollectPanel::~CollectPanel()
{
    delete ui;
}

void CollectPanel::slSetState(int state)
{
    switch (state)
    {
    case 0:
        ui->ledText->setText("离线    ");
        ui->led->setStyleSheet("border-radius:7px;background-color: red;");
        break;

    case 1:
        ui->ledText->setText("在线    ");
        ui->led->setStyleSheet("border-radius:7px;background-color: rgb(46, 204, 113);"); // 绿色
        break;

    case 2:
        ui->ledText->setText("采集中  ");
        ui->led->setStyleSheet("border-radius:7px;background-color: rgb(23, 111, 217);"); // 蓝色
        break;

    case 3:
        ui->ledText->setText("数据波动");
        ui->led->setStyleSheet("border-radius:7px;background-color: rgb(197, 186, 10);"); // 黄色
        break;
    }
}

void CollectPanel::setDeviceName(QString name)
{
    deviceName = name;
    ui->chart->graph()->setName(name);
}

// 防止溢出平均值 double在数值较小时，精度较高
double CollectPanel::average(void)
{
    double ans = 0;
    unsigned long long size = data.size();

    for (unsigned long long i = 0; i < size; ++i)
    {
        ans = (double)i / (double)(i + 1) * ans + data.at(i) / (i + 1);
    }
    emit sgCollectDataGet(data);
    return ans;
}

void CollectPanel::slCollectData(const serialAnalyseCell &cell)
{
    // 更新最后示数
    ui->leastData->setText(QString::number(cell.value));

    // 将Y轴数据添加到曲线图上
    ui->chart->addYPointBaseOnTime(cell);

    // 如果是刚刚打开采集状态，就要重置最大值和最小值
    if (resetRange == true)
    {
        min = cell.value;
        max = cell.value;
        resetRange = false;
    }

    // 如果是采集状态，将数据添加到data中
    if (collectState == true)
    {
        // 采集数据
        data.push_back(cell.value);

        // 检查数据是否波动
        if (checkState)
            checkDataWave(cell.value);

        if (cell.value > max)
        {
            max = cell.value;
            currentRange = max - min;
            ui->lbRange->setText(QString::number(currentRange));
        }
        else if (cell.value < min)
        {
            min = cell.value;
            currentRange = max - min;
            ui->lbRange->setText(QString::number(currentRange));
        }
    }
}

void CollectPanel::collectStart(void)
{
    resetRange = true;
    collectState = true;
    data.clear();
}
void CollectPanel::collectStop(void)
{
    collectState = false;
    ui->lbRange->setText("NULL");
}
void CollectPanel::collectFinish(void)
{
    ui->chart->chartRefresh(); // 最新几个数据点可能卡在软件定时器里了，更新一下
    emit sgCollectDataAverage(average());
    collectStop();
}

double CollectPanel::getRange(void)
{
    return currentRange;
}

QCPAxis *CollectPanel::getXAxis(void)
{
    return ui->chart->xAxis;
}

void CollectPanel::setRange(const double range)
{
    commandRange = range;
}

void CollectPanel::setCheckState(bool check)
{
    checkState = check;
}

bool CollectPanel::isStable(void)
{
    return stableState;
}

// 以滑动窗口的方式检查数据波动
void CollectPanel::checkDataWave(const double &data)
{
    // 滑动窗口
    if (dataWave.size() < 10)
    {
        dataWave.push_back(data);
        stableState = false;
        qDebug() << "dataWave.size() < 10";
        return;
    }
    else
    {
        dataWave.pop_front();
        dataWave.push_back(data);
    }

    // 检查数据波动
    double max = dataWave.at(0);
    double min = dataWave.at(0);
    for (int i = 0; i < 10; ++i)
    {
        if (dataWave.at(i) > max)
            max = dataWave.at(i);
        if (dataWave.at(i) < min)
            min = dataWave.at(i);
    }

    if (max - min > commandRange)
        stableState = false;
    else
        stableState = true;

    qDebug() << deviceName << "StableState:" << stableState;
}
