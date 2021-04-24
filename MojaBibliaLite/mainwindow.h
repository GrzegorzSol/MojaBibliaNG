#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "QGsReadBibleTextClass/qgsreadbibletextclass.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void closeEvent(QCloseEvent *event) override;
    bool event(QEvent *e) override;

    virtual void dropEvent(QDropEvent* event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
private:
    Ui::MainWindow *ui;
    void _InitAllSignalsToolTips();
    //---
    QLabel *_pQGsLabelClass;

private slots:
 //Sloty dla akcji
 void _Act_SearchBibleText();
 void _Act_SetupsWindow();
 void _Act_CloseSheetActiv();
 void _Act_SavetoFile();
 void _Act_ResizeToolsTabs();
};
#endif // MAINWINDOW_H
