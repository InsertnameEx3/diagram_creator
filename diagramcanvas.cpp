#include "diagramcanvas.h"
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
#include <QDebug>

Pen::Pen(){

}

Pen::Pen(QPointF*, QPointF*){

}

Pen::~Pen(){

}

Pen::Pen(QPointF point){
    path = new QPainterPath();
    path->moveTo(point);
}

void Pen::addPixel(QPointF point){
    path->lineTo(point);
}

QRectF Pen::boundingRect() const{
    return path->boundingRect();
}

void Pen::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){

    painter->drawPath(*path);

}


void Pen::setBoundingRect(QRectF* rect){
    qDebug() << *rect;
    this->topLeft = rect->topLeft();
    this->bottomRight = rect->bottomRight();
    addPixel(rect->bottomRight());

}
void Pen::setBoundingRect(QRectF rect){
    qDebug() << rect;
    this->topLeft = rect.topLeft();
    this->bottomRight = rect.bottomRight();
    addPixel(rect.bottomRight());
}
void Pen::setBoundingRect(QPointF* tl, QPointF* br){
    qDebug() << tl;
    this->topLeft = *tl;
    this->bottomRight = *br;
    addPixel(*br);
}
void Pen::setBoundingRect(QPointF tl, QPointF br){
    qDebug() << br;
    this->topLeft = tl;
    this->bottomRight = br;
    addPixel(br);
}
