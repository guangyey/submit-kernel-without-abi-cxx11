#include <sycl/sycl.hpp>

#include <iostream>

int main() {
  auto cgf = [&](sycl::handler& cgh) { cgh.single_task([=]() {}); };
  sycl::queue queue;
  queue.submit(cgf);
  std::cout << "pass!" << std::endl;
}
