#pragma once
#include "element.h"
#include <vector>
#include <memory>
#include <raylib.h>

class elementtree
{
public:
    std::vector<std::unique_ptr<Element>> elements;
    Font defaultFont = GetFontDefault();
    void render();
};