#pragma once
#include "element.h"
#include <vector>
#include <memory>
#include <raylib.h>

class elementtree
{
public:
    std::vector<Element> elements;
    Font defaultFont = GetFontDefault();
    void render();
    void renderSpecficElement(Element *element);
};