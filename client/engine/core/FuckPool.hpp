#ifndef OBJECTPOOL_HPP_
# define OBJECTPOOL_HPP_

namespace cu
{
    template <typename T>
    class	ObjectPool : Object
    {
    public:
        ObjectPool() {}
        virtual ~ObjectPool() {}

        void	create()
        {
            for (int i = 0; i < _size; ++i)
            {
                _objects[i]->obj->init();
                return ;
            }
        }

        struct	s_obj
        {
            T       *obj;
            bool    inUse;
        };

    private:
        ObjectPool::s_obj	*_objects[40];
        static const int	_size = 40;
    };
}

#endif /* !OBJECTPOOL_HPP_ */
