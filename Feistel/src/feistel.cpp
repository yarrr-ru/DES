#include <cassert>
#include "feistel.hpp"
#include "constants.hpp"

namespace {

uint32_t l( const uint64_t a_block)
{
  const static uint64_t mask = ((uint64_t) (0xffffffff)) << 32;
  return ((a_block & mask) >> 32);
}

uint32_t r( const uint64_t a_block )
{
  const static uint64_t mask = 0xffffffff;
  return (a_block & mask);
}

uint64_t merge( const uint32_t a_l, const uint32_t a_r )
{
  return (((uint64_t) a_l) << 32) | (a_r);
}

bool is_byte_empty( const uint64_t a_block, const uint32_t a_ind )
{
  const uint64_t mask = ((uint64_t) 0xff) << (a_ind * 8);
  return (a_block & mask) == 0;
}

}

uint32_t Feistel::f( const uint32_t a_part, const uint32_t a_round ) const
{
  return (m_key[a_round] * a_part);
}

uint64_t Feistel::encrypt_block( const uint64_t a_block ) const
{
  uint32_t l_part = l(a_block), r_part = r(a_block);

  for( uint32_t round = 0; round < ROUNDS; round++ )
  {
    const uint32_t temp = l_part;
    l_part = r_part ^ f(l_part, round);
    r_part = temp;
  }

  return merge(l_part, r_part);
}

uint64_t Feistel::decrypt_block( const uint64_t a_block ) const
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

Feistel::Feistel( const Key & a_key )
  : m_key( a_key )
{
}

void Feistel::encrypt( std::istream & a_in, std::ostream & a_out ) const
{
  uint64_t buffer = 0;
  bool end = false;
  while(!end) {
    buffer = 0;
    a_in.read((char *) (&buffer), sizeof(buffer));
    const size_t readed = a_in.gcount();

    if(readed == sizeof(buffer)) {
      buffer = encrypt_block(buffer);
      a_out.write((char *) (&buffer), sizeof(buffer));
    } else {
      const size_t k = readed * 8;
      buffer |= ((uint64_t) 1) << k;
      buffer = encrypt_block(buffer);
      a_out.write((char *) (&buffer), sizeof(buffer));
      end = true;
    }
  }
}

void Feistel::output_last_byte( const uint64_t a_block, std::ostream & a_out ) const
{
  assert( a_block != 0 );

  uint32_t end = 7;

  while(is_byte_empty(a_block, end))
    --end;

  if(end > 0)
  {
    a_out.write((char *) (&a_block), end);
  }
}

void Feistel::decrypt( std::istream & a_in, std::ostream & a_out ) const
{
  uint64_t last = 0, buffer = 0;
  bool first = true, end = false;
  while(!end) {
    buffer = 0;
    a_in.read((char *) (&buffer), sizeof(buffer));
    const size_t readed = a_in.gcount();
 
    if(!readed) {
      if(!first) {
        output_last_byte(last, a_out);
      }
      end = true;
    } else if(readed == sizeof(buffer)) {
      if(!first) {
        a_out.write((char *) (&last), sizeof(last));
      }
      last = decrypt_block(buffer);
    } else {
      assert(true);
    }

    first = false;
  }
}
