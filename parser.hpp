#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

namespace rgen {

struct obj {
  std::string                id;
  std::filesystem::path      path;
  std::optional<std::string> ns;
};
using resources = std::vector<obj>;

struct info {
  std::string topns;
  resources   res;
};

void      from_json(const nlohmann::json& j, obj& o);
resources get_resouces(const nlohmann::json&);
info      parse(const std::filesystem::path&);
}  // namespace rgen
