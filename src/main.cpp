#include <raylib.h>
#include "window.h"
#include "button.h"
#include "elementtree.h"
#include "defautls.h"

Font font;
elementtree tree;
window mywin;

void mainloop()
{
    tree.render();
}
void onHov(Element *element)
{
    element->style.backgroundColor = {38, 38, 38, 190};
}
void onHovOut(Element *element)
{
    element->style.backgroundColor = {61, 61, 61, 0};
}
void onclk(Element *element)
{
    std::cout << element->style.text << "clicked" << std::endl;
}

int main()
{
    mywin.bgColor = {31, 31, 31, 255};
    createWindow(&mywin);

    font = LoadFont("fonts/Roboto/Roboto-Regular.ttf");
    tree.defaultFont = font;

    Element sc;
    sc.type = SCROLLVIEW;
    sc.style = defaultScrollarea;
    sc.style.flexdirection = "col";
    sc.style.width = 300;
    sc.style.height = 400;
    sc.style.backgroundColor = {20, 20, 20, 255};
    sc.style.borderColor = {61, 61, 61, 180};
    sc.style.borderRadius = 0.00f;
    sc.style.borderWidth = 0.2f;
    sc.style.gap = 5;
    sc.style.scrollBarColor = {61, 61, 61, 0};
    sc.style.scrollBarThubBgColor = {61, 61, 61, 255};

    for (int i = 0; i < 15; i++)
    {
        Element btn;
        btn.type = BUTTON;
        btn.style = defaultButton;
        btn.style.text = "Button" + std::to_string(i);
        btn.style.backgroundColor = {255, 255, 255, 0};
        btn.style.borderColor = {61, 61, 61, 120};
        btn.style.onHover = onHov;
        btn.style.onHoverOut = onHovOut;
        btn.style.onClick = onclk;
        btn.style.color = {255, 255, 255, 255};
        btn.style.borderWidth = 0.3f;
        sc.style.children.push_back(btn);
    };
    tree.elements.push_back(sc);

    windowLoopFunction(mainloop, &mywin);

    // Unload font and close window
    UnloadFont(font);
    CloseWindow();

    return 0;
}