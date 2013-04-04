#include <iostream>
#include <cassert>
#include "des.hpp"
#include "constants.hpp"

// http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

namespace {

inline uint64_t generate_bit( const uint32_t a_bit )
{
  assert(a_bit < BLOCK_BITS);

  return MASKS[a_bit];
}

inline bool get_bit( const uint64_t a_block, const uint32_t a_bit )
{
  return (a_block & generate_bit(a_bit)) != 0;
}

inline void set_bit( uint64_t & a_block, const uint32_t a_bit, const bool a_value )
{
  if(a_value)
    a_block |= generate_bit(a_bit);
  else
    a_block &= ~generate_bit(a_bit);
}

inline uint64_t l_subkey( const uint64_t a_block )
{
  return (a_block & SUBKEY_PART_MASK); 
}

inline uint64_t r_subkey( const uint64_t a_block )
{
  return (a_block << SUBKEY_PART_BITS);
}

inline uint64_t merge_subkey( const uint64_t a_l, const uint64_t a_r )
{
  return a_l | (a_r >> SUBKEY_PART_BITS);
}

inline uint64_t shift_subkey( uint64_t a_block, const uint32_t a_howmuch )
{
  for( uint32_t it = 0; it < a_howmuch; it++ ) {
    const bool bit_value = get_bit(a_block, 0);
    a_block <<= 1;
    set_bit(a_block, SUBKEY_PART_BITS - 1, bit_value);
  }

  return a_block;
}

void print_block( const uint64_t a_block )
{
  for(uint32_t bit = 0; bit < BLOCK_BITS; bit++) {
    if(bit != 0 && (bit % 4) == 0)
      std::cout << " ";

    std::cout << (get_bit(a_block, bit) ? "1" : "0");
  }

  std::cout << std::endl;
}

uint64_t transform_PC1( const uint64_t a_block )
{
  uint64_t res = 0;
  for(uint32_t i = 0; i < PC1_LEN; i++)
    set_bit(res, i, get_bit(a_block, PC1[i]));
  return res;
}

uint64_t transform_PC2( const uint64_t a_block )
{
  uint64_t res = 0;
  for(uint32_t i = 0; i < PC2_LEN; i++)
    set_bit(res, i, get_bit(a_block, PC2[i]));
  return res;
}

uint64_t transform_IP( const uint64_t a_block )
{
  uint64_t res = 0;
  for(uint32_t i = 0; i < BLOCK_BITS; i++)
    set_bit(res, i, get_bit(a_block, IP[i]));
  return res;
}

// OLD FUNCTIONS
uint32_t l( const uint64_t a_block )
{
  return (a_block >> PART_BITS);
}

uint32_t r( const uint64_t a_block )
{
  return (a_block & PART_MASK);
}

uint64_t merge( const uint32_t a_l, const uint32_t a_r )
{
  return (static_cast < uint64_t > (a_l) << PART_BITS) | (a_r);
}

bool is_byte_empty( const uint64_t a_block, const uint32_t a_ind )
{
  const uint64_t mask = (BYTE_MASK << (a_ind * BYTE_BITS));
  return (a_block & mask) == 0;
}

}

DES::DES( const Key & a_key )
{
  const uint64_t K = a_key();
  
  /* DEBUG
  std::cout << "K:" << std::endl; 
  print_block(K);*/

  // K+
  uint64_t Kp = transform_PC1(K);

  /* DEBUG
  std::cout << "K+:" << std::endl;
  print_block(Kp);*/

  // C0 && D0
  uint64_t C = l_subkey(Kp), D = r_subkey(Kp), CD = 0;
  
  /* DEBUG
  std::cout << "C0:" << std::endl;
  print_block(C);
  std::cout << "D0:" << std::endl;
  print_block(D);*/

  // Cn && Dn && Kn 
  for(uint32_t round = 0; round < ROUNDS; round++) {
    C = shift_subkey(C, SUBKEYS_SHIFTS[round]);
    D = shift_subkey(D, SUBKEYS_SHIFTS[round]);
    CD = merge_subkey(C, D);
    m_keys[round] = transform_PC2(CD);

    /* DEBUG
    std::cout << "C" << (round + 1) << std::endl;
    print_block(C);
    std::cout << "D" << (round + 1) << std::endl;
    print_block(D);
    std::cout << "CD" << (round + 1) << std::endl;
    print_block(CD);
    std::cout << "K" << (round + 1) << std::endl;
    print_block(m_keys[round]);*/
  }
}

uint32_t DES::f( const uint32_t a_part, const uint32_t a_round ) const
{
  return a_part;
}

uint64_t DES::encrypt_block( const uint64_t a_block ) const
{
  const uint64_t IP = transform_IP(a_block);

  uint32_t l_part = l(a_block), r_part = r(a_block);

  for( uint32_t round = 0; round < ROUNDS; round++ )
  {
    const uint32_t temp = l_part;
    l_part = r_part ^ f(l_part, round);
    r_part = temp;
  }

  return merge(l_part, r_part);
}

uint64_t DES::decrypt_block( const uint64_t a_block ) const
{
  uint32_t l_part = l(a_block), r_part = r(a_block);

  for( uint32_t round = ROUNDS; round > 0; round-- )
  {
    const uint32_t temp = r_part;
    r_part = l_part ^ f(r_part, round - 1);
    l_part = temp;
  }

  return merge(l_part, r_part);
}

void DES::encrypt( std::istream & a_in, std::ostream & a_out ) const
{
  uint64_t buffer = 0;
  bool end = false;

  while(!end) {
    buffer = 0;
    a_in.read(reinterpret_cast < char * > (&buffer), BLOCK_BYTES);
    const size_t readed = a_in.gcount();

    if(readed == BLOCK_BYTES) {
      buffer = encrypt_block(buffer);
      a_out.write(reinterpret_cast < const char * > (&buffer), BLOCK_BYTES);
    } else {
      const size_t pos = readed * BYTE_BITS;
      buffer |= (static_cast < uint64_t > (1) << pos);
      buffer = encrypt_block(buffer);
      a_out.write(reinterpret_cast < const char * > (&buffer), BLOCK_BYTES);
      end = true;
    }
  }
}

void DES::output_last_byte( const uint64_t a_block, std::ostream & a_out ) const
{
  assert( a_block != 0 );

  uint32_t end = BLOCK_BYTES - 1;

  while(is_byte_empty(a_block, end))
    --end;

  if(end > 0)
    a_out.write(reinterpret_cast < const char * > (&a_block), end);
}

void DES::decrypt( std::istream & a_in, std::ostream & a_out ) const
{
  uint64_t last = 0, buffer = 0;
  bool first = true, end = false;

  while(!end) {
    buffer = 0;
    a_in.read( reinterpret_cast < char * > (&buffer), BLOCK_BYTES);
    const size_t readed = a_in.gcount();
 
    if(readed == 0) {
      if(!first)
        output_last_byte(last, a_out);

      end = true;
    } else if(readed == BLOCK_BYTES) {
      if(!first)
        a_out.write(reinterpret_cast < const char * > (&last), BLOCK_BYTES);
      
      last = decrypt_block(buffer);
    } else {
      assert(true);
    }

    first = false;
  }
}
