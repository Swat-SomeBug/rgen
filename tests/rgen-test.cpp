/**
 * Copyright (c) 2021 Swat SomeBug
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <resource.h>
#include <array>
#include <iostream>

int main() {
  auto printer = [](std::string_view buf) {
    std::cout << "Printing data at: " << std::hex << std::showbase
              << reinterpret_cast<std::uintptr_t>(buf.data()) << "\n"
              << std::dec << std::noshowbase;
    std::cout << "Buffer total buffer size: " << buf.size() << '\n';

    auto looplimit = buf.size() > 500 ? 500 : buf.size();
    for (std::size_t i = 0; i < 500; ++i) {
      std::cout << buf[i];
    }
    std::cout << std::endl;
  };

  printer(R::to_string_view(R::lm1::loip1));

  printer(R::to_string_view(R::loip2));

  return 0;
}