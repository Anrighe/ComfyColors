#include <windows.h>

class ColorHandler {

private:
    COLORREF defaultBaseColor;

public:
    
    ColorHandler(COLORREF defaultBaseColor) : defaultBaseColor(defaultBaseColor) {}

    ~ColorHandler() {}

    // function to implement: e^(-(x - μ)^2/(2 σ^2))/(sqrt(2 π) σ) 
    // Gaussian
    // TODO: use a y axis offset? need to think

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