#ifndef PLUGININFOINTERFACE_H
#define PLUGININFOINTERFACE_H

#include <QtPlugin>
#include <QString>

class IPluginInfo
{
public:
    virtual QString FileName() const = 0;
    virtual QString PluginType() const = 0;
    virtual QString PluginVersion() const = 0;
    virtual QString Description() const = 0;
};

Q_DECLARE_INTERFACE(IPluginInfo, "com.ROzhegov.DataCenter.Plugins.PluginInfoInterface/0.1")

#endif // PLUGININFOINTERFACE_H
