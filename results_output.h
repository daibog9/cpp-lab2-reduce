#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "measurement.h"

struct KMeasurement {
    std::size_t k;
    Measurement measurement;
};

void printLibraryHeader();
void printLibraryRow(const std::string& mode, const Measurement& measurement);
void printOwnAlgorithmTable(const std::vector<KMeasurement>& rows);
void printBestK(const std::vector<KMeasurement>& rows, unsigned hardwareThreads);