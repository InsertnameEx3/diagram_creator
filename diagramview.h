#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

// This is the widget

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "diagramscene.h"

class DiagramView : public QGraphicsView
{
public:
    DiagramView();

private:


public slots:
    void resize();
    void zoomIn();
    void zoomOut();
    void changeTheme();
};

#endif // DIAGRAMVIEW_H
