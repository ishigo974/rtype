#ifndef RCSVPARSER_HPP_
# define RCSVPARSER_HPP_

# include <map>
# include <fstream>
# include <string>
# include "Action.hpp"

class RCSVParser
{
public:
    RCSVParser(std::string const& path);
    ~RCSVParser();

public:
    //TODO Parse
    void    parse(std::multimap<double, Action> &);

private:
    //TODO ParseLine
    void    parseLine(std::multimap<double, Action> &, std::string &);

private:
    std::string     _path;
    std::ifstream   _stream;
};

#endif // !RCSVPARSER_HPP_
