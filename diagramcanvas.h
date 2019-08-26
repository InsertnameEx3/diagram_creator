#ifndef DIAGRAMCANVAS_H
#define DIAGRAMCANVAS_H

#include "diagramitem.h"


class Pen : public DiagramItem
{
public:

    Pen(QPointF);
    Pen();
    Pen(QPointF*, QPointF*);
    ~Pen() override;

    // Properties
    double thickness;
    QColor color;

    void setBoundingRect(QRectF*);
    void setBoundingRect(QRectF);
    void setBoundingRect(QPointF*, QPointF*);
    void setBoundingRect(QPointF, QPointF);

    QRectF boundingRect() const override;
    void addPixel(QPointF);

    // overriding paint()
    virtual void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget) override;
private:
    QPainterPath* path;
};

class Eraser{
    Eraser();
    ~Eraser();
};


class Bucket{

};

class ColorPicker{

};


class DiagramCanvas
{
public:
    DiagramCanvas();
};

#endif // DIAGRAMCANVAS_H
