#include "WeatherRequest.h"
#include "WeatherPrint.h"

#include <chrono>
#include <iostream>
#include <thread>

std::mutex mutex;
std::condition_variable cond_var;

void RequestFunc(Request& request, std::atomic_bool& running,
                   int freq) {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cond_var.wait_for(lock, std::chrono::milliseconds(freq), [&running] { return !running; });
        if (!running) {
            return;
        }
        request.UpdateRequest();
        lock.unlock();
    }
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "Error: no configuration filename" << std::endl;
        return 1;
    }
    std::ifstream config(argv[1]);
    if (!config.is_open()) {
        std::cerr << "Error opening configuration file" << std::endl;
        return 1;
    }

    nlohmann::json json_data;
    config >> json_data;
    config.close();
    int default_weather_days = json_data["default_weather_days"];
    if (default_weather_days < 1) {
        std::cerr << "Error: default_weather_days must be >= 1" << std::endl;
        return 1;
    }
    int update_frequency = json_data["update_frequency"];
    if (update_frequency < 1) {
        std::cerr << "Error: update_frequency must be >= 1" << std::endl;
        return 1;
    }
    std::vector<std::string> cities = json_data["city_list"].get<std::vector<std::string>>();

    Request request(cities);
    request.UpdateRequest();
    const std::vector<nlohmann::json>& data = request.GetData();

    std::atomic_bool running = true;
    std::thread request_thread(RequestFunc, std::ref(request), std::ref(running), update_frequency);

    WeatherPrinter weather_printer(data, cities, default_weather_days);
    weather_printer.PrintCity();

    const int kEscapeCode = 27;
    int symbol;
    while ((symbol = getch()) != kEscapeCode) {
        if (symbol == 'n') {
            weather_printer.PrintNextCity();
        } else if (symbol == 'p') {
            weather_printer.PrintPrevCity();
        } else if (symbol == '+') {
            weather_printer.PrintNextDay();
        } else if (symbol == '-') {
            weather_printer.EraseDay();
        }
    }

    weather_printer.Finish();

    running = false;
    cond_var.notify_one();
    request_thread.join();

    return 0;
}
