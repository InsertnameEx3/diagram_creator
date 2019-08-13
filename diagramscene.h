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

class DiagramScene : public QGraphicsScene
{
public:
    //when there is noMode you use the selection tool to select multiple items inside the square
    enum Mode {NoMode, SelectObject, DrawObject, MoveObject, ResizeObject};
    DiagramScene(QObject* parent = nullptr);
    ~DiagramScene();

    void setMode(Mode mode);
    Mode sceneMode;
    //void paintEvent(QPaintEvent *event);
protected:
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
