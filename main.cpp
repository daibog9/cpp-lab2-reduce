// Compiler: Apple Clang 21.0.0 (clang-2100.3.34.2), C++20.

#include <algorithm>
#include <array>
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "experiments.h"
#include "sequence_io.h"

namespace {

constexpr std::array<std::size_t, 4> kSequenceSizes{10'000, 100'000, 1'000'000, 10'000'000};

std::string sequenceFileName(std::size_t size)
{
    return "sequence_" + std::to_string(size) + ".txt";
}

void prepareSequenceFiles()
{
    for (std::size_t size : kSequenceSizes) {
        const std::string path = sequenceFileName(size);
        if (!std::filesystem::exists(path)) {
            generateSequenceFile(path, size);
        }
    }
}

std::vector<std::size_t> makeKValues(unsigned hardwareThreads)
{
    std::vector<std::size_t> values;
    for (std::size_t k = 1; k <= hardwareThreads; ++k) {
        values.push_back(k);
    }
    values.push_back(2 * static_cast<std::size_t>(hardwareThreads));
    values.push_back(4 * static_cast<std::size_t>(hardwareThreads));
    return values;
}

void printHeader(unsigned hardwareThreads)
{
    std::cout << "Операція: сума (std::reduce)\n" << "Потоків процесора: " << hardwareThreads << '\n'
    << "Час - середнє за " << kRepeats << " запусків, у мілісекундах\n\n";
}

}

int main()
{
    const unsigned hardwareThreads = std::max(1u, std::thread::hardware_concurrency());
    prepareSequenceFiles();
    printHeader(hardwareThreads);

    const std::vector<std::size_t> kValues = makeKValues(hardwareThreads);
    for (std::size_t size : kSequenceSizes) {
        const std::string path = sequenceFileName(size);
        const Sequence data = loadSequence(path);
        std::cout << path << " (N = " << data.size() << ") \n";
        runExperiments(data, kValues, hardwareThreads);
    }
}