#ifndef PLUGININFOMODEL_H
#define PLUGININFOMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include "PluginInfoInterface.h"

class cPluginInfoModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    cPluginInfoModel(QObject *parent = 0);
    int rowCount (const QModelIndex &parent = QModelIndex()) const;
    int columnCount (const QModelIndex &parent = QModelIndex()) const;
    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void setPluginList(QList<IPluginInfo *> *pluginlist);
public slots:

private:
    QList<IPluginInfo*> *plugins;
};

#endif // PLUGININFOMODEL_H
