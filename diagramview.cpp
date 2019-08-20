#include "diagramview.h"
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QApplication>
#include <QMatrix>
#include <QTransform>
#include <QDebug>
DiagramView::DiagramView()
{


    //this->setStyleSheet(\
                "background-image:url(\"images/1.png\"); background-position: center;" );



}

void DiagramView::wheelEvent(QWheelEvent *event){


    if(QApplication::keyboardModifiers() == Qt::ControlModifier){
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        double scaleFactor = 1.15;

        if(event->delta() > 0){
            scale(scaleFactor, scaleFactor);
        }
        else {
            scale(1/scaleFactor, 1/scaleFactor);
        }

    }

    QGraphicsView::wheelEvent(event);
}
