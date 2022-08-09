#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QList>

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

    // 亮度
    int MIN_VALUE = 15;
    void changed(int value);

    // 遮罩
    QList<lightness_mask*> list;

    void trayShow(QSystemTrayIcon::ActivationReason reason);

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
