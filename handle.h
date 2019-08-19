#ifndef HANDLE_H
#define HANDLE_H

#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QPen>
#include <QBrush>
#include "diagramitem.h"
#include <QSizeF>
//#include "handles.h"



class Handle : public QGraphicsItem
{
public:

    enum HandleType{
        TopLeft,
        Top,
        TopRight,
        Left,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };
    // if this is the handle of a line
    int index;

    Handle(QPointF*, QPointF*, HandleType, DiagramItem*);
    Handle(QPointF, QPointF, HandleType, DiagramItem*);
    ~Handle() override;



    HandleType handleType;
    void recalculate(QPointF*, QPointF*);
    void recalculate(QPointF, QPointF);

    void setBoundingRect(QPointF, QPointF);
    void setBoundingRect(QRectF*);
    void setBoundingRect(QPointF*, QPointF*);
    void setPos(QPointF);
    void setPos(QPointF*);

    QRectF boundingRect() const override;
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget) override;


    QPen borderColor;
    QBrush color;


    enum Form{Rounded, Squared};
    Form form;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;  //Select or see options (left or right mouse)
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;   //Move
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override; //selected

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override; //change cursor

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override; //cursor to normal


protected:



private:
    DiagramItem* parent;
    QPointF topLeft;
    QPointF bottomRight;
};



#endif // HANDLE_H
