#include "window.h"
#include <raylib.h>
#include <iostream>
#include <vector>
#include <utility> // For std::pair

void createWindow(struct window *win)
{
    // assign every bool to the related flag to be applied
    std::vector<std::pair<bool, unsigned int>> flagConditions = {
        {win->isResizable, FLAG_WINDOW_RESIZABLE},
        {win->isMaximized, FLAG_WINDOW_MAXIMIZED},
        {win->isMinimized, FLAG_WINDOW_MINIMIZED},
        {win->isOnTop, FLAG_WINDOW_TOPMOST},
        {win->highDpi, FLAG_WINDOW_HIGHDPI},
        {win->msaa4x, FLAG_MSAA_4X_HINT},
        {win->frameLess, FLAG_WINDOW_UNDECORATED}};

    unsigned int combinedFlags = 0;
    for (const auto &condition : flagConditions)
    {
        if (condition.first)
        {
            combinedFlags |= condition.second;
        }
    }

    SetConfigFlags(combinedFlags);
    InitWindow(win->width, win->height, win->title.c_str());
    SetWindowPosition(win->posx, win->posy);
}

void windowLoopFunction(void (*func)(), struct window *win)
{
    while (!WindowShouldClose())
    {
        if (IsWindowResized() && win->onResize)
        {
            onWindowResize(win);
        }
        if (WindowShouldClose() && win->onClose)
        {
            onWindowClosed(win);
        }
        BeginDrawing();
        ClearBackground(Color{win->bgColor[0], win->bgColor[1], win->bgColor[2], win->bgColor[3]});
        func();
        EndDrawing();
    }
    CloseWindow();
}

void onWindowResize(struct window *win)
{
    if (win->onResize)
    {
        win->onResize();
    }
    win->width = GetScreenWidth();
    win->height = GetScreenHeight();
    win->posx = GetWindowPosition().x;
    win->posy = GetWindowPosition().y;
}

void onWindowClosed(struct window *win)
{
    if (win->onClose)
    {
        win->onClose();
    }
}

void onWindowMinimize(struct window *win)
{
    if (win->onMinimize)
    {
        win->onMinimize();
    }
}

void onWindowMaximize(struct window *win)
{
    if (win->onMaximize)
    {
        win->onMaximize();
    }
}

std::vector<int> getScreenSize()
{
    return {GetScreenWidth(), GetScreenHeight()};
}

std::vector<int> getWindowSize(struct window *window)
{
    return {window->width, window->height};
}

// Get window pixel color at location x,y
std::vector<unsigned char> getPixelColor(int x, int y)
{
    // Get the image data from the screen
    Image screenImage = LoadImageFromScreen();
    // Get the pixel color from the image data
    Color color = GetImageColor(screenImage, x, y);
    // Unload the image data to free memory
    UnloadImage(screenImage);

    return {color.r, color.g, color.b, color.a};
}