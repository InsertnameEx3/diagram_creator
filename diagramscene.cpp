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
#include "mainwindow.h"
#include <QApplication>
#include "toolbar.h"
#include "handle.h"
#include "QGraphicsLayout"
#include "handles.h"
Toolbar::SelectedItem Toolbar::selection;

DiagramScene::DiagramScene(QObject* parent)
{



    QColor gridColor = "#cdcccc";
    QColor backgroundColor = "#e4e4e4";

    enum GridType{
        Lines,
        Dots
    };
    GridType grid = Dots;


    this->setBackgroundBrush(backgroundColor);


    double width = this->width() < 1920? 1920 : this->width();
    double height = this->height() < 1920? 1920 : this->height();
    switch(grid){

    case Lines:
        size = 1;
        space = 25;
        for (int x=0; x<=width; x+=space){
            this->addLine(x,0,x,height, QPen(gridColor));

        }
        for (int y=0; y<=height; y+=space){
            this->addLine(0,y,width,y, QPen(gridColor));
        }
        break;
    case Dots:
        size = 1;
        space = 25;
        for(int x=0; x<=2000; x+=space){
            for(int y=0; y<=2000; y+=space){
                this->addEllipse(QRectF(QPointF(x-size,y-size), QPointF(x+size,y+size)), QPen(gridColor), QBrush(gridColor));
            }
        }
        break;
    }
}

DiagramScene::~DiagramScene(){
    //delete[] items;
    //delete origPoint;
    //delete itemToDraw;
}


void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event){


    if(this->sceneMode == this->DrawObject){
    switch(Toolbar::selection){
        case Toolbar::Rectangle:
            itemToDraw = new Rectangle(new QPointF(event->pos()), new QPointF(event->pos()));
            break;
        case Toolbar::Ellipse:
            itemToDraw = new Ellipse(new QPointF(event->pos()), new QPointF(event->pos()));
            break;
        case Toolbar::Line:
            itemToDraw = new Line(new QPointF(event->pos()), new QPointF(event->pos()));
            break;
        case Toolbar::Image:
            itemToDraw = new Image(new QPointF(event->pos()), new QPointF(event->pos()));
            break;

        case Toolbar::SimpleText:
            itemToDraw = new SimpleText(new QPointF(event->pos()), new QPointF(event->pos()));
            break;
        case Toolbar::Text:
            itemToDraw = new Text(new QPointF(event->pos()), new QPointF(event->pos()));
            break;
        }

        this->addItem(itemToDraw);
        origPoint = event->scenePos();

    }

    QGraphicsScene::mousePressEvent(event);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){


    //adding a new diagram item
    if(this->sceneMode == this->DrawObject){

        itemToDraw->setBoundingRect(QRectF(QPointF(origPoint), event->scenePos()));
        this->update();

    }
    //draw selection box
    else{

    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if(this->sceneMode == this->DrawObject){
        //if this is a connectionLine remove item if it is not connected by 1 or 2 diagram items
        if(itemToDraw->boundingRect().height() <= 50){
            double heightDiff = 50 - itemToDraw->boundingRect().height();
            itemToDraw->setBoundingRect(itemToDraw->boundingRect().topLeft() - QPointF(0, heightDiff), itemToDraw->boundingRect().bottomRight());
        }
        if(itemToDraw->boundingRect().width() <= 100){
            double widthDiff = 100 - itemToDraw->boundingRect().width();
            itemToDraw->setBoundingRect(itemToDraw->boundingRect().topLeft() - QPointF(widthDiff, 0), itemToDraw->boundingRect().bottomRight());

        }
        this->update();
        this->setMode(this->NoMode);
    }
    //select everything in selection box
    else{

    }


    QGraphicsScene::mouseReleaseEvent(event);
}

void DiagramScene::keyPressEvent(QKeyEvent* event){
    QGraphicsScene::keyPressEvent(event);
}
void DiagramScene::makeItemsControllable(bool areControllable){

}
void DiagramScene::setMode(Mode mode){
    qDebug() << "jeee";
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

       QGraphicsView* mView = views().at(0);
       if(mView)
           mView->setDragMode(vMode);
}
