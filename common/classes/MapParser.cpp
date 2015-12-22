#include <stdexcept>
#include <sstream>
#include <vector>
#include "MapParser.hpp"

namespace RType
{
    namespace Map
    {
        Parser::Parser(std::string const& path) :
            _path(path), _stream(path)
        {}

        Parser::~Parser()
        {}

        Parser::Map     Parser::parse()
        {
            Map map;

            std::getline(this->_stream, map.first, '\n');
            parseMap(map.second);
            return map;
        }

        void    Parser::parseMap(Content& multipass)
        {
            for (std::string s; std::getline(this->_stream, s, '\n');)
                this->parseLine(multipass, s);
        }

        void    Parser::parseLine(Content& multipass,
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
                tokens.push_back(s);

            if (tokens.size() != 5)
                throw std::runtime_error("Syntax error");
            multipass.emplace(stod(tokens[0]),
                              Element(static_cast<Action>(stoi(tokens[1])),
                              stoi(tokens[2]),
                              stod(tokens[3]), stod(tokens[4])));
        }
    }
}
