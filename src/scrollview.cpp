#include "scrollview.h"
#include "elementtree.h"
#include <iostream>

void drawScrollSkeleton(Element *element)
{
    Color newbackgroundcolor = {element->style.backgroundColor[0], element->style.backgroundColor[1], element->style.backgroundColor[2], element->style.backgroundColor[3]};
    Color newbordercolor = {element->style.borderColor[0], element->style.borderColor[1], element->style.borderColor[2], element->style.borderColor[3]};
    DrawRectangleRounded((Rectangle){(float)element->style.posx, element->style.posy, element->style.width, element->style.height}, element->style.borderRadius, 15, newbackgroundcolor);
    if (element->style.borderWidth <= 0.0f)
    {
        return;
    }
    else
    {
        DrawRectangleRoundedLines((Rectangle){(float)element->style.posx, element->style.posy, element->style.width, element->style.height}, element->style.borderRadius, 15, element->style.borderWidth, newbordercolor);
    }
}

void drawScrollElements(Element *element, std::string direction, elementtree *tree)
{
    int concatedX = 0;
    int concatedY = 0;

    // Begin scissor mode to clip child elements
    BeginScissorMode(element->style.posx, element->style.posy, element->style.width, element->style.height);

    for (auto &child : element->style.children)
    {
        // Adjust the position of the child element considering padding and margin
        child.style.posx = element->style.posx + element->style.padding[0] + concatedX + child.style.margin[0];
        child.style.posy = element->style.posy + element->style.padding[1] + concatedY + child.style.margin[1];
        if (direction == "horizontal")
        {
            child.style.posx -= element->style.scrollDistance;
        }
        else
        {
            child.style.posy -= element->style.scrollDistance;
        }

        // Update the concatenated position for the next child element
        if (direction == "horizontal")
        {
            concatedX += child.style.width + child.style.margin[0] + child.style.padding[0] + child.style.padding[2] + child.style.margin[2] + child.style.borderWidth * 2 + element->style.gap;
        }
        else
        {
            concatedY += child.style.height + child.style.margin[1] + child.style.margin[3] + element->style.gap + child.style.padding[1] + child.style.padding[3] + child.style.borderWidth * 2;
        }

        // Render the specific child element
        tree->renderSpecficElement(&child);
    }

    // End scissor mode
    EndScissorMode();
}

// Converts a vector of integers to a raylib color
Color rgbaToraylibColorsc(std::vector<int> col)
{
    return (Color){static_cast<unsigned char>(col[0]), static_cast<unsigned char>(col[1]), static_cast<unsigned char>(col[2]), static_cast<unsigned char>(col[3])};
}

void drawScrollThubTrack(Element *element, elementtree *tree, std::string direction)
{
    BeginScissorMode(element->style.posx, element->style.posy, element->style.width, element->style.height);

    if (direction == "vertical")
    {
        DrawRectangleRounded((Rectangle){
                                 element->style.posx + element->style.width - element->style.scrollBarWidth,
                                 element->style.posy,
                                 element->style.scrollBarWidth,
                                 element->style.height},
                             element->style.borderRadius, 15, rgbaToraylibColorsc(element->style.scrollBarColor));
        DrawRectangleRoundedLines((Rectangle){
                                      element->style.posx + element->style.width - element->style.scrollBarWidth,
                                      element->style.posy,
                                      element->style.scrollBarWidth,
                                      element->style.height},
                                  element->style.borderRadius, 15, element->style.borderWidth, rgbaToraylibColorsc(element->style.borderColor));
    }
    else if (direction == "horizontal")
    {
        DrawRectangleRounded((Rectangle){
                                 element->style.posx,
                                 element->style.posy + element->style.height - element->style.scrollBarWidth,
                                 element->style.width,
                                 element->style.scrollBarWidth},
                             element->style.borderRadius, 15, rgbaToraylibColorsc(element->style.scrollBarColor));
        DrawRectangleRoundedLines((Rectangle){
                                      element->style.posx,
                                      element->style.posy + element->style.height - element->style.scrollBarWidth,
                                      element->style.width,
                                      element->style.scrollBarWidth},
                                  element->style.borderRadius, 15, element->style.borderWidth, rgbaToraylibColorsc(element->style.borderColor));
    }
    EndScissorMode();
}

void drawScrollThub(Element *element, std::string direction, elementtree *tree)
{
    int concatedheight = 0;

    for (auto &childrens : element->style.children)
    {
        concatedheight += childrens.style.height + childrens.style.margin[1] + childrens.style.margin[3] + element->style.gap + childrens.style.padding[1] + childrens.style.padding[3] + childrens.style.borderWidth * 2;
    }
    int viewportheight = element->style.height;
    float scrollRatio = static_cast<float>(viewportheight) / static_cast<float>(concatedheight);
    float thubHeight = viewportheight * scrollRatio;
    float thubWidth = 5;

    // Calculate the maximum scroll distance
    float maxScrollDistance = concatedheight - viewportheight;

    // Calculate the thumb position based on the scroll distance
    float thumbPosition = (element->style.scrollDistance / maxScrollDistance) * (viewportheight - thubHeight);

    // Clamp the thumb position to ensure it stays within the bounds
    if (thumbPosition < 0)
    {
        thumbPosition = 0;
    }
    if (thumbPosition > viewportheight - thubHeight)
    {
        thumbPosition = viewportheight - thubHeight;
    }

    if (direction == "vertical")
    {
        DrawRectangleRounded((Rectangle){
                                 element->style.posx + element->style.width - (element->style.scrollBarWidth / 2) - thubWidth / 2,
                                 element->style.posy + thumbPosition,
                                 thubWidth,
                                 thubHeight},
                             element->style.borderRadius, 15, rgbaToraylibColorsc(element->style.scrollBarThubBgColor));
    }
}

void handleScroll(Element *element)
{
    float wheelMove = GetMouseWheelMove();
    float scale = element->style.isHover ? element->style.scale : 1.0f;
    float scaledWidth = element->style.width * scale;
    float scaledHeight = element->style.height * scale;
    float scaledPosX = element->style.posx - (scaledWidth - element->style.width) / 2;
    float scaledPosY = element->style.posy - (scaledHeight - element->style.height) / 2;

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){scaledPosX + element->style.margin[0], scaledPosY + element->style.margin[1], scaledWidth + element->style.margin[0] + element->style.margin[2] + element->style.padding[0] + element->style.padding[2], scaledHeight + element->style.margin[1] + element->style.margin[3] + element->style.padding[1] + element->style.padding[3]}))
    {
        element->style.scrollDistance += wheelMove * -element->style.scrollSpeed;
    }
    // Clamp scroll distance to prevent scrolling beyond content
    if (element->style.scrollDistance < 0)
    {
        element->style.scrollDistance = 0;
    }
    int concatedheight = 0;
    for (auto &childrens : element->style.children)
    {
        concatedheight += childrens.style.height + childrens.style.margin[1] + childrens.style.margin[3] + element->style.gap + childrens.style.padding[1] + childrens.style.padding[3] + childrens.style.borderWidth * 2;
    }
    if (element->style.scrollDistance > concatedheight - element->style.height)
    {
        element->style.scrollDistance = concatedheight - element->style.height;
    }
}

void drawScrollArea(struct Element *element, elementtree *tree)
{
    std::string direction = "vertical";
    if (element->style.flexdirection == "row")
    {
        direction = "horizontal";
    }
    else
    {
        direction = "vertical";
    }
    if (element->style.autoScroll)
    {
        handleScroll(element);
    }

    drawScrollSkeleton(element);
    drawScrollElements(element, direction, tree);
    if (element->style.showScrollBar)
    {
        drawScrollThubTrack(element, tree, direction);
        drawScrollThub(element, direction, tree);
    }
}