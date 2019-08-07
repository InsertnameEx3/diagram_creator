#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QVBoxLayout>
#include <QWidget>
#include <QVector>
#include "diagramitem.h"
#include <QSplitter>
#include <QTreeView>
#include "diagramview.h"
class Toolbar : public QTreeView
{
public:
    Toolbar();

    enum SelectedItem{Rectangle, Ellipse, Line, Polygon};
    void CreateCategories();
    void CreateTools();
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void currentColumnChanged(const QModelIndex &current, const QModelIndex &previous);
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    static SelectedItem selection;
    void setDiagramScene(DiagramScene* scene);

private:
    DiagramScene* diagramScene;
    QSplitter* splitter = new QSplitter;
    //QVector<DiagramItem> items;
};

#endif // TOOLBAR_H
