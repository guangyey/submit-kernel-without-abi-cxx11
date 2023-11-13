# submit-kernel-without-abi-cxx11
This file checks the availability of submitting a sycl kernel with compilation option `-D_GLIBCXX_USE_CXX11_ABI=0` and catching the excepted exception.
If unavailable, we can NOT register our operators in PyTorch, implemented by the sycl kernel.
Because `std::string` is used in the operator registry API provided by PyTorch, which is built with `-D_GLIBCXX_USE_CXX11_ABI=0`.

# how to run this demo
```bash
cd submit-kernel-without-abi-cxx11/
cmake .
make
./demo
```

# Results
* With compiler 2024.0.0 (20231017) and [`-D_GLIBCXX_USE_CXX11_ABI=0`](https://github.com/guangyey/submit-kernel-without-abi-cxx11/blob/716a290b0caa738072d5cb1025b5955d46d32f7b/CMakeLists.txt#L33)
```bash
cmake .
make
[ 50%] Building CXX object CMakeFiles/demo.dir/demo.cpp.o
[100%] Linking CXX executable demo
/usr/bin/ld: /tmp/icpx-7c7e36bcb5/demo-865163.o: in function `std::_Function_handler<void (sycl::_V1::handler&), main::{lambda(sycl::_V1::handler&)#1}>::_M_invoke(std::_Any_data const&, sycl::_V1::handler&)':
demo-664cd0.cpp:(.text+0x5bf): undefined reference to `sycl::_V1::handler::verifyUsedKernelBundle(std::string const&)'
/usr/bin/ld: /tmp/icpx-7c7e36bcb5/demo-865163.o: in function `sycl::_V1::runtime_error::runtime_error(std::error_code, std::string const&, int)':
demo-664cd0.cpp:(.text._ZN4sycl3_V113runtime_errorC2ESt10error_codeRKSsi[_ZN4sycl3_V113runtime_errorC2ESt10error_codeRKSsi]+0x2d2): undefined reference to `sycl::_V1::exception::exception(std::error_code, std::shared_ptr<sycl::_V1::context>, std::string const&)'
icpx: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [CMakeFiles/demo.dir/build.make:98: demo] Error 1
make[1]: *** [CMakeFiles/Makefile2:83: CMakeFiles/demo.dir/all] Error 2
make: *** [Makefile:91: all] Error 2
```
* With compiler 2024.0.0 (20231017) and [change `-D_GLIBCXX_USE_CXX11_ABI=1`](https://github.com/guangyey/submit-kernel-without-abi-cxx11/blob/716a290b0caa738072d5cb1025b5955d46d32f7b/CMakeLists.txt#L33)
```bash
cmake .
make
[ 50%] Building CXX object CMakeFiles/demo.dir/demo.cpp.o
[100%] Linking CXX executable demo
[100%] Built target demo
./demo
Allocation is out of device memory on the current platform.
pass!
```
* **We expect this demo can build pass and run pass when using [`-D_GLIBCXX_USE_CXX11_ABI=0`](https://github.com/guangyey/submit-kernel-without-abi-cxx11/blob/716a290b0caa738072d5cb1025b5955d46d32f7b/CMakeLists.txt#L33)**
