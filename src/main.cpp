#include <iostream>
#include <fstream>
#include <cassert>
#include <boost/program_options.hpp>
#include "des.hpp"

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
    ("key,k", po::value < std::string > (), "64-bit hex key")

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
             decrypt_mode  = vm.count("decrypt");

  const int total_modes = static_cast < int > ( encrypt_mode ) +
                          static_cast < int > ( decrypt_mode );

  if(total_modes == 0) {
    std::cerr << desc;
    return 1;
  } else if(total_modes != 1) {
    std::cerr << desc;
    return 1;
  }

  // check key
  if( !vm.count("key") ) {
    std::cerr << "No key specified" << std::endl;
    return 1;
  }

  // open output file, we always need them
  if( not vm.count("output") ) {
    std::cerr << "No output file specifed" << std::endl;
    return 1;
  }
  
  std::ofstream out( vm["output"].as < std::string > (), std::ios::out | std::ios::binary );
  assert( out );

  // wee need input stream too
  if( not vm.count("input") ) {
    std::cerr << "No input file specifed" << std::endl;
    return 1;
  }

  std::ifstream in(vm["input"].as < std::string > (), std::ios::in | std::ios::binary);
  assert( in );

  const std::string key = vm["key"].as < std::string > ();
  Key k( key );

  const DES f( k );

  if(decrypt_mode) {
    f.decrypt(in, out);
  } else if(encrypt_mode) {
    f.encrypt(in, out);
  } else {
    assert(true);
  }

  return 0;
}
