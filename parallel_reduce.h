#pragma once

#include <cstddef>
#include <numeric>
#include <thread>
#include <vector>

#include "sequence_io.h"

inline Value parallelReduce(const Sequence& data, std::size_t k)
{
    const std::size_t baseSize = data.size() / k;
    const std::size_t remainder = data.size() % k;

    std::vector<Value> partialResults(k, Value{0});
    std::vector<std::thread> threads;
    threads.reserve(k);

    std::size_t start = 0;
    for (std::size_t i = 0; i < k; ++i) {
        const std::size_t partSize = baseSize + (i < remainder ? 1 : 0);
        const auto first = data.cbegin() + start;
        const auto last = first + partSize;

        threads.emplace_back([&partialResults, i, first, last] {
            partialResults[i] = std::reduce(first, last, Value{0});
        });
        start += partSize;
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    return std::reduce(partialResults.cbegin(), partialResults.cend(), Value{0});
}