#include "toolbar.h"
#include <QPushButton>
Toolbar::Toolbar()
{
    //this->addSpacing(1000);

    QPushButton *button4 = new QPushButton("Four");
    this->addWidget(button4);
    this->splitter->addWidget(button4);
    //this->addWidget(button4);

    //DiagramItem c = new DiagramItem();
    //this->items.append(c);
}
