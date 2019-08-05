#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QContextMenuEvent>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "properties.h"
#include "toolbar.h"
#include <QSplitter>
#include <QPushButton>
#include <diagramscene.h>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *widget = new QWidget;
        setCentralWidget(widget);

        QWidget *topFiller = new QWidget;
        topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QWidget *bottomFiller = new QWidget;
        bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



        DiagramView* view = new DiagramView();
        DiagramScene* scene = new DiagramScene(view);
        view->setScene(scene);

        scene->setMode(scene->DrawObject);


        //this->setStyleSheet("background-image:url(:/1.png)");
        //view->show();



        //Properties* properties = new Properties();

        //QAction* lineAction = new QAction;
        //QAction* selectAction = new QAction;
        //QActionGroup *actionGroup = new QActionGroup(lineAction);
        //actionGroup->addAction(selectAction);
        //QToolBar* drawingToolBar = new QToolBar;

        Toolbar* toolbar = new Toolbar();
        toolbar->setOrientation(Qt::Vertical);
        QAction *action = new QAction("bla", this);
        QAction *action2 = new QAction("blab", this);
        QAction *action3 = new QAction("blaasdasd", this);
        toolbar->addAction(action);
        toolbar->addAction(action2);
        toolbar->addAction(action3);

        QComboBox *iconComboBox = new QComboBox;
        iconComboBox->addItem(QIcon(":/images/bad.svg"), tr("Bad"));
        iconComboBox->addItem(QIcon(":/images/heart.svg"), tr("Heart"));
        iconComboBox->addItem(QIcon(":/images/trash.svg"), tr("Trash"));

        QHBoxLayout* layout = new QHBoxLayout;
        layout->setContentsMargins(0,0,0,0);



        QSplitter *splitter = new QSplitter(parent);

        layout->addWidget(view);
        layout->addWidget(iconComboBox);

        //layout->addWidget(splitter);
        //splitter->addWidget(drawingToolBar);
        //splitter->addWidget(toolbar);
        //splitter->addWidget(view);
        //splitter->addWidget(properties);
        //splitter->setCursor(QCursor(Qt::SizeHorCursor));

        //layout->addItem(toolbar);
        //layout->addWidget(view);
        //layout->addItem(properties);
        //
        widget->setLayout(layout);


        createActions();
          createMenus();

          setWindowTitle(tr("Menus"));
          setMinimumSize(160, 160);
          resize(480, 320);
}

void MainWindow::createActions()
{
    //void newFile();
    //void about();
    //void open();

    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(scene->Mode::DrawObject));
    lineAction->setIcon(QIcon(":/icons/line.png"));
    lineAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(scene->Mode::SelectObject));
    selectAction->setIcon(QIcon(":/icons/select.png"));
    selectAction->setCheckable(true);

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(selectAction);


    newAct = new QAction(tr("&New file"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    aboutAct = new QAction(tr("&About"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("About UML Creator"));
    connect(newAct, &QAction::triggered, this, &MainWindow::about);

    openAct = new QAction(tr("&Open file"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Open a file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::open);

//    openAct = new QAction(tr("&Item panel"), this);
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(tr("Open an items panel window"));
//    connect(newAct, &QAction::triggered, this, &MainWindow::open);

//    openAct = new QAction(tr("&Properties panel"), this);
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(tr("Open a file"));
//    connect(newAct, &QAction::triggered, this, &MainWindow::open);
}

void MainWindow::createMenus()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();

    auto editMenu = menuBar()->addMenu(tr("&Edit"));

    auto viewMenu = menuBar()->addMenu(tr("&View"));

    auto toolMenu = menuBar()->addMenu(tr("&Tool"));
    toolMenu->addAction(lineAction);
    toolMenu->addAction(selectAction);
    toolMenu->addActions(actionGroup->actions());

    auto helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();



}

void MainWindow::newFile(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}
void MainWindow::about(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}
void MainWindow::open(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void MainWindow::createConnections(){
    connect(actionGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(actionGroupClicked(QAction*)));
}

void MainWindow::actionGroupClicked(QAction *action){
    scene->setMode(DiagramScene::Mode(action->data().toInt()));
}


#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
