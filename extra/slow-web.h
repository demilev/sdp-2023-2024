#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <stdexcept>

class SlowWeb
{
private:
    // Вектор, който съдържа двойки url и съдържанието на страницата на този адрес
    std::vector<std::pair<std::string, std::string>> data;

    // Рандом генератор
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;

public:
    SlowWeb(const std::vector<std::pair<std::string, std::string>> &data) : data(data), rng(std::random_device()()), dist(500, 1000) {}
    std::string getContent(const std::string &url)
    {
        // Генерираме едно число от 500 до 1000 и заспиваме/блокираме програмата за толкова на брой милисекунди.
        // Така симулираме бавното четене на страница
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));

        for (const std::pair<std::string, std::string> &page : data)
        {
            // Връщаме страницата, която е на дадения адрес
            if (page.first == url)
                return page.second;
        }

        // Ако такава не е намерена, хвърляме грешка
        throw std::runtime_error("url " + url + " not found");
    }
};
