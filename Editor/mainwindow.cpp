#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdichild.h"
#include <QMdiSubWindow>
#include <QDebug>
#include <QFileDialog>
#include <QSignalMapper>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <QAbstractScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    actionSeparator = new QAction(this);
    actionSeparator->setSeparator(true);

    //更新菜单
    updateMenus();
    //当有活动窗口时更新菜单
    //subWindowActivated 窗口变为actived会有信号发出
    //在mdiArea 切换活动窗口时，被切换到的窗口会是actived
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(updateMenus()));

    //创建信号映射器
    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
            this,SLOT(setActiveSubWindow(QWidget*)));

    //更新窗口菜单
    updateWindowMenu();
    //窗口菜单将要显示的信号，关联到updateWindowMenu
    connect(ui->menuW,SIGNAL(aboutToShow()),this,SLOT(updateWindowMenu()));

    //读取窗口设置
    readSettings();
    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    MdiChild *child = createMdiChild();


    child->newFile();
    child->show();
}

//设置各个子菜单是否可用
void MainWindow::updateMenus()
{
    qDebug()<<"update Menus";
    //根据是否有活动窗口来设置各个动作是否可用
    bool hasMdiChild = (activeMdiChild()!=0);
    ui->actionSave->setEnabled(hasMdiChild);
    ui->actionSaveAs->setEnabled(hasMdiChild);
    ui->actionPaste->setEnabled(hasMdiChild);
    ui->actionClose->setEnabled(hasMdiChild);
    ui->actionCloseAll->setEnabled(hasMdiChild);
    ui->actionTile->setEnabled(hasMdiChild);
    ui->actionCascade->setEnabled(hasMdiChild);
    ui->actionNext->setEnabled(hasMdiChild);
    ui->actionPrevious->setEnabled(hasMdiChild);

    //设置间隔器是否显示
    actionSeparator->setVisible(hasMdiChild);

    //有活动窗口 且有被选择的文本 复制剪切才可以用
    bool hasSelection = (activeMdiChild() && activeMdiChild()->textCursor().hasSelection());

    ui->actionCut->setEnabled(hasSelection);
    ui->actionCopy->setEnabled(hasSelection);



    ui->actionUndo->setEnabled(activeMdiChild() && activeMdiChild()->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(activeMdiChild() && activeMdiChild()->document()->isRedoAvailable());


}

MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild();
    //多文档区域添加子窗口 ，child为中心部件
    ui->mdiArea->addSubWindow(child);

    //根据QTextEdit类的 是否可以复制信号设置剪切复制是否可用
    connect(child,SIGNAL(copyAvailable(bool)),ui->actionCopy,SLOT(setEnabled(bool)));
    connect(child,SIGNAL(copyAvailable(bool)),ui->actionCut,SLOT(setEnabled(bool)));

    connect(child->document(), SIGNAL(undoAvailable(bool)), ui->actionUndo,SLOT(setEnabled(bool)));
    connect(child->document(), SIGNAL(redoAvailable(bool)), ui->actionRedo,SLOT(setEnabled(bool)));

    connect(child,SIGNAL(cursorPositionChanged()),this,SLOT(showTextRowAndCol()));
    return  child;
}

void MainWindow::showTextRowAndCol()
{
    if(activeMdiChild()) {
        //获取的行号是从0开始的，所以要加1
        int rowNum = activeMdiChild()->textCursor().blockNumber()+1;
        int colNum = activeMdiChild()->textCursor().columnNumber()+1;

        ui->statusBar->showMessage(tr("%1行 %2列").arg(rowNum).arg(colNum),2000);
    }
}

void MainWindow::updateWindowMenu()
{
    qDebug()<<"updateWindowMenu";
    //先清空菜单，再添加
    ui->menuW->clear();

    ui->menuW->addAction(ui->actionClose);
    ui->menuW->addAction(ui->actionCloseAll);
    //间隔器在UI上面就是一条分隔线
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionTile);
    ui->menuW->addAction(ui->actionCascade);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionNext);
    ui->menuW->addAction(ui->actionPrevious);
    ui->menuW->addAction(actionSeparator);

    QList<QMdiSubWindow *>windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());

    for(int i=0;i<windows.size(); ++i){
        MdiChild *child = qobject_cast<MdiChild*>(windows.at(i)->widget());
        QString text;

        //窗口数<9,则设置编号为快捷键
        if(i<9) {
            text = tr("&%1 %2").arg(i+1)
                    .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i+1)
                    .arg(child->userFriendlyCurrentFile());
        }

        QAction *action = ui->menuW->addAction(text);
        action->setCheckable(true);
        //设置当前活动窗口动作为选中状态 (显示一个V对号)
        action->setChecked(child == activeMdiChild());

        //关联新添加的action触发信号到信号映射器的map()
        connect(action,SIGNAL(triggered()),windowMapper, SLOT(map()));

        //将动作与窗口部件进行映射，发射mapped()信号时就会以这个窗口部件为参数
        windowMapper->setMapping(action,windows.at(i));
    }
}

MdiChild* MainWindow::activeMdiChild()
{
    if(QMdiSubWindow * activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());

    return 0;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName)
{
    //返回绝对路径的规范名
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    foreach (QMdiSubWindow * windows, ui->mdiArea->subWindowList()) {
        MdiChild * mdiChild = qobject_cast<MdiChild *>(windows->widget());
        if(mdiChild->currentFilePath() == canonicalFilePath)
            return windows;
    }
    return NULL;
}

void MainWindow::readSettings()
{
    qDebug()<<"readSettings";
    QSettings settings(QCoreApplication::applicationDirPath()+"/Config.ini", QSettings::IniFormat);
    QPoint pos = settings.value("pos", QPoint(200,200)).toPoint();
    QSize size = settings.value("size", QPoint(4000,4000)).toSize();
    qDebug()<<pos;
    qDebug()<<size;

    move(pos);
    resize(size);
}

void MainWindow::writeSettings()
{
    qDebug()<<"writeSettings";
    QSettings settings(QCoreApplication::applicationDirPath()+"/Config.ini", QSettings::IniFormat);
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    qDebug()<<pos();
    qDebug()<<size();

}

void MainWindow::initWindow()
{
    setWindowTitle(tr("多文档编辑器"));
    ui->mainToolBar->setWindowTitle(tr("工具栏"));

    //超过可视区域，出现滚动条
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->statusBar->showMessage(tr("欢迎使用多文档编辑器"));


}

void MainWindow::on_actionOpen_triggered()
{
    //用户使用对话框选中一个文件，并返回文件名
    QString fileName = QFileDialog::getOpenFileName(this);
    //如果该文件存在，需要检查该文件是否已经被打开了
    if(!fileName.isEmpty()){
        QMdiSubWindow * existing = findMdiChild(fileName);
        if(existing) {
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        MdiChild * child = createMdiChild();
        if(child->loadFile(fileName)) {
            ui->statusBar->showMessage(tr("打开文件成功"),2000);
            child->show();
        } else {
            child->close();
        }
    }
}



void MainWindow::on_actionSave_triggered()
{
    if(activeMdiChild() && activeMdiChild()->save())
        ui->statusBar->showMessage(tr("文件保存成功"),2000);
}

void MainWindow::on_actionUndo_triggered()
{
    if(activeMdiChild())
        activeMdiChild()->undo();
}

void MainWindow::on_actionClose_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //执行多文档区域的关闭操作
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();
}
