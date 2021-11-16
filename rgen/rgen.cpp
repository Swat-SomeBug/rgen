/**
 * Copyright (c) 2021 Swat SomeBug
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <filesystem>
#include <fstream>
#include <string>
#include <utility>

// CLI
#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>

// Project local
#include <parser.hpp>
#include <printer.hpp>

int main(int argc, char* argv[]) {
  using fsp = std::filesystem::path;
  CLI::App            app{"Generate resource artifacts"};
  std::pair<fsp, fsp> files{"./resource.hpp", "./resource.cpp"};
  fsp                 jsonfilepath;

  app.add_option("-i,--input", jsonfilepath,
                 "Input JSON resource configuration file")
      ->required();
  app.add_option("-o,--header", files.first, "Output header name");
  app.add_option("-s,--source", files.second, "Output source name");

  CLI11_PARSE(app, argc, argv);

  auto rgeninfo = rgen::parse(jsonfilepath);

  if (files.first.is_relative()) {
    files.first = jsonfilepath.parent_path() / files.first;
  }
  if (files.second.is_relative()) {
    files.second = jsonfilepath.parent_path() / files.second;
  }
  rgen::print_header(files.first, rgeninfo);
  rgen::print_source(files, rgeninfo);

  return 0;
}
