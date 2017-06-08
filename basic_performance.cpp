#include <vector>
#include <iostream>
#include <hc.hpp>

// Parameters assume a Radeon R9 Nano (Fiji). 

constexpr size_t minutes = 3;
constexpr size_t iterations_per_thread = minutes * 1200 * 1000;
constexpr size_t flops_per_iteration = 1000; // max 1024 due to compiler limit on template recursion depth

// Fiji has 64 Compute Units, each with 4 Vector Units, each of which can have 10 wavefronts
// of 64 threads each
constexpr size_t no_fiji_threads = 64 * 4 * 10 * 64; 

// recursive template for manual inner loop unrolling in kernel
template<size_t n> float n_flops(float arg) [[hc]] { return arg + arg * n_flops<n-1>(arg); }
template<> float n_flops<0>(float arg) [[hc]] { return arg; }


int main(){
  // allocate and initialize data on the host; allocate memory on the GPU device;
  // copy host data to device
  constexpr float initial_value = 1.001f;
  std::vector<float> host_data(no_fiji_threads, initial_value);
  auto device_data = hc::array<float, 1>(hc::extent<1>(no_fiji_threads));
  hc::copy(host_data.begin(), device_data);

  // run kernel on GPU device
  hc::parallel_for_each(hc::extent<1>(no_fiji_threads), [=,&device_data](hc::index<1> i) [[hc]] {
      for(std::size_t iter = 0; iter != iterations_per_thread; ++iter){
	device_data[i] = n_flops<flops_per_iteration>(device_data[i]);
      }
    });

  // copy results back to host (otherwise, compiler will optimize kernel away)
  hc::copy(device_data, host_data.begin());
  auto sum = std::accumulate(host_data.begin(), host_data.end(), 0.0f);
  std::cout << sum << '\n';
}

