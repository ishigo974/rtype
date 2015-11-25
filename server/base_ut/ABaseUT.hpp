#ifndef ABASEUT_HPP_
# define ABASEUT_HPP_

# include <string>
# include <map>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
# define __STRING(res)    #res
#endif

# define UT_ASSERT(res) (ABaseUT::assert(res, __FILE__, __LINE__, __STRING(res)))

namespace UnitTesting
{
  class ABaseUT
  {
  public:
    typedef void    (*TestHandler)(void);

  public:
    ABaseUT();
    virtual ~ABaseUT();

  private:
    ABaseUT(ABaseUT const& other) = delete;
    ABaseUT&            operator=(ABaseUT const& other) = delete;

  public:
    void                run();
    void                run(std::string const& name);

  public:
    virtual std::string getName() const = 0;

  protected:
    virtual void        registerTests() = 0;
    void                registerTest(std::string const& name, TestHandler th);

  protected:
    static void         assert(bool res, std::string const& file,
                               unsigned int line, std::string const& expr);

  protected:
    static std::string    colorRed;
    static std::string    colorGreen;
    static std::string    colorBase;

  protected:
    bool                                  _isInit;
    std::map<std::string, TestHandler>    _tests;
  };
}

#endif /* !ABASEUT_HPP_ */
