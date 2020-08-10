#ifndef MDICHILD_H
#define MDICHILD_H

#include <QWidget>
#include <QTextEdit>

class MdiChild : public QTextEdit
{
    Q_OBJECT
public:
    explicit MdiChild(QTextEdit *parent = 0);
    void newFile();
    bool loadFile(const QString &filename);
    bool save();
    bool saveAs();
    bool saveFile(const QString &filename);

    QString userFriendlyCurrentFile();//提取文件名
    QString currentFilePath(); //得到文件路径

protected:
    void closeEvent(QCloseEvent * event);//关闭事件
    void contextMenuEvent(QContextMenuEvent *e);

private slots:
    void documentWasModify();//文档被更改时，窗口显示更改标志

private:
    bool maybeSave();
    void setCurrentFile(const QString &filename); //设置文件
    QString curFile;
    bool isUntitled; //当前文件内容是否被保存在硬盘上标志

signals:

public slots:

};

#endif // MDICHILD_H
