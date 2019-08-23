#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPolygonItem>
#include <QPen>
#include <QBrush>
#include "handles.h"
#include <QGraphicsAnchorLayout>
#include <QPainter>



struct Theme;

class DiagramItem : public QGraphicsItem
{
public:

    enum RenderStyle {
        Antialiasing = 0x01,
        TextAntialiasing = 0x02,
        SmoothPixmapTransform = 0x04,
        HighQualityAntialiasing = 0x08,
        NonCosmeticDefaultPen = 0x10,
        Qt4CompatiblePainting = 0x20,
        LosslessImageRendering = 0x40,
    };

    RenderStyle renderingStyle;
    void setRenderStyle(RenderStyle);

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


    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    //check whether the mouse button is on the item itself (base is only logic for a rectangle)


    enum Mode{Selected, None, Hover};

    // if selected add resize points
    // on hover show element and all arrows connected

    DiagramItem(QPointF*, QPointF*, Handles::Types = Handles::eightHandles, double = 15);




    DiagramItem(Handles::Types = Handles::eightHandles, double = 15);
    DiagramItem(int,int,int,int, Handles::Types = Handles::eightHandles, double = 15);
    DiagramItem(QPointF*,QPointF*,QPointF*,QPointF*);
    ~DiagramItem();

    void mouseDoublePressEvent();
    void setBoundingRect(QRectF*);
    void setBoundingRect(QRectF);
    void setBoundingRect(QPointF*, QPointF*);
    void setBoundingRect(QPointF, QPointF);
    void setLine(QPointF, QPointF);

    QRectF boundingRect() const;

    // overriding paint()
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);

    // item state
    Mode state;
    bool Pressed;
    bool connectable;
    bool overlappable;


protected: //overriden methods

    //static double minHeight;
    void mousePressEvent(QGraphicsSceneMouseEvent* event);  //Select or see options (left or right mouse)
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);   //Move
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event); //selected
    //virtual method for setting the resizing handles

    QPointF topLeft;
    QPointF bottomRight;


};

#endif // DIAGRAMITEM_H

