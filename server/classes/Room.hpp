#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <string>
# include <vector>

namespace RType
{
    class Room
    {
    public:
        Room();
        virtual ~Room();

    public:
        Room(Room const& other);
        Room&           operator=(Room const& other);

    public:
        unsigned int    getId() const;
        std::string     getName() const;
        unsigned int    getNbPlayers() const;

    public:
        void            setId(unsigned int id);
        void            setName(std::string const& name);
        void            setNbPlayers(unsigned int nbPlayers);

    protected:
        unsigned int    _id;
        std::string     _name;
        unsigned int    _nbPlayers;
    };

    typedef std::vector<RType::Room>    RoomsCollection;
}


#endif /* !ROOM_HPP_ */
