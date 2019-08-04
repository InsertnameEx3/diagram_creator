#include "diagramitem.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


DiagramItem::DiagramItem()
{

}
DiagramItem::~DiagramItem(){

}
QRectF DiagramItem::boundingRect() const{

}

QRectF DiagramItem::boundingRect(QPointF topLeft, QPointF bottomRight) const
{
    return QRectF(topLeft, bottomRight);
}

// overriding paint()
void DiagramItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPointF tl(0,0);
    QPointF br(0,0);
    QRectF rect = boundingRect(tl,br);
    if(Pressed)
    {
        QPen pen(Qt::red, 3);
        painter->setPen(pen);
        painter->drawEllipse(rect);
    }
    else
    {
        QPen pen(Qt::black, 3);
        painter->setPen(pen);
        painter->drawRect(rect);
    }
}


void DiagramItem::mouseDoublePressEvent(){

}


void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    Pressed = true;
    //check if it touches any of the resize points if so, change mode to resize, else select
    //if()
    event->pos().x();
    event->pos().y();

}
void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //on resize check which point is selected, move on:
    // *x&y *y  *x&y
    // *x       *x
    // *x&y *y  *x&y
}
void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    Pressed = false;
}
void DiagramItem::PrepareGeometryChange(){
    this->prepareGeometryChange();
}
