#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MdiChild;
class QMdiSubWindow;
//菜单窗口添加子窗口列表显示打开的文件名
//信号映射器类，实现对多个相同部件的相同信号进行映射
class QSignalMapper;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void updateMenus();
    MdiChild * createMdiChild(); //新建窗口
    void showTextRowAndCol(); //显示文本的行号和列号

    void updateWindowMenu();
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionUndo_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    //间隔器 窗口菜单显示子窗口菜单，将它与前面的菜单动作分隔开
    QAction *actionSeparator;
    QSignalMapper * windowMapper;

    MdiChild *activeMdiChild();
    QMdiSubWindow * findMdiChild(const QString &filename);

    void readSettings();
    void writeSettings();
    void initWindow();
};

#endif // MAINWINDOW_H
