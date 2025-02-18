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

        // TODO: get latitude/longitude
        double lat = 44.52989203907902;
        double lng = 10.782190547321138;
    
        Settings settings(desktopController);
    
        SolarCycleClient solarCycleClient(settings.getSolarCycleApiEndpoint());
    
        SolarCycleDTO solarCycleDTO(lat, lng);
        SolarCycleResponse solarCycleResponse = solarCycleClient.getSolarCycleData(solarCycleDTO);
    
        ColorHandler colorHandler(settings, solarCycleResponse);
        desktopController.setDesktopBackgroundColorColorref(colorHandler.getColorPerTimeOfDay());
    }
    
};