#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include <random>
#include <string> 
#include <locale>

class Printer 
{
public:
    void print(const std::string& message)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        std::cout << message << "\n";
    }

private:
    std::mutex mutex_;
};

void sortAndPrint(Printer& printer, std::vector<int> data) 
{
    std::sort(data.begin(), data.end());
    printer.print("Отсортированные данные: ");
    for (const auto& num : data) 
    {
        printer.print(std::to_string(num)); // Преобразование числа в строку
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    Printer printer;

    // Генерация случайных данных
    std::vector<int> data1(10);
    std::vector<int> data2(10);
    std::vector<int> data3(10);

    std::generate(data1.begin(), data1.end(), []() { return rand() % 100; });
    std::generate(data2.begin(), data2.end(), []() { return rand() % 100; });
    std::generate(data3.begin(), data3.end(), []() { return rand() % 100; });

    // Создание потоков
    std::thread t1(sortAndPrint, std::ref(printer), data1);
    t1.join();
    std::thread t2(sortAndPrint, std::ref(printer), data2);
    t2.join();
    std::thread t3(sortAndPrint, std::ref(printer), data3);
    t3.join();


    return 0;
}