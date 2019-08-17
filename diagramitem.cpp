#include "diagramitem.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "toolbar.h"
#include <QDebug>

#include "handle.h"
#include "handles.h"
#include <QGraphicsWidget>
DiagramItem::DiagramItem(QPointF* tl, QPointF* br): topLeft{*tl}, bottomRight{*br}, handles{*new Handles(this)}{

    borderColor = QPen(Qt::black, 5);
    color = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
}

DiagramItem::DiagramItem(int tlX,int tlY,int brX,int brY): topLeft{QPointF(tlX,tlY)}, bottomRight{QPointF(brX, brY)}, handles{*new Handles(this)} {
    borderColor = QPen(Qt::black, 5);
    color = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
}

DiagramItem::DiagramItem(): handles{*new Handles(this)}{
    borderColor = QPen(Qt::black, 5);
    color = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);

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
    qDebug() << topLeft;
}

void DiagramItem::setBoundingRect(QPointF* tl, QPointF* br){
    this->prepareGeometryChange();
    qDebug() << *tl;
    topLeft = *tl;
    bottomRight = *br;
    this->update();
    //if(handles.length() != 0)
        //handles.recalculate(*tl);
}

void DiagramItem::setBoundingRect(QPointF tl, QPointF br){
    this->prepareGeometryChange();
    qDebug() << QRectF(tl, br).height();
    qDebug() << QRectF(tl, br).width();
    if(QRectF(tl, br).height() >= 50){
        topLeft.setY(tl.y());
        bottomRight.setY(br.y());
    }
    if(QRectF(tl, br).width() >= 100){
        topLeft.setX(tl.x());
        bottomRight.setX(br.x());
    }

    this->update();
    qDebug() << tl;

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



QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    qDebug() << handles;

    qDebug() << "fllaaa";
    //prepareGeometryChange();


    if (change == QGraphicsItem::ItemSelectedChange)
    {
        qDebug() << change;
        if (value == true)
        {


            if(!handles.changed){
                auto handleSize = 15.0;

                            handles.append(new Handle(QPointF(
                                                    this->boundingRect().topLeft() - QPointF(handleSize, handleSize)),
                                                    QPointF(
                                                    this->boundingRect().topLeft())
                                                    , Handle::TopLeft, this));
                            handles.append(new Handle(QPointF(
                                                    this->boundingRect().topLeft() + ((this->boundingRect().topRight() - this->boundingRect().topLeft())/2)) - QPointF(handleSize/2,0),
                                                    QPointF(
                                                    this->boundingRect().topLeft() + ((this->boundingRect().topRight() - this->boundingRect().topLeft())/2)) + QPointF(handleSize/2,-handleSize)
                                                    , Handle::Top, this));
                            handles.append(new Handle(QPointF(this->boundingRect().topRight()), QPointF(this->boundingRect().topRight() +  QPointF(handleSize,-handleSize))
                                                    , Handle::TopRight, this));
                            handles.append(new Handle(QPointF(
                                                        this->boundingRect().topLeft() + ((this->boundingRect().bottomLeft() - this->boundingRect().topLeft())/2)) - QPointF(handleSize, handleSize/2),
                                                        QPointF(
                                                        this->boundingRect().topLeft() + ((this->boundingRect().bottomLeft() - this->boundingRect().topLeft())/2)) + QPointF(0, handleSize/2)
                                                        , Handle::Left, this));
                            handles.append(new Handle(QPointF(
                                                        this->boundingRect().topRight() + ((this->boundingRect().bottomRight() - this->boundingRect().topRight())/2)) - QPointF(0, handleSize/2),
                                                        QPointF(
                                                        this->boundingRect().topRight() + ((this->boundingRect().bottomRight() - this->boundingRect().topRight())/2)) + QPointF(handleSize, handleSize/2)
                                                        , Handle::Right, this));
                            handles.append(new Handle(QPointF(this->boundingRect().bottomLeft() - QPointF(handleSize,-handleSize)), QPointF(this->boundingRect().bottomLeft())
                                                    , Handle::BottomLeft, this));
                            handles.append(new Handle(QPointF(
                                                        this->boundingRect().bottomLeft() + ((this->boundingRect().bottomRight() - this->boundingRect().bottomLeft())/2)) - QPointF(handleSize/2,0),
                                                        QPointF(
                                                        this->boundingRect().bottomLeft() + ((this->boundingRect().bottomRight() - this->boundingRect().bottomLeft())/2)) + QPointF(handleSize/2,handleSize)
                                                        , Handle::Bottom, this));
                            handles.append(new Handle(QPointF(this->boundingRect().bottomRight()), QPointF(this->boundingRect().bottomRight() + QPointF(handleSize,handleSize))
                                                    , Handle::BottomRight, this));

                handles.setAcceptHoverEvents(true);
                handles.setAcceptTouchEvents(true);
                handles.setAcceptedMouseButtons(Qt::LeftButton);
                handles.addToScene(scene());
                //handles.recalculate();
                handles.changed = true;
            }



            handles.show();


            this->update();
            scene()->update();





            this->borderColor.setStyle(Qt::DashLine);
            //this->color = Qt::blue;
        }
        else
        {
                //handles.update();
                handles.hide();
                scene()->update();
                this->borderColor.setStyle(Qt::SolidLine);

                this->update();
                scene()->update();






            this->update();


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


