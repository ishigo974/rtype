#ifndef ABASEUT_HPP_
# define ABASEUT_HPP_

# include <string>
# include <map>

# define UT_ASSERT(res)   (ABaseUT::assert(res, __FILE__, __LINE__))

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
    ABaseUT&     operator=(ABaseUT const& other) = delete;

  public:
    void                run() const;
    void                run(std::string const& name) const;

  public:
    virtual std::string getName() const = 0;

  protected:
    virtual void        registerTests() = 0;
    void                registerTest(std::string const& name, TestHandler th);

  protected:
    static void         assert(bool res);
    // static void         assertWithFile(std::string const& output,
    //                                    std::string const& file);

  protected:
    static std::string    colorRed;
    static std::string    colorGreen;
    static std::string    colorBase;

  protected:
    std::map<std::string, TestHandler>   _tests;
  };
}

#endif /* !ABASEUT_HPP_ */
