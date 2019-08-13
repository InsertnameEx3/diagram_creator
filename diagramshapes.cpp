#include "diagramshapes.h"
#include <QPainter>


Line::Line(): DiagramItem (){

}
Line::Line(QPointF* tl, QPointF* br): DiagramItem(){
    this->setBoundingRect(tl, br);
}

void Line::setHandles(){

}
void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawLine(DiagramItem::topLeft, DiagramItem::bottomRight);
}



Ellipse::Ellipse(): DiagramItem (){

}
Ellipse::Ellipse(QPointF* tl, QPointF* br): DiagramItem (){
    this->setBoundingRect(tl, br);
}
void Ellipse::setHandles(){

}
void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawEllipse(boundingRect());
}



Rectangle::Rectangle(): DiagramItem (){

}
Rectangle::Rectangle(QPointF* tl, QPointF* br): DiagramItem (){
    this->setBoundingRect(tl, br);
}
void Rectangle::setHandles(){

}
void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(boundingRect());
}



Image::Image(): DiagramItem (){

}
Image::Image(QPointF* tl, QPointF* br): DiagramItem (){
    this->setBoundingRect(tl, br);
}
void Image::setHandles(){

}
void Image::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    image = QImage("/root/Downloads/images/4sgqS82.png");
    painter->drawImage(boundingRect(), image);
}



Text::Text(): DiagramItem (){

}

Text::Text(QPointF* tl, QPointF* br): DiagramItem (){
    this->setBoundingRect(tl, br);
}
void Text::setHandles(){

}
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawText(topLeft, text);
}



SimpleText::SimpleText(): DiagramItem (){

}

SimpleText::SimpleText(QPointF* tl, QPointF* br){
    this->setBoundingRect(tl, br);
}
void SimpleText::setHandles(){

}
void SimpleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawText(topLeft, text);
}

