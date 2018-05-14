#ifndef QWINDOWPLUGIN_H
#define QWINDOWPLUGIN_H

#include "PluginInfoInterface.h"
#include "WindowManagerInterface.h"
#include "WindowMDI/windowmdi.h"
#include <QObject>
#include <QVariant>


class qWindowPlugin : public QObject, IPluginInfo, IWindowManager
{
    Q_OBJECT
    Q_INTERFACES(IPluginInfo)
    Q_INTERFACES(IWindowManager)
public:
    explicit qWindowPlugin(QObject *parent = 0) :
        QObject(parent)
    {
    }

    // IPluginInfo implementation
    QString FileName() const;
    QString PluginType() const;
    QString PluginVersion() const;
    QString Description() const {return QString();}

    QStringList Types(void) const {return QStringList();}
    QWidget *newWindowWidget(QString WindowType);
    QWidget *AddWindow(QString WindowType);
    void SetData(QString ChannelName, QVariant Data);

    void startRecord (QString newLineName) const;
    void stopRecord() const;

    void resetData() const;

    QList<WindowMDI *> *childList(){return &child_list;}
    void addToChildList(WindowMDI *subwindow);

signals:
    void setDataToWindow(QString, QVariant);

public slots:

private slots:
    void DeleteEmptyWindowfromList();

private:
    QList<WindowMDI *> child_list;
};

#endif // QWINDOWPLUGIN_H
