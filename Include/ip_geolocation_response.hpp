#pragma once

#include <string>
#include <unordered_map>

#include "../Dependencies/nlohmann/json.hpp"
#include "../Dependencies/nlohmann/json_fwd.hpp"

class IpGeolocationResponse {

private:

    std::string ip;
    long ip_decimal;
    std::string country;
    std::string country_iso;
    bool country_eu;
    std::string region_name;
    std::string region_code;
    std::string zip_code;
    std::string city;
    double latitude;
    double longitude;
    std::string time_zone;
    std::string asn;
    std::string asn_org;
    std::unordered_map<std::string, std::string> user_agent;
    
public:

    IpGeolocationResponse(
        std::string ip, 
        long ip_decimal, 
        std::string country, 
        std::string country_iso, 
        bool country_eu, 
        std::string region_name, 
        std::string region_code, 
        std::string zip_code, 
        std::string city,
        double latitude, 
        double longitude, 
        std::string time_zone, 
        std::string asn, 
        std::string asn_org, 
        std::unordered_map<std::string, std::string> user_agent)
        :   ip(std::move(ip)), 
            ip_decimal(std::move(ip_decimal)), 
            country(std::move(country)),
            country_iso(std::move(country_iso)), 
            country_eu(std::move(country_eu)),
            region_name(std::move(region_name)), 
            region_code(std::move(region_code)),
            zip_code(std::move(zip_code)),
            city(std::move(city)),
            latitude(std::move(latitude)), 
            longitude(std::move(longitude)),
            time_zone(std::move(time_zone)), 
            asn(std::move(asn)), 
            asn_org(std::move(asn_org)),
            user_agent(std::move(user_agent))
            {}

    IpGeolocationResponse(const nlohmann::ordered_json& response) 
        :   ip(response["ip"].get<std::string>()),
            ip_decimal(response["ip_decimal"].get<long>()),
            country(response["country"].get<std::string>()),
            country_iso(response["country_iso"].get<std::string>()),
            country_eu(response["country_eu"].get<bool>()),
            region_name(response["region_name"].get<std::string>()),
            region_code(response["region_code"].get<std::string>()),
            zip_code(response["zip_code"].get<std::string>()),
            city(response["city"].get<std::string>()),
            latitude(response["latitude"].get<double>()),
            longitude(response["longitude"].get<double>()),
            time_zone(response["time_zone"].get<std::string>()),
            asn(response["asn"].get<std::string>()),
            asn_org(response["asn_org"].get<std::string>()),
            user_agent(response["user_agent"].get<std::unordered_map<std::string, std::string>>())
            {}

    std::string getIp() const { return ip; }
    long getIpDecimal() const { return ip_decimal; }
    std::string getCountry() const { return country; }
    std::string getCountryIso() const { return country_iso; }
    bool getCountryEu() const { return country_eu; }
    std::string getRegionName() const { return region_name; }
    std::string getRegionCode() const { return region_code; }
    std::string getZipCode() const { return zip_code; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    std::string getCity() const { return city; }
    std::string getTimeZone() const { return time_zone; }
    std::string getAsn() const { return asn; }
    std::string getAsnOrg() const { return asn_org; }
    std::unordered_map<std::string, std::string> getUserAgent() const { return user_agent; }
};
    