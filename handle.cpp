#include "handle.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>







Handle::Handle(QPointF* tl, QPointF* br, HandleType type, DiagramItem* p): QGraphicsItem(), parent{p}{

    form = this->Rounded;
    topLeft = *tl;

    bottomRight = *br;
    borderColor = QPen(Qt::black);
    color = Qt::white;

    handleType = type;
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

Handle::Handle(QPointF tl, QPointF br, HandleType type, DiagramItem* p): QGraphicsItem(), parent{p}{
    form = this->Rounded;





    setBoundingRect(&tl,&br);
    borderColor = QPen(Qt::black);
     color = Qt::white;

    topLeft = tl;

    bottomRight = br;

    handleType = type;
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

Handle::~Handle(){

}

void Handle::recalculate(QPointF* tl, QPointF* br){
    topLeft = *tl;

    bottomRight = *br;
}

void Handle::recalculate(QPointF tl, QPointF br){
    topLeft = tl;
    bottomRight = br;
}

void Handle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    auto borderColor = QBrush(Qt::black);
    auto borderWidth = 3;
    auto border = QPen(borderColor, borderWidth);

    painter->setPen(border);
    painter->setBrush(color);

    switch(this->form){
    case Handle::Rounded:
        painter->drawEllipse(boundingRect());
        break;
    case Handle::Squared:
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

void Handle::setBoundingRect(QPointF tl, QPointF br){
    topLeft = tl;
    bottomRight = br;
}

QRectF Handle::boundingRect() const{
    return QRectF(topLeft, bottomRight);
};

void Handle::mousePressEvent(QGraphicsSceneMouseEvent* event){
    parent->prepareGeometryChange();
    this->prepareGeometryChange();
    switch(parent->handles.handleType){
        case Handles::twoHandles:
//        switch(handleType){
//            case TopLeft:
//                //set boundingrect according to event position and recalculate the handles
//                parent->setBoundingRect(event->pos(), parent->boundingRect().bottomRight());
//                parent->handles.recalculate();
//                break;
//            case BottomRight:
//                parent->setBoundingRect(parent->boundingRect().topLeft(), event->pos());
//                parent->handles.recalculate();
//                break;

//                }
//            break;
        case Handles::eightHandles:
            switch(handleType){
                case TopLeft:
                    //set boundingrect according to event position and recalculate the handles
                    parent->setBoundingRect(event->pos(), parent->boundingRect().bottomRight());
                    parent->handles.recalculate();
                    break;
                case Top:
                    parent->setBoundingRect(QPointF(parent->boundingRect().topLeft().x(), event->pos().y()), parent->boundingRect().bottomRight());
                    parent->handles.recalculate();
                    break;
                case TopRight:
                    parent->setBoundingRect(QPointF(parent->boundingRect().topLeft().x(), event->pos().y()), QPointF(event->pos().x(), parent->boundingRect().bottomRight().y()));
                    parent->handles.recalculate();
                    break;
                case Left:
                    parent->setBoundingRect(QPointF(event->pos().x(), parent->boundingRect().topLeft().y()), parent->boundingRect().bottomRight());
                    parent->handles.recalculate();
                    break;
                case Right:
                    parent->setBoundingRect(parent->boundingRect().topLeft(), QPointF(event->pos().x(), parent->boundingRect().bottomRight().y()));
                    parent->handles.recalculate();
                    break;
                case BottomLeft:
                parent->setBoundingRect(QPointF(event->pos().x(), parent->boundingRect().topLeft().y()), QPointF(parent->boundingRect().bottomRight().x(), event->pos().y()));
                parent->handles.recalculate();
                    break;
                case Bottom:
                    parent->setBoundingRect(parent->boundingRect().topLeft(), QPointF(parent->boundingRect().bottomRight().x(), event->pos().y()));
                    parent->handles.recalculate();
                    break;
                case BottomRight:
                    parent->setBoundingRect(parent->boundingRect().topLeft(), event->pos());
                    parent->handles.recalculate();
                    break;
            }
            break;
    }

    parent->update();
    parent->scene()->update();
    this->update();
    //QGraphicsItem::mousePressEvent(event);
}

void Handle::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    parent->prepareGeometryChange();
    this->prepareGeometryChange();
    parent->handles.setOpacity(0);
    switch(handleType){
        case TopLeft:
            //set boundingrect according to event position and recalculate the handles
            parent->setBoundingRect(event->pos(), parent->boundingRect().bottomRight());
            parent->handles.recalculate();
            break;
        case Top:
            parent->setBoundingRect(QPointF(parent->boundingRect().topLeft().x(), event->pos().y()), parent->boundingRect().bottomRight());
            parent->handles.recalculate();
            break;
        case TopRight:
            parent->setBoundingRect(QPointF(parent->boundingRect().topLeft().x(), event->pos().y()), QPointF(event->pos().x(), parent->boundingRect().bottomRight().y()));
            parent->handles.recalculate();
            break;
        case Left:
            parent->setBoundingRect(QPointF(event->pos().x(), parent->boundingRect().topLeft().y()), parent->boundingRect().bottomRight());
            parent->handles.recalculate();
            break;
        case Right:
            parent->setBoundingRect(parent->boundingRect().topLeft(), QPointF(event->pos().x(), parent->boundingRect().bottomRight().y()));
            parent->handles.recalculate();
            break;
        case BottomLeft:
        parent->setBoundingRect(QPointF(event->pos().x(), parent->boundingRect().topLeft().y()), QPointF(parent->boundingRect().bottomRight().x(), event->pos().y()));
        parent->handles.recalculate();
            break;
        case Bottom:
            parent->setBoundingRect(parent->boundingRect().topLeft(), QPointF(parent->boundingRect().bottomRight().x(), event->pos().y()));
            parent->handles.recalculate();
            break;
        case BottomRight:
            parent->setBoundingRect(parent->boundingRect().topLeft(), event->pos());
            parent->handles.recalculate();
            break;
    }


    parent->update();
    parent->scene()->update();
    this->update();

    //QGraphicsItem::mouseMoveEvent(event);
}

void Handle::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    parent->handles.setOpacity(100);
//    parent->stackBefore(parent->handles.at(0));
//    parent->stackBefore(parent->handles.at(1));
//    parent->stackBefore(parent->handles.at(2));
//    parent->stackBefore(parent->handles.at(3));
//    parent->stackBefore(parent->handles.at(4));
//    parent->stackBefore(parent->handles.at(5));
//    parent->stackBefore(parent->handles.at(6));
//    parent->stackBefore(parent->handles.at(7));

    parent->update();
    parent->scene()->update();
    this->update();
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

