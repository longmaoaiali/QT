#include "gameview.h"
#include <QApplication>
#include <QTextCodec>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    //设置随机数
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    GameView view;
    view.show();
    return a.exec();
}
