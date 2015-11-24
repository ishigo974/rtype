//
// Created by fourdr_b on 23/11/15.
//

#ifndef RTYPE_OBJECT_HPP
# define RTYPE_OBJECT_HPP

# include <string>
# include <sstream>

class Object
{
public:
    Object();
    Object(uint _id, std::string const& _name);

    Object(Object const& other);
    Object(Object&& other);
    Object& operator=(Object other);

    virtual ~Object()
    { };

    virtual bool operator==(Object const& other);
    virtual bool operator!=(Object const& other);

    uint getId() const;
    void setId(uint _id);

    std::string const& getName() const;
    void setName(std::string const& _name);

    virtual std::string const& toString();

    friend void swap(Object& first, Object& second);

protected:
    uint        _id;
    std::string _name;
    std::string _toString;
};

#endif //RTYPE_OBJECT_HPP
