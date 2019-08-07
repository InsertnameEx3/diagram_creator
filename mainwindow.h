// dialog.h

#ifndef DIALOG_H
#define DIALOG_H
#include <QMainWindow>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QAction>
#include "diagramview.h"
#include "diagramscene.h"
#include "toolbar.h"
#include "properties.h"
#include <QGridLayout>
#include <QToolBar>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Diagram{SequenceDiagram, CaseDiagram, ClassDiagram};
    enum Key{Ctrl, Shift, Alt};
    void actionGroupClicked(QAction*);
    explicit MainWindow(QWidget *parent = nullptr);
    Toolbar* toolbar;
private:
    void createActions();
    void createMenus();
    Ui::MainWindow *ui;
    QGridLayout* layout = new QGridLayout;
    //The widget for showing the diagram scene
    DiagramView *view;
    //
    DiagramScene* scene;
    //The widget containing all the necessary tools

    //The widget containing all the properties of a selection
    Properties* properties;
    QAction *openProject;
    QAction *newProject;
    QAction *openAct;
    QAction *aboutAct;
    QAction *newAct;
    void createConnections();
    void createToolBar();
    QAction* lineAction;
    QAction* selectAction;
    QActionGroup *actionGroup;
    QToolBar* drawingToolBar;

private slots:
    void newFile();
    void open();
    void about();

protected:
    #ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
    #endif // QT_NO_CONTEXTMENU

};
#endif // DIALOG_H
