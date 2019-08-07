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

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(sceneMode == DrawObject)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(this->sceneMode == this->DrawObject){
        this->setMode(this->NoMode);
        QGraphicsRectItem* rectangle = this->addRect((QRectF(origPoint.x(),origPoint.y(), event->scenePos().x() - origPoint.x(), event->scenePos().y() - origPoint.y())));
        //rectangle->setFlag(QGraphicsItem::ItemIsMovable);
    }

    QGraphicsScene::mouseReleaseEvent(event);


}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    this->clear();

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

        // This is for certain shapes that can
        //if current scene position is more left on the screen than the original point
        //itemToDraw->Overlappable = false;

        //if(itemToDraw->Overlappable){
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
        //} else {
            // No overlap
            //brX = (brX <= tlX + 20)? tlX + 20 : brX;
            //brY = (brY <= tlY + 20)? tlY + 20 : brY;
//        }

        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) == true){
            double samePoint = event->scenePos().x() > event->scenePos().y()? event->scenePos().x() : event->scenePos().y();

        }
        // Draw the same amount in all angles
        else if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) == true){

        }
        else{

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




//        if(origPoint.x() >= event->scenePos().x() - origPoint.x()){
//            left = event->scenePos().x();
//            width = (event->scenePos().x() * -1) + origPoint.x();
//        }
//        else{
//            left = origPoint.x();
//            width = event->scenePos().x() - origPoint.x();
//        }
//        if(origPoint.y() >= event->scenePos().y() - origPoint.y()){
//            top = event->scenePos().y();
//            height = (event->scenePos().y() * -1) + origPoint.y();
//        }
//        else{
//            height = event->scenePos().y() - origPoint.y();
//            top = origPoint.y();

//        }


//        QRectF rectangle;
//        // Draw diagonally
//        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) == true){


//            double samePoint = width > height? width : height;

//            rectangle = QRectF(left,top, samePoint, samePoint);

//        }
//        // Draw the same amount in all angles
//        else if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) == true){

//            rectangle = QRectF((event->scenePos().x() * -1) + origPoint.x()  , (event->scenePos().y() * -1) + origPoint.y(), width, height);



//        }
//        else{
//            qDebug() << "left: " << origPoint.x() << "\ntop:" << origPoint.y() << "\nwidth:" << event->scenePos().y() << "\nheight" << event->scenePos();
//            //left, top, width, height
//            //rectangle = QPolygonF(10);
//        }
//        //itemToDraw = this->addItem(rectangle);

    }
    else if(sceneMode == SelectObject){

        //move the object
    }
    else if(sceneMode == ResizeObject){

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
