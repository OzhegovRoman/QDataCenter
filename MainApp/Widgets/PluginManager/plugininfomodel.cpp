#include "plugininfomodel.h"


cPluginInfoModel::cPluginInfoModel(QObject *parent):
    QAbstractTableModel(parent),
    plugins(NULL)
{
}

int cPluginInfoModel::rowCount (const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (plugins == NULL) return 0;
    return plugins->count();
}

int cPluginInfoModel::columnCount (const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

void cPluginInfoModel::setPluginList(QList<IPluginInfo *> *pluginlist)
{
    plugins = pluginlist;
    emit layoutChanged();
}


QVariant cPluginInfoModel::data (const QModelIndex &index, int role) const
{
    if (plugins == NULL) return QVariant();

    if (!index.isValid()) return QVariant();

    if (index.row()>=plugins->count())  return QVariant();

    if (role== Qt::DisplayRole)
        switch (index.column()) {
        case 0: return plugins->at(index.row())->FileName();
        case 1: return plugins->at(index.row())->PluginType();
        case 2: return plugins->at(index.row())->PluginVersion();
        case 3: return plugins->at(index.row())->Description();
        }
    return QVariant();
}

QVariant cPluginInfoModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (role!=Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0: return QString(tr("DLL Name"));
        case 1: return QString(tr("DLL Type"));
        case 2: return QString(tr("Version"));
        case 3: return QString(tr("Description"));\
        default: return QString(tr("Column %1")).arg(section);
        }
    }
    else return QString("Row %1").arg(section);
}

