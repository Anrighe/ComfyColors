#include "../Include/Settings.hpp"


int main(int argc, char *argv[]) {

    DesktopController desktopController;
    std::cout<<TimeUtils::getCurrentSystemTime()<<"\n";
    std::cout<<TimeUtils::getCurrentSystemTimeStringFormatted();

    Settings settings(desktopController);

    // Example: testing parsing time with TimeUtils
    std::time_t time = TimeUtils::parseTimeFromTodayHourMinuteSecond("08:43:07 PM");

    if (time != -1) {
        std::cout << "Parsed time: " << std::string(std::ctime(&time)) << std::endl;
    } else {
        std::cerr << "Failed to parse time.\n";
    }

    return 0;
}