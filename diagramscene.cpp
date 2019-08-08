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

    //rect->setFlags(QGraphicsItem::ItemIsMovable);

}

DiagramScene::~DiagramScene(){
    //delete[] items;
    //delete origPoint;
    //delete itemToDraw;
}


void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    itemToDraw = new DiagramItem(new QPointF(150,150), new QPointF(120,100));
    //QGraphicsItem::item

    this->addItem(itemToDraw);
    itemToDraw->setFlag(QGraphicsItem::ItemIsMovable);
    this->removeItem(itemToDraw);
    itemToDraw = nullptr;
    if(sceneMode == DrawObject)
        origPoint = event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if(this->sceneMode == this->DrawObject){
        this->setMode(this->NoMode);
    }
    QGraphicsScene::mouseReleaseEvent(event);
    //add to list of items in scene and remove the old temporary object from the scene
    //items.append(itemToDraw);

    //this->removeItem(itemToDraw);
    // To avoid a dangling pointer:
    //itemToDraw = nullptr;
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){



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
