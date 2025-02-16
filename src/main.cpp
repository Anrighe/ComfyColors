#include "../Include/Settings.hpp"
#include "../Include/SolarCycleClient.hpp"
#include "../Include/ColorHandler.hpp"
#include <ctime>

int main(int argc, char *argv[]) {
    
    // TODO: implement argument for simulation + Simulator class

    DesktopController desktopController;
    std::cout<<TimeUtils::getCurrentSystemTime()<<"\n";
    std::cout<<TimeUtils::getCurrentSystemTimeStringFormatted();

    Settings settings(desktopController);

    // Example: testing parsing time with TimeUtils
    std::time_t time = TimeUtils::parseTimeFromTodayHourMinuteSecond("08:43:07 PM");

    if (time != -1) {
        std::cout<<"Parsed time: "<<std::string(std::ctime(&time))<<"\n";
    } else {
        std::cerr<<"Failed to parse time.\n";
    }


    SolarCycleClient solarCycleClient(settings.getSolarCycleApiEndpoint());

    double lat = 44.52989203907902;
    double lng = 10.782190547321138;


    SolarCycleDTO solarCycleDTO(lat, lng);
    SolarCycleResponse solarCycleResponse = solarCycleClient.getSolarCycleData(solarCycleDTO);

    std::cout<<solarCycleResponse.getDate()<<" "<<solarCycleResponse.getDawn()<<" "<<solarCycleResponse.getDusk()<<"\n";

    ColorHandler colorHandler(settings, solarCycleResponse);

    desktopController.setDesktopBackgroundColorColorref(colorHandler.getColorPerTimeOfDay());

    return 0;
}