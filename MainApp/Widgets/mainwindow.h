#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "NewWindow/newwindowdialog.h"
#include "PluginManager/pluginmanagerdialog.h"
#include "Options/optiondialog.h"
#include "PluginInfoInterface.h"
#include "WindowManagerInterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updatePluginList();

private slots:
    void updatePrintMenuStatus();
    void updateWindowMenu();
    void setActiveSubWindow(QWidget *window);
    void addNewWindow(QString windowType);

    void dataSender(QString channelName, QVariant Data);
    void TimerTick();
    void on_actionReading_triggered(bool checked);

    void on_actionRecording_triggered(bool checked);

signals:
    void sendData(QString, QVariant);

private:
    Ui::MainWindow *ui;
    QSignalMapper *windowMapper;
    NewWindowDialog *wNew;
    cPluginManagerDialog *wPlugin;
    OptionDialog *wOption;
    QList<IPluginInfo*> PluginInfoList;
    QList<IWindowManager*> mWindowPlugins;
    QTimer *mTimer;

    QWidget *activeMDIChild();
};

#endif // MAINWINDOW_H
