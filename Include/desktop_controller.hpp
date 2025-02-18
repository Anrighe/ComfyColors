#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "color_utils.hpp"

class DesktopController {

private:

    const int cElements = 1;
    const int lpaElements[1] = {COLOR_DESKTOP};

    COLORREF desktopBackgroundColor = CLR_INVALID;
    COLORREF lpaRgbValues[1] = {desktopBackgroundColor};

    COLORREF fetchDesktopBackgroundColor() {
        DWORD desktopBackgroundColorDWORD = GetSysColor(cElements);
        return ColorUtils::getColorrefFromDword(desktopBackgroundColorDWORD);
    }

public:

    DesktopController() {
        desktopBackgroundColor = fetchDesktopBackgroundColor();
    }

    void setDesktopBackgroundColorColorref(const COLORREF desktopBackgroundColorToSet) {
        constexpr int numElements = 1;
        constexpr int displayElements[] = {COLOR_DESKTOP};

        COLORREF newColors[] = {desktopBackgroundColorToSet};

        SetSysColors(numElements, displayElements, newColors);
    }

    void setDesktopBackgroundColorRGB(int red, int green, int blue) {
        desktopBackgroundColor = RGB(red, green, blue);
        *lpaRgbValues = {desktopBackgroundColor};
    }

    void changeDesktopBackgroundColor() {
        SetSysColors(cElements, lpaElements, lpaRgbValues);
    }
    
    void adjustBrightness() {
        // IMPLEMENT IN THE FUTURE IF NEEDED
    }

    void resetBackgroundColorToDefault() {
        // IMPLEMENT IN THE FUTURE IF NEEDED
    }

    void resetToDefault() {
        // IMPLEMENT IN THE FUTURE IF NEEDED
    }

    COLORREF getDesktopBackgroundColor() {
        if (desktopBackgroundColor == CLR_INVALID) {
            desktopBackgroundColor = fetchDesktopBackgroundColor();
        }
        return desktopBackgroundColor;
    }

};