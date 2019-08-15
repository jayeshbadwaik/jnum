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
in the manner as shown in this
[test](https://github.com/jayeshbadwaik/test_jnum/blob/master/src/bin/test_jnum.cpp).
It automatically correctly links the generated header file to the desired
target and generates install definitions for the same. This means that the
consumer of your library does not have to use the code generator for your
headers. (You still depend on the `jnum` header only utility library though
which is installed along with the code generator.)

The library is somewhat similar to
[`magic_enum`](https://github.com/Neargye/magic_enum), but since there are no
macros in this libraries, you get good code-completion and debugging
facilities.

## How to use this library?

### First Step : Install

To use this, install this library as
```
cmake -DCMAKE_INSTALL_PREFIX=<prefix>
cmake --install .
```

and discover the package using
```
find_package(jnum REQUIRED)
```

### Second Step : Place all the `.jnum` files in the directory
tree as you wish. You can have multiple directory trees and then run the
command below for each one of them. For example, you might have a tree as
follows:

```
${PROJECT_SOURCE_DIR}/jnum_dir
  |
  |-- your_lib
        |
        |-- some_option.jnum
        |-- another_dir
              |-- other_option.jnum
```


### Third Step: Configure CMake to build the target
Assume that `jnum_dir` is the relative path with respect to the
`PROJECT_SOURCE_DIR`.  Then use the library in your cmake as
```
target_jnum_directory(<target> PUBLIC|PRIVATE|INTERFACE jnum_dir)
```

Due to some quirkiness which I have not completely mastered yet, it is the
responsibility of the user to make sure that the `<target>` is somehow built.
The situation might improve in future.  The target will create a directory tree
in `${PROJECT_BINARY_DIR}/jnum/jnum_dir/include` and generate header files
there as

```
${PROJECT_BINARY_DIR}/jnum/jnum_dir/include
  |
  |-- your_lib
        |
        |-- some_option.hpp
        |-- another_dir
              |-- other_option.hpp
```

and then you are good to go.

You can look at this [test repo](https://github.com/jayeshbadwaik/test_jnum) to
see how it works.
