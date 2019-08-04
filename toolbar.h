#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QVBoxLayout>
#include <QWidget>
#include <QVector>
#include "diagramitem.h"
#include <QSplitter>
class Toolbar : public QWidget, public QVBoxLayout
{
public:
    enum SelectedItem{ Table, OneToMany, OneToOne, ManyToMany};
    void CreateItems();
    void CreateActions();
    Toolbar();
private:
    QSplitter* splitter = new QSplitter;
    //QVector<DiagramItem> items;
};

#endif // TOOLBAR_H
