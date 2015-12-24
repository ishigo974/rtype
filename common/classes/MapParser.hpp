#ifndef RCSVPARSER_HPP_
# define RCSVPARSER_HPP_

# include <map>
# include <fstream>
# include <string>

namespace RType
{
    namespace Map
    {
        class Parser
        {
        public:
            enum Action
            {
                SPAWN = 0
            };

        public:
            struct Element
            {
                Element(Action _action, unsigned int _id,
                     unsigned int _x, unsigned int _y) :
                    action(_action), id(_id), x(_x), y(_y)
                {}

                Action          action;
                unsigned int    id;
                unsigned int    x;
                unsigned int    y;

                std::string     toString() const
                {
                    return  "MapElement {"
                            "\n\taction: " + std::to_string(action) +
                            "\n\tid: " + std::to_string(id) +
                            "\n\tx: " + std::to_string(x) +
                            "\n\ty: " + std::to_string(y) +
                            "\n}\n";
                }
            };

        public:
            typedef std::multimap<double, Element>      Content;
            typedef std::pair<std::string, Content>     Map;

        public:
            Parser(std::string const& path);
            ~Parser();

        public:
            Map     parse();

        private:
            void    parseMap(Content&);
            void    parseLine(Content&, std::string&);

        private:
            std::string     _path;
            std::ifstream   _stream;
        };

        typedef std::vector<Parser::Map>    Collection;
    }
}

#endif // !RCSVPARSER_HPP_
