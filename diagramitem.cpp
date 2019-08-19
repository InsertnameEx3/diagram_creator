#include "diagramitem.h"
#include <QPen>
#include "mainwindow.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "toolbar.h"
#include <QDebug>

#include "handle.h"
#include "handles.h"
#include <QGraphicsWidget>
DiagramItem::DiagramItem(QPointF* tl, QPointF* br): topLeft{*tl}, bottomRight{*br}, handles{*new Handles(this)}{
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

DiagramItem::DiagramItem(int tlX,int tlY,int brX,int brY): topLeft{QPointF(tlX,tlY)}, bottomRight{QPointF(brX, brY)}, handles{*new Handles(this)} {
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

DiagramItem::DiagramItem(): handles{*new Handles(this)}{
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);

    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

DiagramItem::~DiagramItem(){

}

void DiagramItem::setBoundingRect(QRectF* newRectangle){
    this->prepareGeometryChange();
    topLeft = newRectangle->topLeft();
    bottomRight = newRectangle->bottomRight();
    this->update();
    qDebug() << topLeft;
}

void DiagramItem::setBoundingRect(QRectF newRectangle){
    this->prepareGeometryChange();
    topLeft = newRectangle.topLeft();
    bottomRight = newRectangle.bottomRight();
    this->update();
}

void DiagramItem::setBoundingRect(QPointF* tl, QPointF* br){
    this->prepareGeometryChange();
    topLeft = *tl;
    bottomRight = *br;
    this->update();
}

void DiagramItem::setBoundingRect(QPointF tl, QPointF br){
    this->prepareGeometryChange();
    switch(handles.handleType){
    case Handles::eightHandles:
        if(QRectF(tl, br).height() >= 50){
            topLeft.setY(tl.y());
            bottomRight.setY(br.y());
        }
        if(QRectF(tl, br).width() >= 100){
            topLeft.setX(tl.x());
            bottomRight.setX(br.x());
        }
        break;
    case Handles::twoHandles:
        topLeft = tl;
        bottomRight = br;
        break;
    }
    this->update();
}

void DiagramItem::setLine(QPointF tl, QPointF br){
    this->prepareGeometryChange();
    topLeft = tl;
    bottomRight = br;
    this->update();
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
    //setHandles();
    QGraphicsItem::mouseReleaseEvent(event);
}


void DiagramItem::prepareGeometryChange(){
    QGraphicsItem::prepareGeometryChange();
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value){

    if (change == QGraphicsItem::ItemSelectedChange)
    {
        qDebug() << change;
        if (value == true)
        {

            handles.handleType = handles.eightHandles;

            qDebug() << "sha";
            if(!handles.changed){


                handles.recalculate();
                //auto handleSize = 15.0;

                handles.setAcceptHoverEvents(true);
                handles.setAcceptTouchEvents(true);
                handles.setAcceptedMouseButtons(Qt::LeftButton);
                handles.addToScene(scene());
                handles.changed = true;


            }

            handles.show();

            this->update();
            scene()->update();


            //this->color = Qt::blue;
        }
        else
        {

                handles.hide();
                this->update();
                scene()->update();

            // do stuff if not selected
        }
    }
    if (change == QGraphicsItem::ItemPositionChange){

        //handles.recalculate();

        handles.setPos(value.toPoint());

        scene()->update();
        this->update();
    }
    if(change == QGraphicsItem::ItemScaleChange){

        //handles.recalculate();
    }

    return QGraphicsItem::itemChange(change, value);


}


