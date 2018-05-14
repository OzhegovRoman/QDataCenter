#ifndef PLUGINMANAGERDIALOG_H
#define PLUGINMANAGERDIALOG_H

#include <QDialog>
#include <QtGui>
#include "PluginInfoInterface.h"
#include "plugininfomodel.h"

namespace Ui {
class PLuginManagerDialog;
}

class cPluginManagerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit cPluginManagerDialog(QWidget *parent = 0);
    ~cPluginManagerDialog();
    void setPluginInfos(QList<IPluginInfo*>* plugInfoList);

private:
    Ui::PLuginManagerDialog *ui;
    cPluginInfoModel *plugModel;

private slots:
    void ReBuildForm(void);

signals:
    void refreshPluginsList();
};

#endif // PLUGINMANAGERDIALOG_H
