#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPolygonItem>
#include <QPen>
#include <QBrush>
#include "handles.h"
#include <QGraphicsAnchorLayout>
#include <QPainter>


class Line;

struct Theme;

class DiagramItem : public QGraphicsItem
{
public:

    QList<DiagramItem*> connectedLines;

    enum ItemType{
        ConnectionLine, // A connection line that connects two shapes
        Shape,          // All shapes
        NoType
    };
    ItemType diagramItemType = Shape;

    QPainter::RenderHint renderingStyle;
    void setRenderStyle(QPainter::RenderHint);

    // Return QPainter renderhint from DiagramItem renderstyle
    QPainter::RenderHint getRenderStyle();

    //properties for property panel:
    QPen border;
    double borderWidth;
    QBrush borderColor;
    QBrush innerColor;
    QSize size;

    Handle* addPointHandle;

    Handles& handles;

    //methods for properties:
    void changeBorderColor();
    void changeInnerColor();
    //when changing from the properties panel (no mouse event)
    void changeSize();
    //when changing from the handles
    void resize(QGraphicsSceneMouseEvent*);


    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    //check whether the mouse button is on the item itself (base is only logic for a rectangle)


    enum Mode{Selected, None, Hover};

    // if selected add resize points
    // on hover show element and all arrows connected

    DiagramItem(QPointF*, QPointF*, Handles::Types = Handles::eightHandles, double = 15);




    DiagramItem(Handles::Types = Handles::eightHandles, double = 15);
    DiagramItem(int,int,int,int, Handles::Types = Handles::eightHandles, double = 15);
    DiagramItem(QPointF*,QPointF*,QPointF*,QPointF*);
    ~DiagramItem() override;

    void mouseDoublePressEvent();
    void setBoundingRect(QRectF*);
    void setBoundingRect(QRectF);
    void setBoundingRect(QPointF*, QPointF*);
    void setBoundingRect(QPointF, QPointF);
    void setLine(QPointF, QPointF);
    void updateLines();

    QRectF boundingRect() const override;

    // overriding paint()
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget) override;

    // item state
    bool hovered;   // Check if item is currently being hovered
    Mode state;
    bool Pressed;
    bool connectable;
    bool overlappable;


protected: //overriden methods

    //static double minHeight;

    //virtual method for setting the resizing handles

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override; //change cursor

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override; //cursor to normal

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


    QPointF topLeft;
    QPointF bottomRight;


};

#endif // DIAGRAMITEM_H

