#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include "connectionh.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //先实例化应用，后面得到应用路径使用
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    connectionh con;
    if(!con.createConnection())
        return 0; //create SQL failed


    //先创建数据库，先实例化Widget会导致数据还没open
    Widget w;
    w.show();
    return a.exec();
}
