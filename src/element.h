#pragma once
#include <raylib.h>

class Element
{
public:
    virtual ~Element() = default;
    virtual void render(Font font) = 0; // Pure virtual function for rendering
};