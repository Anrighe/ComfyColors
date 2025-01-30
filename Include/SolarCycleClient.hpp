/*#include "../Dependencies/HTTPRequest/HTTPRequest.hpp"*/
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../Dependencies/cpp-httplib/httplib.h"
#include "../Dependencies/nlohmann/json.hpp"
#include "../Dependencies/nlohmann/json_fwd.hpp"
#include "../Include/SolarCycleDTO.hpp"
#include "../Include/SolarCycleResponse.hpp"

using json = nlohmann::ordered_json;

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
        std::cout<<preparedSolarCycleEndpoint<<"\n";
        httplib::Client cli("https://api.sunrisesunset.io");
        try {
            httplib::Result response = cli.Get("/json?lat=44.52989203907902&lng=10.782190547321138");
 
            if (response->status != 200) {
                throw std::runtime_error(std::format("Failed to retrieve solar cycle data from the API: return code", response->status));
            }

            std::cout<<std::format("Response body: {}\n", response->body);

            SolarCycleResponse solarCycleResponse(json::parse(response->body));

            return solarCycleResponse;

        } catch (const std::exception &e) {
            std::cerr<<std::format("Error while fetching solar cycle data: {}\n", e.what());
            exit(1);
        }

   
    }


};