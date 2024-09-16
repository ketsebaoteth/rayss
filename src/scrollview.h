#pragma once

#include <vector>
#include <string>
#include "element.h"
#include "elementtree.h"

void drawScrollArea(struct Element *element, elementtree *tree);
void drawScrollElements(struct Element *element, std::string direction);
void getScrollDistance();
void setScrollArea(int distance);
void scrollTo(std::string id);
void scrollToTop();
void scrollToBottom();
void scrollToLeft();
void scrollToRight();
void setMaxScrollDistance(int distance);
