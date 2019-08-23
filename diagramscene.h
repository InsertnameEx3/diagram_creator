#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QGraphicsItem>
#include "diagramitem.h"
#include <QList>

#include "diagramshapes.h"

struct Theme;

class DiagramScene : public QGraphicsScene
{
public:


    QColor gridColor = Qt::darkGray;

    QColor backgroundColor = Qt::blue;

    static double size;

    static int space;

    enum GridType{
        Lines,
        Dots,

    };
    GridType grid = Lines;

    bool showGrid;
    static DiagramItem* currentHoveredItem;

    //when there is noMode you use the selection tool to select multiple items inside the square
    enum Mode {NoMode, SelectObject, DrawObject, MoveObject, ResizeObject, Drawing};
    DiagramScene(QObject* parent = nullptr);
    ~DiagramScene();

    void setMode(Mode mode);
    Mode sceneMode;
    //void paintEvent(QPaintEvent *event);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);


    void keyPressEvent(QKeyEvent* event);
    //QList views() const;
    void getScene();

private:
    QRectF* previousItem;
    QPointF origPoint;
    DiagramItem* itemToDraw;
    static void makeItemsControllable(bool areControllable);
};

#endif // DIAGRAMSCENE_H
