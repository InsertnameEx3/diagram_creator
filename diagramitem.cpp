#include "diagramitem.h"
#include <QPen>
#include "mainwindow.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "toolbar.h"
#include <QDebug>

#include "handle.h"
#include "handles.h"
#include <QGraphicsWidget>
#include <QApplication>
#include <cmath>

DiagramItem::DiagramItem(QPointF* tl, QPointF* br, Handles::Types type, double size): topLeft{*tl}, bottomRight{*br}, handles{*new Handles(this, type, size)}{
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

DiagramItem::DiagramItem(int tlX,int tlY,int brX,int brY, Handles::Types type, double size): topLeft{QPointF(tlX,tlY)}, bottomRight{QPointF(brX, brY)}, handles{*new Handles(this, type, size)} {
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

DiagramItem::DiagramItem(Handles::Types type, double size): handles{*new Handles(this, type, size)}{
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);

    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
}

DiagramItem::~DiagramItem(){

}

void DiagramItem::setBoundingRect(QRectF* newRectangle){
    this->prepareGeometryChange();
    topLeft = newRectangle->topLeft();
    bottomRight = newRectangle->bottomRight();
    this->update();
}

void DiagramItem::setBoundingRect(QRectF newRectangle){
    this->prepareGeometryChange();
    topLeft = newRectangle.topLeft();
    bottomRight = newRectangle.bottomRight();
    this->update();
}

void DiagramItem::setBoundingRect(QPointF* tl, QPointF* br){
    this->prepareGeometryChange();
    topLeft = *tl;
    bottomRight = *br;
    this->update();
}

void DiagramItem::setBoundingRect(QPointF tl, QPointF br){
    this->prepareGeometryChange();

    switch(handles.handleType){
    case Handles::eightHandles:
        if(QRectF(tl, br).height() >= 50){
            topLeft.setY(tl.y());
            bottomRight.setY(br.y());
        }
        if(QRectF(tl, br).width() >= 100){
            topLeft.setX(tl.x());
            bottomRight.setX(br.x());
        }
        break;
    case Handles::twoHandles:
        topLeft = tl;
        bottomRight = br;
        break;
    }
    this->update();
}

void DiagramItem::setLine(QPointF tl, QPointF br){
    this->prepareGeometryChange();
    topLeft = tl;
    bottomRight = br;
    this->update();
}

QRectF DiagramItem::boundingRect() const{
            return QRectF(topLeft, bottomRight);
}



// overriding paint()
void DiagramItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    switch(renderingStyle){
        case Antialiasing:
            painter->setRenderHint(QPainter::Antialiasing);
        break;
        case TextAntialiasing:
            painter->setRenderHint(QPainter::TextAntialiasing);
        break;
        case SmoothPixmapTransform :
            painter->setRenderHint(QPainter::SmoothPixmapTransform);
        break;
        case HighQualityAntialiasing:
            painter->setRenderHint(QPainter::HighQualityAntialiasing);
        break;
        case NonCosmeticDefaultPen:
            painter->setRenderHint(QPainter::NonCosmeticDefaultPen);
        break;
        case Qt4CompatiblePainting:
            painter->setRenderHint(QPainter::Qt4CompatiblePainting);
        break;
        case LosslessImageRendering:
            painter->setRenderHint(QPainter::LosslessImageRendering);
        break;

    }


//    Antialiasing = 0x01,
//    TextAntialiasing = 0x02,
//    SmoothPixmapTransform = 0x04,
//    HighQualityAntialiasing = 0x08,
//    NonCosmeticDefaultPen = 0x10,
//    Qt4CompatiblePainting = 0x20,
//    LosslessImageRendering = 0x40,
    //QGraphicsItem::paint(painter, option, widget);
}


void DiagramItem::mouseDoublePressEvent(){

}

void DiagramItem::setRenderStyle(RenderStyle style){
    this->renderingStyle = style;
}

void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
    Pressed = true;
    QGraphicsItem::mousePressEvent(event);
}
void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){

    //scene()->views()[0]->setRenderHints(QPainter::NonCosmeticDefaultPen);
    this->setRenderStyle(NonCosmeticDefaultPen);
    //this->handles.set
    QGraphicsItem::mouseMoveEvent(event);

}
void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    this->setRenderStyle(Antialiasing);
    Pressed = false;
    state = Selected;
    //setHandles();
    QGraphicsItem::mouseReleaseEvent(event);
}


int DiagramScene::space;
bool Properties::gridSnap;

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value){



    if (change == QGraphicsItem::ItemSelectedChange)
    {
        qDebug() << change;
        if (value == true)
        {

            if(!handles.changed){

                handles.recalculate();
                handles.setAcceptHoverEvents(true);
                handles.setAcceptTouchEvents(true);
                handles.setAcceptedMouseButtons(Qt::LeftButton);
                handles.addToScene(scene());
                handles.changed = true;
            }

            handles.show();

            this->update();
            scene()->update();


            //this->color = Qt::blue;
        }
        else {
            handles.hide();
            this->update();
            scene()->update();

            // do stuff if not selected
        }
    }
    if (change == QGraphicsItem::ItemPositionChange){

        this->setRenderStyle(NonCosmeticDefaultPen);

        //handles.recalculate();
        QPointF newPos = value.toPointF();
        this->prepareGeometryChange();

        if(QApplication::mouseButtons() == Qt::LeftButton && Properties::gridSnap){

            int gridSpace = DiagramScene::space;
            qreal xV = round(newPos.x()/gridSpace)*gridSpace;
            qreal yV = round(newPos.y()/gridSpace)*gridSpace;
            handles.setPos(QPointF(xV, yV));
            return QPointF(xV, yV);
        }
        else{
            handles.setPos(newPos);
            return newPos;
        }


        scene()->update();
        this->update();
    }
    if(change == QGraphicsItem::ItemScaleChange){

        //handles.recalculate();
    }

    return QGraphicsItem::itemChange(change, value);


}


QPainter::RenderHint DiagramItem::getRenderStyle(){
    switch(renderingStyle){
        case Antialiasing:
            return QPainter::Antialiasing;

        case TextAntialiasing:
            return QPainter::TextAntialiasing;

        case SmoothPixmapTransform :
            return QPainter::SmoothPixmapTransform;

        case HighQualityAntialiasing:
            return QPainter::HighQualityAntialiasing;

        case NonCosmeticDefaultPen:
            return QPainter::NonCosmeticDefaultPen;

        case Qt4CompatiblePainting:
            return QPainter::Qt4CompatiblePainting;

        case LosslessImageRendering:
            return QPainter::LosslessImageRendering;
    }
}

DiagramItem* DiagramScene::currentHoveredItem;
void DiagramItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    hovered = true;
    DiagramScene::currentHoveredItem = this;
}

void DiagramItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    hovered = false;
    DiagramScene::currentHoveredItem = nullptr;
}
