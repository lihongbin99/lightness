#include "lightness_mask.h"

#include <QDebug>
#define cout qDebug()

lightness_mask::lightness_mask(QScreen *screen)
    : QMainWindow()
    , screen(screen)
{
    // 获取显示器的位置和宽高
    QRect deskRect = screen->geometry();

    // 移动位置
    move(deskRect.x(), deskRect.y());

    // 设置宽高
    resize(deskRect.width(), deskRect.height() - 1);

    cout << deskRect.width() << " " << deskRect.height();

    // 透明度
    setWindowOpacity(0.5);

    // 鼠标穿透
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    // 取消标题栏
    setWindowFlag(Qt::FramelessWindowHint);
    // 取消任务栏图标
    setWindowFlag(Qt::Tool);

    // 窗口置顶
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);

    // 设置黑色背景
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    setPalette(palette);
}

void lightness_mask::changeWindowOpacity(double value)
{
    setWindowOpacity(value);
}

lightness_mask::~lightness_mask()
{

}
