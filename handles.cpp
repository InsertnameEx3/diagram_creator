#include "handles.h"
#include "handle.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsLayout>





Handles::Handles(DiagramItem* p, Types type, double size): parent{p}, handleType{type}, handleSize{size}{

    switch (type) {
        case eightHandles:
        {

            this->append(new Handle(QPointF(
                                    p->boundingRect().topLeft()),
                                    QPointF(
                                    p->boundingRect().topLeft())
                                    , Handle::TopLeft, *p));
            this->append(new Handle(QPointF(
                                    p->boundingRect().topLeft() + ((p->boundingRect().topRight() - p->boundingRect().topLeft())/2)) - QPointF(handleSize/2,0),
                                    QPointF(
                                    p->boundingRect().topLeft() + ((p->boundingRect().topRight() - p->boundingRect().topLeft())/2)) + QPointF(handleSize/2,-handleSize)
                                    , Handle::Top, *p));
            this->append(new Handle(QPointF(p->boundingRect().topRight()), QPointF(p->boundingRect().topRight() +  QPointF(handleSize,-handleSize))
                                    , Handle::TopRight, *p));
            this->append(new Handle(QPointF(
                                        p->boundingRect().topLeft() + ((p->boundingRect().bottomLeft() - p->boundingRect().topLeft())/2)) - QPointF(handleSize, handleSize/2),
                                        QPointF(
                                        p->boundingRect().topLeft() + ((p->boundingRect().bottomLeft() - p->boundingRect().topLeft())/2)) + QPointF(0, handleSize/2)
                                        , Handle::Left, *p));
            this->append(new Handle(QPointF(
                                        p->boundingRect().topRight() + ((p->boundingRect().bottomRight() - p->boundingRect().topRight())/2)) - QPointF(0, handleSize/2),
                                        QPointF(
                                        p->boundingRect().topRight() + ((p->boundingRect().bottomRight() - p->boundingRect().topRight())/2)) + QPointF(handleSize, handleSize/2)
                                        , Handle::Right, *p));
            this->append(new Handle(QPointF(p->boundingRect().bottomLeft() - QPointF(handleSize,-handleSize)), QPointF(p->boundingRect().bottomLeft())
                                    , Handle::BottomLeft, *p));
            this->append(new Handle(QPointF(
                                        p->boundingRect().bottomLeft() + ((p->boundingRect().bottomRight() - p->boundingRect().bottomLeft())/2)) - QPointF(handleSize/2,0),
                                        QPointF(
                                        p->boundingRect().bottomLeft() + ((p->boundingRect().bottomRight() - p->boundingRect().bottomLeft())/2)) + QPointF(handleSize/2,handleSize)
                                        , Handle::Bottom, *p));
            this->append(new Handle(QPointF(p->boundingRect().bottomRight()), QPointF(p->boundingRect().bottomRight() + QPointF(handleSize,handleSize))
                                    , Handle::BottomRight, *p));
        }
            break;
        case twoHandles:
        {

        }
            break;

    }






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

void Handles::updateHandles(){


    switch (handleType) {
    case eightHandles:
        //this->first()->setPos(this->boundingRect().topLeft() - QPointF(handleSize, handleSize));
//        this[0].setPos(this->boundingRect().topLeft() - QPointF(handleSize, handleSize));
//        this[1].setPos(this->boundingRect().topLeft() + ((this->boundingRect().topRight() - this->boundingRect().topLeft())/2));
//        this[2].setPos(this->boundingRect().topRight());
//        this[3].setPos(this->boundingRect().topLeft() + ((this->boundingRect().bottomLeft() - this->boundingRect().topLeft())/2));
//        this[4].setPos(this->boundingRect().topRight() + ((this->boundingRect().bottomRight() - this->boundingRect().topRight())/2));
//        this[5].setPos(this->boundingRect().bottomLeft() - QPointF(handleSize,-handleSize));
//        this[6].setPos(this->boundingRect().bottomLeft() + ((this->boundingRect().bottomRight() - this->boundingRect().bottomLeft())/2));
//        this[7].setPos(this->boundingRect().bottomRight());
        break;
    case twoHandles:
        break;

    }

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
    qDebug() << parent->boundingRect();
    switch (handleType) {
        case eightHandles:
        {
            //this->erase(this->begin(), this->end());




        }
            break;
        case twoHandles:
        {

        }
            break;

    }


    this->replace(0, new Handle(QPointF(
                            parent->boundingRect().topLeft()),
                            QPointF(
                            parent->boundingRect().topLeft())
                            , Handle::TopLeft, *parent));

    this->replace(1, new Handle(QPointF(
                            parent->boundingRect().topLeft() + ((parent->boundingRect().topRight() - parent->boundingRect().topLeft())/2)) - QPointF(handleSize/2,0),
                            QPointF(
                            parent->boundingRect().topLeft() + ((parent->boundingRect().topRight() - parent->boundingRect().topLeft())/2)) + QPointF(handleSize/2,-handleSize)
                            , Handle::Top, *parent));



    this->replace(2, new Handle(QPointF(parent->boundingRect().topRight()), QPointF(parent->boundingRect().topRight() +  QPointF(handleSize,-handleSize))
                        , Handle::TopRight, *parent));


    this->replace(3, new Handle(QPointF(
                             parent->boundingRect().topLeft() + ((parent->boundingRect().bottomLeft() - parent->boundingRect().topLeft())/2)) - QPointF(handleSize, handleSize/2),
                             QPointF(
                             parent->boundingRect().topLeft() + ((parent->boundingRect().bottomLeft() - parent->boundingRect().topLeft())/2)) + QPointF(0, handleSize/2)
                             , Handle::Left, *parent));

    this->replace(4, new Handle(QPointF(
                            parent->boundingRect().topRight() + ((parent->boundingRect().bottomRight() - parent->boundingRect().topRight())/2)) - QPointF(0, handleSize/2),
                            QPointF(
                            parent->boundingRect().topRight() + ((parent->boundingRect().bottomRight() - parent->boundingRect().topRight())/2)) + QPointF(handleSize, handleSize/2)
                            , Handle::Right, *parent));

    this->replace(5, new Handle(QPointF(parent->boundingRect().bottomLeft() - QPointF(handleSize,-handleSize)), QPointF(parent->boundingRect().bottomLeft())
                         , Handle::BottomLeft, *parent));
    this->replace(6, new Handle(QPointF(
                            parent->boundingRect().bottomLeft() + ((parent->boundingRect().bottomRight() - parent->boundingRect().bottomLeft())/2)) - QPointF(handleSize/2,0),
                            QPointF(
                            parent->boundingRect().bottomLeft() + ((parent->boundingRect().bottomRight() - parent->boundingRect().bottomLeft())/2)) + QPointF(handleSize/2,handleSize)
                            , Handle::Bottom, *parent));
    this->replace(7, new Handle(QPointF(parent->boundingRect().bottomRight()), QPointF(parent->boundingRect().bottomRight() + QPointF(handleSize,handleSize))
                         , Handle::BottomRight, *parent));

    //this->addToScene(parent->scene());
    for(auto handle : *this){
        handle->update();
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

    //this->update();
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
