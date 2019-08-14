#include "handle.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>







Handle::Handle(QPointF* tl, QPointF* br, HandleType type, DiagramItem& p): QGraphicsItem(), parent{p}{

    form = this->Squared;
    topLeft = *tl;

    bottomRight = *br;
    borderColor = QPen(Qt::black);
    color = Qt::black;

    handleType = type;
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

Handle::Handle(QPointF tl, QPointF br, HandleType type, DiagramItem& p): QGraphicsItem(), parent{p}{
    form = this->Squared;
    setBoundingRect(&tl,&br);
    borderColor = QPen(Qt::black);
    color = Qt::black;

    topLeft = tl;

    bottomRight = br;

    handleType = type;
    this->setFlag(QGraphicsItem::ItemIsMovable);
}
Handle::~Handle(){

}

void Handle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(borderColor);
    painter->setBrush(color);

    switch(this->form){
    case 0:
        painter->drawEllipse(boundingRect());
        break;
    case 1:
        painter->drawRect(boundingRect());
        break;
    }
}

void Handle::setBoundingRect(QRectF* rect){
    topLeft = rect->topLeft();
    bottomRight = rect->bottomRight();
}
void Handle::setBoundingRect(QPointF* tl, QPointF* br){
    topLeft = *tl;
    bottomRight = *br;
}
QRectF Handle::boundingRect() const{
    return QRectF(topLeft, bottomRight);
};

void Handle::mousePressEvent(QGraphicsSceneMouseEvent* event){
    //event->accept();

    switch(handleType){
        case TopLeft:
            //this->setPos(event->pos());
            //parent.setBoundingRect(event->pos(), parent.boundingRect().bottomRight());

            //parent->update();
            break;
        case Top:
            break;
        case TopRight:
            break;
        case Left:
            break;
        case Right:
            break;
        case BottomLeft:
            break;
        case Bottom:
            break;
        case BottomRight:
            break;
    }
    //QGraphicsItem::mousePressEvent(event);

}

void Handle::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //qDebug() << parent;
    switch(handleType){
        case TopLeft:
            qDebug() << "topLeft";
            //this->setPos(event->pos());
            //parent.setBoundingRect(event->pos(), parent.boundingRect().bottomRight());


            //parent->update();
            break;
        case Top:
            break;
        case TopRight:
            break;
        case Left:
            break;
        case Right:
            break;
        case BottomLeft:
            break;
        case Bottom:
            break;
        case BottomRight:
            break;
    }

    //QGraphicsItem::mouseMoveEvent(event);
}
void Handle::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){

    switch(handleType){
        case TopLeft:
            //this->setPos(event->pos());
            //parent.setBoundingRect(event->pos(), parent.boundingRect().bottomRight());
            //parent->update();
            break;
        case Top:
            break;
        case TopRight:
            break;
        case Left:
            break;
        case Right:
            break;
        case BottomLeft:
            break;
        case Bottom:
            break;
        case BottomRight:
            break;
    }

    //QGraphicsItem::mouseReleaseEvent(event);
}


void Handle::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << event;
    switch(handleType){
        case TopLeft:
        case BottomRight:
            this->setCursor(Qt::SizeFDiagCursor);
            break;
        case Top:
        case Bottom:
        this->setCursor(Qt::SizeVerCursor);
            break;
        case TopRight:
        case BottomLeft:
            this->setCursor(Qt::SizeBDiagCursor);
            break;
        case Left:
        case Right:
            this->setCursor(Qt::SizeHorCursor);
            break;
    }
}


void Handle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->setCursor(Qt::ArrowCursor);
}

void Handle::setPos(QPointF point){
    this->prepareGeometryChange();

    //QGraphicsItem::moveBy(point.x(), point.y());
    qDebug() << point;
    QGraphicsItem::setPos(point);
    this->update();
    this->setFlags(QGraphicsItem::ItemIsMovable);
}

void Handle::setPos(QPointF* point){
    this->prepareGeometryChange();
    QGraphicsItem::setPos(*point);
    this->update();
    this->setFlags(QGraphicsItem::ItemIsMovable);
}

