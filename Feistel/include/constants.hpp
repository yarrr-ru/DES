#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include <cstdint>

const static uint32_t ROUNDS = 16,
                      HEX_LEN = 8, 
                      BYTE_BITS = 8,
                      PART_BITS = 32,
                      BLOCK_BYTES = 8;
                      
const static uint64_t PART_MASK = 0xffffffff,
                      BYTE_MASK = 0xff;
                      

#endif
