#include "button.h"
#include <raylib.h>
#include <vector>

void button::checkOnClick()
{
    float scale = isHover ? this->scale : 1.0f;
    float scaledWidth = width * scale;
    float scaledHeight = height * scale;
    float scaledPosX = posx - (scaledWidth - width) / 2;
    float scaledPosY = posy - (scaledHeight - height) / 2;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){scaledPosX + margin[0], scaledPosY + margin[1], scaledWidth + margin[0] + padding[0], scaledHeight + margin[1] + padding[1]}))
        {
            isPressed = true;
            if (onClick != nullptr)
            {
                onClick(this);
            }
        }
    }
    else
    {
        isPressed = false;
    }
}

void button::checkOnHover()
{
    float scale = isHover ? this->scale : 1.0f;
    float scaledWidth = width * scale;
    float scaledHeight = height * scale;
    float scaledPosX = posx - (scaledWidth - width) / 2;
    float scaledPosY = posy - (scaledHeight - height) / 2;

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){scaledPosX + margin[0], scaledPosY + margin[1], scaledWidth + margin[0] + padding[0], scaledHeight + margin[1] + padding[1]}))
    {
        if (!isHover && onHover != nullptr)
        {
            onHover(this);
        }
        isHover = true;
    }
    else
    {
        if (isHover && onHoverOut != nullptr)
        {
            onHoverOut(this);
        }
        isHover = false;
    }
}

void button::render(Font font)
{
    checkOnClick();
    checkOnHover();
    drawButtonSceleteon(this);
    drawButtonBorder(this);
    drawButtonText(this, font);
}

// converts a vector of integers to a raylib color
Color rgbaToraylibColor(std::vector<int> col)
{
    return (Color){col[0], col[1], col[2], col[3]};
}

// draws the main body of a button
void drawButtonSceleteon(struct button *button)
{
    // Calculate scaled dimensions and position
    float scale = button->isHover ? button->scale : 1.0f;
    float scaledWidth = button->width * scale;
    float scaledHeight = button->height * scale;
    float scaledPosX = button->posx - (scaledWidth - button->width) / 2;
    float scaledPosY = button->posy - (scaledHeight - button->height) / 2;
    DrawRectangleRounded((Rectangle){(float)scaledPosX + button->margin[0], (float)scaledPosY + button->margin[1], (float)scaledWidth + button->padding[0] + button->padding[2], (float)scaledHeight + button->padding[1] + button->padding[3]}, button->borderRadius, 15, rgbaToraylibColor(button->backgroundColor));
}

// draws the border for a button if it has one
void drawButtonBorder(struct button *button)
{
    // Calculate scaled dimensions and position
    float scale = button->isHover ? button->scale : 1.0f;
    float scaledWidth = button->width * scale;
    float scaledHeight = button->height * scale;
    float scaledPosX = button->posx - (scaledWidth - button->width) / 2;
    float scaledPosY = button->posy - (scaledHeight - button->height) / 2;
    DrawRectangleRoundedLines((Rectangle){(float)scaledPosX + button->margin[0], (float)scaledPosY + button->margin[1], (float)scaledWidth + button->padding[0] + button->padding[2], (float)scaledHeight + button->padding[1] + button->padding[3]}, button->borderRadius, 15, button->borderWidth, rgbaToraylibColor(button->borderColor));
}

// draws the text for a button
void drawButtonText(struct button *button, Font font)
{
    // Calculate scaled dimensions and position
    float scale = button->isHover ? button->scale : 1.0f;
    float scaledWidth = button->width * scale;
    float scaledHeight = button->height * scale;
    float scaledPosX = button->posx - (scaledWidth - button->width) / 2;
    float scaledPosY = button->posy - (scaledHeight - button->height) / 2;
    // Generate mipmaps and set texture filter for better quality
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    // Calculate the text position based on button position, margin, and padding
    Vector2 textpos;
    if (button->display == "flex")
    {
        textpos = {
            scaledPosX + button->margin[0] + button->padding[0],
            scaledPosY + button->margin[1] + button->padding[1]};
    }
    else if (button->display == "block")
    {
        textpos = {
            scaledPosX + button->margin[0] + button->padding[0] + scaledWidth / 2 - MeasureTextEx(font, button->text.c_str(), button->fontSize * scale, 2).x / 2,
            scaledPosY + button->margin[1] + button->padding[1] + scaledHeight / 2 - MeasureTextEx(font, button->text.c_str(), button->fontSize * scale, 2).y / 2};
    }

    // Draw the text with the specified font
    DrawTextEx(font, button->text.c_str(), textpos, button->fontSize * scale, 2, BLACK);
}