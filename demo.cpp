#include <sycl/sycl.hpp>

#include <iostream>

int main() {
  try {
    auto cgf = [&](sycl::handler& cgh) { cgh.single_task([=]() {}); };
    sycl::queue queue;
    // Try to allocate 100GB of memory.
    for (auto i = 0; i < 25; i++) {
      sycl::malloc_device(4294967296 ,queue);
    }
    auto event = queue.submit(cgf);
    event.wait_and_throw();
  } catch (const sycl::exception& ep) {
    const std::string_view err_msg(ep.what());
    if (err_msg.find("PI_ERROR_OUT_OF_RESOURCES") != std::string::npos) {
      std::cout << "Allocation is out of device memory on the current platform." << std::endl;
    } else {
      throw ep;
    }
  }
  std::cout << "pass!" << std::endl;
}
