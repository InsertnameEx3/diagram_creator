#ifndef HANDLES_H
#define HANDLES_H
#include <QRectF>

//#include "diagramitem.h"
#include <QList>
//#include "diagramscene.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsGridLayout>
class DiagramScene;

class Handle;
class DiagramItem;

//Interface for all handles of a DiagramItem
class Handles : public QList<Handle* >
{
public:
    enum Types{
        eightHandles,
        twoHandles
    };

    void setOpacity(qreal opacity);
    Types handleType;
    double handleSize;
    bool changed = false;

    DiagramItem* parent;
    Handles(DiagramItem* parent = nullptr, Types = eightHandles, double = 15);
    ~Handles();


    void recalculate();
    void setBoundingRect(QRectF*);
    void setBoundingRect(QPointF, QPointF);
    QRectF boundingRect() const;
    //DiagramScene& scene;

    void resize();
    void update();
    void setPos(QPointF);
    void show();
    void hide();
    void addToScene(QGraphicsScene* scene);
    void append(Handle *const &t);

    void setAcceptHoverEvents(bool enabled);
    void setAcceptTouchEvents(bool enabled);
    void setAcceptedMouseButtons(Qt::MouseButtons buttons);

private:
    QRectF* rect;

};

#endif // HANDLES_H
