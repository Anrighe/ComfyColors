#include <ctime>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <sstream>
class TimeUtils {

private:
    const std::string TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

public:
    TimeUtils();
    ~TimeUtils();

    static std::time_t getCurrentSystemTime() {
        return std::time(nullptr);
    }

    /**
     * Retrieves the current system time as a formatted string.
     *
     * @return A string representing the current system time
     */
    static std::string getCurrentSystemTimeStringFormatted() {
        std::time_t currentTime = getCurrentSystemTime();
        return std::string(std::ctime(&currentTime));
    }

    /**
     * @brief Compares two time_t elements to determine if they fall on the same day.
     *
     * @param time1 The first time to compare.
     * @param time2 The second time to compare.
     * 
     * @return `true` if both time points are on the same calendar day (same year, month, and day),
     *         `false` otherwise.
     */
    static bool areTimesInSameDay(std::time_t time1, std::time_t time2) {

        std::tm localTime1 = *std::localtime(&time1);
        std::tm localTime2 = *std::localtime(&time2);

        return (localTime1.tm_year == localTime2.tm_year &&
                localTime1.tm_mon == localTime2.tm_mon &&
                localTime1.tm_mday == localTime2.tm_mday);
    }

    /**
     * Gets the start of the current day for the local timezone (using system time) in time_t format (00:00:00 AM).
     *
     * @return std::time_t The time at the start of the current day.
     */
    static std::time_t getStartOfCurrentDayTime() {
        std::time_t now = std::time(nullptr);

        std::tm startOfDayTimeStruct = *std::localtime(&now);

        startOfDayTimeStruct.tm_hour = 0;
        startOfDayTimeStruct.tm_min = 0;
        startOfDayTimeStruct.tm_sec = 0;

        return std::mktime(&startOfDayTimeStruct);
    }

    /**
     * Parses a time string representing hour, minute, and second from today and returns the corresponding time_t value.
     *
     * @param timeString The time string to parse, in the format "HH:MM:SS AM/PM".
     * @return A time_t value representing the parsed time on the current day, or -1 if parsing or conversion fails.
     */
    static std::time_t parseTimeFromTodayHourMinuteSecond(std::string timeString) {
        std::tm parsedTimeHolder = {};
        std::istringstream ss(timeString);
        ss >> std::get_time(&parsedTimeHolder, "%I:%M:%S %p");

        if (ss.fail()) {
            std::cerr << "Time parsing failed\n";
            return -1;
        }
        
        std::time_t startOfTodayTime = getStartOfCurrentDayTime();
        
        std::tm timeToReturnStruct = *std::localtime(&startOfTodayTime);
        timeToReturnStruct.tm_hour = parsedTimeHolder.tm_hour;
        timeToReturnStruct.tm_min = parsedTimeHolder.tm_min;
        timeToReturnStruct.tm_sec = parsedTimeHolder.tm_sec;

        std::time_t parsedTime = std::mktime(&timeToReturnStruct);
        if (parsedTime == -1) {
            std::cerr << "Error converting parsed time to time_t\n";
            return -1;
        }

        return parsedTime;
    }
};