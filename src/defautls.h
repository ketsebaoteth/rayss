#include "stylesheet.h"
#include <vector>
#include <string>
#include <raylib.h>

stylesheet defaultButton = {
    .text = "Button",
    .id = "button",
    .posx = 50,
    .posy = 50,
    .width = 120,
    .height = 10,
    .fontSize = 19,
    .backgroundColor = {255, 255, 255, 255}, // White background
    .color = {255, 255, 255, 255},           // Black text color
    .display = "block",
    .flexdirection = "row",
    .justifycontent = "center",
    .alignitems = "center",
    .border = "1px solid black",
    .padding = {10.0f, 20.0f, 10.0f, 20.0f}, // Padding for a larger clickable area
    .margin = {0.0f, 0.0f, 0.0f, 0.0f},      // Margin for spacing between elements
    .borderWidth = 1.2f,                     // Slightly thicker border
    .scale = 1.0f,
    .borderColor = {176, 176, 176, 150}, // Black border color
    .borderRadius = 0.2f,                // Rounded corners
    .isPressed = false,
    .isHover = false,
    .onClick = nullptr,
    .onHover = nullptr,
    .onHoverOut = nullptr,
    // Additional CSS properties to be implemented later
    // .boxShadow = "0 4px 6px rgba(0, 0, 0, 0.1)",
    // .transition = "all 0.2s ease-in-out",
    // .hoverBackgroundColor = {245, 245, 245, 255}, // Slightly darker background on hover
    // .hoverBorderColor = {0, 0, 0, 255}, // Darker border on hover
    // .activeBackgroundColor = {230, 230, 230, 255}, // Even darker background on active
    // .activeBorderColor = {0, 0, 0, 255}, // Darker border on active
};

stylesheet defaultScrollarea = {
    .text = "Button",
    .id = "button",
    .posx = 50,
    .posy = 50,
    .width = 180,
    .height = 60,
    .fontSize = 19,
    .backgroundColor = {255, 255, 255, 255}, // White background
    .color = {255, 255, 255, 255},           // Black text color
    .display = "block",
    .flexdirection = "row",
    .justifycontent = "center",
    .alignitems = "center",
    .border = "1px solid black",
    .padding = {5.0f, 5.0f, 5.0f, 5.0f},    // Padding for a larger clickable area
    .margin = {10.0f, 10.0f, 10.0f, 10.0f}, // Margin for spacing between elements
    .borderWidth = 0.0f,                    // Slightly thicker border
    .scale = 1.0f,
    .gap = 0.0f,
    .borderColor = {176, 176, 176, 150}, // Black border color
    .scrollBarColor = {111, 112, 112, 255},
    .scrollBarThubBgColor = {0, 0, 112, 255},
    .scrollBarWidth = 10.0f,
    .borderRadius = 0.2f, // Rounded corners
    .isPressed = false,
    .isHover = false,
    .onClick = nullptr,
    .onHover = nullptr,
    .onHoverOut = nullptr,
    // Additional CSS properties to be implemented later
    // .boxShadow = "0 4px 6px rgba(0, 0, 0, 0.1)",
    // .transition = "all 0.2s ease-in-out",
    // .hoverBackgroundColor = {245, 245, 245, 255}, // Slightly darker background on hover
    // .hoverBorderColor = {0, 0, 0, 255}, // Darker border on hover
    // .activeBackgroundColor = {230, 230, 230, 255}, // Even darker background on active
    // .activeBorderColor = {0, 0, 0, 255}, // Darker border on active
};