#include "gameview.h"
#include <QIcon>

static const qreal INITSPEED = 500;


GameView::GameView(QWidget *parent):QGraphicsView(parent)
{
    initView();
}

void GameView::startGame()
{
    initGame();
}

void GameView::initView()
{
    qDebug()<<tr("Game initView");
    //使用抗锯齿渲染
    setRenderHint(QPainter::Antialiasing);
    //设置缓存背景，加快渲染速度
    setCacheMode(CacheBackground);
    setWindowTitle(tr("方块游戏"));
    setWindowIcon(QIcon(":/myImage/images/icon.png"));
    setMinimumSize(810,510);
    setMaximumSize(810,510);

    //设置场景
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(5,5,800,500);
    scene->setBackgroundBrush(QPixmap(":/myImage/images/background.png"));
    setScene(scene);

    //方块移动区域的边界线
    topLine = scene->addLine(197,47,403,47);
    bottomLine = scene->addLine(197,453,403,453);
    leftLine = scene->addLine(197,47,197,453);
    rightLine = scene->addLine(403,47,403,453);

    boxGroup = new BoxGroup();
    connect(boxGroup, SIGNAL(needNewBox()),this,SLOT(clearFullRows()));
    connect(boxGroup, SIGNAL(gameFinished()),this,SLOT(gameOver()));

    scene->addItem(boxGroup);
    nextBoxGroup = new BoxGroup();
    scene->addItem(nextBoxGroup);

    startGame();

}

void GameView::initGame()
{
    boxGroup->createBox(QPointF(300,70));
    //设置当前组拥有焦点
    boxGroup->setFocus();
    boxGroup->startTimer(INITSPEED);
    gameSpeed = INITSPEED;
    nextBoxGroup->createBox(QPointF(500,70));
}

void GameView::updateScore(const int fullRowNum)
{

}

//清除满行
void GameView::clearFullRows()
{
    for(int y=429;y>50;y-=20){
        QList<QGraphicsItem*> list = scene()->items(199,y,202,2,Qt::ContainsItemShape);
        if(list.count() == 10) {
            //该行已满
            foreach (QGraphicsItem *item, list) {
                OneBox *box = (OneBox*)item;
                box->deleteLater();
            }
            //保存满行的位置
            rows<<y;
        }
    }
    /*满行 则下移满行上面的方块组
     *没有满行 则直接出现新的方块组
    */
    if(rows.count()>0){
        moveBox();
    } else {
        boxGroup->createBox(QPointF(300,70),nextBoxGroup->getCurrentShape());
        //清除方块组的小方块
        nextBoxGroup->clearBoxGroup(true);
        nextBoxGroup->createBox(QPointF(500,70));
    }
}

void GameView::moveBox()
{
    qDebug()<<tr("moveBox");
    for(int i=rows.count();i>0;--i){
        //找到这一行上面所有的方块，然后下移20
        int row = rows.at(i-1);
        foreach (QGraphicsItem* item, scene()->items(199,49,202,row-47,Qt::ContainsItemShape)) {
            item->moveBy(0,20);
        }
    }

    //更新分数
    updateScore(rows.count());
    rows.clear();

    boxGroup->createBox(QPointF(300,70),nextBoxGroup->getCurrentShape());
    nextBoxGroup->clearBoxGroup(true);
    nextBoxGroup->createBox(QPoint(500,70));
}

void GameView::gameOver()
{

}

