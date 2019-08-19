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
    Line(QPointF*, QPointF*);
protected:
    QPainterPath path;
    QVector<QGraphicsLineItem> lines;

    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class SimpleText : public DiagramItem
{
public:
    SimpleText();
    SimpleText(QPointF*, QPointF*);

protected:
    QString text;
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Text : public DiagramItem
{
public:
    Text();
    Text(QPointF*, QPointF*);
protected:
    QString text;
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Rectangle : public DiagramItem
{
public:
    Rectangle();
    Rectangle(QPointF*, QPointF*);
protected:
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};

class Ellipse : public DiagramItem
{
public:
    Ellipse(QPointF*, QPointF*);
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
    Image(QPointF*, QPointF*);
    Image();

protected:
    QImage image;
    void setHandles();
    void paint(QPainter * painter,
        const QStyleOptionGraphicsItem * option,
        QWidget * widget);
};
#endif // SHAPES_H
