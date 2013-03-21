#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdint>
#include "key.hpp"
#include "constants.hpp"

namespace
{

uint32_t hex_value( char c )
{
  assert( isxdigit(c) );

  // A-F
  c = tolower(c);

  return isdigit(c) ? (c - '0') : (c - 'a' + 10);
}

uint32_t from_hex( const std::string & a_key )
{
  assert( a_key.size() == HEX_LEN );
  uint32_t res = 0;

  for( size_t i = 0; i < HEX_LEN; i++ )
  {
    assert( isxdigit(a_key[i]) );
    const char c = a_key[i];
    res = (16 * res + hex_value(c));
  }

  return res;
}

std::string to_hex( const uint32_t a_key )
{
  std::stringstream ss;

  ss << std::hex << a_key;

  std::string part = ss.str();

  size_t need_nulls = HEX_LEN - part.size();
  
  return std::string(need_nulls, '0') + part;
}
}

Key::Key()
{
}

Key::Key( const std::vector < uint32_t > & a_keys )
  : m_keys( a_keys.begin(), a_keys.end() )
{
}

Key::Key( const std::string & a_key )
{
  from_string( a_key );
}

bool Key::ready() const
{
  return m_keys.size() == ROUNDS;
}

uint32_t Key::operator [] ( const size_t a_ind ) const
{
  assert( a_ind < m_keys.size() );

  return m_keys[a_ind];
}

void Key::from_string( const std::string & a_key )
{
  assert( a_key.size() == HEX_LEN * ROUNDS );

  m_keys.resize( ROUNDS );

  for(size_t i = 0; i < ROUNDS; i++)
  {
    m_keys[i] = from_hex(a_key.substr(i * HEX_LEN, HEX_LEN));
  }
}

std::string Key::to_string() const
{
  assert( m_keys.size() == ROUNDS );

  std::stringstream res;

  for( size_t i = 0; i < ROUNDS; i++ )
  {
    res << to_hex( m_keys[i] );
  }

  return res.str();
}

std::ostream & operator << ( std::ostream & a_out, const Key & a_key )
{
  a_out << a_key.to_string();
  return a_out;
}

std::istream & operator >> ( std::istream & a_in, Key & a_key )
{
  std::string str;
  a_in >> str;

  a_key.from_string(str);

  return a_in;
}
