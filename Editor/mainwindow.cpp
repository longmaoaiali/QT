#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdichild.h"
#include <QMdiSubWindow>
#include <QDebug>
#include <QFileDialog>

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

    return  child;
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


