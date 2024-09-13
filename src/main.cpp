#include <raylib.h>
#include "window.h"
#include "button.h"
#include "elementtree.h"

Font font;
elementtree tree;
window mywin;

void mainloop()
{
    tree.render();
}
void sayhi(void *btn)
{
    std::cout << "Hi" << std::endl;
}
void btnhov(void *btn)
{
    // change btn color
    auto b = (button *)btn;
    b->backgroundColor = {232, 232, 232, 255};
    b->scale = 1.3f;
}
void btnhovout(void *btn)
{
    // change btn color
    auto b = (button *)btn;
    b->backgroundColor = {227, 227, 227, 255};
    b->scale = 1.0f;
}
int main()
{
    mywin.bgColor = {255, 255, 255, 255};
    createWindow(&mywin);

    font = LoadFont("fonts/Roboto/Roboto-Regular.ttf");
    tree.defaultFont = font;

    // Create a button and add it to the element tree
    auto btn = std::make_unique<button>();
    btn->text = "Click me!";
    btn->width = 100;
    btn->height = 23;
    btn->onClick = sayhi;
    btn->onHover = btnhov;
    btn->onHoverOut = btnhovout;
    btn->display = "block";

    tree.elements.push_back(std::move(btn));

    windowLoopFunction(mainloop, &mywin);

    // Unload font and close window
    UnloadFont(font);
    CloseWindow();

    return 0;
}