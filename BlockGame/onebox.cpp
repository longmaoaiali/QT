#include "onebox.h"
#include <QPainter>

OneBox::OneBox(const QColor &color):brushColor(color)
{

}

QRectF OneBox::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10-penWidth/2, -10-penWidth/2,20+penWidth,20+penWidth);
}

void OneBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //为小方块贴图
    painter->drawPixmap(-10,-10,20,20,QPixmap(":/myImage/images/box.gif"));
    painter->setBrush(brushColor);
    QColor penColor = brushColor;

    //减小颜色透明度
    penColor.setAlpha(20);
    painter->setPen(penColor);
    painter->drawRect(-10,-10,20,20);
}

QPainterPath OneBox::shape() const
{
    QPainterPath path;
    //形状比边框矩形小0.5,所以方框组的小方块才不会发生碰撞
    path.addRect(-9.5,-9.5,19,19);
    return path;
}





