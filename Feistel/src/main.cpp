#include <iostream>
#include <boost/program_options.hpp>
#include "generator.hpp"

int main(int argc, char ** argv)
{
  namespace po = boost::program_options;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("encrypt,e", "encrypt mode")
    ("decrypt,d", "decrypt mode")
    ("generate,g", "generate random key")
    ("seed,s", po::value < uint32_t > (), "set seed for key generation")
    ("key,k", po::value < std::string > (), "key file")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    

  if (vm.count("help"))
  {
    std::cerr << desc << std::endl;
    return 1;
  }

  bool encrypt_mode = vm.count("encrypt"),
       decrypt_mode = vm.count("decrypt"),
       generate_mode = vm.count("generate");

  int total_modes = encrypt_mode + decrypt_mode + generate_mode;

  if(total_modes == 0)
  {
    std::cerr << "Select work mode" << std::endl;
    return 1;
  } else if(total_modes != 1) {
    std::cerr << "Ambiguous work mode" << std::endl;
    return 1;
  }

  if(generate_mode) {
    if( !vm.count("seed") ) {
      std::cerr << "Set seed for key generation" << std::endl;
      return 1;
    }

    const uint32_t seed = vm["seed"].as < uint32_t >();
    Generator gen(seed);
    const Key k = gen();

    std::cout << k << std::endl;
  } else if(decrypt_mode) {
  } else if(encrypt_mode) {
  } else {
    assert(true);
  }

  return 0;
}
