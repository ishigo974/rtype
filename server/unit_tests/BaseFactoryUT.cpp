#include <vector>
#include <iostream>
#include <string>
#include "BaseFactory.hpp"
#include "BaseFactoryUT.hpp"

namespace Utils
{
    /*
    ** Constructor/Destructor
    */
    BaseFactoryUT::BaseFactoryUT()
    {
    }

    BaseFactoryUT::~BaseFactoryUT()
    {
    }

    /*
    ** Public member functions
    */
    void            BaseFactoryUT::registerTests()
    {
        registerTest("LearnType", &BaseFactoryUT::learnType);
        registerTest("UnlearnType", &BaseFactoryUT::unlearnType);
        registerTest("GenerateType", &BaseFactoryUT::generateType);
        registerTest("Errors", &BaseFactoryUT::errors);
    }

    std::string     BaseFactoryUT::getName() const
    {
        return "BaseFactory";
    }

    /*
    ** Unit tests
    */
    void            BaseFactoryUT::learnType()
    {
        BaseFactory<IClonable>& factory = BaseFactory<IClonable>::getInstance();

        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable1>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable2>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable3>()) == true);
        UT_ASSERT(factory.getType("Clonable1") != nullptr);
        UT_ASSERT(factory.getType("Clonable2") != nullptr);
        UT_ASSERT(factory.getType("Clonable3") != nullptr);
        factory.clear();
    }

    void            BaseFactoryUT::unlearnType()
    {
        BaseFactory<IClonable>& factory = BaseFactory<IClonable>::getInstance();

        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable1>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable2>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable3>()) == true);
        UT_ASSERT(factory.getType("Clonable1") != nullptr);
        UT_ASSERT(factory.getType("Clonable2") != nullptr);
        UT_ASSERT(factory.getType("Clonable3") != nullptr);
        UT_ASSERT(factory.unlearn("Clonable1") == true);
        UT_ASSERT(factory.unlearn("Clonable2") == true);
        UT_ASSERT(factory.unlearn("Clonable3") == true);
        UT_ASSERT(factory.getType("Clonable1") == nullptr);
        UT_ASSERT(factory.getType("Clonable2") == nullptr);
        UT_ASSERT(factory.getType("Clonable3") == nullptr);
        factory.clear();
    }

    void            BaseFactoryUT::generateType()
    {
        BaseFactory<IClonable>& factory = BaseFactory<IClonable>::getInstance();
        IClonable*              t;

        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable1>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable2>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable3>()) == true);
        UT_ASSERT((t = factory.generate("Clonable1")) != nullptr);
        UT_ASSERT(t->getName() == "Clonable1");
        UT_ASSERT(t != factory.getType("Clonable1"));
        delete t;
        UT_ASSERT((t = factory.generate("Clonable2")) != nullptr);
        UT_ASSERT(t->getName() == "Clonable2");
        UT_ASSERT(t != factory.getType("Clonable2"));
        delete t;
        UT_ASSERT((t = factory.generate("Clonable3")) != nullptr);
        UT_ASSERT(t->getName() == "Clonable3");
        UT_ASSERT(t != factory.getType("Clonable3"));
        delete t;
        factory.clear();
    }

    void            BaseFactoryUT::errors()
    {
        BaseFactory<IClonable>& factory = BaseFactory<IClonable>::getInstance();

        UT_ASSERT(factory.learn(nullptr) == false);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable1>()) == true);
        UT_ASSERT(factory.learn(std::make_unique<Sample::Clonable1>())
                    == false);
        UT_ASSERT(factory.generate("Clonable2") == nullptr);
        UT_ASSERT(factory.generate("Clonable3") == nullptr);
        UT_ASSERT(factory.getType("Clonable2") == nullptr);
        UT_ASSERT(factory.getType("Clonable3") == nullptr);
        UT_ASSERT(factory.unlearn("Clonable2") == false);
        UT_ASSERT(factory.unlearn("Clonable3") == false);
        factory.clear();
    }

    namespace Sample
    {
        Clonable1::Clonable1() {}
        Clonable1::~Clonable1() {}
        std::string Clonable1::getName() const { return "Clonable1"; }
        IClonable*  Clonable1::clone() { return new Clonable1(); }

        Clonable2::Clonable2() {}
        Clonable2::~Clonable2() {}
        std::string Clonable2::getName() const { return "Clonable2"; }
        IClonable*  Clonable2::clone() { return new Clonable2(); }

        Clonable3::Clonable3() {}
        Clonable3::~Clonable3() {}
        std::string Clonable3::getName() const { return "Clonable3"; }
        IClonable*  Clonable3::clone() { return new Clonable3(); }
    }
}
