#include "elementtree.h"
#include "button.h"
#include "scrollview.h"
#include <iostream>

void elementtree::render()
{
    for (auto &element : this->elements)
    {
        renderSpecficElement(&element);
    }
}

void elementtree::renderSpecficElement(Element *element)
{
    switch (element->type)
    {
    case BUTTON:
        drawButtonSceleteon(element);
        drawButtonBorder(element);
        drawButtonText(element, this->defaultFont);
        checkOnClick(element);
        checkOnHover(element);
        break;

    case SCROLLVIEW:
        drawScrollArea(element, this);
        break;

    default:
        break;
    }
}
