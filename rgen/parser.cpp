/**
 * Copyright (c) 2021 Swat SomeBug
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <fstream>
#include <parser.hpp>

namespace rgen {
void from_json(const nlohmann::json& j, obj& o) {
  j["id"].get_to(o.id);
  j["path"].get_to(o.path);
  if (j.contains("namespace"))
    o.ns = j["namespace"];
}

resources get_resouces(const nlohmann::json& j) {
  std::vector<obj> resources;
  for (const auto& res : j["resources"].items()) {
    resources.emplace_back(res.value().get<rgen::obj>());
  }
  return resources;
}

info parse(const std::filesystem::path& p) {
  std::ifstream jsonfile{p};
  if (!jsonfile.good()) {
    throw std::runtime_error("Cannot open input JSON file");
  }
  nlohmann::json j;
  jsonfile >> j;
  // Assign global top namespace

  return {j.value("namespace", "R"), get_resouces(j)};
}
}  // namespace rgen