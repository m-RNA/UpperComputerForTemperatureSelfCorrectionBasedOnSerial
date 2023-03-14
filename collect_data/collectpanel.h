#ifndef COLLECTPANEL_H
#define COLLECTPANEL_H
#include "config.h"

#include <QWidget>
#include <vector>
#include "interactchart.h"
#include "bll_serialrecvanalyse.h"
using namespace std;

namespace Ui
{
    class CollectPanel;
}

class CollectPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CollectPanel(QWidget *parent = nullptr);
    ~CollectPanel();

    void setDeviceName(QString name);
    void setOnlineState(bool state);
    void setCheckWaveState(bool check);
    void setCheckWaveNum(int num);
    void setCheckWaveRange(const double range);

    bool isStable(void);
    double getRange(void);
    QCPAxis *getXAxis(void);

    void collectStart(void);
    void collectStop(void);
    void collectFinish(void);

public slots:
    void slCollectData(const serialAnalyseCell &cell);

signals:
    void sgCollectDataAverage(const DECIMAL_TYPE &average);

    void sgCollectDataGet(const vector<double> &data);

private slots:

private:
    Ui::CollectPanel *ui;
    QString deviceName;
    vector<double> data;
    bool collectState = false;

    double min = 0;
    double max = 0;
    double currentRange = 0;
    double commandRange = 0.01;
    double checkWaveNum = 10;
    bool resetRange = true;

    bool onlineState = false;
    bool checkWaveState = false;
    bool stableState = false;
    bool laseStableState = false;
    QVector<double> dataWave;

    void setState(int state);
    double average(void);
    void checkDataWave(const double &data);
};

#endif // COLLECTPANEL_H
