#ifndef BASEFACTORY_HPP_
# define BASEFACTORY_HPP_

# include <memory>
# include <unordered_map>
# include <utility>
# include <string>
# include "IClonable.hpp"

/*
** BaseFactory
** Singleton design pattern
** Factory that can learn/unlearn types and then generates them
** Be careful, Type has to be able to use the clone member function /!\
*/
template <typename Type>
class BaseFactory
{
public:
    typedef std::unique_ptr<BaseFactory>        UniqueFactoryPtr;
    typedef std::unique_ptr<Type>               UniqueTypePtr;
    typedef std::unordered_map<std::string,
                                UniqueTypePtr>  TypeBook;
    typedef std::pair<std::string,
                        UniqueTypePtr>          TypeEntry;

protected:
    BaseFactory()
    {}

public:
    virtual ~BaseFactory()
    {}

public:
    static BaseFactory&     getInstance()
    {
        if (instance == nullptr)
            instance = std::unique_ptr<BaseFactory>(new BaseFactory());
        return *instance;
    }

public:
    bool                    learn(UniqueTypePtr type)
    {
        // std::pair<typename TypeBook::iterator, bool>	ret;

        if (type == nullptr)
            return false;
        // ret = _book.insert(std::make_pair(type->getName(), type->clone()));
        return _book.insert(std::make_pair(type->getName(), type->clone()))
                    .second;
        // return ret.second;
    }

    bool                    unlearn(std::string const& name)
    {
        return _book.erase(name) > 0;
    }

    Type*                   generate(std::string const& name) const
    {
        typename TypeBook::const_iterator      it;

        if ((it = _book.find(name)) == _book.end())
            return nullptr;
        return it->second->clone();
    }

    Type const*             getType(std::string const& name) const
    {
        typename TypeBook::const_iterator      it;

        if ((it = _book.find(name)) == _book.end())
            return nullptr;
        return it->second;
    }

protected:
    TypeBook                    _book;
    static UniqueFactoryPtr     _instance;
};

template <typename Type>
std::unique_ptr<BaseFactory<Type> >     BaseFactory<Type>::instance = nullptr;

#endif /* !BASEFACTORY_HPP_ */
