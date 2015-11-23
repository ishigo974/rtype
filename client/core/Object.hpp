//
// Created by fourdr_b on 23/11/15.
//

#ifndef RTYPE_OBJECT_HPP
# define RTYPE_OBJECT_HPP

# include <string>

class Object
{
    virtual std::string const& toString()
    {
        return "Object { }";
    };
};

#endif //RTYPE_OBJECT_HPP
