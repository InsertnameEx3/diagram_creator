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
    //itemToDraw = new DiagramItem(new QPointF(150,150), new QPointF(444,444));
//        itemToDraw = new DiagramItem(origPoint, event->pos());
    this->setBackgroundBrush(Qt::blue);
    // Add the vertical lines first, paint them red
    for (int x=0; x<=1000; x+=50)
        this->addLine(x,0,x,1000, QPen(Qt::white));

    // Now add the horizontal lines, paint them green
    for (int y=0; y<=1000; y+=50)
        this->addLine(0,y,1000,y, QPen(Qt::white));


}

DiagramScene::~DiagramScene(){
    //delete[] items;
    //delete origPoint;
    //delete itemToDraw;
}


void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event){

//    if(this->sceneMode == this->DrawObject){
        itemToDraw = new DiagramItem(new QPointF(origPoint.x(), origPoint.y()), new QPointF(event->scenePos()));

        this->addItem(itemToDraw);
        origPoint = event->scenePos();
//        itemToDraw = new DiagramItem(new QPointF(event->pos()), new QPointF(event->pos()));

//    }

    QGraphicsScene::mousePressEvent(event);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if(Toolbar::selection){

        this->setMode(this->NoMode);

        //add to list of items in scene and remove the old temporary object from the scene
        // To avoid a dangling pointer:
        //itemToDraw = nullptr;
    }
    //select everything in selection box
    else{

    }


    QGraphicsScene::mouseReleaseEvent(event);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){


    //adding a new diagram item
    if(this->sceneMode == this->DrawObject){

        itemToDraw->setBoundingRect(QRectF(QPointF(origPoint), event->scenePos()));
        //itemToDraw->setPos(QPointF(event->pos().x(), event->pos().y()));
        itemToDraw->prepareGeometryChange();
        itemToDraw->update();
        this->update();

    }
    //draw selection box
    else{

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
