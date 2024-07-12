#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

const std::string kMyKey = "1xGnLyawXSUGylAiKc6k0A==5iHQ9odXOBmpGmcf";
const std::string kWeatherParameters =
    "&daily=weathercode,temperature_2m_max,temperature_2m_min,precipitation_sum,precipitation_probability_max,windspeed_10m_max,winddirection_10m_dominant&forecast_days=16&timezone=auto";
const std::string kCityAPIUrl = "https://api.api-ninjas.com/v1/city?name=";
const std::string kWeatherAPIUrl = "https://api.open-meteo.com/v1/forecast?";

class Request {
    public:
        explicit Request(const std::vector<std::string>& cities): cities_(cities) {}

        void UpdateRequest();

        [[nodiscard]] static nlohmann::json RequestCity(const std::string& city);

        [[nodiscard]] const std::vector<nlohmann::json>& GetData() const;

    private:
        const std::vector<std::string>& cities_;
        std::vector<nlohmann::json> data_;
};
