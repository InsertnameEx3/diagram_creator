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
