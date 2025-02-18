#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <unistd.h>
#include <limits>

#include "../Dependencies/nlohmann/json.hpp"
#include "desktop_controller.hpp"
#include "time_utils.hpp"
#include "ip_geolocation_client.hpp"

using json = nlohmann::ordered_json;

#define PROJECT_NAME "ComfyColors"
#define SETTINGS_FILE_NAME "settings.json"
#define CONFIG_INDENTATION_SIZE 4

#define DEBUG false

#define DEFAULT_BRIGHTNESS_REDUCTION_PERCENTAGE 0.35

#define DEFAULT_MAXIMUM_BRIGHTNESS_TIME_PERCENTAGE 0.5

#define DEFAULT_SOLAR_CYCLE_ENDPOINT "https://api.sunrisesunset.io"

#define DEFAULT_IP_API_GEOLOCATION_ENDPOINT "https://ifconfig.co"

#define DEFAULT_SOLAR_CYCLE_CACHE_FILENAME "solar_cycle.cache"

#define DEFAULT_IP_GEOLOCATION_CACHE_FILENAME "ip_geolocation.cache"

#define DEFAULT_LATITUDE 0.0

#define DEFAULT_LONGITUDE 0.0


/**
 * @class Settings
 * @brief Manages the loading and retrieval of application settings from a JSON configuration file.
 */
class Settings {

private:

    const std::string projectName = std::string(PROJECT_NAME);
    const std::string settingsFileName = std::string(SETTINGS_FILE_NAME);
    
    const std::filesystem::path currentPath = std::filesystem::current_path();
    const std::filesystem::path settingsDirectoryPath = currentPath.string();
    const std::filesystem::path settingsFilePath = settingsDirectoryPath.string() + "\\" + settingsFileName;

    bool debugEnabled;

    json settingsFile;

    DesktopController desktopController;

    COLORREF desktopDefaultColorColorref;
    std::string desktopDefaultColorHex;
    std::time_t lastExecutionTime;

    std::string solarCycleApiEndpoint;

    double brightnessReductionPercentage;
    double maximumBrightnessTimePercentage;

    std::string ipGeolocationApiEndpoint;

    double latitude;
    double longitude;

    void generateSettingsDirectory() {
        std::cout<<"Generating new settings directory...\n";
        std::filesystem::create_directory(settingsDirectoryPath);
        std::cout<<"Directory " + settingsDirectoryPath.string() + " successfully generated\n";
    }

    void generateSettingsDirectoryIfNotExists() {
        bool directoryExists = std::filesystem::is_directory(settingsDirectoryPath);
        if (!directoryExists) {
            std::cout<<std::format("Configuration directory does not exist in path: {}\n", settingsDirectoryPath.string());
            generateSettingsDirectory();
        }
    }

    void generateSettingsFile() {
        std::cout<<std::format("Generating settings.json file in {}\n", settingsFilePath.string());
        
        settingsFile["debug"] = DEBUG;
        
        settingsFile["desktopDefaultColorHex"] = ColorUtils::getColorHexRepresentation(desktopController.getDesktopBackgroundColor());

        settingsFile["lastExecutionTime"] = TimeUtils::getCurrentSystemTime();

        settingsFile["brightnessReductionPercentage"] = DEFAULT_BRIGHTNESS_REDUCTION_PERCENTAGE;

        settingsFile["maximumBrightnessTimePercentage"] = DEFAULT_MAXIMUM_BRIGHTNESS_TIME_PERCENTAGE;

        settingsFile["solarCycleApiEndpoint"] = DEFAULT_SOLAR_CYCLE_ENDPOINT;

        settingsFile["ipGeolocationApiEndpoint"] = DEFAULT_IP_API_GEOLOCATION_ENDPOINT;

        IpGeolocationClient ipGeolocationClient(DEFAULT_IP_API_GEOLOCATION_ENDPOINT);
        IpGeolocationResponse ipGeolocationResponse = ipGeolocationClient.getIpGeolocationData();
        settingsFile["latitude"] = ipGeolocationResponse.getLatitude();
        settingsFile["longitude"] = ipGeolocationResponse.getLongitude();
        
        std::ofstream file(settingsFilePath);
        file<<settingsFile.dump(4);
        file.close();
    }

    void generateSettingsFileIfNotExists() {
        bool settingsFileExists = std::filesystem::is_regular_file(settingsFilePath);
        if (!settingsFileExists)
            generateSettingsFile();
    }

    void loadSettingsFile() {
        try {
            std::cout<<"Loding settings file configuration...\n";

            std::ifstream file(settingsFilePath);
            if (!file.is_open()) {
                std::cout<<std::format("Error while opening settings file: {}\\{}\n", settingsDirectoryPath.string(), settingsFileName);
                exit(1);
            }

            file>>settingsFile;
            file.close();

            debugEnabled = settingsFile["debug"].get<bool>();            
            desktopDefaultColorHex = settingsFile["desktopDefaultColorHex"].get<std::string>();

            // This get's parsed to COLORREF from hex value because it the only way I found to make this work.
            //  If parsed and casted directly in COLORREF it returned random numbers
            desktopDefaultColorColorref = ColorUtils::HexToColorRef(desktopDefaultColorHex);

            lastExecutionTime = settingsFile["lastExecutionTime"].get<std::time_t>();
            brightnessReductionPercentage = settingsFile["brightnessReductionPercentage"].get<double>();
            maximumBrightnessTimePercentage = settingsFile["maximumBrightnessTimePercentage"].get<double>();
            solarCycleApiEndpoint = settingsFile["solarCycleApiEndpoint"].get<std::string>();
            ipGeolocationApiEndpoint = settingsFile["ipGeolocationApiEndpoint"].get<std::string>();

            latitude = settingsFile["latitude"].get<double>();
            longitude = settingsFile["longitude"].get<double>();

            std::cout<<"Settings file successfully loaded\n";
        } catch (const std::exception &e) {
            std::cout<<std::format("Error while loading the settings file: {}\n", e.what());
        }
    }



public:

    Settings(DesktopController desktopController) : desktopController(desktopController) { 
        
        generateSettingsDirectoryIfNotExists();
        generateSettingsFileIfNotExists();

        loadSettingsFile();
    }

    // Getter methods
    std::string getProjectName() { return projectName; }
    std::string getSettingsFileName() { return settingsFileName; }

    std::string getSettingsDirectoryPathString() { return settingsDirectoryPath.string(); }
    std::string getSettingsFilePathString() { return settingsFilePath.string(); }

    std::filesystem::path getSettingsDirectoryPath() { return settingsDirectoryPath; }
    std::filesystem::path getSettingsFilePath() { return settingsFilePath; }
    
    json getSettingsFile() { return settingsFile; }

    bool isDebugEnabled() { return debugEnabled; }

    COLORREF getDesktopDefaultColorColorref() { return desktopDefaultColorColorref; }

    std::string getDesktopDefaultColorHex() { return desktopDefaultColorHex; }

    std::time_t getLastExecutionTime() { return lastExecutionTime; }

    double getBrightnessReductionPercentage() { return brightnessReductionPercentage; }

    double getMaximumBrightnessTimePercentage() { return maximumBrightnessTimePercentage; }

    std::string getSolarCycleApiEndpoint() { return solarCycleApiEndpoint; }

    std::string getIpGeolocationApiEndpoint() { return ipGeolocationApiEndpoint; }

    double getLatitude() { return latitude; }

    double getLongitude() { return longitude; }

    //TODO: implement setters which modify the settings.json file
};