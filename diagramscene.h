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
class DiagramScene : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawObject, MoveObject, ResizeObject};
    DiagramScene(QObject* parent = nullptr);

    void setMode(Mode mode);
    //void paintEvent(QPaintEvent *event);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

private:
    Mode sceneMode;
    QPointF origPoint;
    DiagramItem* itemToDraw;
    void makeItemsControllable(bool areControllable);
};

#endif // DIAGRAMSCENE_H
