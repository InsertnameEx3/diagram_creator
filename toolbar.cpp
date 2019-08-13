#include "toolbar.h"
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QToolBar>
#include "mainwindow.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QDebug>




Toolbar::Toolbar()
{


        auto model_drzewa = new QStandardItemModel();



        //model_drzewa->appendRow(new QStandardItem("Shapes"));
        model_drzewa->
        model_drzewa->appendRow(new QStandardItem("Rectangle"));
        model_drzewa->appendRow(new QStandardItem("Ellipse"));
        model_drzewa->appendRow(new QStandardItem("Line"));


        model_drzewa->setHeaderData(0, Qt::Horizontal, "asd");
        this->setModel(model_drzewa);
        this->expandAll();


        QFile styleSheet("/home/marten/projects/diagram-creator/toolbar.qss");
        if(!styleSheet.open(QFile::ReadOnly))
                QMessageBox::information(nullptr, "Error", styleSheet.errorString());
        QString StyleSheet = QLatin1String(styleSheet.readAll());


        this->setStyleSheet(StyleSheet);

}
Toolbar::~Toolbar(){
}

/* (Tree) For example:
 *
 * Class: (Category)
 *  table (Tool)
 * Relations:
 *  One to many
 *  One to one
 *  Many to many
 * Shapes:
 *  Ellipse
 *  Rectangle
*/
void Toolbar::CreateCategories(){



}
void Toolbar::CreateTools(){



}


void Toolbar::currentChanged(const QModelIndex &current, const QModelIndex &previous){

    diagramScene->setMode(diagramScene->DrawObject);
    switch(current.row()){
        case 0:
            selection = SelectedItem::Rectangle;
        break;
        case 1:
            selection = SelectedItem::Ellipse;
        break;
        case 2:
            selection = SelectedItem::Line;
        break;
        case 3:
            selection = SelectedItem::Polygon;
        break;

    }

}
void Toolbar::currentColumnChanged(const QModelIndex &current, const QModelIndex &previous){

}
void Toolbar::currentRowChanged(const QModelIndex &current, const QModelIndex &previous){

}
void Toolbar::setDiagramScene(DiagramScene* scene){
    diagramScene = scene;
}


