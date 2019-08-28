#include "diagramshapes.h"
#include <QPainter>
#include "handle.h"
#include <QStyleOptionGraphicsItem>
#include <QtDebug>
#include <QLineF>
#include "handles.h"

Line::Line(): DiagramItem (){

}

Line::Line(QPointF* tl, QPointF* br): DiagramItem(tl,br, Handles::twoHandles, 15){



    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsFocusable);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);

}

void Line::setHandles(){

}



void Line::setPos(const QPointF &pos){
    for (int i =0; i <path.elementCount(); ++i) {
        path.setElementPositionAt(i, path.elementAt(i).x + pos.x(), path.elementAt(i).y + pos.y());
    }
    DiagramItem::setPos(pos);
}


void Line::mousePressEvent(QGraphicsSceneMouseEvent* event){
    //DiagramItem::mousePressEvent(event);
}
void Line::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //setPos(event->pos());
    //DiagramItem::mouseMoveEvent(event);
}
void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    //DiagramItem::mouseReleaseEvent(event);
}

void Line::setFirstPointPos(QPointF val){
    this->prepareGeometryChange();
    //DiagramItem::boundingRect().setTopLeft(val);
    this->path.setElementPositionAt(0, val.x(), val.y());
    //path.setElementPositionAt()
    this->update();

}

void Line::setLastPointPos(QPointF val){
    this->prepareGeometryChange();

    //DiagramItem::boundingRect().setTopLeft(val);
    path.setElementPositionAt(path.elementCount(), val.x(), val.y());
    this->update();
}


void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(this->getRenderStyle());
    //painter->setClipRect( option->exposedRect );
    borderColor = QBrush(Qt::black);
    borderWidth = 5;
    border = QPen(borderColor, DiagramItem::borderWidth);
    painter->setPen(border);

    if(path.elementCount() == 0){
        path.moveTo(DiagramItem::topLeft);
        path.lineTo(DiagramItem::bottomRight);
    }

    path.setElementPositionAt(0, DiagramItem::topLeft.x() ,DiagramItem::topLeft.y());
    path.setElementPositionAt(1, DiagramItem::bottomRight.x() ,DiagramItem::bottomRight.y());


    auto painterPath = path;
    painter->drawPath(path);
    //path.clear();



    //painter->drawLines(pointss);
}

QPainterPath Line::shape() const{
    QLineF temp;
    QPainterPath path;

    // For each element in the path set a larger zone
    for (int i = 0; i < this->path.elementCount() - 1; ++i) {
        temp = QLineF(this->path.elementAt(i).x, this->path.elementAt(i).y, this->path.elementAt(i+1).x, this->path.elementAt(i+1).y);
        QPolygonF poly;
        temp.translate(QPointF(-borderWidth,borderWidth));
        poly.push_back(temp.p1());
        poly.push_back(temp.p2());
        temp.translate(QPointF(borderWidth*2,-borderWidth*2));
        poly.push_back(temp.p1());
        poly.push_back(temp.p2());
        path.addPolygon(poly);

//        temp.translate(QPointF(borderWidth,-borderWidth));
//        poly.push_back(temp.p2());
//        poly.push_back(temp.p1());
//        path.addPolygon(poly);
    }



     return path;
}


void Line::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
//    if(isSelected()){
//        const QPointF point = closestPoint(event->pos());
//        const double handleSize = this->handles.getHandleSize();

//        addPointHandle = new Handle(point - QPointF(handleSize/2, handleSize/2), point + QPointF(handleSize/2, handleSize/2)
//                                , Handle::TopLeft, this);
//        addPointHandle->form = Handle::Rounded;
//        this->scene()->addItem(addPointHandle);

//        QGraphicsItem::hoverEnterEvent(event);
//    }
}
void Line::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
//    if(isSelected()){
//        const QPointF point = closestPoint(event->pos());
//        const double handleSize = this->handles.getHandleSize();

//        addPointHandle->setBoundingRect(point - QPointF(handleSize/2, handleSize/2), point + QPointF(handleSize/2, handleSize/2));

//        addPointHandle->update();
//        this->scene()->update();

//        QGraphicsItem::hoverMoveEvent(event);
//    }
}

void Line::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(isSelected()){
        this->scene()->removeItem(addPointHandle);

        this->scene()->update();

        //delete addPointHandle;
        //addPointHandle = nullptr;
        QGraphicsItem::hoverLeaveEvent(event);
    }
}

Ellipse::Ellipse(): DiagramItem (){

}
Ellipse::Ellipse(QPointF* tl, QPointF* br): DiagramItem (tl,br){
    this->setBoundingRect(tl, br);
}
void Ellipse::setHandles(){

}
void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        painter->setRenderHint(this->getRenderStyle());
    //painter->setClipRect( option->exposedRect );
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawEllipse(DiagramItem::boundingRect());
}



Rectangle::Rectangle(): DiagramItem (){

}
Rectangle::Rectangle(QPointF* tl, QPointF* br): DiagramItem (tl,br){
    this->setBoundingRect(tl, br);
}
void Rectangle::setHandles(){

}
void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(this->getRenderStyle());
    //painter->setClipRect( option->exposedRect );
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
    painter->setRenderHint(this->getRenderStyle());
    //painter->setClipRect( option->exposedRect );
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);

    painter->setBrush(DiagramItem::innerColor);

    image = QImage("/root/Downloads/images/4sgqS82.png");
    painter->drawImage(boundingRect(), image);
}


// for having an editable text box
Text::Text(): DiagramItem (){
    text = "Type..";
    QGraphicsTextItem(this->text);
    setTextInteractionFlags(Qt::TextEditorInteraction);
}

Text::Text(QPointF* tl, QPointF* br): DiagramItem (tl,br){
    text = "Type..";
    QGraphicsTextItem(this->text);
    this->setBoundingRect(tl, br);
    setTextInteractionFlags(Qt::TextEditorInteraction);
}
void Text::setHandles(){

}
void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(this->getRenderStyle());
    //painter->setClipRect( option->exposedRect );
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawText(topLeft, text);
}


//for showing plain text in an item
SimpleText::SimpleText(): DiagramItem (){

}

SimpleText::SimpleText(QPointF* tl, QPointF* br): DiagramItem(tl,br){
    this->setBoundingRect(tl, br);
    //QGraphicsSimpleTextItem("blop");
}
void SimpleText::setHandles(){

}
void SimpleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(this->getRenderStyle());
    //painter->setClipRect( option->exposedRect );
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    painter->setPen(border);
    painter->setBrush(DiagramItem::innerColor);
    painter->drawText(topLeft, text);
}



