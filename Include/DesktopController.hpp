#include <iostream>
#include <string>
#include <sstream>
#include "ColorUtils.hpp"

class DesktopController {

private:
    
    const int cElements = 1;
    const int lpaElements[1] = {COLOR_DESKTOP};

    COLORREF desktopBackgroundColor = CLR_INVALID;
    COLORREF lpaRgbValues[1] = {desktopBackgroundColor};

    void setBrightnessLevel() {
        // IMPLEMENT IN THE FUTURE IF NEEDED
    }

    COLORREF fetchDesktopBackgroundColor() {
        DWORD desktopBackgroundColorDWORD = GetSysColor(cElements);
        return ColorUtils::getColorrefFromDword(desktopBackgroundColorDWORD);
    }

public:

    DesktopController() {
        desktopBackgroundColor = fetchDesktopBackgroundColor();
    }

    ~DesktopController() {
        // TODO: handle destructor
    }

    void setDesktopBackgroundColor(int red, int green, int blue) {
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