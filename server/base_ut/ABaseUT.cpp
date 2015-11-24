#include <iostream>
#include <stdexcept>
#include "ABaseUT.hpp"
#include "AssertError.hpp"
#include "ValueError.hpp"

namespace UnitTesting
{
  /*
  ** Static variables
  */
  std::string          ABaseUT::colorRed    = "\033[1;31m";
  std::string          ABaseUT::colorGreen  = "\033[1;32m";
  std::string          ABaseUT::colorBase   = "\033[m";

  /*
  ** Constructor/Destructor
  */
  ABaseUT::ABaseUT() : _isInit(false)
  {
  }

  ABaseUT::~ABaseUT()
  {
  }

  /*
  ** Public member functions
  */
  void                ABaseUT::run()
  {
    if (!_isInit)
    {
      registerTests();
      _isInit = true;
    }
    std::cout << "| Running " << getName() << " unit tests" << std::endl;
    for (auto&& test: _tests)
    {
      try {
        std::cout << "Running test " + test.first + ": ";
        (*test.second)();
        std::cout << colorGreen << "OK" << colorBase << std::endl;
      } catch (Exception::AssertError const& e) {
        std::cout << colorRed << "KO" << colorBase << std::endl;
        std::cerr << e.what() << std::endl;
      } catch (std::exception const& e) {
        std::cout << colorRed << "KO" << colorBase << std::endl;
        std::cerr << "Exception caught: " << e.what() << std::endl;
      }
    }
  }

  void                ABaseUT::run(std::string const& name)
  {
    if (!_isInit)
    {
      registerTests();
      _isInit = true;
    }
    auto it = _tests.find(name);

    if (it == _tests.end())
      throw Exception::ValueError("Test '" + name + "' does not exists'");
    try {
      std::cout << "Running test " + it->first + ": ";
      (*it->second)();
      std::cout << colorGreen << "OK" << colorBase << std::endl;
    } catch (Exception::AssertError const& e) {
      std::cout << colorRed << "KO" << colorBase << std::endl;
      std::cerr << e.what() << std::endl;
    }
  }

  /*
  ** Protected member functions
  */
  void                ABaseUT::registerTest(std::string const& name,
                                            TestHandler th)
  {
    _tests[name] = th;
  }

  /*
  ** Static functions
  */
  void                ABaseUT::assert(bool res, std::string const& file,
                                      unsigned int line,
                                      std::string const& expr)
  {
    if (!res)
      throw Exception::AssertError(file + ":" + std::to_string(line) +
                                   ": assertion " + expr + " failed");
  }
}
