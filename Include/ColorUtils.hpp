#include <windows.h>
#include <string>
#include <iostream>
#include <tuple>

class ColorUtils {

public:

    ColorUtils();

    ~ColorUtils();

    static std::tuple<BYTE, BYTE, BYTE> getRgbFromDword(DWORD colorDWORD) {
        
        BYTE red = (colorDWORD >> 16) & 0xFF;
        BYTE green = (colorDWORD >> 8) & 0xFF;
        BYTE blue = colorDWORD & 0xFF;

        return {red, green, blue};
    }

    static COLORREF getColorrefFromDword(DWORD colorDWORD) {

        BYTE red = (colorDWORD >> 16) & 0xFF;
        BYTE green = (colorDWORD >> 8) & 0xFF;
        BYTE blue = colorDWORD & 0xFF;

        return RGB(red, green, blue);
    }

    static BYTE getRedfromDword(DWORD colorDWORD) {
        return (colorDWORD >> 16) & 0xFF;
    }

    static BYTE getGreenfromDword(DWORD colorDWORD) {
        return (colorDWORD >> 8) & 0xFF;
    }

    static BYTE getBluefromDword(DWORD colorDWORD) {
        return colorDWORD & 0xFF;
    }

    static std::string getRgbStringRepresentation(DWORD colorDWORD) {
        return std::format("({},{},{})", getRedfromDword(colorDWORD), getGreenfromDword(colorDWORD), getBluefromDword(colorDWORD));
    }

    static std::string getColorHexRepresentation(COLORREF color) {
        return std::format("#{:02X}", color);
    }

};