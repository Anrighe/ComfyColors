#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "../Dependencies/cpp-httplib/httplib.h"
#include "../Dependencies/nlohmann/json.hpp"
#include "../Dependencies/nlohmann/json_fwd.hpp"

#include "ip_geolocation_response.hpp"

using json = nlohmann::ordered_json;

class IpGeolocationClient {

private:
    std::string ipGeolocationEndpoint;
    const std::string ipGeolocationParameters = "/json"; 

public:

    IpGeolocationClient(std::string ipGeolocationEndpoint): ipGeolocationEndpoint(ipGeolocationEndpoint) {}

    IpGeolocationResponse getIpGeolocationData() {

        httplib::Client cli(ipGeolocationEndpoint);
        try {
            httplib::Result response = cli.Get(ipGeolocationParameters);

            if (response->status != 200) {
                throw std::runtime_error(std::format("Failed to retrieve IP Geolocation data from the API: return code", response->status));
            }
        
            IpGeolocationResponse ipGeolocationResponse(json::parse(response->body));
            
            return ipGeolocationResponse;

        } catch (const std::exception &e) {
            std::cerr<<std::format("Error while fetching IP Geolocation data: {}\n", e.what());
            exit(1);
        }
    }
};