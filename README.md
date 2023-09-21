# Boost TCP/IP demo

Simple demo of using Boost.asio and Python for TCP/IP communication.

Tested on Windows with Visual Studio 2022.

Code is for demonstration purposes only, and is not necessary perfect.

### Building with vcpkg (using manifest mode)

Call CMake with
```
-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
```

#### Building under MinGW

Under MinGW you'll need to specify the vcpkg triplet:
```
-DVCPKG_TARGET_TRIPLET=x64-mingw-[static|dynamic]   # choose either `static` or `dynamic`.
-DVCPKG_HOST_TRIPLET=x64-mingw-[static|dynamic]       # <-- needed only if MSVC cannot be found. 
```
