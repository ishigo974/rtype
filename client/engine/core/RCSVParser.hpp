#ifndef RCSVPARSER_HPP_
# define RCSVPARSER_HPP_

# include <map>
# include <fstream>
# include <string>
# include "Spawn.hpp"

class RCSVParser
{
public:
    RCSVParser(std::string const& path);
    ~RCSVParser();

public:
    //TODO Parse
    void    parse(std::multimap<double, Spawn> &);

private:
    //TODO ParseLine
    void    parseLine(std::multimap<double, Spawn> &, std::string &);

private:
    std::string     _path;
    std::ifstream   _stream;
};

#endif // !RCSVPARSER_HPP_
