#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPolygonItem>

class DiagramItem : public QGraphicsItem
{
public:
    enum Mode{Selected, None, Hover};
             // if selected add resize points
             // one hover show element and all arrows connected
    DiagramItem();
    ~DiagramItem();
    void mouseDoublePressEvent();
    QRectF boundingRect() const;
    QRectF boundingRect(QPointF topLeft, QPointF bottomRight) const;
    void PrepareGeometryChange();


    // overriding paint()
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);

    // item state
    bool Pressed;

protected: //overriden methods
    void mousePressEvent(QGraphicsSceneMouseEvent* event);  //Select or see options (left or right mouse)
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);   //Move
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event); //selected
};

#endif // DIAGRAMITEM_H
