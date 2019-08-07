#include "diagramscene.h"
#include <QPainter>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsView>
#include <QtDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QPointF>
#include <QPolygonF>
#include <QVector>

#include <QDebug>
#include <mainwindow.h>
#include <QApplication>
#include "toolbar.h"

Toolbar::SelectedItem Toolbar::selection;

DiagramScene::DiagramScene(QObject* parent)
{

    auto bpoint1 = QPointF(150 , 150);
            auto bpoint2 = QPointF(200 , 150);
            auto bpoint3 = QPointF(200 , 200);
            auto bpoint4 = QPointF(150 , 200);
            QVector<QPointF> t {bpoint1 , bpoint2 , bpoint3 , bpoint4};
            auto bproto = QPolygonF(t);
    this->addPolygon(t);


    //rect->setFlags(QGraphicsItem::ItemIsMovable);

}

DiagramScene::~DiagramScene(){
    //delete[] items;
    //delete origPoint;
    //delete itemToDraw;
}


void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawObject)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if(this->sceneMode == this->DrawObject){
        this->setMode(this->NoMode);
    }
    QGraphicsScene::mouseReleaseEvent(event);
    items.append(itemToDraw);
    // To avoid a dangling pointer:
    itemToDraw = nullptr;
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    this->clear();
    //itemToDraw->PrepareGeometryChange();
    if(!itemToDraw){
        itemToDraw = new DiagramItem();
        //itemToDraw->setPen(QPen(Qt::black, 3, Qt::SolidLine));


        itemToDraw->setPos(origPoint);
        itemToDraw->PrepareGeometryChange();

    }

    if(sceneMode == DrawObject){
        double brX {event->scenePos().x()};
        double brY {event->scenePos().y()};
        double tlX {origPoint.x()};
        double tlY{origPoint.y()};




        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) == true){
            double samePoint = event->scenePos().x() > event->scenePos().y()? event->scenePos().x() : event->scenePos().y();
            brX = samePoint;
            brY = samePoint;

        }
        // Draw the same amount in all angles
        else if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) == true){

        }
        else{

        }

        if(origPoint.x() > event->scenePos().x()){
            double swap = brX;
            brX = tlX;
            tlX = swap;
        }
        if(origPoint.y() > event->scenePos().y()){
            double swap = brY;
            brY = tlY;
            tlY = swap;
        }




        QPointF tl(tlX, tlY);
        QPointF br(brX, brY);
        QRectF rect = itemToDraw->boundingRect(tl,br);


        if(Toolbar::selection == Toolbar::SelectedItem::Ellipse)
            this->addEllipse(rect);

        if(Toolbar::selection == Toolbar::SelectedItem::Rectangle)
            this->addRect(rect);
        if(Toolbar::selection == Toolbar::SelectedItem::Line){
            //auto line = QLineF(tlX,tlY,brX, brY); //cool animation
            auto line = QLineF(event->scenePos().x(), event->scenePos().y(), origPoint.x(), origPoint.y());
            this->addLine(line);
        }
        if(Toolbar::selection == Toolbar::SelectedItem::Polygon){
            this->addPolygon(rect);

        }


    }
    else if(sceneMode == SelectObject){
        //itemToDraw->moveBy();
        //move the object
    }
    else if(sceneMode == ResizeObject){
        itemToDraw->resetTransform();

    }
    else{
        qDebug() << "else";
        //QGraphicsRectItem::mouseMoveEvent(event);
        QGraphicsScene::mouseMoveEvent(event);
    }


}

void DiagramScene::keyPressEvent(QKeyEvent* event){

}
void DiagramScene::makeItemsControllable(bool areControllable){

}
void DiagramScene::setMode(Mode mode){
    sceneMode = mode;

    QGraphicsView::DragMode vMode =
               QGraphicsView::NoDrag;
       if(mode == DrawObject){
           makeItemsControllable(false);
           vMode = QGraphicsView::NoDrag;
       }
       else if(mode == SelectObject){
           makeItemsControllable(true);
           vMode = QGraphicsView::RubberBandDrag;
       }
//       QGraphicsView* mView = views().at(0);
//       if(mView)
//           mView->setDragMode(vMode);
}
