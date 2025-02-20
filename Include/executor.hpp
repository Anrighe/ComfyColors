#pragma once

#include "settings.hpp"
#include "solar_cycle_cacher.hpp"
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
        
        SolarCycleCacher solarCycleCacher(
            settings.getCacheDirectoryPath(),
            settings.getSolarCycleCacheFilenamePathString(),
            solarCycleClient, 
            solarCycleDTO
        );
        
        SolarCycleResponse solarCycleResponse = solarCycleCacher.getSolarCycleResponse();
    
        ColorHandler colorHandler(settings, solarCycleResponse);

        desktopController.setDesktopBackgroundColorColorref(colorHandler.getColorPerTimeOfDay());
    }
    
};