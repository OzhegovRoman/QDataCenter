#ifndef NEWWINDOWDIALOG_H
#define NEWWINDOWDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include "WindowManagerInterface.h"

namespace Ui {
class NewWindowDialog;
}

class NewWindowDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewWindowDialog(QWidget *parent = 0);
    ~NewWindowDialog();

    void setWindowManagers(QList<IWindowManager*> *WindowManager);

    int exec();
    
private slots:
    void setNewWindowProperties(QString WindowType);
    void on_buttonBox_accepted();

private:
    Ui::NewWindowDialog *ui;
    QList<IWindowManager*> *mWindowPlugins;
    QWidget *wNewProperties;
    void updateComboBox(void);
    void moveToCenter();

    void resizeEvent(QResizeEvent *e);
signals:
    void createNewWindow(QString);
};

#endif // NEWWINDOWDIALOG_H
