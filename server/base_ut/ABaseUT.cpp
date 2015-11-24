#include "ABaseUT.hpp"

namespace UnitTesting
{
  /*
  ** Constructor/Destructor
  */
  ABaseUT::ABaseUT()
  {
  }

  ABaseUT::~ABaseUT()
  {
  }

  /*
  ** Public member functions
  */
  void                ABaseUT::run() const
  {
  }

  void                ABaseUT::run(std::string const& name) const
  {
    auto it = _tests.find(name);

    if (it == _tests.end())
      throw std::runtime_error("lol"); // todo
    try {
      (*it->second)();
    } catch (Exception::AssertError const& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  /*
  ** Protected member functions
  */
  void                ABaseUT::registerTest(std::string const& name, TestHandler th)
  {
  }

  /*
  ** Static functions
  */
  static void         ABaseUT::assert(bool res, std::string const& file,
                                      unsigned int line)
  {
    if (!res)
      throw Exception::AssertError(file + ":" + std::to_string(line) +
                                   ": assertion failed");
  }
}
