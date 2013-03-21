#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include <cstdint>
#include <boost/random.hpp>
#include "key.hpp"
#include "constants.hpp"

class Generator {
  boost::random::mt19937 m_rand;

  public:
    Generator( const uint32_t a_seed );

    Key operator() () const;
};

#endif