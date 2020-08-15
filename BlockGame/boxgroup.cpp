#include "boxgroup.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
//#include <QGraphicsView>
//QGraphicsView::rotate(qreal angle)

BoxGroup::BoxGroup()
{
    qDebug()<<tr("BoxGroup 构造器");
    setFlags(QGraphicsEllipseItem::ItemIsFocusable);
    //保存构造时的变换矩阵,Group旋转变换后可以使用他来恢复
    oldTransform = transform();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveOneStep()));
    currentShape = RandomShape;
}

QRectF BoxGroup::boundingRect() const
{
    qDebug()<<tr("BoxGroup boundingRect");
    qreal penWidth = 1;
    return QRectF(-40-penWidth/2, -40-penWidth/2, 80+penWidth,80+penWidth);

}

//只检测方块组里面的四块小方块
bool BoxGroup::isColliding()
{
    QList<QGraphicsItem *> itemList = childItems();
    QGraphicsItem *item;
    foreach (item, itemList) {
        if(item->collidingItems().count() > 1)
            return true;
    }

    return false;
}

void BoxGroup::createBox(const QPointF &point, BoxGroup::BoxShape shape)
{
    qDebug()<<tr("BoxGroup::createBox");
    static const QColor colorTab[7] = {
        QColor(200,0,0,100),QColor(255,200,0,100),
        QColor(0,0,200,100),QColor(0,200,0,100),
        QColor(0,200,255,100),QColor(200,0,255,100),
        QColor(150,100,100,100)
    };
    int shapeID = shape;
    if(shape == RandomShape){
        //shapeID --> 0-6
        shapeID = qrand()%7;
    }

    QColor color = colorTab[shapeID];
    QList<OneBox *> list;

    //恢复方块组的恢复矩阵
    setTransform(oldTransform);

    for(int i=0;i<4;i++){
        OneBox *temp = new OneBox(color);
        list.append(temp);
        addToGroup(temp);
    }

    switch (shapeID) {
    case IShape:
        currentShape = IShape;
        list.at(0)->setPos(-30,-10);
        list.at(1)->setPos(-10,-10);
        list.at(2)->setPos(10,-10);
        list.at(3)->setPos(30,-10);
        break;

    case JShape:
        currentShape = JShape;
        list.at(0)->setPos(10,-10);
        list.at(1)->setPos(10,10);
        list.at(2)->setPos(10,30);
        list.at(3)->setPos(-10,30);
        break;

    case LShape:
        currentShape = LShape;
        list.at(0)->setPos(-10,-10);
        list.at(1)->setPos(-10,10);
        list.at(2)->setPos(-10,30);
        list.at(3)->setPos(10,30);
        break;

    case OShape:
        currentShape = OShape;
        list.at(0)->setPos(-10,-10);
        list.at(1)->setPos(10,-10);
        list.at(2)->setPos(-10,10);
        list.at(3)->setPos(10,10);
        break;

    case SShape:
        currentShape = SShape;
        list.at(0)->setPos(10,-10);
        list.at(1)->setPos(30,-10);
        list.at(2)->setPos(-10,10);
        list.at(3)->setPos(10,10);
        break;

    case TShape:
        currentShape = TShape;
        list.at(0)->setPos(-10,-10);
        list.at(1)->setPos(10,-10);
        list.at(2)->setPos(30,10);
        list.at(3)->setPos(10,10);
        break;

    case ZShape:
        currentShape = ZShape;
        list.at(0)->setPos(-10,-10);
        list.at(1)->setPos(10,-10);
        list.at(2)->setPos(10,10);
        list.at(3)->setPos(30,10);
        break;

    default:
        break;
    }

    setPos(point);
    //如果在创建groupBox时
    if(isColliding()){
        stopTimer();
        emit gameFinished();
    }

}

void BoxGroup::clearBoxGroup(bool destroyBox)
{
    QList<QGraphicsItem *> itemList = childItems();
    QGraphicsItem *item;
    foreach (item, itemList) {
        removeFromGroup(item);
        if(destroyBox){
            OneBox *box = (OneBox*)item;
            box->deleteLater();
        }
    }
}

void BoxGroup::moveOneStep()
{
    moveBy(0,20);
    //向下移动一步之后发生碰撞，说明方块已经接触到底部了
    if(isColliding()){
        moveBy(0,-20);
        clearBoxGroup();
        emit needNewBox();
    }
}

void BoxGroup::startTimer(int interval)
{
    timer->start(interval);
}

void BoxGroup::stopTimer()
{
    timer->stop();
}

void BoxGroup::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<tr("BoxGroup keyPressEvent");
    switch(event->key())
    {
        case Qt::Key_Down:
            moveBy(0,20);
            if(isColliding()){
                //发生碰撞说明已经接触底部了
                moveBy(0,-20);
                //将小方块从方块组中移到场景中
                clearBoxGroup();
                //显示新的方块
                emit needNewBox();
            }
            break;

        case Qt::Key_Left:
            moveBy(-20,0);
            if(isColliding()){
                moveBy(20,0);
            }
            break;

        case Qt::Key_Right:
            moveBy(20,0);
            if(isColliding()){
                moveBy(-20,0);
            }
            break;

        //UP实现旋转
        case Qt::Key_Up:
            rotate(90.0);
            if(isColliding()){
                rotate(-90.0);
            }
            break;

        //空格实现下坠
        case Qt::Key_Space:
            moveBy(0,20);
            while(! isColliding()){
                moveBy(0,20);
            }
            //跳出循环说明已经检测到碰撞，需要回退一次
            moveBy(0,-20);
            clearBoxGroup();
            //emit 仅仅是标识
            emit needNewBox();
            break;
    }
}
