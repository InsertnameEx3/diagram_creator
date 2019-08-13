#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QVBoxLayout>
#include <QWidget>
#include <QVector>
#include "diagramitem.h"
#include <QSplitter>
#include <QTreeView>
#include "diagramview.h"
#include <QStandardItem>
class Toolbar : public QTreeView
{
public:
    Toolbar();
    ~Toolbar();

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
};

#endif // TOOLBAR_H
