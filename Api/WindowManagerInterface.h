#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QtPlugin>
#include <QString>
#include <QVariant>

class IWindowManager
{
public:
    /**
     * @brief Types
     * @return функция возвращает типы окон в данном плагине
     * результат действия функции - список всех типов, который далее будет отображен при
     * создании нового окна
     */
    virtual QStringList Types(void) const = 0;

    /**
     * @brief newWindowWidget
     * Предназначена для отображения начальных настроек окна
     * @param WindowType
     * @return указатель на Виджет настроек
     */
    virtual QWidget* newWindowWidget(QString WindowType) = 0;

    /**
     * @brief AddWindow
     * Создаем новое окно
     * @param WindowType
     * @return
     */
    virtual QWidget *AddWindow(QString WindowType) = 0;

    /**
     * @brief SetData
     * @param ChannelName
     * @param Data
     */
    virtual void SetData(QString ChannelName, QVariant Data) = 0;

    /**
     * @brief startRecord
     * @param newLineName
     */
    virtual void startRecord (QString newLineName) const = 0;

    /**
     * @brief stopResord
     */
    virtual void stopRecord() const = 0;

    virtual void resetData()  const = 0;

    //virtual void AddNewLine(QString AName) const = 0;

    //    virtual QString Key_Options(void) const = 0;

    //    virtual IWindow GetItem(const int AIndex) const = 0;
    //    virtual int GetCount(void) const = 0;

    //    virtual void DeleteWindow(const int AIndex) const = 0;
    //    virtual void DeleteAllWindows(void) const = 0;

    //    virtual void ResetData(void) const = 0;
    //    virtual void SetData(QString ChannelName, float Data) const = 0;
    //    virtual void Save2File(QFile File) const = 0;
    //    virtual void OpenFile(QFile File) const = 0;
    //    virtual void SaveSettings(QString DestSettings) const = 0;
    //    virtual void OpenIniFile(QString DestSettings) const = 0;
};

Q_DECLARE_INTERFACE(IWindowManager, "com.ROzhegov.DataCenter.Plugins.WindowManagerInterface/0.1")

#endif // WINDOWMANAGER_H
