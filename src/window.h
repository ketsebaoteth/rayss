#pragma once
#include <vector>
#include <string>
#include <raylib.h>

struct window
{
    // window properties
    int posx = 50;
    int posy = 50;
    int width = 800;
    int height = 600;
    std::vector<unsigned char> bgColor = {0, 0, 0, 255};
    std::string title = "Default window title";
    // flags
    bool isResizable = true;
    bool isMaximized = false;
    bool isMinimized = false;
    bool isOnTop = false;
    bool highDpi = true;
    bool msaa4x = true;
    bool frameLess = false;
    // callbacks
    void (*onResize)() = nullptr;
    void (*onClose)() = nullptr;
    void (*onMinimize)() = nullptr;
    void (*onMaximize)() = nullptr;
};

void createWindow(struct window *window);
void windowLoopFunction(void (*func)(), struct window *window);
void onWindowResize(struct window *window);
void onWindowClosed(struct window *window);
void onWindowMinimize(struct window *window);
void onWindowMaximize(struct window *window);

// Get the screen size
std::vector<int> getScreenSize();
// Get the window size
std::vector<int> getWindowSize(struct window *window);
// Get window pixel color at location x,y
std::vector<unsigned char> getPixelColor(int x, int y);