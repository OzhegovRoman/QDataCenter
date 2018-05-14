#include "qWindowPlugin.h"
#include <QDebug>
#include <qWindowPlugin.h>

QString qWindowPlugin::FileName() const
{
    return QString(ORIGIN_TARGET);
}

QString qWindowPlugin::PluginType() const
{
    return QString(PLUGINTYPE);
}

QString qWindowPlugin::PluginVersion() const
{
    return QString(VER);
}

QWidget *qWindowPlugin::newWindowWidget(QString WindowType)
{
    Q_UNUSED(WindowType)
    return NULL;
}

QWidget *qWindowPlugin::AddWindow(QString WindowType)
{
    Q_UNUSED(WindowType)
    return NULL;
}

void qWindowPlugin::SetData(QString ChannelName, QVariant Data)
{
    emit setDataToWindow(ChannelName, Data);
}

void qWindowPlugin::startRecord(QString newLineName) const
{
    foreach (WindowMDI* window, child_list) {
        window->startRecord(newLineName);
    }
}

void qWindowPlugin::stopRecord() const
{
    foreach (WindowMDI* window, child_list) {
        window->stopRecord();
    }
}

void qWindowPlugin::resetData() const
{
    foreach (WindowMDI* window, child_list) {
        window->resetData();
    }
}

void qWindowPlugin::addToChildList(WindowMDI *subwindow)
{
    if (!subwindow) return;
    child_list.append(subwindow);
    qDebug()<<"size of child_list"<<child_list.count();
    connect(subwindow,SIGNAL(destroyed()),this, SLOT(DeleteEmptyWindowfromList()));
    connect(this, SIGNAL(setDataToWindow(QString,QVariant)), subwindow, SLOT(setData(QString,QVariant)));
}

void qWindowPlugin::DeleteEmptyWindowfromList()
{
    int i = 0;
    while (i<child_list.count())
    {
        WindowMDI *child = qobject_cast<WindowMDI *> (child_list[i]);
        if (child)
            ++i;
        else
            child_list.removeAt(i);
    }
}
