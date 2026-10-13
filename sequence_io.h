#pragma once

#include <cstddef>
#include <string>
#include <vector>

using Value = long long;
using Sequence = std::vector<Value>;

void generateSequenceFile(const std::string& path, std::size_t size);
Sequence loadSequence(const std::string& path);