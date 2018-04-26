#include <vector>

#include <cstdlib> 

#include <iostream>

bool is_sorted(const int32_t* input, size_t n) {
  if (n < 2) {
    return true;
  }

  for (size_t i=0; i < n - 1; i++) {
    if (input[i] > input[i + 1])
      return false;
  }

  return true;
}

int main() {

  std::vector<int32_t> input;
  size_t max_size = 1024;
  bool ok = false;

  // fill the vector ordered
  input.clear();
  input.reserve(max_size);
  for (size_t i=0; i < max_size; ++i) {
    input[i] = i;
  }

  ok = is_sorted(&input[0], max_size);

  std::cout << std::boolalpha << ok << std::endl;

}