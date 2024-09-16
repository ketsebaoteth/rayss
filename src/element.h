#pragma once
#include <vector>
#include <string>
#include <raylib.h>

struct Element;

struct stylesheet
{
    std::string text = "Button";
    std::string id = "button";
    std::vector<Element> children;
    int posx = 50;
    int posy = 50;
    int width = 100;
    int height = 50;
    int fontSize = 20;
    std::vector<int> backgroundColor = {227, 227, 227, 255};
    std::vector<int> color = {255, 255, 255, 255};
    std::string display = "flex";
    std::string flexdirection = "row";
    std::string justifycontent = "center";
    std::string alignitems = "center";
    std::string border = "1px solid black";
    std::vector<float> padding = {5.0f, 5.0f, 5.0f, 5.0f};
    std::vector<float> margin = {5.0f, 5.0f, 5.0f, 5.0f};
    float borderWidth = 1.5f;
    float scale = 1.0f;
    float gap = 0.0f;
    std::vector<int> borderColor = {111, 112, 112, 255};
    std::vector<int> scrollBarColor = {111, 112, 112, 255};
    std::vector<int> scrollBarThubBgColor = {111, 112, 112, 255};
    float scrollBarWidth = 10.0;
    float borderRadius = 0.3f;
    bool isPressed = false;
    bool isHover = false;
    void (*onClick)(Element *);
    void (*onHover)(Element *);
    void (*onHoverOut)(Element *);
    void checkOnClick();
    void checkOnHover();
};

enum elementtype
{
    BUTTON,
    TEXT,
    SCROLLVIEW,
    IMAGE,
    INPUT,
    DIV
};

struct Element
{
    elementtype type;
    stylesheet style;
};