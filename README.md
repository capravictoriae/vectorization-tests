# vectorization-tests

## Debug VECT registers

When using the `#include <immintrin.h>` intrinsecs, to see the contents with GDB:

- `info all-registers`: to see the registers (and content)
    + `apropos registers`: to see the available options
- `print $xmm0`: to see the content of the `xmm0` register in various formats
- `p $xmm0.v4_int32`: to see a spceific view of the register
- `p $xmm0.v4_int32[2]`: to see the 3 component of a 4 int32 register interpretation

- `p *(int32_t *)&chunk0@4`: to print the value of the `chunk0` variable of type `__m128` casted to 4 `int32_t` integers.
