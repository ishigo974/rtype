#ifndef BASEFACTORYUT_HPP_
# define BASEFACTORYUT_HPP_

# include <string>
# include "ABaseUT.hpp"
# include "IClonable.hpp"

namespace Utils
{
    class BaseFactoryUT : public UnitTesting::ABaseUT
    {
    public:
        BaseFactoryUT();
        virtual ~BaseFactoryUT();

    private:
        BaseFactoryUT(BaseFactoryUT const& other) = delete;
        BaseFactoryUT&          operator=(BaseFactoryUT const& other) = delete;

    protected:
        static void             learnType();
        static void             unlearnType();
        static void             generateType();
        static void             errors();

    public:
        virtual void            registerTests();
        virtual std::string     getName() const;
    };

    namespace Sample
    {
        class Clonable1 : public IClonable
        {
        public:
            Clonable1();
            virtual ~Clonable1();

        public:
            virtual std::string getName() const;
            virtual IClonable*  clone();
        };

        class Clonable2 : public IClonable
        {
        public:
            Clonable2();
            virtual ~Clonable2();

        public:
            virtual std::string getName() const;
            virtual IClonable*  clone();
        };

        class Clonable3 : public IClonable
        {
        public:
            Clonable3();
            virtual ~Clonable3();

        public:
            virtual std::string getName() const;
            virtual IClonable*  clone();
        };
    }
}

#endif /* !BASEFACTORYUT_HPP_ */
