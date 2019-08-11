# jnum

jnum is an enum enabled with reflection for C++ in a CMake-friendly form. The
program takes in a json file with `.jnum` extension as follows

```json
{
  "namespace" : "test_jnum",
  "name" : "log_level",
  "string" : "log_level",
  "underlying_type" : "std::size_t",
  "option_list" :
  {
    "quiet"  : "0",
    "normal": "10"
  },
  "default_option" : "normal"
}
```

and generates an [header file](share/loglevel.hpp) as linked and you can use it
in the manner as shown in this [test](https://github.com/jayeshbadwaik/test_jnum/blob/master/src/bin/test_jnum.cpp).


To use this, install this library as
```
cmake -DCMAKE_INSTALL_PREFIX=<prefix>
make install
```

And use it from your cmake as
```
find_package(jnum REQUIRED)
target_jnum_directory(<target> PUBLIC|PRIVATE|INTERFACE <dir-containing-jnum>)
```

and you are good to go. Note that your target must somehow be built for the
code generator to be run. You can look at this [test
repo](https://github.com/jayeshbadwaik/test_jnum) to see how it works.
