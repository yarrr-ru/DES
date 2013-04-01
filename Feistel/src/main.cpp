#include <iostream>
#include <fstream>
#include <cassert>
#include <boost/program_options.hpp>
#include "generator.hpp"
#include "feistel.hpp"

int main(int argc, char ** argv)
{
  // speed up cpp streams
  std::ios_base::sync_with_stdio( false );

  namespace po = boost::program_options;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("encrypt,e", "encrypt mode")
    ("decrypt,d", "decrypt mode")
    ("generate,g", "generate random key")
    ("seed,s", po::value < uint32_t > (), "set seed for key generation")
    ("key,k", po::value < std::string > (), "key file")

    // we use files, cause cin/cout too slow for us :(
    ("input,i", po::value < std::string > (), "input file")
    ("output,o", po::value < std::string > (), "output file")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    

  if (vm.count("help")) {
    std::cerr << desc;
    return 1;
  }

  const bool encrypt_mode  = vm.count("encrypt"),
             decrypt_mode  = vm.count("decrypt"),
             generate_mode = vm.count("generate");

  const int total_modes = static_cast < int > ( encrypt_mode ) +
                          static_cast < int > ( decrypt_mode ) +
                          static_cast < int > ( generate_mode );

  if(total_modes == 0) {
    std::cerr << desc;
    return 1;
  } else if(total_modes != 1) {
    std::cerr << desc;
    return 1;
  }

  // open output file, we always need them
  if( not vm.count("output") ) {
    std::cerr << "No output file specifed" << std::endl;
    return 1;
  }
  
  std::ofstream out( vm["output"].as < std::string > (), std::ios::out | std::ios::binary );
  assert( out );

  if(generate_mode) {
    if( not vm.count("seed") ) {
      std::cerr << "Set seed for key generation" << std::endl;
      return 1;
    }

    const uint32_t seed = vm["seed"].as < uint32_t >();
    Generator gen(seed);
    const Key k = gen();

    out << k << std::endl;
    return 0;
  }

  // wee need input stream too
  if( not vm.count("input") ) {
    std::cerr << "No input file specifed" << std::endl;
    return 1;
  }

  std::ifstream in(vm["input"].as < std::string > (), std::ios::in | std::ios::binary);
  assert( in );

  // open key file
  if( !vm.count("key") ) {
    std::cerr << "No keyfile specified" << std::endl;
    return 1;
  }

  std::ifstream key_file(vm["key"].as < std::string > (), std::ios::in | std::ios::binary);
  assert( key_file );

  Key k;
  key_file >> k;
  key_file.close();

  assert( k.ready() );

  const Feistel f( k );

  if(decrypt_mode) {
    f.decrypt(in, out);
  } else if(encrypt_mode) {
    f.encrypt(in, out);
  } else {
    assert(true);
  }

  return 0;
}
