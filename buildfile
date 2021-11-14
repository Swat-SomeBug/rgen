libs =
import libs += nlohmann-json%lib{json}
import libs += cli11%lib{cli11}

./: exe{rgen} doc{README.md} manifest

exe{rgen}: {hxx cxx}{*} $libs

cxx.poptions =+ "-I$out_root" "-I$src_root"

./: tests/