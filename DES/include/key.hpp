#ifndef __KEY_HPP__
#define __KEY_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

class Key {
  uint64_t m_key;

private:
  void from_string( const std::string & a_key );
  std::string to_string() const;

public:
  Key();
  Key( const uint64_t m_key );
  Key( const std::string & a_key );

  uint64_t operator () () const;

  friend std::ostream & operator << ( std::ostream & a_out, const Key & a_key );
  friend std::istream & operator >> ( std::istream & a_in, Key & a_key );

};

#endif
