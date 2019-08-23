#include "handles.h"
#include "handle.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsLayout>




double Handles::handleSize;
Handles::Handles(DiagramItem* p, Types type, double size): parent{p}, handleType{type}{
    const double handleSize = size;
    setHandleSize(size);
    switch (this->handleType) {
    case Handles::twoHandles:

        this->append(new Handle(QPointF(
                                parent->boundingRect().topLeft() - QPointF(handleSize/2, handleSize/2)),
                                QPointF(
                                parent->boundingRect().topLeft())
                                , Handle::TopLeft, parent));
        this->append(new Handle(QPointF(parent->boundingRect().bottomRight()), QPointF(parent->boundingRect().bottomRight() + QPointF(handleSize,handleSize))
                                , Handle::BottomRight, parent));

        break;
    case Handles::eightHandles:

        this->append(new Handle(QPointF(
                                parent->boundingRect().topLeft() - QPointF(handleSize/2, handleSize/2)),
                                QPointF(
                                parent->boundingRect().topLeft()) + QPointF(handleSize/2, handleSize/2)
                                , Handle::TopLeft, parent));
        this->append(new Handle(QPointF(
                                parent->boundingRect().topLeft() + ((parent->boundingRect().topRight() - parent->boundingRect().topLeft())/2)) - QPointF(handleSize/2,0),
                                QPointF(
                                parent->boundingRect().topLeft() + ((parent->boundingRect().topRight() - parent->boundingRect().topLeft())/2)) + QPointF(handleSize/2,-handleSize)
                                , Handle::Top, parent));
        this->append(new Handle(QPointF(parent->boundingRect().topRight()), QPointF(parent->boundingRect().topRight() +  QPointF(handleSize,-handleSize))
                                , Handle::TopRight, parent));
        this->append(new Handle(QPointF(
                                    parent->boundingRect().topLeft() + ((parent->boundingRect().bottomLeft() - parent->boundingRect().topLeft())/2)) - QPointF(handleSize, handleSize/2),
                                    QPointF(
                                    parent->boundingRect().topLeft() + ((parent->boundingRect().bottomLeft() - parent->boundingRect().topLeft())/2)) + QPointF(0, handleSize/2)
                                    , Handle::Left, parent));
        this->append(new Handle(QPointF(
                                    parent->boundingRect().topRight() + ((parent->boundingRect().bottomRight() - parent->boundingRect().topRight())/2)) - QPointF(0, handleSize/2),
                                    QPointF(
                                    parent->boundingRect().topRight() + ((parent->boundingRect().bottomRight() - parent->boundingRect().topRight())/2)) + QPointF(handleSize, handleSize/2)
                                    , Handle::Right, parent));
        this->append(new Handle(QPointF(parent->boundingRect().bottomLeft() - QPointF(handleSize,-handleSize)), QPointF(parent->boundingRect().bottomLeft())
                                , Handle::BottomLeft, parent));
        this->append(new Handle(QPointF(
                                    parent->boundingRect().bottomLeft() + ((parent->boundingRect().bottomRight() - parent->boundingRect().bottomLeft())/2)) - QPointF(handleSize/2,0),
                                    QPointF(
                                    parent->boundingRect().bottomLeft() + ((parent->boundingRect().bottomRight() - parent->boundingRect().bottomLeft())/2)) + QPointF(handleSize/2,handleSize)
                                    , Handle::Bottom, parent));
        this->append(new Handle(QPointF(parent->boundingRect().bottomRight()), QPointF(parent->boundingRect().bottomRight() + QPointF(handleSize,handleSize))
                                , Handle::BottomRight, parent));

    break;
    }

    changed = false;

}
Handles::~Handles(){
    //QGraphicsLayout
}

void Handles::setBoundingRect(QRectF* r){
    qDebug() << "blaaa";
    //rect = r;
    //parent->setBoundingRect(r);
}
void Handles::setBoundingRect(QPointF tl, QPointF br){
    qDebug() << "blaaa";
    //rect = new QRectF(tl,br);
    //parent->setBoundingRect(new QRectF(tl,br));
}



QRectF Handles::boundingRect() const{
    return parent->boundingRect();
}
void Handles::resize(){

}

void Handles::setPos(QPointF point){
    for(auto handle : *this){
        handle->setPos(point);
    }
}

void Handles::recalculate(){
    changed = true;
    const double handleSize = this->getHandleSize();
    switch (handleType) {
        case eightHandles:
        {
            this->at(0)->recalculate(QPointF(
                                    parent->boundingRect().topLeft() - QPointF(handleSize/2, handleSize/2)),
                                    QPointF(
                                    parent->boundingRect().topLeft()) + QPointF(handleSize/2, handleSize/2));

            this->at(1)->recalculate(QPointF(
                                          parent->boundingRect().topLeft() + ((parent->boundingRect().topRight() - parent->boundingRect().topLeft())/2)) - QPointF(handleSize/2,handleSize/2),
                                          QPointF(
                                          parent->boundingRect().topLeft() + ((parent->boundingRect().topRight() - parent->boundingRect().topLeft())/2)) + QPointF(handleSize/2,handleSize/2));

            this->at(2)->recalculate(QPointF(parent->boundingRect().topRight()) - QPointF(handleSize/2,handleSize/2), QPointF(parent->boundingRect().topRight() +  QPointF(handleSize/2,handleSize/2))
                                      );

            this->at(3)->recalculate(QPointF(
                                         parent->boundingRect().topLeft() + ((parent->boundingRect().bottomLeft() - parent->boundingRect().topLeft())/2)) - QPointF(handleSize/2, handleSize/2),
                                         QPointF(
                                         parent->boundingRect().topLeft() + ((parent->boundingRect().bottomLeft() - parent->boundingRect().topLeft())/2)) + QPointF(handleSize/2, handleSize/2)
                                         );

            this->at(4)->recalculate(QPointF(
                                         parent->boundingRect().topRight() + ((parent->boundingRect().bottomRight() - parent->boundingRect().topRight())/2)) - QPointF(handleSize/2, handleSize/2),
                                         QPointF(
                                         parent->boundingRect().topRight() + ((parent->boundingRect().bottomRight() - parent->boundingRect().topRight())/2)) + QPointF(handleSize/2, handleSize/2)
                                         );

            this->at(5)->recalculate(QPointF(parent->boundingRect().bottomLeft() - QPointF(handleSize/2,handleSize/2)), QPointF(parent->boundingRect().bottomLeft()) + QPointF(handleSize/2,handleSize/2)
                                     );
            this->at(6)->recalculate(QPointF(
                                         parent->boundingRect().bottomLeft() + ((parent->boundingRect().bottomRight() - parent->boundingRect().bottomLeft())/2)) - QPointF(handleSize/2,handleSize/2),
                                         QPointF(
                                         parent->boundingRect().bottomLeft() + ((parent->boundingRect().bottomRight() - parent->boundingRect().bottomLeft())/2)) + QPointF(handleSize/2,handleSize/2)
                                         );

            this->at(7)->recalculate(QPointF(parent->boundingRect().bottomRight()) - QPointF(handleSize/2, handleSize/2), QPointF(parent->boundingRect().bottomRight() + QPointF(handleSize/2,handleSize/2)));

        }
            break;
        case twoHandles:
        {
            this->at(0)->recalculate(QPointF(
                                parent->boundingRect().topLeft() - QPointF(handleSize/2, handleSize/2)),
                                QPointF(
                                parent->boundingRect().topLeft()  + QPointF(handleSize/2, handleSize/2)));

             this->at(1)->recalculate(QPointF(parent->boundingRect().bottomRight() - QPointF(handleSize/2,handleSize/2)), QPointF(parent->boundingRect().bottomRight() + QPointF(handleSize/2,handleSize/2)));
        }
            break;

    }
}

void Handles::show(){
    for(auto handle : *this){
        handle->show();
    }
}

void Handles::hide(){
    for(auto handle : *this){
        handle->hide();
    }
}

void Handles::addToScene(QGraphicsScene* scene){
    for(auto handle : *this){
        scene->addItem(handle);
        handle->setFlags(QGraphicsItem::ItemIsMovable);
    }
}
void Handles::append(Handle *const &t){
    QList::append(t);
    this->update();
}
void Handles::update(){
    for(auto handle : *this){
        handle->update();
    }
}

void Handles::setAcceptHoverEvents(bool enabled){
    for(auto handle : *this){
        handle->setAcceptHoverEvents(enabled);
    }
}

void Handles::setAcceptedMouseButtons(Qt::MouseButtons buttons){
    for(auto handle: *this){
        handle->setAcceptedMouseButtons(buttons);
    }
}

void Handles::setAcceptTouchEvents(bool enabled){
    for(auto handle : *this){
        handle->setAcceptTouchEvents(enabled);
    }
}

void Handles::setOpacity(qreal opacity){
    for(auto handle : *this){
        handle->setOpacity(opacity);
    }
}

void Handles::setHandleSize(double size){

//    Handles::handleSize = size;
    //Handles::handleSize = size;
}

double Handles::getHandleSize(){
    //return Handles::handleSize;
    return 15;
}
