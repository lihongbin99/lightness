#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#define cout qDebug()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("lightness");

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
    QMenu *menu = new QMenu(this);
    QAction *quit = new QAction(this);
    quit->setText("退出程序");
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    menu->addAction(quit);
    tray->setContextMenu(menu);
    tray->show();

    // 获取历史记录
    QFile file(configFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write("50");
        file.close();
        file.open(QIODevice::ReadOnly | QIODevice::Text);
    }
    QString lightnessConfig = QString(file.readAll());

    // 初始化遮罩
    maskInit();

    // 监听亮度改变
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::changed);
    // 设置初始亮度
    ui->horizontalSlider->setValue(lightnessConfig.toInt());

    // 监听显示器变化
    QDesktopWidget *desktopwidget = QApplication::desktop();
    connect(desktopwidget, &QDesktopWidget::resized, this, &MainWindow::changeSize);
    connect(desktopwidget, &QDesktopWidget::screenCountChanged, this, &MainWindow::changeSize);
}

void MainWindow::changed(int value)
{
    if (value < MIN_VALUE) {
        value = MIN_VALUE;
        ui->horizontalSlider->setValue(MIN_VALUE);
    }
    QString v = QString::number(value);
    ui->label->setText(v + "%");

    // 修改屏幕亮度
    lightness = 1 - value / 100.0;
    for(int i=0; i<list.size(); ++i){
        lightness_mask *mask = list.at(i);
        mask->changeWindowOpacity(lightness);
    }
    // 保存记录
    QFile file(configFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(v.toStdString().c_str());
    file.close();
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

void MainWindow::changeSize(int)
{
    maskInit();
}

void MainWindow::maskInit() {
    // 删除遮罩
    for(int i=0; i<list.size(); ++i){
        lightness_mask *mask = list.at(i);
        delete mask;
    }
    list.clear();
    // 创建遮罩
    QList<QScreen*> screenList = QGuiApplication::screens();
    for (int i = 0; i < screenList.count(); i++) {
        QScreen *screen = screenList.at(i);
        lightness_mask *mask = new lightness_mask(screen);
        mask->changeWindowOpacity(lightness);
        mask->show();
        list.append(mask);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

