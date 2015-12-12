#ifndef BASEFACTORY_HPP_
# define BASEFACTORY_HPP_

# include <memory>
# include <unordered_map>
# include <utility>
# include <string>
# include <sstream>
# include "IClonable.hpp"
# include "IStringable.hpp"

namespace Utils
{
    /*
    ** BaseFactory
    ** Factory that can learn/unlearn types and then generates them
    ** Be careful, Type has to be able to use the clone member function /!\
    */
    template <typename Type>
    class BaseFactory : public IStringable
    {
    public:
        typedef std::unique_ptr<Type>               UniqueTypePtr;
        typedef std::unordered_map<std::string,
                                    UniqueTypePtr>  TypeBook;
        typedef std::pair<std::string,
                            UniqueTypePtr>          TypeEntry;

    public:
        BaseFactory()
        {}

        virtual ~BaseFactory()
        {}

    public:
        bool                    learn(UniqueTypePtr type)
        {
            if (type == nullptr)
                return false;
            return _book.insert(
                std::make_pair(type->getName(),
                                std::unique_ptr<Type>(type->clone()))).second;
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
            return it->second.get();
        }

        void                    clear()
        {
            _book.clear();
        }

    public:
        virtual std::string     toString() const
        {
            std::ostringstream  ss;

            ss << "BaseFactory {"
                << "\n\ttypes:";
            for (auto& entry: _book)
                ss << "\n\t\t" << entry.first;
            ss << "\n}\n";
            return ss.str();
        }

    protected:
        TypeBook                    _book;
    };
}


#endif /* !BASEFACTORY_HPP_ */
