#include <fstream>
#include <printer.hpp>

namespace rgen {

void print_header(const std::filesystem::path& file, const info& rinfo) {
  std::ofstream o_h{file};
  o_h << "#pragma once\n\n";
  o_h << "#include <string_view>\n";
  o_h << "namespace " << rinfo.topns << " {\n"
      << "using bytearray_t = std::basic_string_view<unsigned char>;\n"
      << "std::string_view to_string_view(bytearray_t);\n";
  for (const auto& r : rinfo.res) {
    if (r.ns) {
      o_h << "namespace " << r.ns.value() << "{\n";
    }
    o_h << "extern bytearray_t " << r.id << ";\n";
    if (r.ns) {
      o_h << "}\n";
    }
  }
  o_h << "}\n";
}

void print_source(const std::filesystem::path& file, const info& rinfo) {
  std::ofstream o_src{file};
  o_src << std::hex << "#include <resource.h>\n"
        << "namespace " << rinfo.topns << " {\n"
        << "using bytearray_t = std::basic_string_view<unsigned char>;\n"
        << "std::string_view to_string_view(bytearray_t ba) { return "
           "{reinterpret_cast<const char*>(ba.data()), ba.size()};}\n";
  for (const auto& r : rinfo.res) {
    if (r.ns) {
      o_src << "namespace " << r.ns.value() << "{\n";
    }
    o_src << std::hex << "static const unsigned char _uchar_arr_" << r.id
          << "[] = "
          << "{\n";

    std::size_t   charcount = 0;
    std::ifstream f{r.path, std::ios::binary};

    if (!f.good()) {
      continue;
    }

    while (true) {
      unsigned char v[16];
      f.read(reinterpret_cast<char*>(v), 16);
      auto readbytes = f.gcount();
      charcount += readbytes;
      // Pull 1st byte out of the loop to get the commas correct
      if (readbytes != 0) {
        o_src << "0x" << static_cast<unsigned int>(v[0]);
      }
      for (int i = 1; i < readbytes; i++)
        o_src << ",0x" << static_cast<unsigned int>(v[i]);
      if (f.good()) {
        o_src << ",\n";
      } else {
        break;
      }
    }
    o_src << "};\n";
    o_src << std::dec << "bytearray_t " << r.id << "{_uchar_arr_" << r.id << ','
          << charcount << "};\n";

    if (r.ns) {
      o_src << "}\n";
    }
  }
  o_src << "}\n";
}
}  // namespace rgen