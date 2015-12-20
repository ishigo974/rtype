#include <stdexcept>
#include <sstream>
#include <vector>
#include "RCSVParser.hpp"

RCSVParser::RCSVParser(std::string const& path) :
    _path(path), _stream(path)
{}

RCSVParser::~RCSVParser()
{}

void    RCSVParser::parse(std::multimap<double, Action> &multipass)
{
    for (std::string s; std::getline(this->_stream, s, '\n');)
    {
        this->parseLine(multipass, s);
    }
}

void    RCSVParser::parseLine(std::multimap<double, Action> &multipass,
                              std::string& line)
{
    std::stringstream           ss;
    std::vector<std::string>    tokens(0);

    if (line.find_first_of('#') != std::string::npos)
        line = line.substr(0, line.find_first_of('#'));
    if (!line.size())
        return ;
    ss.str(line);

    for (std::string s; std::getline(ss, s, ';');)
    {
        tokens.push_back(s);
    }

    if (tokens.size() != 6)
        throw std::runtime_error("Syntax Error : " + this->_path);

    multipass.emplace(stod(tokens[0]),
                      Action(static_cast<ActionType>(stoi(tokens[1])),
                      static_cast<MobType>(stoi(tokens[2])),
                      static_cast<MovementType>(stoi(tokens[3])),
                      cu::Position(stod(tokens[4]), stod(tokens[5]))));
}
