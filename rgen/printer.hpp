/**
 * Copyright (c) 2021 Swat SomeBug
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once
#include <filesystem>
#include <parser.hpp>

namespace rgen {
void print_header(const std::filesystem::path&, const info&);
void print_source(
    const std::pair<std::filesystem::path, std::filesystem::path>&,
    const info&);
}  // namespace rgen