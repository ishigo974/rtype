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
    Object(unsigned int _id, std::string const& _name);

    Object(Object const& other);
    Object(Object&& other);
    Object& operator=(Object other);

    virtual ~Object()
    { };

    virtual bool operator==(Object const& other);
    virtual bool operator!=(Object const& other);

    virtual unsigned int getMask();

    unsigned int getId() const;
    void         setId(unsigned int _id);

    std::string const& getName() const;
    void setName(std::string const& _name);

    virtual std::string toString();


protected:
    void swap(Object& first, Object& second);

protected:
    unsigned int _id;
    std::string  _name;
};

#endif //RTYPE_OBJECT_HPP
