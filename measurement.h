#pragma once

#include <chrono>

#include "sequence_io.h"

inline constexpr int kRepeats = 5;

struct Measurement {
    double milliseconds;
    Value result;
};

template <typename Func>
Measurement measureAverage(Func func)
{
    Value result = 0;
    std::chrono::duration<double, std::milli> total{0};

    for (int i = 0; i < kRepeats; ++i) {
        const auto start = std::chrono::steady_clock::now();
        result = func();
        total += std::chrono::steady_clock::now() - start;
    }

    return {total.count() / kRepeats, result};
}