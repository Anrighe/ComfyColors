#pragma once

#include "settings.hpp"
#include "solar_cycle_client.hpp"
#include "color_handler.hpp"
#include <ctime>
#include <iostream>
#include <ctime>

class Executor {
public:
    Executor() {};
    
    void run() {
        DesktopController desktopController;

        Settings settings(desktopController);
    
        SolarCycleClient solarCycleClient(settings.getSolarCycleApiEndpoint());

        SolarCycleDTO solarCycleDTO(settings.getLatitude(), settings.getLongitude());
        SolarCycleResponse solarCycleResponse = solarCycleClient.getSolarCycleData(solarCycleDTO);
    
        ColorHandler colorHandler(settings, solarCycleResponse);
        desktopController.setDesktopBackgroundColorColorref(colorHandler.getColorPerTimeOfDay());
    }
    
};