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

uint64_t from_hex( const std::string & a_key )
{
  assert( a_key.size() == KEY_LEN );

  uint64_t res = 0;

  for( size_t i = 0; i < KEY_LEN; i++ )
  {
    const char c = a_key[i];
    assert( isxdigit(c) );
    res = (16 * res + hex_value(c));
  }

  return res;
}

std::string to_hex( const uint64_t a_key )
{
  std::stringstream ss;

  ss << std::hex << a_key;

  std::string part = ss.str();

  size_t need_nulls = KEY_LEN - part.size();
  
  return std::string(need_nulls, '0') + part;
}
}

Key::Key()
{
}

Key::Key( const uint64_t a_key )
  : m_key( a_key )
{
}

Key::Key( const std::string & a_key )
{
  from_string( a_key );
}

uint64_t Key::operator () () const
{
  return m_key;
}


void Key::from_string( const std::string & a_key )
{
  assert( a_key.size() == KEY_LEN );

  m_key = from_hex( a_key );
}

std::string Key::to_string() const
{
  std::stringstream res;

  res << to_hex( m_key );

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
