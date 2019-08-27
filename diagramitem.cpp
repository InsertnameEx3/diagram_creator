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

DiagramItem::~DiagramItem(){

    delete this->addPointHandle;

}

DiagramItem::DiagramItem(QPointF* tl, QPointF* br, Handles::Types type, double size): topLeft{*tl}, bottomRight{*br}, handles{*new Handles(this, type, size)}{
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsFocusable);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
}

DiagramItem::DiagramItem(int tlX,int tlY,int brX,int brY, Handles::Types type, double size): topLeft{QPointF(tlX,tlY)}, bottomRight{QPointF(brX, brY)}, handles{*new Handles(this, type, size)} {
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsFocusable);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
}

DiagramItem::DiagramItem(Handles::Types type, double size): handles{*new Handles(this, type, size)}{
    borderColor = QBrush(Qt::black);
    borderWidth = 3;
    border = QPen(borderColor, DiagramItem::borderWidth);

    innerColor = QBrush(Qt::white);

    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsMovable|QGraphicsItem::GraphicsItemFlag::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsFocusable);
    this->setAcceptHoverEvents(true);
    this->setAcceptTouchEvents(true);
}


void DiagramItem::updateLines(QPointF newPos){

    qDebug() << this;
    qDebug() << newPos;
    //?
    newPos = this->pos();
    if(connectedLines.count() != 0){
        for(auto line : connectedLines){
            if(this->contains(line->boundingRect().topLeft())){
//                offset = pos-rect.center();
//                super().moveBy(offset.rx, offset.ry);

                //line->setFirstPointPos(newPos);
                //line->setFirstPointPos(newPos.isNull() ? this->boundingRect().center() : newPos);

                line->setBoundingRect(this->boundingRect().center(), line->bottomRight);
            }
            else{
                //line->setLastPointPos(newPos);
                //line->setLastPointPos(newPos.isNull() ? this->boundingRect().center() : newPos);
                line->setBoundingRect(line->topLeft, this->boundingRect().center());

            }
        }
    }
}


void DiagramItem::setBoundingRect(QRectF* newRectangle){

    this->prepareGeometryChange();
    topLeft = newRectangle->topLeft();
    bottomRight = newRectangle->bottomRight();
    this->update();

}

void DiagramItem::setBoundingRect(QRectF newRectangle){
    qDebug() << newRectangle;
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

    this->updateLines();
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
void DiagramItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){
    painter->setRenderHint(renderingStyle);
}

void DiagramItem::mouseDoublePressEvent(){

}

void DiagramItem::setRenderStyle(QPainter::RenderHint style){
    this->renderingStyle = style;
}

int DiagramScene::space;
bool Properties::gridSnap;

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value){


    qDebug() << "selected";
    if (change == QGraphicsItem::ItemSelectedChange)
    {

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


        this->setRenderStyle(QPainter::NonCosmeticDefaultPen);

        //handles.recalculate();
        QPointF newPos = value.toPointF();

        this->prepareGeometryChange();

        this->updateLines(newPos);
        if(QApplication::mouseButtons() == Qt::LeftButton && Properties::gridSnap){

            int gridSpace = DiagramScene::space;
            qreal xV = round(newPos.x()/gridSpace)*gridSpace;
            qreal yV = round(newPos.y()/gridSpace)*gridSpace;
            handles.setPos(QPointF(xV, yV));
            return QPointF(xV, yV);
        }
        else{
            handles.setPos(newPos);


            //this->updateLines();
                for(auto line : connectedLines){
                    if(this->contains(line->boundingRect().topLeft())){

                                //newPos, line->bottomRight);

                    }
                    else{

                        //line->setBoundingRect(line->topLeft, this->pos());
                    }
                }


            return newPos;
        }


        //this->updateLines();
    }
    if(change == QGraphicsItem::ItemScaleChange){

        //handles.recalculate();
    }

    return QGraphicsItem::itemChange(change, value);


}

QPainter::RenderHint DiagramItem::getRenderStyle(){
   return renderingStyle;
}

DiagramItem* DiagramScene::currentHoveredItem;

void DiagramItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    hovered = true;
    DiagramScene::currentHoveredItem = this;
    //set shadow-y background around item
}

void DiagramItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    hovered = false;
    DiagramScene::currentHoveredItem = nullptr;
    //remove shadow-y background around item
}


void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    hovered = true;
    DiagramScene::currentHoveredItem = this;
    setSelected(true);
    QGraphicsItem::mousePressEvent(event);
}
void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event);

}
void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
}
