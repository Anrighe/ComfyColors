#pragma once

#include <winsock2.h>
#include <windows.h>
#include "solar_cycle_response.hpp"
#include "time_utils.hpp"
#include "settings.hpp"

#define MAXIMUM_BRIGHTNESS_PERCENTAGE 1.0

class ColorHandler {

private:

    COLORREF defaultBaseColor;
    double brightnessReductionPercentage;
    double maximumBrightnessTimePercentage;
    std::string desktopDefaultColorHex;

    time_t sunrise;
    time_t sunset;

    time_t firstLight;
    time_t lastLight;

    time_t maximumBrightnessTimeStart; // Time where the maximum brightness setting is applied
    time_t maximumBrightnessTimeEnd; // Time where the maximum brightness setting ends

    unsigned int secondsFromFirstToLastLight;
    unsigned int secondsOfMaximumBrightness;

    // Seconds from the first light to the maximum brightness period.
    // This value is both valid for the period of brightness increase and decrease
    unsigned int secondsOfSingleVariableBrightnessChange; 

public:
    
    /**
     * @brief Constructs a ColorHandler object with settings and solar cycle data.
     * @param settings The settings object containing user-defined brightness parameters
     * @param solarCycleResponse The solar cycle data providing sunrise and sunset times
     */
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
        secondsOfMaximumBrightness = (secondsFromFirstToLastLight * maximumBrightnessTimePercentage);

        // It just refers to a single increase/decrease of brightness. Not both
        secondsOfSingleVariableBrightnessChange = (secondsFromFirstToLastLight - secondsOfMaximumBrightness) / 2;

        maximumBrightnessTimeStart = firstLight + secondsOfSingleVariableBrightnessChange;
        maximumBrightnessTimeEnd = firstLight + secondsOfSingleVariableBrightnessChange + secondsOfMaximumBrightness;
    }

    /**
     * @brief Calculates the brightness reduction percentage based on the given time.
     *  Takes into consideration how far it's been from the first light and how much time 
     *   will it take to reach the last light to calculate a linear decrement/increment for the reduction factor.
     *    At its peak (brightness) the reduction factor is minimized, at its lows the reduction factor is maximized.
     * @param time The current time for which brightness reduction is calculated
     * @return The brightness reduction percentage
     * @throws std::invalid_argument if the given time is not within the current day
     */
    double getPercentageReductionPerTimeOfDay(time_t time) {
        if (!TimeUtils::areTimesInSameDay(TimeUtils::getStartOfCurrentDayTime(), time))
            throw std::invalid_argument("Argument 'time' must refer to the current day");

        if (time > maximumBrightnessTimeStart && time < maximumBrightnessTimeEnd) {
            return MAXIMUM_BRIGHTNESS_PERCENTAGE;
        }
        
        if (time > firstLight && time < maximumBrightnessTimeStart) {
            double currentTimeReductionFactor = (time - firstLight) / (maximumBrightnessTimeStart - firstLight);
            return MAXIMUM_BRIGHTNESS_PERCENTAGE - (brightnessReductionPercentage * currentTimeReductionFactor);
        }

        if (time > maximumBrightnessTimeEnd && time < lastLight) {
            double currentTimeReductionFactor = (time - maximumBrightnessTimeEnd) / (lastLight - maximumBrightnessTimeEnd);
            return MAXIMUM_BRIGHTNESS_PERCENTAGE - (brightnessReductionPercentage * currentTimeReductionFactor) ;
        }

        return brightnessReductionPercentage;
    }

    /**
     * @brief Modifies the brightness of a given COLORREF value, by a specified  factor.
     *  E.g.: The factor passed as argument is 0.7 (I want to reduce brightness of the colorref to
     *   70% of its original values).
     * @param colorref The original color
     * @param brightnessFactor The reduction percentage factor 
     * @return The color with reduced brightness
     */
    COLORREF getColorrefBrightnessByFactor(COLORREF colorref, double brightnessFactor) {

        int red = ColorUtils::getRedfromColorref(colorref);
        int green = ColorUtils::getGreenfromColorref(colorref);
        int blue = ColorUtils::getBluefromColorref(colorref);

        red = static_cast<int>(red * brightnessFactor);
        green = static_cast<int>(green * brightnessFactor);
        blue = static_cast<int>(blue * brightnessFactor);

        return RGB(red, green, blue);
    }

    /**
     * @brief Gets the adjusted color based on the current time of day.
     * @return The adjusted COLORREF value
     */
    COLORREF getColorPerTimeOfDay() {
        return getColorrefBrightnessByFactor(
            defaultBaseColor, 
            MAXIMUM_BRIGHTNESS_PERCENTAGE - getPercentageReductionPerTimeOfDay(std::time(0))
        );
    }

    /**
     * @brief Gets the adjusted color based on the given time of day.
     * @param time The current time
     * @return The adjusted COLORREF value
     */
    COLORREF getColorPerTimeOfDay(time_t time) {
        return getColorrefBrightnessByFactor(
            defaultBaseColor, 
            MAXIMUM_BRIGHTNESS_PERCENTAGE - getPercentageReductionPerTimeOfDay(time)
        );
    }
    
    /**
     * @brief Gets the default base color.
     * @return The default COLORREF value.
     */    
    COLORREF getDefaultBaseColor() {
        return defaultBaseColor;
    }

    /**
     * @brief Sets a new default base color.
     * 
     * @param newDefaultBaseColor The new base color.
     */    
    void setDefaultBaseColor(COLORREF newDefaultBaseColor) {
        defaultBaseColor = newDefaultBaseColor;
    }
};