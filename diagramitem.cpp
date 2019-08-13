#include "diagramitem.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "toolbar.h"

DiagramItem::DiagramItem(QPointF* tl, QPointF* br): topLeft{*tl}, bottomRight{*br}{

}

DiagramItem::DiagramItem(int tlX,int tlY,int brX,int brY): topLeft{QPointF(tlX,tlY)}, bottomRight{QPointF(brX, brY)} {

}

DiagramItem::DiagramItem(){

}

DiagramItem::~DiagramItem(){

}

void DiagramItem::setBoundingRect(QRectF* newRectangle){
    topLeft = newRectangle->topLeft();
    bottomRight = newRectangle->bottomRight();
}

void DiagramItem::setBoundingRect(QPointF* tl, QPointF* br){
    topLeft = *tl;
    bottomRight = *br;
}

QRectF DiagramItem::boundingRect() const{
            return QRectF(topLeft, bottomRight);

}



// overriding paint()
void DiagramItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
//    borderColor.setBrush(Qt::black);

//    color.setPen(Qt::black);
//    borderColor.setWidth(1);

    painter->setPen(Qt::darkRed);
    painter->setBrush(Qt::darkGray);
    //painter->drawRect(boundingRect());
    //painter->drawArc(boundingRect());



}


void DiagramItem::mouseDoublePressEvent(){

}


void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    Pressed = true;
    //check if it touches any of the resize points if so, change mode to resize, else select
    //if()

    if(event->pos().x() < 10 && event->pos().x() > 5 && event->pos().y() < 10 && event->pos().y() > 5){

    }



}
void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //on resize check which point is selected, move on:
    // *x&y *y  *x&y
    // *x       *x
    // *x&y *y  *x&y
}
void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    Pressed = false;
    state = Selected;
    setHandles();

}
void DiagramItem::setHandles(){


    // ?
    setHandlesChildEvents(true);
}

void DiagramItem::prepareGeometryChange(){
    QGraphicsItem::prepareGeometryChange();
}

