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


    QList<QStandardItem *>  items,items2;

        auto model_drzewa= new QStandardItemModel;


        QStandardItem *z1 = new QStandardItem(  "Shapes" );
        QStandardItem *z1_1 = new QStandardItem(  "Rectangle" );
        QStandardItem *z1_2 = new QStandardItem(  "Ellipse" );
        QStandardItem *z1_3 = new QStandardItem(  "Line" );
        QStandardItem *z1_4 = new QStandardItem(  "Polygon" );

        model_drzewa->invisibleRootItem()->appendRow(z1);
        z1->appendRow(z1_1);
        z1->appendRow(z1_2);
        z1->appendRow(z1_3);
        z1->appendRow(z1_4);

        model_drzewa->setHeaderData(0, Qt::Horizontal, "");
        this->setModel(model_drzewa);


        this->expandAll();



        QFile styleSheet("/home/marten/projects/diagram-creator/toolbar.qss");
        if(!styleSheet.open(QFile::ReadOnly))
                QMessageBox::information(nullptr, "Error", styleSheet.errorString());
        QString StyleSheet = QLatin1String(styleSheet.readAll());


        this->setStyleSheet(StyleSheet);

}


/* (Tree) For example:
 *
 * Class: (Category)
 *  table (Tool)
 * Relations:
 *  One to many
 *  One to one
 *  Many to many
*/
void Toolbar::CreateCategories(){



}
void Toolbar::CreateTools(){



}


void Toolbar::currentChanged(const QModelIndex &current, const QModelIndex &previous){

    //DiagramScene::setMode(DiagramScene::DrawObject);
    //change selection

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


