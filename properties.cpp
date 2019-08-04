#include "properties.h"
#include <QPushButton>
Properties::Properties()
{
    this->setStyleSheet("background-color: black");
    QPushButton *button4 = new QPushButton("Four");
    this->addWidget(button4);

}
