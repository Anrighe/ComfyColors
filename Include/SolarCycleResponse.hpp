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
    std::string status;

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
        int utcOffset,
        std::string status
    ):  date(std::move(date)),
        sunrise(std::move(sunrise)), 
        sunset(std::move(sunset)), 
        firstLight(std::move(firstLight)), 
        lastLight(std::move(lastLight)), 
        dawn(std::move(dawn)), 
        dusk(std::move(dusk)), 
        solarNoon(std::move(solarNoon)), 
        goldenHour(std::move(goldenHour)), 
        dayLength(std::move(dayLength)), 
        timezone(std::move(timezone)), 
        utcOffset(std::move(utcOffset)),
        status(std::move(status)) {};

    SolarCycleResponse(const nlohmann::ordered_json response) :
        date(response["results"]["date"].get<std::string>()),
        sunrise(response["results"]["sunrise"].get<std::string>()),
        sunset(response["results"]["sunset"].get<std::string>()),
        firstLight(response["results"]["first_light"].get<std::string>()),
        lastLight(response["results"]["last_light"].get<std::string>()),
        dawn(response["results"]["dawn"].get<std::string>()),
        dusk(response["results"]["dusk"].get<std::string>()),
        solarNoon(response["results"]["solar_noon"].get<std::string>()),
        goldenHour(response["results"]["golden_hour"].get<std::string>()),
        dayLength(response["results"]["day_length"].get<std::string>()),
        timezone(response["results"]["timezone"].get<std::string>()),
        utcOffset(response["results"]["utc_offset"].get<int>()),
        status(response["status"].get<std::string>())
    {};


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

    std::string getStatus() {
        return status;
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