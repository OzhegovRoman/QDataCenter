#include "pluginmanagerdialog.h"
#include "ui_pluginmanagerdialog.h"
#include <QHeaderView>

cPluginManagerDialog::cPluginManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PLuginManagerDialog),
    plugModel(new cPluginInfoModel(this))
{
    ui->setupUi(this);
    setWindowTitle(tr("Plugin Manager"));

    connect(ui->pbRefresh, SIGNAL(clicked()), this, SIGNAL(refreshPluginsList()));

    ui->tableView->setModel(plugModel);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

cPluginManagerDialog::~cPluginManagerDialog()
{
    delete ui;
}

void cPluginManagerDialog::setPluginInfos(QList<IPluginInfo*> *plugInfoList)
{
    plugModel->setPluginList(plugInfoList);
    ReBuildForm();
}

void cPluginManagerDialog::ReBuildForm(void)
{
    for (int i = 0; i < plugModel->columnCount()-1; ++i)
        ui->tableView->resizeColumnToContents(i);
}


