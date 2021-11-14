# rgen

## Getting Started
`rgen` is a cross platform resource generator that generates the appropriate header and source files containing binary resource data.

Resource data can be specified using a JSON configuration file as shown in the example below
```
{
  "namespace": "R",
  "resources": [
    {
      "id": "loip1",
      "path": "./loremipsum1.txt",
      "namespace": "lm1"
    },
    {
      "id": "loip2",
      "path": "./loremipsum2.txt"
    }
  ]
}
```

The `resources` array can specify any number of `{id,path}` objects. The `namespace` tags are optional. However, to ensure resource variables don't pollute the global namespace, all generated resources belong to the default namespace called `R` when no global namespace is specified. The above sample configuration generates the following header, that can be used directly in project source files.
```
#pragma once

#include <string_view>
namespace R {
using bytearray_t = std::basic_string_view<unsigned char>;
std::string_view to_string_view(bytearray_t);
namespace lm1{
extern bytearray_t loip1;
}
extern bytearray_t loip2;
}
```
`rgen` internally represents the data as an array of `unsigned char` in the generated source file which can be accessed via `std::basic_string_view<unsigned char>` (aliased to `bytearray_t`) variables generated from the specified `id`.

Additionally, a convenience method to convert from `std::basic_string_view<unsigned char>` to `std::string_view` is provided, as most existing APIs use `const char*`.

The generated source file must be compiled using a target compiler (which maybe different from a host compiler) which supports `C++17`, and can be compiled either as `obj` file or `shared` or `static` library.

## Command Line Options
`rgen` has a simple command line interface that summarized below
```
Usage: ./rgen [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i,--input TEXT REQUIRED    Input JSON resource configuration file
  -o,--header TEXT            Output header name
  -s,--source TEXT            Output source namen be summarised below
```

Here, the header and source file names are optional and default to using `header=./resource.hpp` and `source=./resource.cpp` both of which are relative to the directory containing the input JSON file. The same applies to any relative resource paths specified within the JSON file as well.

## Build and Installation
`rgen` uses [`build2`](https://build2.org/) build system and can be consumed by placing a build tool dependency clause in the package manifest.
```
depends: * rgen
```

Resource files can be generated as a part of the build process by using the following ad-hoc rule in a `buildfile`
```
import! rgen = rgen%exe{rgen}
<hxx{resource} cxx{resource}>: $rgen file{res.json}
{{
  diag rgen $path($<[1])
  $rgen --input $path($<[1]) \
        --header $path($>[0]) \
        --source $path($>[1])
}}
```