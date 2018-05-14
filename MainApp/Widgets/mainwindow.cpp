#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>
#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include <QString>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    wNew(new NewWindowDialog(this)),
    wPlugin(new cPluginManagerDialog(this)),
    wOption(new OptionDialog(this)),
    mTimer(new QTimer(this))
{

    ui->setupUi(this);
    this->setWindowTitle(QString(tr("DATA Center v.%1"))
                         .arg(VER));

    windowMapper = new QSignalMapper(this);
    connect(ui->actionExit, SIGNAL(triggered()),qApp, SLOT(quit()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updatePrintMenuStatus()));
    connect(windowMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));
    connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    connect(ui->actionPlugin_Manager, SIGNAL(triggered()), wPlugin, SLOT(exec()));
    connect(wPlugin, SIGNAL(refreshPluginsList()), this, SLOT(updatePluginList()));

    connect(ui->actionNew, SIGNAL(triggered()), wNew, SLOT(exec()));
    connect(wNew, SIGNAL(createNewWindow(QString)), this, SLOT(addNewWindow(QString)));

    connect(ui->actionOptions, SIGNAL(triggered()), wOption, SLOT(exec()));

    updatePluginList();


    connect(mTimer, SIGNAL(timeout()), SLOT(TimerTick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWindowMenu()
{

    //Refresh Menu
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    bool empty_window = windows.isEmpty();

    //Update Window Menu
    ui->menuWindow->clear();
    ui->menuWindow->addAction(ui->actionCascade);
    ui->menuWindow->addAction(ui->actionTile);

    if (!empty_window) ui->menuWindow->addSeparator();

    for (int i = 0; i < windows.size(); ++i)
    {
        QWidget *child = windows[i]->widget();

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1).arg(child->windowTitle());
        } else {
            text = tr("%1 %2").arg(i + 1).arg(child->windowTitle());
        }
        QAction *action  = ui->menuWindow->addAction(text);
        action->setCheckable(true);
        action ->setChecked(child == activeMDIChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows[i]);
    }
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::addNewWindow(QString windowType)
{
    qDebug()<<"Add new Window"<<windowType;
    foreach (IWindowManager *wManager, mWindowPlugins)
        if (wManager->Types().contains(windowType)){
            QWidget *newWindow = wManager->AddWindow(windowType);
            if (newWindow == NULL) return;
            ui->mdiArea->addSubWindow(newWindow);
            newWindow->show();
            return;
        }
}

void MainWindow::dataSender(QString channelName, QVariant Data)
{
    foreach (IWindowManager* wManager, mWindowPlugins) {
        wManager->SetData(channelName, Data);
    }
}

void MainWindow::TimerTick()
{
    dataSender("X", qrand());
    dataSender("Z", qrand());
}

QWidget *MainWindow::activeMDIChild()
{
    QMdiSubWindow *activeSubWindow =ui->mdiArea->activeSubWindow();
    if (activeSubWindow)
        return activeSubWindow->widget();
    return 0;
}

void MainWindow::updatePluginList()
{
    // Обновляем подключенных плагинов
    // Подключаем только библиотеки
    QDir PluginDIR("Plugins","*.dll", QDir::IgnoreCase, QDir::Files);
    PluginInfoList.clear();
    mWindowPlugins.clear();

    foreach (QString plugfilename, PluginDIR.entryList()){
        plugfilename.insert(0,"Plugins/");
        QPluginLoader PlugLoader(plugfilename);
        QObject *possiblePlugin = PlugLoader.instance();
        if (possiblePlugin){
            IPluginInfo *plugin = qobject_cast<IPluginInfo*>(possiblePlugin);
            if (plugin){
                qDebug()<<"plugin name = "<< plugin->FileName();
                PluginInfoList.append(plugin);
                if (plugin->PluginType() == "Window"){
                    qDebug()<<"+ window manager "+plugin->FileName();
                    IWindowManager *wmanager = qobject_cast<IWindowManager*>(possiblePlugin);
                    if (wmanager){
                        mWindowPlugins.append(wmanager);
                        qDebug()<<"window manager appended";
                    }
                }
                else if (plugin->PluginType() == "Device"){
                    qDebug()<<"+ device manager "+plugin->FileName();
                }
            }
        }
    }

    wPlugin->setPluginInfos(&PluginInfoList);
    wNew->setWindowManagers(&mWindowPlugins);
}

void MainWindow::updatePrintMenuStatus()
{
    //Refresh Menu
    ui->actionPrint->setEnabled(!ui->mdiArea->subWindowList().isEmpty());
}


void MainWindow::on_actionReading_triggered(bool checked)
{
    if (checked) {
        foreach (IWindowManager* wManager, mWindowPlugins)
            wManager->resetData();
        mTimer->start(200);
    }
    else mTimer->stop();
}

void MainWindow::on_actionRecording_triggered(bool checked)
{
    if (checked){
        QString newLineName = QInputDialog::getText(this,
                                                    tr("New Line"),
                                                    tr("Input new line name ..."),
                                                    QLineEdit::Normal,
                                                    QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss:zzz"));

        if (newLineName.isEmpty()){
            ui->actionRecording->setChecked(false);
            return;
        }
        foreach (IWindowManager* wManager, mWindowPlugins)
            wManager->startRecord(newLineName);
    }
    else
        foreach (IWindowManager* wManager, mWindowPlugins)
            wManager->stopRecord();
}
