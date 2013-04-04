#include <vector>
#include "generator.hpp"
#include "constants.hpp"

Generator::Generator( const uint32_t a_seed )
  : m_rand( a_seed )
{
}

Key Generator::operator() ()
{
  std::vector < uint32_t > keys( ROUNDS );

  for(size_t i = 0; i < ROUNDS; i++)
  {
    keys[i] = m_rand();
  }

  return Key( keys );
}
