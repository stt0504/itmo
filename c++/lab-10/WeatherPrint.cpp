#include "WeatherPrint.h"

const std::unordered_map<int, std::string> weather_icons {
    {0, R"(
              \     /
                .-.
           -- (     ) --
                '-'
              /     \       )"},
    {1, R"(
              \     /
                .-.
           -- (     ) --
                '-'
              /     \       )"},
    {2, R"(
             \   /
         __  /""  .--.
             \ _ (    ).
             /  (____(___)  )"},
    {3, R"(
              .----.
           .-(      )--.
          ( ____. ___)__)   )"},
    {45, R"(
            _ - _ - _ -
             _ - _ - _
            _ - _ - _ -     )"},
    {48, R"(
            _ - _ - _ -
             _ - _ - _
            _ - _ - _ -     )"},
    {51, R"(
           _'/"".--.
            ,\_(    )-.
            / (____(___)
                , , , ,
                , , , ,     )"},
    {53, R"(
               .--.
              (    ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {55, R"(
               .--.
              (    ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {56, R"(
          _'/"".--.
           ,\_(    ).
           / (____(___)
               , , , ,
               , , , ,      )"},
    {57, R"(
               .--.
              (    ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {61, R"(
          _'/"".--.
           ,\_(    ).
           / (____(___)
               , , , ,
               , , , ,      )"},
    {63, R"(
               .--.
              (    ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {65, R"(
               .--.
              (    ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {66, R"(
          _'/"".--.
           ,\_(    ).
           / (____(___)
               , , , ,
               , , , ,      )"},
    {67, R"(
               .--.
              (    ).
             (___(___)
             ‘‘‘‘‘‘‘‘
             ‘‘‘‘‘‘‘‘       )"},
    {71, R"(
           _'/"".--.
            ,\_(    ).
             / (___(___)
                *  *  *
               *  *  *      )"},
    {73, R"(
               .---.
              (     ).
             (___(___)
             *   *   *
            *   *   *       )"},
    {75, R"(
               .---.
              (     ).
             (___(___)
             * * * * *
            * * * * *       )"},
    {77, R"(
               .---.
              (     ).
             (___(___)
             * * * * *
            * * * * *       )"},
    {80, R"(
            _'/"".--.
             ,\_(    ).
              /(___(___)
                , , , ,
                , , , ,     )"},
    {81, R"(
               .---.
              (     ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {82, R"(
               .---.
              (     ).
             (___(___)
              , , , ,
              , , , ,       )"},
    {85, R"(
               .---.
              (     ).
             (___(___)
             *   *   *
            *   *   *
           *   *   *        )"},
    {86, R"(
              .---.
             (     ).
            (___(____)
            *  *  *  *
            *  *  *  *
             *  *  *        )"},
    {95, R"(
           _'/"".--.
            ,\_(    ).
           /  (___(___)
              , / , / ,
               , , , ,      )"},
    {96, R"(
              .---.
             (     ).
            (____(___)
            , / . / ,
             , , , ,        )"},
    {99, R"(
              .--.
             (    ).
            (____(__)
            / , / , /
            . , . , .       )"},
};

const std::unordered_map<int, std::string> weather_name{
    {0, "Clear"},
    {1, "Mainly clear"},
    {2, "Partly cloudy"},
    {3, "Overcast"},
    {45, "Fog"},
    {48, "Depositing rime fog"},
    {51, "Light drizzle"},
    {53, "Moderate drizzle"},
    {55, "Intensive drizzle"},
    {56, "Light freezing drizzle"},
    {57, "Intensive freezing drizzle"},
    {61, "Slight rain"},
    {63, "Moderate rain"},
    {65, "Intensive rain"},
    {66, "Light freezing rain"},
    {67, "Intensive freezing rain"},
    {71, "Slight snow fall"},
    {73, "Moderate show fall"},
    {75, "Heavy snow fall"},
    {77, "Snow grains"},
    {80, "Slight rain showers"},
    {81, "Moderate rain showers"},
    {82, "Violent rain showers"},
    {85, "Slight snow showers"},
    {86, "Heavy show showers"},
    {95, "Thunderstorm"},
    {96, "Thunderstorm with slight hail"},
    {99, "Thunderstorm with heavy hail"},
};

void WeatherPrinter::PrintDailyWeather() {
    if (current_day_index_ >= kMaxDaysNumber) {
        return;
    }
    const int kDailyWeatherWinHeight = 15;
    const int kDailyWeatherWinWidth = 35;
    const int kPaddingY = 3;
    const int kPaddingX = 6;
    const int kMaxCountWinsInLine = 5;
    int y = kPaddingY + kDailyWeatherWinHeight * (current_day_index_ / kMaxCountWinsInLine);
    int x = kPaddingX + kDailyWeatherWinWidth * (current_day_index_ % kMaxCountWinsInLine);
    WINDOW* main_window = derwin(stdscr, kDailyWeatherWinHeight, kDailyWeatherWinWidth, y, x);
    std::string image = weather_icons.at(data_[current_city_index_]["daily"]["weathercode"][current_day_index_]);

    const int kImageY = 1;
    const int kImageX = 1;
    mvwprintw(main_window, kImageY, kImageX, image.c_str());

    const int kTextY = kDailyWeatherWinHeight / 2;
    int string_number = 1;
    std::string weather_text = weather_name.at(data_[current_city_index_]["daily"]["weathercode"][current_day_index_]);
    int center_x = (kDailyWeatherWinWidth - weather_text.length()) / 2;
    mvwprintw(main_window, kTextY + string_number++, center_x, weather_text.c_str());

    std::string
        temperature_min = to_string(data_[current_city_index_]["daily"]["temperature_2m_min"][current_day_index_]);
    std::string
        temperature_max = to_string(data_[current_city_index_]["daily"]["temperature_2m_max"][current_day_index_]);
    std::string temperature_text = "Temperature: " + temperature_max + " (" + temperature_min + ") C";
    center_x = (kDailyWeatherWinWidth - temperature_text.length()) / 2;
    mvwprintw(main_window, kTextY + string_number++, center_x, temperature_text.c_str());

    std::string wind_speed = to_string(data_[current_city_index_]["daily"]["windspeed_10m_max"][current_day_index_]);
    std::string wind_speed_text = "Wind speed: " + wind_speed + " km/h";
    center_x = (kDailyWeatherWinWidth - wind_speed_text.length()) / 2;
    mvwprintw(main_window, kTextY + string_number++, center_x, wind_speed_text.c_str());

    std::string
        precipitation_sum = to_string(data_[current_city_index_]["daily"]["precipitation_sum"][current_day_index_]);
    std::string
        precipitation_probability_max =
        to_string(data_[current_city_index_]["daily"]["precipitation_probability_max"][current_day_index_]);
    std::string precipitation_text = "Precipitation: " + precipitation_sum + " mm | " + precipitation_probability_max;
    center_x = (kDailyWeatherWinWidth - precipitation_text.length()) / 2;
    mvwprintw(main_window, kTextY + string_number++, center_x, precipitation_text.c_str());

    box(main_window, 0, 0);
    std::string date = data_[current_city_index_]["daily"]["time"][current_day_index_];
    center_x = (kDailyWeatherWinWidth - date.length()) / 2;
    mvwprintw(main_window, 0, center_x, date.c_str());

    wrefresh(main_window);
    forecast_windows_.push(main_window);
}

WeatherPrinter::WeatherPrinter(const std::vector<nlohmann::json>& data,
                               const std::vector<std::string>& cities,
                               int default_weather_days):
                               data_(data), cities_(cities), default_weather_days_(default_weather_days) {
    initscr();
    curs_set(0);
    cbreak();
    noecho();
}

void WeatherPrinter::PrintCity() {
    const int kHeaderY = 1;
    const int kHeaderX = 1;

    std::string header = "Weather forecast:  " + cities_[current_city_index_];
    attron(A_UNDERLINE);
    mvwprintw(stdscr, kHeaderY, kHeaderX, header.c_str());
    attroff(A_UNDERLINE);

    for (int i = 0; i < std::min(kMaxDaysNumber, default_weather_days_); ++i) {
        PrintDailyWeather();
        ++current_day_index_;
    }
}

void WeatherPrinter::EraseCity() {
    for (size_t i = 0; i < current_day_index_; ++i) {
        WINDOW* win = forecast_windows_.top();
        werase(win);
        delwin(win);
        forecast_windows_.pop();
    }
    current_day_index_ = 0;
}

void WeatherPrinter::PrintNextCity() {
    EraseCity();
    current_city_index_ = (current_city_index_ + 1) % cities_.size();
    werase(stdscr);
    wrefresh(stdscr);
    PrintCity();
}

void WeatherPrinter::PrintPrevCity() {
    EraseCity();
    current_city_index_ = (current_city_index_ - 1 + cities_.size()) % cities_.size();
    werase(stdscr);
    wrefresh(stdscr);
    PrintCity();
}

void WeatherPrinter::PrintNextDay() {
    if (current_day_index_ < kMaxDaysNumber) {
        PrintDailyWeather();
        ++current_day_index_;
    }
}

void WeatherPrinter::EraseDay() {
    if (current_day_index_ > 1) {
        WINDOW* win = forecast_windows_.top();
        werase(win);
        wrefresh(win);
        delwin(win);
        forecast_windows_.pop();
        --current_day_index_;
    }
}

void WeatherPrinter::Finish() {
    EraseCity();
    endwin();
}
