#include "elementtree.h"

void elementtree::render()
{
    for (const auto &element : elements)
    {
        element->render(this->defaultFont);
    }
}