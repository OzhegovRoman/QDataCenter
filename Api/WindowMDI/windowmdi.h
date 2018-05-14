#ifndef WINDOWMDI_H
#define WINDOWMDI_H

#include <QMainWindow>
#include <QVariant>

class WindowMDI : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowMDI(QWidget *parent = 0);
    ~WindowMDI();

    bool isActive(){return mActive;}
    bool isRecordable(){return mRecordable;}
    bool isRecorded(){return mRecordState;}

    virtual void startRecord(QString newLineName = QString());
    void stopRecord();
    virtual void resetData(){}

    quint64 startTime(){return mStartTime;}

public slots:
    void setData(QString Channel, QVariant data);
    virtual void setActive(bool value){mActive = value;}
    virtual void setRecordable(bool value){mRecordable = value;}

private:
    bool mActive;
    bool mRecordable;
    bool mRecordState;
    quint64 mStartTime;
};

#endif // WINDOWMDI_H
