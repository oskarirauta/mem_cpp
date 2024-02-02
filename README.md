# mem_cpp
Minimal C++ library for monitor free/used memory on Linux through /proc/meminfo

[![C++ CI build](https://github.com/oskarirauta/mem_cpp/actions/workflows/build.yml/badge.svg)](https://github.com/oskarirauta/mem_cpp/actions/workflows/build.yml)

### Depends

 - [common_cpp](https://github.com/oskarirauta/common_cpp)

### Importing
 - clone common_cpp as a submodule to common
 - clone logger_cpp as a submodule to logger
 - clone mem_cpp as a submodule to mem
 - include common_cpp's, logger_cpp's and mem_cpp's Makefile.incs in your Makefile
 - link with COMMON_OBJS and MEM_OBJS

Paths are modifiable, check Makefiles. For example code, clone this repository
with --recursive-submodules enabled.

### Example

Sample code is provided

### License

MIT
