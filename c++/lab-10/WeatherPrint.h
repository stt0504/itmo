#pragma once

#include <nlohmann/json.hpp>
#include <curses.h>

#include <stack>

const int kMaxDaysNumber = 15;

class WeatherPrinter {
    public:
        explicit WeatherPrinter(const std::vector<nlohmann::json>& data,
                                const std::vector<std::string>& cities,
                                int default_weather_days);

        void PrintDailyWeather();

        void PrintCity();

        void EraseCity();

        void PrintNextCity();

        void PrintPrevCity();

        void PrintNextDay();

        void EraseDay();

        void Finish();

    private:
        int default_weather_days_ = 0;
        int current_city_index_ = 0;
        int current_day_index_ = 0;
        std::stack<WINDOW*> forecast_windows_;
        const std::vector<nlohmann::json>& data_;
        const std::vector<std::string>& cities_;
};
