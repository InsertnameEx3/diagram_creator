#ifndef SHAPES_H
#define SHAPES_H

#include "diagramitem.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

class Line : public DiagramItem
{
public:
    Line();

protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class SimpleText : public DiagramItem
{
public:
    SimpleText();

protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Text : public DiagramItem
{
public:
    Text();

protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Rectangle : public DiagramItem
{
public:
    Rectangle();

protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Ellipse : public DiagramItem
{
public:
    Ellipse();

protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Image : public DiagramItem
{
public:
    Image();

protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

#endif // SHAPES_H
