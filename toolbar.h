#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QVBoxLayout>
#include <QWidget>
#include <QVector>
#include "diagramitem.h"
#include <QSplitter>
#include <QTreeView>
class Toolbar : public QTreeView
{
public:
    enum SelectedItem{ Table, OneToMany, OneToOne, ManyToMany};
    void CreateCategories();
    void CreateTools();
    Toolbar();
private:
    QSplitter* splitter = new QSplitter;
    //QVector<DiagramItem> items;
};

#endif // TOOLBAR_H
