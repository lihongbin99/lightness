#ifndef LIGHTNESS_MASK_H
#define LIGHTNESS_MASK_H

#include <QMainWindow>

#include <QGuiApplication>
#include <QScreen>

class lightness_mask : public QMainWindow
{
    Q_OBJECT

public:
    lightness_mask(QScreen *screen);
    ~lightness_mask();

    void changeWindowOpacity(double);

private:
    QScreen *screen;
};

#endif // LIGHTNESS_MASK_H
