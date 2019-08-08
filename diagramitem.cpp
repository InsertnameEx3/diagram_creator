#include "diagramitem.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


DiagramItem::DiagramItem(QPointF* tl, QPointF* br): topLeft{*tl}, bottomRight{*br}{

}

DiagramItem::~DiagramItem(){

}

QRectF DiagramItem::boundingRect() const{
            return QRectF(topLeft, bottomRight);
}



// overriding paint()
void DiagramItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->drawRect(boundingRect());
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
