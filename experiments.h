#pragma once

#include <cstddef>
#include <execution>
#include <numeric>
#include <vector>

#include "measurement.h"
#include "parallel_reduce.h"
#include "results_output.h"
#include "sequence_io.h"

template <typename Policy>
Measurement measureLibraryWithPolicy(const Policy& policy, const Sequence& data)
{
    return measureAverage([&] {
        return std::reduce(policy, data.cbegin(), data.cend(), Value{0});
    });
}

inline void runLibraryExperiments(const Sequence& data)
{
    printLibraryHeader();
    printLibraryRow("без політики", measureAverage([&] {
        return std::reduce(data.cbegin(), data.cend(), Value{0});
    }));
    printLibraryRow("std::execution::seq", measureLibraryWithPolicy(std::execution::seq, data));
    printLibraryRow("std::execution::par", measureLibraryWithPolicy(std::execution::par, data));
    printLibraryRow("std::execution::par_unseq", measureLibraryWithPolicy(std::execution::par_unseq, data));
    printLibraryRow("std::execution::unseq", measureLibraryWithPolicy(std::execution::unseq, data));
}

inline void runOwnAlgorithmExperiments(const Sequence& data, const std::vector<std::size_t>& kValues, unsigned hardwareThreads)
{
    std::vector<KMeasurement> rows;
    for (std::size_t k : kValues) {
        rows.push_back({k, measureAverage([&] {
            return parallelReduce(data, k);
        })});
    }

    printOwnAlgorithmTable(rows);
    printBestK(rows, hardwareThreads);
}

inline void runExperiments(const Sequence& data, const std::vector<std::size_t>& kValues, unsigned hardwareThreads)
{
    runLibraryExperiments(data);
    runOwnAlgorithmExperiments(data, kValues, hardwareThreads);
}