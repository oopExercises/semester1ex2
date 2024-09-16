#pragma once

#include "Location.h"
enum Keys
{
    KB_Escape = 27,
    SpecialKey = 224,
    
};
enum SpecialKeys
{
    KB_Up = 72,
    KB_Down = 80,
    KB_Left = 75,
    KB_Right = 77,
    KB_Space = 32,
};
namespace Screen
{
// Reset terminal cursor location to start of the screen (0,0)
void resetLocation();
// Set terminal cursor location to the desired location
void setLocation(const Location& location);
}
