#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include "connectionh.h"
#include "logindialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //先实例化应用，后面得到应用路径使用
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    connectionh con;

    if(!con.createConnection())
        return 0; //create SQL failed
    if(!con.createDailyXml())
        return 0;

    //先创建数据库，先实例化Widget会导致数据还没open

    LoginDialog dialog;
    if(dialog.exec() == QDialog::Accepted){
        Widget w;
        w.show();
        return a.exec();
    } else {
        return 0;
    }
}
