#include <string>

class SolarCycleResponse {


private:
    std::string date;
    std::string sunrise;
    std::string sunset;
    std::string firstLight;
    std::string lastLight;
    std::string dawn;
    std::string dusk;
    std::string solarNoon;
    std::string goldenHour;
    std::string dayLength;
    std::string timezone;
    int utcOffset;

public:
    
    SolarCycleResponse(
        std::string date, 
        std::string sunrise, 
        std::string sunset, 
        std::string firstLight, 
        std::string lastLight, 
        std::string dawn, 
        std::string dusk, 
        std::string solarNoon, 
        std::string goldenHour, 
        std::string dayLength, 
        std::string timezone, 
        int utcOffset
    ):  date(date),
        sunrise(sunrise), 
        sunset(sunset), 
        firstLight(firstLight), 
        lastLight(lastLight), 
        dawn(dawn), 
        dusk(dusk), 
        solarNoon(solarNoon), 
        goldenHour(goldenHour), 
        dayLength(dayLength), 
        timezone(timezone), 
        utcOffset(utcOffset) {}

    

    std::string getDate() {
        return date;
    }

    std::string getSunrise() {
        return sunrise;
    }

    std::string getSunset() {
        return sunset;
    }

    std::string getFirstLight() {
        return firstLight;
    }

    std::string getLastLight() {
        return lastLight;
    }

    std::string getDawn() {
        return dawn;
    }

    std::string getDusk() {
        return dusk;
    }

    std::string getSolarNoon() {
        return solarNoon;
    }

    std::string getGoldenHour() {
        return goldenHour;
    }

    std::string getDayLength() {
        return dayLength;
    }

    std::string getTimezone() {
        return timezone;
    }

    int getUtcOffset() {
        return utcOffset;
    }

    void setDate(std::string date) {
        this->date = date;
    }

    void setSunrise(std::string sunrise) {
        this->sunrise = sunrise;
    }

    void setSunset(std::string sunset) {
        this->sunset = sunset;
    }

    void setFirstLight(std::string firstLight) {
        this->firstLight = firstLight;
    }

    void setLastLight(std::string lastLight) {
        this->lastLight = lastLight;
    }

    void setDawn(std::string dawn) {
        this->dawn = dawn;
    }

    void setDusk(std::string dusk) {
        this->dusk = dusk;
    }

    void setSolarNoon(std::string solarNoon) {
        this->solarNoon = solarNoon;
    }

    void setGoldenHour(std::string goldenHour) {
        this->goldenHour = goldenHour;
    }

    void setDayLength(std::string dayLength) {
        this->dayLength = dayLength;
    }

    void setTimezone(std::string timezone) {
        this->timezone = timezone;
    }

    void setUtcOffset(int utcOffset) {
        this->utcOffset = utcOffset;
    }
};