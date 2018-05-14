#include "newwindowdialog.h"
#include "ui_newwindowdialog.h"
#include "../mainwindow.h"
#include "WindowManagerInterface.h"
#include <QDebug>
#include <QDesktopWidget>

NewWindowDialog::NewWindowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWindowDialog),
    mWindowPlugins(NULL),
    wNewProperties(NULL)
{
    ui->setupUi(this);
    setWindowTitle(tr("New Window"));
    connect(ui->cbWindowTypes, SIGNAL(currentIndexChanged(QString)), SLOT(setNewWindowProperties(QString)));
}

NewWindowDialog::~NewWindowDialog()
{
    delete ui;
}

void NewWindowDialog::setWindowManagers(QList<IWindowManager *> *WindowManager)
{
    mWindowPlugins = WindowManager;
    updateComboBox();
}

int NewWindowDialog::exec()
{
    moveToCenter();
    return QDialog::exec();
}

void NewWindowDialog::setNewWindowProperties(QString WindowType)
{
    foreach (IWindowManager *wmanager, *mWindowPlugins){
        if (wmanager->Types().contains(WindowType)){
            if (wNewProperties != NULL) wNewProperties->deleteLater();
            wNewProperties = wmanager->newWindowWidget(WindowType);
            if (wNewProperties != NULL)
                ui->verticalLayout->insertWidget(1, wNewProperties);
            return;
        }
    }
}

void NewWindowDialog::updateComboBox()
{
    ui->cbWindowTypes->clear();
    foreach (IWindowManager *wmanager, *mWindowPlugins)
        ui->cbWindowTypes->addItems(wmanager->Types());
}

void NewWindowDialog::moveToCenter()
{
    this->move(parentWidget()->geometry().center()-this->rect().center());
}

void NewWindowDialog::resizeEvent(QResizeEvent *e)
{
    moveToCenter();
    QDialog::resizeEvent(e);
}

void NewWindowDialog::on_buttonBox_accepted()
{
    qDebug()<<"Button box accepted";
    emit createNewWindow(ui->cbWindowTypes->currentText());
}
