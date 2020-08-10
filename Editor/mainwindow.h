#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MdiChild;
class QMdiSubWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void updateMenus();
    MdiChild * createMdiChild(); //新建串口

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    //间隔器 窗口菜单显示子窗口菜单，将它与前面的菜单动作分隔开
    QAction *actionSeparator;
    MdiChild *activeMdiChild();
    QMdiSubWindow * findMdiChild(const QString &filename);
};

#endif // MAINWINDOW_H
