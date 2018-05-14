#include "windowmdi.h"
#include <QDateTime>
#include <QDebug>

WindowMDI::WindowMDI(QWidget *parent) :
    QMainWindow(parent),
    mActive(true),
    mRecordable(true),
    mRecordState(false)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

WindowMDI::~WindowMDI()
{
}

void WindowMDI::startRecord(QString newLineName)
{
    Q_UNUSED(newLineName)
    mRecordState = true;
    mStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    qDebug()<<"StartTime"<<mStartTime;
}

void WindowMDI::stopRecord()
{
    mRecordState = false;
}

void WindowMDI::setData(QString Channel, QVariant data)
{
    Q_UNUSED(Channel)
    Q_UNUSED(data)

    qDebug()<<"WindowMDI::SetData";
}
