#include "mdichild.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QDebug>

MdiChild::MdiChild(QTextEdit *parent) : QTextEdit(parent)
{
    qDebug()<<tr("MdiChild::MdiChild");
    setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时，delete对象
    isUntitled = true;//未保存标志设为true

}

void MdiChild::newFile()
{
    qDebug()<<"MdiChild::newFile";
    static int sequenceNumber = 1;
    isUntitled = true;

    curFile = tr("未命名文档%1.txt").arg(sequenceNumber++);
    //这里在设置窗口标题时添加了“[*]”字符，
    //它可以保证编辑器内容被更改后，在相应位置显示 * 号
    setWindowTitle(curFile+"[*]"+tr("-多文档编辑器"));

    //连接槽与信号
    connect(document(),SIGNAL(contentsChanged()),
            this,SLOT(documentWasModify()));
}

//loadFile方法的参数是一个引用
bool MdiChild::loadFile(const QString &filename)
{
    qDebug()<<"MdiChild::loadFile";
    QFile file(filename);
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n %2.")
                             .arg(filename).arg(file.errorString()));
        return false;
    }

    //新建文本流对象，传入file对象的指针
    QTextStream in(&file);
    //设置鼠标状态为等待
    QApplication::setOverrideCursor(Qt::WaitCursor);

    //将文件内容全部读取出来
    setPlainText(in.readAll());
    //恢复鼠标状态
    QApplication::restoreOverrideCursor();

    //设置加载的文件的一些状态
    setCurrentFile(filename);
    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModify()));

            return true;
}

bool MdiChild::saveAs()
{
    qDebug()<<"MdiChild::saveAs";
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &filename)
{
    qDebug()<<"MdiChild::saveFile";
    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text)) {
        QMessageBox::warning(this,tr("多文档编辑器"),
                             tr("无法写入文件 %1, \n%2.")
                             .arg(filename).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    out<<toPlainText();
    QApplication::restoreOverrideCursor();
    setCurrentFile(filename);
    return true;
}

QString MdiChild::userFriendlyCurrentFile()
{
    qDebug()<<"MdiChild::userFriendlyCurrentFile";
    //返回路径名中的文件名
    return QFileInfo(curFile).fileName();
}



QString MdiChild::currentFilePath()
{
    qDebug()<<"MdiChild::currentFilePath";
    return curFile;
}

//close Event
void MdiChild::closeEvent(QCloseEvent *event)
{
    qDebug()<<"MdiChild::closeEvent";
    if(maybeSave()){
        event->accept();
    }else {
        event->ignore();
    }
}

void MdiChild::documentWasModify()
{
    qDebug()<<"MdiChild::documentWasModify";
    //根据文档的 ismodified()函数的返回值，判断编辑器内容是否被更改了
    //setWindowModified函数设置窗口的更改状态标志“”，如果参数为true
    //那么就会在标题中的设置了“[*]”号的地方显示“*”号，表示该文件已经被修改
    setWindowModified(document()->isModified());
}

bool MdiChild::maybeSave()
{
    qDebug()<<"MdiChild::maybeSave";
    if(document()->isModified()){
        QMessageBox box(this);
        box.setWindowTitle(tr("多文档编辑器"));
        box.setText(tr("是否保存对 %1 的更改？").arg(userFriendlyCurrentFile()));
        box.setIcon(QMessageBox::Warning);

        QPushButton* yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
        box.addButton(tr("否(&N)"),QMessageBox::NoRole);
        QPushButton* cancleBtn = box.addButton(tr("取消"),QMessageBox::RejectRole);

        box.exec();

        if(box.clickedButton() == yesBtn)
            return save();
        else if(box.clickedButton() == cancleBtn)
            return false;

    }
    //文档未修改过直接返回true
    return true;
}

void MdiChild::setCurrentFile(const QString &filename)
{
    qDebug()<<"MdiChild::setCurrentFile";
    //去除文件路径中的. ..符号
    curFile = QFileInfo(filename).canonicalFilePath();

    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);

    //设置窗口标题 userFriendlyCurrentFile 返回文件名
    setWindowTitle(userFriendlyCurrentFile()+"[*]");
}

bool MdiChild::save()
{
    qDebug()<<"MdiChild::save";
    if(isUntitled){
        //未被保存过
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}




