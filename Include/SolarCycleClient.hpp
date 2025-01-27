#include "../Dependencies/HTTPRequest/HTTPRequest.hpp"
#include "../Dependencies/nlohmann/json.hpp"
#include "../Dependencies/nlohmann/json_fwd.hpp"
#include "../Include/SolarCycleDTO.hpp"
#include "../Include/SolarCycleResponse.hpp"

using json = nlohmann::json;

class SolarCycleClient {

private:
    std::string solarCycleEndpoint;

    std::string prepareSolarCycleDataEndpoint(SolarCycleDTO solarCycleDTO) {
        return std::format("{}json?lat={}&lng={}", solarCycleEndpoint, solarCycleDTO.getLatitude(), solarCycleDTO.getLongitude());
    }

public:

    SolarCycleClient(std::string solarCycleEndpoint): solarCycleEndpoint(solarCycleEndpoint) {}

    SolarCycleResponse getSolarCycleData(SolarCycleDTO solarCycleDTO) {

        std::string preparedSolarCycleEndpoint = prepareSolarCycleDataEndpoint(solarCycleDTO);

        http::Request request(preparedSolarCycleEndpoint);
        const http::Response response = request.send("GET");

        if (response.status.code != 200) {
            throw std::runtime_error("Failed to retrieve solar cycle data from the API.");
        }

        json jsonResponse = json::parse(response.body);

        SolarCycleResponse solarCycleResponse(
            jsonResponse["results"]["date"],
            jsonResponse["results"]["sunrise"],
            jsonResponse["results"]["sunset"],
            jsonResponse["results"]["civil_twilight_begin"],
            jsonResponse["results"]["civil_twilight_end"],
            jsonResponse["results"]["nautical_twilight_begin"],
            jsonResponse["results"]["nautical_twilight_end"],
            jsonResponse["results"]["solar_noon"],
            jsonResponse["results"]["golden_hour_end"],
            jsonResponse["results"]["day_length"],
            jsonResponse["results"]["timezone"],
            jsonResponse["results"]["utc_offset"]
        );

        return solarCycleResponse;
    }


};