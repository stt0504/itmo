#include "WeatherRequest.h"

void Request::UpdateRequest() {
    std::vector<std::future<nlohmann::json>> futures;
    for (const std::string& city: cities_) {
        futures.emplace_back(std::async(std::launch::async, &RequestCity, city));
    }
    if (data_.empty()) {
        data_.resize(cities_.size());
    }
    for (size_t i = 0; i < futures.size(); ++i) {
        nlohmann::json new_data = futures[i].get();
        data_[i] = new_data;
    }
}

nlohmann::json Request::RequestCity(const std::string& city) {
    std::string city_request_url = kCityAPIUrl + city;
    cpr::Response response_city = cpr::Get(cpr::Url{city_request_url}, cpr::Header{{"X-Api-Key", kMyKey}});
    if (response_city.error) {
        std::string error_message = "Failed to get city data. " + response_city.error.message;
        throw std::runtime_error(error_message);
    }
    const int kExtraCharacters = 2;
    if (response_city.text.size() < kExtraCharacters) {
        std::string error_message = "Error: invalid response. ";
        throw std::runtime_error(error_message);
    }
    nlohmann::json
        city_data = nlohmann::json::parse(response_city.text.substr(1, response_city.text.size() - kExtraCharacters));

    std::string latitude = to_string(city_data["latitude"]);
    std::string longitude = to_string(city_data["longitude"]);
    std::string weather_request_url = kWeatherAPIUrl + "latitude=" + latitude + "&longitude=" + longitude
        + kWeatherParameters;
    cpr::Response response_weather = cpr::Get(cpr::Url{weather_request_url});
    if (response_weather.error) {
        std::string error_message = "Failed to get weather data: " + response_weather.error.message;
        throw std::runtime_error(error_message);
    }
    nlohmann::json weather_city_data = nlohmann::json::parse(response_weather.text);
    return weather_city_data;
}

const std::vector<nlohmann::json>& Request::GetData() const {
    return data_;
}
