#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include <cstdint>

const static uint32_t ROUNDS = 16,                           // Total rounds
                      KEY_LEN = 16,                          // Key length in chars
                      BYTE_BITS = 8,                         // Bits in one byte
                      BLOCK_BITS = 64,                       // Bits in one block
                      PART_BITS = BLOCK_BITS / 2,            // Bits in one block part
                      SUBKEY_BITS = 56,                      // Bits in one subkey
                      SUBKEY_PART_BITS = SUBKEY_BITS / 2,    // Bits in one subkey part
                      BLOCK_BYTES = 8;                       // Bytes in one block
                      
const static uint64_t PART_MASK = 0xffffffff,                // Mask for first part of block
                      BYTE_MASK = 0xff,                      // Mask for first byte
                      SUBKEY_PART_MASK = 0xfffffff000000000; // Mask for first part of subkey

const static uint32_t PC1_LEN = 56;

const static uint32_t PC1[PC1_LEN] = {
  56, 48, 40, 32, 24, 16, 8,
  0, 57, 49, 41, 33, 25, 17,
  9, 1, 58, 50, 42, 34, 26,
  18, 10, 2, 59, 51, 43, 35,
  62, 54, 46, 38, 30, 22, 14,
  6, 61, 53, 45, 37, 29, 21,
  13, 5, 60, 52, 44, 36, 28,
  20, 12, 4, 27, 19, 11, 3
};

const static uint32_t PC2_LEN = 48;

const static uint32_t PC2[PC2_LEN] = {
  13, 16, 10, 23, 0, 4,
  2, 27, 14, 5, 20, 9,
  22, 18, 11, 3, 25, 7,
  15, 6, 26, 19, 12, 1,
  40, 51, 30, 36, 46, 54,
  29, 39, 50, 44, 32, 47,
  43, 48, 38, 55, 33, 52,
  45, 41, 49, 35, 28, 31
};

const static uint32_t SUBKEYS_SHIFTS[ROUNDS] = {
  1, 1, 2, 2, 2, 2, 2, 2,
  1, 2, 2, 2, 2, 2, 2, 1
};



#endif
