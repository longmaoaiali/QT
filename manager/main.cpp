#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include "connectionh.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    if(!connectionh::createConnection())
        return 0; //create SQL failed

    QApplication a(argc, argv);
    //先创建数据库，先实例化Widget会导致数据还没open
    Widget w;
    w.show();
    return a.exec();
}
