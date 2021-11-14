#pragma once
#include <filesystem>
#include <parser.hpp>

namespace rgen {
void print_header(const std::filesystem::path&, const info&);
void print_source(const std::filesystem::path&, const info&);
}  // namespace rgen