#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "element.h"
#include <raylib.h>

void checkOnClick(Element *element);
void checkOnHover(struct Element *button);

void drawButtonSceleteon(struct Element *button);
void drawButtonBorder(struct Element *button);
void drawButtonText(struct Element *button, Font font);