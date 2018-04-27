#include <vector>
#include <cstdlib> 
#include <iostream>

#include <immintrin.h>

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

bool is_sorted_sse(const int32_t* input, size_t n) {
  size_t i = 0;

  if (n > 4) {
    for (/**/; i < n - 4; i +=4) {
      const __m128i curr = _mm_loadu_si128(reinterpret_cast<const __m128i*>(input + i));
      const __m128i next = _mm_loadu_si128(reinterpret_cast<const __m128i*>(input + i + 1));

      const __m128i mask = _mm_cmpgt_epi32(curr, next);
      if (!_mm_test_all_zeros(mask, mask)) {
        return false;
      }

    }
  }

  // normal checking
  for (/**/; i + 1 < n; i++) {
    if (input[i] > input[i + 1])
      return false;
  }

  return true;
}

bool is_sorted_sse_2(int32_t* a, size_t n) {

  size_t i = 0;
  if (n >= 8) {
    __m128i chunk0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(a));
    do {
      const __m128i chunk1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(a + i + 4));
      const __m128i curr = chunk0;
      const __m128i next = _mm_alignr_epi8(chunk1, chunk0, 4);

      const __m128i mask = _mm_cmpgt_epi32(curr, next);
      if (!_mm_test_all_zeros(mask, mask)) {
        return false;
      }

      chunk0 = chunk1;
      i += 4;
    } while (i < n - 4);
  }

  for (/**/; i + 1 < n; i++) {
    if (a[i] > a[i + 1])
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
  std::cout << "no vec: " << std::boolalpha << ok << std::endl;
  ok = is_sorted_sse(&input[0], max_size);
  std::cout << "sse vec: " << std::boolalpha << ok << std::endl;
  ok = is_sorted_sse_2(&input[0], max_size);
  std::cout << "sse2 vec: " << std::boolalpha << ok << std::endl;
  


  std::cout << "\nNot ordered\n" << std::endl;

  // not ordered
  input[max_size/2] = 0;
  ok = is_sorted(&input[0], max_size);
  std::cout << "no vec: " << std::boolalpha << ok << std::endl;
  ok = is_sorted_sse(&input[0], max_size);
  std::cout << "sse vec: " << std::boolalpha << ok << std::endl;
  ok = is_sorted_sse_2(&input[0], max_size);
  std::cout << "sse2 vec: " << std::boolalpha << ok << std::endl;



}