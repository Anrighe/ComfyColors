class SolarCycleDTO {

private:
    double latitude;
    double longitude;

public:

    SolarCycleDTO(double latitude, double longitude): latitude(latitude), longitude(longitude) {}

    double getLatitude() {
        return latitude;
    }

    double getLongitude() {
        return longitude;
    }

    void setLatitude(double latitude) {
        this->latitude = latitude;
    }

    void setLongitude(double longitude) {
        this->longitude = longitude;
    }
};