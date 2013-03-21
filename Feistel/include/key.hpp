#ifndef __KEY_HP__
#define __KEY_HP__

#include <iostream>
#include <vector>
#include <string>

class Key {
  std::vector < uint32_t > m_keys;

private:
  static uint32_t hex_value( const char c );
  static uint32_t from_hex( const std::string & a_key );
  static std::string to_hex( const uint32_t a_key );

  void from_string( const std::string & a_key );
  std::string to_string() const;

public:
  Key();
  Key( const std::vector < uint32_t > & a_keys );
  Key( const std::string & a_key );

  bool ready() const;
  uint32_t operator [] ( const size_t a_ind ) const;

  friend std::ostream & operator << ( std::ostream & a_out, const Key & a_key );
  friend std::istream & operator >> ( std::istream & a_in, Key & a_key );

};

#endif
