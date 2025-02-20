#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "../Dependencies/nlohmann/json.hpp"
#include "desktop_controller.hpp"
#include "time_utils.hpp"
#include "solar_cycle_client.hpp"


using json = nlohmann::ordered_json;

class SolarCycleCacher {

private:
    SolarCycleResponse solarCycleCachedResponse;
    std::filesystem::path solarCycleCachePath;
    std::filesystem::path solarCycleCacheFilePath;
    time_t dataTime; // Time in which the data was collected
    nlohmann::ordered_json solarCycleCacheFileJson;
    SolarCycleClient solarCycleClient;
    SolarCycleDTO solarCycleDTO;

public:

    SolarCycleCacher(std::filesystem::path solarCycleCachePath, std::filesystem::path solarCycleCacheFilePath, SolarCycleClient solarCycleClient, SolarCycleDTO solarCycleDTO)
        : solarCycleCachePath(solarCycleCachePath), solarCycleCacheFilePath(solarCycleCacheFilePath), solarCycleClient(solarCycleClient), solarCycleDTO(solarCycleDTO) {

        try {
            boolean solarCycleCacheFileExists = false;
            boolean solarCycleCacheFileNeedsRefreshing = true;

            // If the cache file exist, try to read the data from it
            if (std::filesystem::exists(solarCycleCachePath)) {

                if (std::filesystem::exists(solarCycleCacheFilePath)) {
                    std::cout<<std::format("Found a Solar Cycle cache file in {}. Checking if cache is up to date...\n", solarCycleCacheFilePath.string());
                    solarCycleCacheFileExists = true;
    
                    std::ifstream file(solarCycleCacheFilePath);
                    if (!file.is_open()) {
                        std::cout<<std::format("Error while opening the solar cycle cache file: {}\n", solarCycleCacheFilePath.string());
                        exit(1);
                    }
        
                    file>>solarCycleCacheFileJson;
                    file.close();
    
                    dataTime = solarCycleCacheFileJson["dataTime"];
                    if (TimeUtils::areTimesInSameDay(solarCycleCacheFileJson["dataTime"], std::time(0))) {
                        std::cout<<"Solar Cycle cache is up do date, loading data...\n";
                        solarCycleCacheFileNeedsRefreshing = false;
                    } else
                        std::cout<<"Solar Cycle cache is not up do date, fetching new data...\n";

    
                    solarCycleCachedResponse = solarCycleCacheFileJson["response"];
                }
            } else
                std::filesystem::create_directories(solarCycleCachePath);

            
            if (!solarCycleCacheFileExists || solarCycleCacheFileNeedsRefreshing) {

                // If the cache file does not exists or needs refreshing, get new data
                std::cout<<std::format("Creating new cache file in {}\n", solarCycleCacheFilePath.string());
                std::ofstream file(solarCycleCacheFilePath);

                solarCycleCachedResponse = solarCycleClient.getSolarCycleData(solarCycleDTO);

                dataTime = std::time(0);

                solarCycleCacheFileJson["response"] = solarCycleCachedResponse.getJsonOriginalResponse();
                solarCycleCacheFileJson["dataTime"] = dataTime;

                std::cout<<solarCycleCacheFileJson<<"\n";
                file<<solarCycleCacheFileJson.dump(4);
                file.close();
            }

        } catch (const std::exception &e) {
            std::cerr<<std::format("Error in solar cycle cacher: {}\n", e.what());
            exit(1);
        }
    };

    SolarCycleResponse getSolarCycleResponse() { return solarCycleCachedResponse; }
    time_t getDataTime() { return dataTime; };

};