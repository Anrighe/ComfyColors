#include <ctime>

class TimeUtils {

private:
    const std::string TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

public:
    TimeUtils();
    ~TimeUtils();

    static std::time_t getCurrentSystemTime() {
        return std::time(nullptr);
    }

    static std::string getCurrentSystemTimeStringFormatted() {
        std::time_t currentTime = getCurrentSystemTime();
        return std::string(std::ctime(&currentTime));
    }

    /*static std::chrono::system_clock::time_point buildTimePointFromString(std::string timeString) {

        std::chrono::system_clock::time_point tp;
        std:
    }*/

    static bool areInSameDay(std::chrono::system_clock::time_point timePoint1, std::chrono::system_clock::time_point timePoint2) {
        std::time_t time1 = std::chrono::system_clock::to_time_t(timePoint1);
        std::time_t time2 = std::chrono::system_clock::to_time_t(timePoint2);

        std::tm localTime1 = *std::localtime(&time1);
        std::tm localTime2 = *std::localtime(&time2);

        return (localTime1.tm_year == localTime2.tm_year &&
                localTime1.tm_mon == localTime2.tm_mon &&
                localTime1.tm_mday == localTime2.tm_mday);
    }



};