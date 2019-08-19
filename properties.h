#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
class Properties : public QWidget, public QVBoxLayout
{
public:
    Properties();

    //    void change
    //    theme.UIColor
    //    theme.sceneColor
    //    theme.sceneGridColor
    //    theme.activeTextColor
    //    theme.inActiveTextColor
    //    theme.selectedColor

private:
    QSplitter* splitter = new QSplitter;
    enum Selection{Item, Arrow, None};
    //blender
    //Scene
    //Selection (item)
    //Handles
};

#endif // PROPERTIES_H
