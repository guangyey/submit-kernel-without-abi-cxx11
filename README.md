# submit-kernel-without-abi-cxx11
This file checks the availability of submitting a sycl kernel with compilation option `-D_GLIBCXX_USE_CXX11_ABI=0`.
If unavailable, we can NOT register our operators, implemented by the sycl kernel, in PyTorch.
Because `std::string` is used in the operator registry API provided by PyTorch, which is built with `-D_GLIBCXX_USE_CXX11_ABI=0`.

# how to run this demo
```bash
cd submit-kernel-without-abi-cxx11/
cmake .
make
./demo
```
We expect this demo can build pass and run pass.
