#include "diagramitem.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "toolbar.h"
#include <QDebug>
DiagramItem::DiagramItem(QPointF* tl, QPointF* br): topLeft{*tl}, bottomRight{*br}{
    borderColor = QPen(Qt::black, 5);
    color = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
}

DiagramItem::DiagramItem(int tlX,int tlY,int brX,int brY): topLeft{QPointF(tlX,tlY)}, bottomRight{QPointF(brX, brY)} {
    borderColor = QPen(Qt::black, 5);
    color = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
}

DiagramItem::DiagramItem(){
    borderColor = QPen(Qt::black, 5);
    color = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
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

    QGraphicsItem::mousePressEvent(event);

}
void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //on resize check which point is selected, move on:
    // *x&y *y  *x&y
    // *x       *x
    // *x&y *y  *x&y
    QGraphicsItem::mouseMoveEvent(event);
}
void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    Pressed = false;
    state = Selected;
    setHandles();
    QGraphicsItem::mouseReleaseEvent(event);
}
void DiagramItem::setHandles(){

    DiagramItem* topLeftHandle = new Rectangle(new QPointF(this->topLeft - QPointF(5,5)), new QPointF(this->topLeft + QPointF(5,5)));

    this->childItems().append(topLeftHandle);
    scene()->addItem(topLeftHandle);
    scene()->update();
    this->update();
    // ?
    setHandlesChildEvents(true);
}

void DiagramItem::prepareGeometryChange(){
    QGraphicsItem::prepareGeometryChange();
}



QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    prepareGeometryChange();

    if (change == QGraphicsItem::ItemSelectedChange)
    {
        qDebug() << change;
        if (value == true)
        {
            handleSize = 15;
            this->setHandles();
            handles = {
                //syntax: qrectf(topLeft, bottomRight)
                QRectF(QPointF(this->boundingRect().topLeft() - QPointF(handleSize, handleSize)), QPointF(this->boundingRect().topLeft())),    //topleft

                QRectF(QPointF(
                this->boundingRect().topLeft() + ((this->boundingRect().topRight() - this->boundingRect().topLeft())/2)) - QPointF(handleSize/2,0),
                QPointF(
                this->boundingRect().topLeft() + ((this->boundingRect().topRight() - this->boundingRect().topLeft())/2)) + QPointF(handleSize/2,-handleSize)
                ),    //topmiddle

                QRectF(QPointF(this->boundingRect().topRight()), QPointF(this->boundingRect().topRight() +  QPointF(handleSize,-handleSize))),    //topright

                QRectF(QPointF(
                this->boundingRect().topLeft() + ((this->boundingRect().bottomLeft() - this->boundingRect().topLeft())/2)) - QPointF(handleSize, handleSize/2),
                QPointF(
                this->boundingRect().topLeft() + ((this->boundingRect().bottomLeft() - this->boundingRect().topLeft())/2)) + QPointF(0, handleSize/2)),    //middleleft

                QRectF(QPointF(
                this->boundingRect().topRight() + ((this->boundingRect().bottomRight() - this->boundingRect().topRight())/2)) - QPointF(0, handleSize/2),
                QPointF(
                this->boundingRect().topRight() + ((this->boundingRect().bottomRight() - this->boundingRect().topRight())/2)) + QPointF(handleSize, handleSize/2)),//middleright

                QRectF(QPointF(this->boundingRect().bottomLeft() - QPointF(handleSize,-handleSize)), QPointF(this->boundingRect().bottomLeft())),//bottomleft

                QRectF(QPointF(
                this->boundingRect().bottomLeft() + ((this->boundingRect().bottomRight() - this->boundingRect().bottomLeft())/2)) - QPointF(handleSize/2,0),
                QPointF(
                this->boundingRect().bottomLeft() + ((this->boundingRect().bottomRight() - this->boundingRect().bottomLeft())/2)) + QPointF(handleSize/2,handleSize)
                ),//bottommiddle

                QRectF(QPointF(this->boundingRect().bottomRight()), QPointF(this->boundingRect().bottomRight() + QPointF(handleSize,handleSize))),//bottomright
            };


            for(auto handle : handles){
                scene()->addRect(handle);
            }

            //scene()->addqgr);

            scene()->update();
            this->update();
            this->borderColor.setStyle(Qt::DashLine);
            //this->color = Qt::blue;
        }
        else
        {
            for(auto handle : handles){
                //scene()->removeItem(handle);

            }
            //scene()->removeItem(topLeftHandle);
            this->borderColor.setStyle(Qt::SolidLine);
            // do stuff if not selected
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
