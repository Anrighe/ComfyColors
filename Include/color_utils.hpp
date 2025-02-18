

#include <winsock2.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <tuple>

class ColorUtils {

public:

    ColorUtils();

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

    // RGB values in COLORREF are store in the opposite "direction" as BGR and not RGB

    static uint8_t getBluefromColorref(COLORREF color) {
        return (color >> 16) & 0xFF;
    }
    
    static uint8_t getGreenfromColorref(COLORREF color) {
        return (color >> 8) & 0xFF;
    }
    
    static uint8_t getRedfromColorref(COLORREF color) {
        return color & 0xFF;
    }

    static std::string getRgbStringRepresentation(COLORREF color) {
        return std::format("({},{},{})", getRedfromColorref(color), getGreenfromColorref(color), getBluefromColorref(color));
    }

    static std::string getColorHexRepresentation(COLORREF color) {
        return std::format("#{:02X}", color);
    }

    static COLORREF HexToColorRef(const std::string& hex) {
        if (hex.size() != 7 || hex[0] != '#') {
            return RGB(0, 0, 0); // Default to black if invalid
        }
    
        int r, g, b;
        std::istringstream(hex.substr(1, 2)) >> std::hex >> r;
        std::istringstream(hex.substr(3, 2)) >> std::hex >> g;
        std::istringstream(hex.substr(5, 2)) >> std::hex >> b;
    
        return RGB(r, g, b);
    }

};