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

const static uint64_t MASKS[BLOCK_BITS] = {
  0x8000000000000000, 0x4000000000000000, 0x2000000000000000, 0x1000000000000000,
  0x800000000000000, 0x400000000000000, 0x200000000000000, 0x100000000000000,
  0x80000000000000, 0x40000000000000, 0x20000000000000, 0x10000000000000, 0x8000000000000,
  0x4000000000000, 0x2000000000000, 0x1000000000000, 0x800000000000, 0x400000000000,
  0x200000000000, 0x100000000000, 0x80000000000, 0x40000000000, 0x20000000000, 0x10000000000,
  0x8000000000, 0x4000000000, 0x2000000000, 0x1000000000, 0x800000000, 0x400000000, 0x200000000,
  0x100000000, 0x80000000, 0x40000000, 0x20000000, 0x10000000, 0x8000000, 0x4000000, 0x2000000,
  0x1000000, 0x800000, 0x400000, 0x200000, 0x100000, 0x80000, 0x40000, 0x20000, 0x10000,
  0x8000, 0x4000, 0x2000, 0x1000, 0x800, 0x400, 0x200, 0x100, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1
};

const static uint32_t IP[BLOCK_BITS] = {
  57, 49, 41, 33, 25, 17, 9, 1,
  59, 51, 43, 35, 27, 19, 11, 3,
  61, 53, 45, 37, 29, 21, 13, 5,
  63, 55, 47, 39, 31, 23, 15, 7,
  56, 48, 40, 32, 24, 16, 8, 0,
  58, 50, 42, 34, 26, 18, 10, 2,
  60, 52, 44, 36, 28, 20, 12, 4,
  62, 54, 46, 38, 30, 22, 14, 6
};  

#endif
