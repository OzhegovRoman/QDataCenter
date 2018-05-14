#ifndef WINDOWPLUGIN_H
#define WINDOWPLUGIN_H

#include <QObject>

class WindowPlugin : public QObject
{
    Q_OBJECT
public:
    explicit WindowPlugin(QObject *parent = 0) :
        QObject(parent){}
signals:

public slots:

};

#endif // WINDOWPLUGIN_H
