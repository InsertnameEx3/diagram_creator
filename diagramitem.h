#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPolygonItem>

class DiagramItem : public QGraphicsItem
{
public:
    //properties for property panel:
    QColor borderColor;
    QColor color;
    QSize size;
    //methods for properties:
    void changeBorderColor();
    void changeInnerColor();
    void changeSize();


    enum Mode{Selected, None, Hover};

    // if selected add resize points
    // on hover show element and all arrows connected

    DiagramItem(QPointF*, QPointF*);

    DiagramItem(int,int,int,int);
    DiagramItem(QPointF*,QPointF*,QPointF*,QPointF*);
    ~DiagramItem();

    void mouseDoublePressEvent();
    void setBoundingRect(QRectF);
    QRectF boundingRect() const;
    void PrepareGeometryChange();


    // overriding paint()
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);

    // item state
    Mode state;
    bool Pressed;
    bool Overlappable;

protected: //overriden methods
    void mousePressEvent(QGraphicsSceneMouseEvent* event);  //Select or see options (left or right mouse)
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);   //Move
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event); //selected
    void setHandles();
private:
    QPointF topLeft;
    QPointF bottomRight;
};

#endif // DIAGRAMITEM_H

