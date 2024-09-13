#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "element.h"
#include <raylib.h>

class button : public Element
{
public:
    std::string text = "Button";
    std::string id = "button";
    int posx = 50;
    int posy = 50;
    int width = 100;
    int height = 50;
    int fontSize = 20;
    std::vector<int> backgroundColor = {227, 227, 227, 255};
    Color color = BLACK;
    std::string display = "flex";
    std::string flexdirection = "row";
    std::string justifycontent = "center";
    std::string alignitems = "center";
    std::string border = "1px solid black";
    std::vector<float> padding = {5.0f, 5.0f, 5.0f, 5.0f};
    std::vector<float> margin = {5.0f, 5.0f, 5.0f, 5.0f};
    float borderWidth = 1.5f;
    float scale = 1.0f;
    std::vector<int> borderColor = {111, 112, 112, 255};
    float borderRadius = 0.3f;
    bool isPressed = false;
    bool isHover = false;
    void render(Font font) override;
    void (*onClick)(void *);
    void (*onHover)(void *);
    void (*onHoverOut)(void *);
    void checkOnClick();
    void checkOnHover();
    void checkOnHoverOut();
};

void drawButtonSceleteon(struct button *button);
void drawButtonBorder(struct button *button);
void drawButtonText(struct button *button, Font font);