#include "results_output.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace {

constexpr int kTimeWidth = 14;
constexpr int kResultWidth = 20;
constexpr int kKWidth = 8;

void printMeasurement(const Measurement& measurement)
{
    std::cout << std::fixed << std::setprecision(4) << std::setw(kTimeWidth) << measurement.milliseconds 
    << std::setw(kResultWidth) << measurement.result;
}

}

void printLibraryHeader()
{
    std::cout << "  Бібліотечний std::reduce:\n" << "        Час, мс           Результат   Режим\n";
}

void printLibraryRow(const std::string& mode, const Measurement& measurement)
{
    printMeasurement(measurement);
    std::cout << "   " << mode << '\n';
}

void printOwnAlgorithmTable(const std::vector<KMeasurement>& rows)
{
    std::cout << "  Власний паралельний алгоритм (K частин = K потоків):\n" 
    << "         K       Час, мс           Результат\n";

    for (const KMeasurement& row : rows) {
        std::cout << std::setw(kKWidth) << row.k;
        printMeasurement(row.measurement);
        std::cout << '\n';
    }
}

void printBestK(const std::vector<KMeasurement>& rows, unsigned hardwareThreads)
{
    const auto best = std::min_element(rows.begin(), rows.end(),
        [](const KMeasurement& a, const KMeasurement& b) {
            return a.measurement.milliseconds < b.measurement.milliseconds;
        });

    std::cout << std::fixed << std::setprecision(4) << "  Найкраще K = " << best->k 
    << " (час " << best->measurement.milliseconds << " мс); " << "потоків процесора = " << hardwareThreads << "; " 
    << std::setprecision(2) << "K / потоки процесора = " << static_cast<double>(best->k) / hardwareThreads << "\n\n";
}