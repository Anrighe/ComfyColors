#include <winsock2.h>
#include <windows.h>
#include "Settings.hpp"
#include "SolarCycleResponse.hpp"
#include "TimeUtils.hpp"

#define MAXIMUM_BRIGHTNESS_PERCENTAGE 100

class ColorHandler {

private:
    COLORREF defaultBaseColor;
    unsigned short brightnessReductionPercentage;
    unsigned short maximumBrightnessTimePercentage;
    std::string desktopDefaultColorHex;

    time_t sunrise;
    time_t sunset;

    time_t firstLight; // 1739598046
    time_t lastLight; //  1739647445

    time_t maximumBrightnessTimeStart; 
    time_t maximumBrightnessTimeEnd;

    unsigned int secondsFromFirstToLastLight;
    unsigned int secondsOfMaximumBrightness;
    unsigned int secondsOfSingleVariableBrightnessChange;


public:
    
    ColorHandler(Settings settings, SolarCycleResponse solarCycleResponse) {
        brightnessReductionPercentage = settings.getBrightnessReductionPercentage();
        maximumBrightnessTimePercentage = settings.getMaximumBrightnessTimePercentage();
        defaultBaseColor = settings.getDesktopDefaultColorColorref();
        desktopDefaultColorHex = settings.getDesktopDefaultColorHex();

        sunrise = TimeUtils::parseTimeFromTodayHourMinuteSecond(solarCycleResponse.getFirstLight());
        sunset = TimeUtils::parseTimeFromTodayHourMinuteSecond(solarCycleResponse.getLastLight());

        firstLight = TimeUtils::parseTimeFromTodayHourMinuteSecond(solarCycleResponse.getFirstLight());
        lastLight = TimeUtils::parseTimeFromTodayHourMinuteSecond(solarCycleResponse.getLastLight());

        secondsFromFirstToLastLight = lastLight - firstLight;
        secondsOfMaximumBrightness = (secondsFromFirstToLastLight * maximumBrightnessTimePercentage) / MAXIMUM_BRIGHTNESS_PERCENTAGE;

        // It just refers to a single increase/decrease of brightness. Not both
        secondsOfSingleVariableBrightnessChange = (secondsFromFirstToLastLight - secondsOfMaximumBrightness) / 2;

        maximumBrightnessTimeStart = firstLight + secondsOfSingleVariableBrightnessChange;
        maximumBrightnessTimeEnd = firstLight + secondsOfSingleVariableBrightnessChange + secondsOfMaximumBrightness;
    }

    ~ColorHandler() {}

    unsigned short getPercentageReductionPerTimeOfDay(time_t time) {
        if (!TimeUtils::areTimesInSameDay(TimeUtils::getStartOfCurrentDayTime(), time))
            throw std::invalid_argument("Argument 'time' must refer to the current day");

        if (time > maximumBrightnessTimeStart && time < maximumBrightnessTimeEnd)
            return MAXIMUM_BRIGHTNESS_PERCENTAGE;
        

        if (time > firstLight && time < maximumBrightnessTimeStart)
            return (int)((double)time * ((double)(MAXIMUM_BRIGHTNESS_PERCENTAGE / 100) - (double)brightnessReductionPercentage));

        if (time > maximumBrightnessTimeEnd && time < lastLight)
            return (int)((double)time * -1 * ((double)(MAXIMUM_BRIGHTNESS_PERCENTAGE / 100) - (double)brightnessReductionPercentage));

        return brightnessReductionPercentage;
    }

    COLORREF getColorPerTimeOfDay(time_t time) {

        

        return RGB(0,0,0);
    }
    
    
    COLORREF getDefaultBaseColor() {
        return defaultBaseColor;
    }

    void setDefaultBaseColor(COLORREF newDefaultBaseColor) {
        defaultBaseColor = newDefaultBaseColor;
    }


};