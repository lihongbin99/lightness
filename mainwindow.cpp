#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#define cout qDebug()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);

    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);

    // 设置图标
    setWindowIcon(QIcon(QPixmap(icon)));

    // 设置托盘
    QSystemTrayIcon *tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(QPixmap(icon)));
    connect(tray, &QSystemTrayIcon::activated, this, &MainWindow::trayShow);
    // 托盘功能
    QMenu *menu = new QMenu(this);                                                                         /* 菜单中的显示窗口，单击连接显示窗口 */
    QAction *quit = new QAction(this);                                                                                                                             /* 初始化退出程序 */
    quit->setText("退出程序");
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    menu->addAction(quit);
    tray->setContextMenu(menu);
    tray->show();

    // 创建遮罩
    QList<QScreen*> screenList = QGuiApplication::screens();
    for (int i = 0; i < screenList.count(); i++) {
        QScreen *screen = screenList.at(i);
        lightness_mask *mask = new lightness_mask(screen);
        mask->show();
        list.append(mask);
    }

    // 监听亮度改变
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::changed);
    // 设置初始亮度
    ui->horizontalSlider->setValue(50);
}

void MainWindow::changed(int value)
{
    if (value < MIN_VALUE) {
        value = MIN_VALUE;
        ui->horizontalSlider->setValue(MIN_VALUE);
    }
    ui->label->setText(QString::number(value) + "%");

    // TODO 修改屏幕亮度
    double lightnes = value / 100.0;
    lightnes = 1 - lightnes;
    for(int i=0; i<list.size(); ++i){
        lightness_mask *mask = list.at(i);
        mask->changeWindowOpacity(lightnes);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void MainWindow::trayShow(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick) {
        this->showNormal();
    } else if (reason == QSystemTrayIcon::Trigger) {
        this->showNormal();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

