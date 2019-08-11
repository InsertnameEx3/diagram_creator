#include "toolbar.h"
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QToolBar>
#include "mainwindow.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QDebug>
#include <QFileSystemModel>




Toolbar::Toolbar()
{

CreateTools();


//        QFile styleSheet("/home/marten/projects/diagram-creator/toolbar.qss");
//        if(!styleSheet.open(QFile::ReadOnly))
//                QMessageBox::information(nullptr, "Error", styleSheet.errorString());
//        QString StyleSheet = QLatin1String(styleSheet.readAll());


//        this->setStyleSheet(StyleSheet);

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

    //QStandardItemModel* model_drzewa = new QStandardItemModel;


//    QStandardItem* shapes = new QStandardItem("Shapes");
//    QStandardItem* rectangle = new QStandardItem("Rectangle");
//    QStandardItem* ellipse = new QStandardItem("Ellipse");
//    QStandardItem* line = new QStandardItem("Line");

//    model_drzewa->appendRow(shapes);
//    shapes->appendRow(rectangle);
//    shapes->appendRow(ellipse);
//    shapes->appendRow(line);


    //model_drzewa->setHeaderData(0, Qt::Horizontal, "asd");
    //this->setModel(model_drzewa);
    //this->expandAll();

}
void Toolbar::CreateTools(){

    QTreeWidgetItem* wiptr = nullptr;
    for(auto category : {"Shapes"}){
        wiptr = new QTreeWidgetItem(QStringList(category), 0);
        this->addTopLevelItem(wiptr);
        categories.append(wiptr);
    }

    for(auto category : categories){
        for(auto tool : {"Rectangle", "Ellipse", "Line", "Image", "SimpleText", "Text"}){
            wiptr = new QTreeWidgetItem(QStringList(tool), 0);
            category->addChild(wiptr);
            tools.append(wiptr);
        }
    }


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
            selection = SelectedItem::Image;
        break;
        case 4:
            selection = SelectedItem::SimpleText;
        break;
        case 5:
            selection = SelectedItem::Text;
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


