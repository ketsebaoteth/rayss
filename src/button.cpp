#include "button.h"
#include "element.h"
#include <raylib.h>
#include <vector>

void checkOnClick(Element *element)
{
    float scale = element->style.isHover ? element->style.scale : 1.0f;
    float scaledWidth = element->style.width * scale;
    float scaledHeight = element->style.height * scale;
    float scaledPosX = element->style.posx - (scaledWidth - element->style.width) / 2;
    float scaledPosY = element->style.posy - (scaledHeight - element->style.height) / 2;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){scaledPosX + element->style.margin[0], scaledPosY + element->style.margin[1], scaledWidth + element->style.margin[0] + element->style.margin[2] + element->style.padding[0] + element->style.padding[2], scaledHeight + element->style.margin[1] + element->style.margin[3] + element->style.padding[1] + element->style.padding[3]}))
        {
            element->style.isPressed = true;
            if (element->style.onClick != nullptr)
            {
                element->style.onClick(element);
            }
        }
    }
    else
    {
        element->style.isPressed = false;
    }
}

void checkOnHover(Element *element)
{
    float scale = element->style.isHover ? element->style.scale : 1.0f;
    float scaledWidth = element->style.width * scale;
    float scaledHeight = element->style.height * scale;
    float scaledPosX = element->style.posx - (scaledWidth - element->style.width) / 2;
    float scaledPosY = element->style.posy - (scaledHeight - element->style.height) / 2;

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){scaledPosX + element->style.margin[0], scaledPosY + element->style.margin[1], scaledWidth + element->style.margin[0] + element->style.margin[2] + element->style.padding[0] + element->style.padding[2], scaledHeight + element->style.margin[1] + element->style.margin[3] + element->style.padding[1] + element->style.padding[3]}))
    {
        if (!element->style.isHover)
        {
            if (element->style.onHover != nullptr)
            {
                element->style.onHover(element);
            }
            element->style.isHover = true;
        }
    }
    else
    {
        if (element->style.isHover)
        {
            if (element->style.onHoverOut != nullptr)
            {
                element->style.onHoverOut(element);
            }
            element->style.isHover = false;
        }
    }
}

// converts a vector of integers to a raylib color
Color rgbaToraylibColor(std::vector<int> col)
{
    return (Color){static_cast<unsigned char>(col[0]), static_cast<unsigned char>(col[1]), static_cast<unsigned char>(col[2]), static_cast<unsigned char>(col[3])};
};

// draws the main body of a button
void drawButtonSceleteon(struct Element *element)
{
    // Calculate scaled dimensions and position
    float scale = element->style.isHover ? element->style.scale : 1.0f;
    float scaledWidth = element->style.width * scale;
    float scaledHeight = element->style.height * scale;
    float scaledPosX = element->style.posx - (scaledWidth - element->style.width) / 2;
    float scaledPosY = element->style.posy - (scaledHeight - element->style.height) / 2;
    DrawRectangleRounded((Rectangle){(float)scaledPosX + element->style.margin[0], (float)scaledPosY + element->style.margin[1], (float)scaledWidth + element->style.padding[0] + element->style.padding[2], (float)scaledHeight + element->style.padding[1] + element->style.padding[3]}, element->style.borderRadius, 15, rgbaToraylibColor(element->style.backgroundColor));
}

// draws the border for a button if it has one
void drawButtonBorder(struct Element *element)
{
    // Calculate scaled dimensions and position
    float scale = element->style.isHover ? element->style.scale : 1.0f;
    float scaledWidth = element->style.width * scale;
    float scaledHeight = element->style.height * scale;
    float scaledPosX = element->style.posx - (scaledWidth - element->style.width) / 2;
    float scaledPosY = element->style.posy - (scaledHeight - element->style.height) / 2;
    DrawRectangleRoundedLines((Rectangle){(float)scaledPosX + element->style.margin[0], (float)scaledPosY + element->style.margin[1], (float)scaledWidth + element->style.padding[0] + element->style.padding[2], (float)scaledHeight + element->style.padding[1] + element->style.padding[3]}, element->style.borderRadius, 15, element->style.borderWidth, rgbaToraylibColor(element->style.borderColor));
}

// draws the text for a button
void drawButtonText(struct Element *element, Font font)
{
    // Calculate scaled dimensions and position
    float scale = element->style.isHover ? element->style.scale : 1.0f;
    float scaledWidth = element->style.width * scale;
    float scaledHeight = element->style.height * scale;
    float scaledPosX = element->style.posx - (scaledWidth - element->style.width) / 2;
    float scaledPosY = element->style.posy - (scaledHeight - element->style.height) / 2;
    Color textcolor = {element->style.color[0], element->style.color[1], element->style.color[2], element->style.color[3]};
    // Generate mipmaps and set texture filter for better quality
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    // Calculate the text position based on button position, margin, and padding
    Vector2 textpos;
    if (element->style.display == "flex")
    {
        textpos = {
            scaledPosX + element->style.margin[0] + element->style.padding[0],
            scaledPosY + element->style.margin[1] + element->style.padding[1]};
    }
    else if (element->style.display == "block")
    {
        textpos = {
            scaledPosX + element->style.margin[0] + element->style.padding[0] + scaledWidth / 2 - MeasureTextEx(font, element->style.text.c_str(), element->style.fontSize * scale, 2).x / 2,
            scaledPosY + element->style.margin[1] + element->style.padding[1] + scaledHeight / 2 - MeasureTextEx(font, element->style.text.c_str(), element->style.fontSize * scale, 2).y / 2};
    }

    // Draw the text with the specified font
    DrawTextEx(font, element->style.text.c_str(), textpos, element->style.fontSize * scale, 2, textcolor);
}