#include <windows.h>

class ColorHandler {

private:
    COLORREF defaultBaseColor;

public:
    
    ColorHandler(COLORREF defaultBaseColor) : defaultBaseColor(defaultBaseColor) {}

    ~ColorHandler() {}

    COLORREF getColorPerTimeOfDay(time_t time) {

        //TODO: Implement

        return RGB(0,0,0);
    }
    
    
    COLORREF getDefaultBaseColor() {
        return defaultBaseColor;
    }

    void setDefaultBaseColor(COLORREF newDefaultBaseColor) {
        defaultBaseColor = newDefaultBaseColor;
    }


};