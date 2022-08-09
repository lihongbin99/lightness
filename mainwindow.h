#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QList>
#include <QFile>
#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QSystemTrayIcon>

#include "lightness_mask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString icon = ":/static/keqing.jpg";
    QString configFile = "config";

    // 亮度
    int MIN_VALUE = 15;
    double lightness = 0.5;
    void changed(int value);

    // 遮罩
    QList<lightness_mask*> list;
    void maskInit();

    void trayShow(QSystemTrayIcon::ActivationReason reason);

    void changeSize(int);

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
