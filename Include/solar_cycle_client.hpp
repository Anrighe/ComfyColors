#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "../Dependencies/cpp-httplib/httplib.h"
#include "../Dependencies/nlohmann/json.hpp"
#include "../Dependencies/nlohmann/json_fwd.hpp"

#include "../Include/solar_cycle_dto.hpp"
#include "../Include/solar_cycle_response.hpp"

using json = nlohmann::ordered_json;

class SolarCycleClient {

private:
    std::string solarCycleEndpoint;

    std::string prepareSolarCycleRequestParameters(SolarCycleDTO solarCycleDTO) {
        return std::format("json?lat={}&lng={}", solarCycleDTO.getLatitude(), solarCycleDTO.getLongitude());
    }

public:

    SolarCycleClient(std::string solarCycleEndpoint): solarCycleEndpoint(solarCycleEndpoint) {}

    SolarCycleResponse getSolarCycleData(SolarCycleDTO solarCycleDTO) {

        httplib::Client cli(solarCycleEndpoint);
        try {
            httplib::Result response = cli.Get(prepareSolarCycleRequestParameters(solarCycleDTO));
 
            if (response->status != 200) {
                throw std::runtime_error(std::format("Failed to retrieve solar cycle data from the API: return code", response->status));
            }

            //std::cout<<std::format("Response body: {}\n", response->body);

            SolarCycleResponse solarCycleResponse(json::parse(response->body));

            return solarCycleResponse;

        } catch (const std::exception &e) {
            std::cerr<<std::format("Error while fetching solar cycle data: {}\n", e.what());
            exit(1);
        }

   
    }


};