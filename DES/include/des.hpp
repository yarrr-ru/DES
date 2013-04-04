#ifndef __DES_HPP__
#define __DES_HPP__

#include <iostream>
#include "key.hpp"
#include "constants.hpp"

class DES {
  uint64_t m_keys[ROUNDS];

  private:
    uint64_t start_permutation ( const uint64_t a_block ) const;
    uint64_t end_permutation ( const uint64_t a_block ) const;

    uint32_t f( const uint32_t a_part, const uint32_t a_round ) const;
    uint64_t encrypt_block( const uint64_t a_block ) const;
    uint64_t decrypt_block( const uint64_t a_block ) const;
    void output_last_byte( const uint64_t a_block, std::ostream & a_out ) const;

  public:
    DES( const Key & a_key );
    void encrypt( std::istream & a_in, std::ostream & a_out ) const;
    void decrypt( std::istream & a_in, std::ostream & a_out ) const;
};

#endif
