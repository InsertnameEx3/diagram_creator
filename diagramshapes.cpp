#include "diagramshapes.h"
#include <QPainter>
#include "handle.h"
Line::Line(): DiagramItem (){

}
Line::Line(QPointF* tl, QPointF* br): DiagramItem(tl,br){
    this->setBoundingRect(tl, br);
}

void Line::setHandles(){

}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    //painter->setBrush(DiagramItem::color);

    //path.moveTo(DiagramItem::topLeft);
    //path.lineTo(DiagramItem::bottomRight);
    //path.lineTo(DiagramItem::bottomRight + QPointF(100, 100));
    //painter->drawLine(DiagramItem::topLeft, DiagramItem::bottomRight);
    path.moveTo(DiagramItem::topLeft);
    //path.lineTo(DiagramItem::topLeft + QPointF(0, 100));
    path.lineTo(DiagramItem::bottomRight);
    painter->drawPath(path);
    path.clear();



    //painter->drawLines(pointss);
}

void Line::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    if(this->path.contains(event->pos())){
    auto handleSize = 15;

    addPointHandle = new Handle(event->pos() - QPointF(handleSize/2, handleSize/2), event->pos() + QPointF(handleSize/2, handleSize/2)
                            , Handle::TopLeft, this);
    addPointHandle->form = Handle::Rounded;
    this->scene()->addItem(addPointHandle);
    }
}
void Line::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    if(this->path.contains(event->pos())){
    auto handleSize = 15;
    addPointHandle->setBoundingRect(event->pos() - QPointF(handleSize/2, handleSize/2), event->pos() + QPointF(handleSize/2, handleSize/2));

    addPointHandle->update();
    this->scene()->update();
    }
}
void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    //this->scene()->removeItem(addPointHandle);

    //delete addPointHandle;
    //addPointHandle = nullptr;
}

Ellipse::Ellipse(): DiagramItem (){

}
Ellipse::Ellipse(QPointF* tl, QPointF* br): DiagramItem (tl,br){
    this->setBoundingRect(tl, br);
}
void Ellipse::setHandles(){

}
void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawEllipse(boundingRect());
}



Rectangle::Rectangle(): DiagramItem (){

}
Rectangle::Rectangle(QPointF* tl, QPointF* br): DiagramItem (tl,br){
    this->setBoundingRect(tl, br);
}
void Rectangle::setHandles(){

}
void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawRect(boundingRect());
}



Image::Image(): DiagramItem (){

}
Image::Image(QPointF* tl, QPointF* br): DiagramItem (tl,br){

    this->setBoundingRect(tl, br);
}
void Image::setHandles(){

}
void Image::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);

    painter->setBrush(DiagramItem::innerColor);

    image = QImage("/root/Downloads/images/4sgqS82.png");
    painter->drawImage(boundingRect(), image);
}



Text::Text(): DiagramItem (){

}

Text::Text(QPointF* tl, QPointF* br): DiagramItem (tl,br){
    this->setBoundingRect(tl, br);
}
void Text::setHandles(){

}
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawText(topLeft, text);
}



SimpleText::SimpleText(): DiagramItem (){

}

SimpleText::SimpleText(QPointF* tl, QPointF* br): DiagramItem(tl,br){
    this->setBoundingRect(tl, br);
}
void SimpleText::setHandles(){

}
void SimpleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawText(topLeft, text);
}

