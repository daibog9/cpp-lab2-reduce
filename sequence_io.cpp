#include "sequence_io.h"

#include <fstream>
#include <random>

namespace {
constexpr unsigned long long kSeed = 13;
constexpr Value kMinValue = -1'000'000;
constexpr Value kMaxValue = 1'000'000;
}

void generateSequenceFile(const std::string& path, std::size_t size)
{
    std::mt19937_64 engine(kSeed);
    std::uniform_int_distribution<Value> distribution(kMinValue, kMaxValue);

    std::ofstream out(path);
    out << size << '\n';
    for (std::size_t i = 0; i < size; ++i) {
        out << distribution(engine) << '\n';
    }
}

Sequence loadSequence(const std::string& path)
{
    std::ifstream in(path);
    std::size_t size = 0;
    in >> size;

    Sequence data(size);
    for (Value& value : data) {
        in >> value;
    }
    return data;
}