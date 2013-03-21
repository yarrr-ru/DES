#include <sstream>
#include <cassert>
#include <cstring>
#include <boost/lexical_cast.hpp>
#include "key.hpp"
#include "constants.hpp"

Key::Key()
{
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

uint32_t Key::hex_value( const char c )
{
  assert( isxdigit(c) );

  return isdigit(c) ? (c - '0') : (c - 'a' + 10);
}

uint32_t Key::from_hex( const std::string & a_key )
{
  assert( a_key.size() == 8 );
  uint32_t res = 0;

  for( size_t i = 0; i < 8; i++ )
  {
    assert( isxdigit(a_key[i]) );
    const char c = a_key[i];
    res = (16 * res + hex_value(c));
  }

  return res;
}

std::string Key::to_hex( const uint32_t a_key )
{
  std::stringstream ss;

  ss << std::hex << a_key;

  std::string part = ss.str();

  size_t need_nulls = 8 - part.size();
  
  return std::string(need_nulls, '0') + part;
}

void Key::from_string( const std::string & a_key )
{
  assert( a_key.size() == 8 * ROUNDS );

  m_keys.resize( ROUNDS );

  for(size_t i = 0; i < ROUNDS; i++)
  {
    m_keys[i] = from_hex(a_key.substr(i * 8, 8));
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
