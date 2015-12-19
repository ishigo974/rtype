//
// Thread.hpp for Plazza in /home/fourdr_b/rendu/cpp_plazza
// 
// Made by fourdr_b
// Login   <fourdr_b@epitech.net>
// 
// Started on  Wed Jul  1 13:11:59 2015 fourdr_b
// Last update Wed Jul  1 13:12:00 2015 fourdr_b
//

#ifndef THREAD_H
# define THREAD_H

#include <pthread.h>

class Thread
{
	typedef	void *(*func)(void *);
public:
	enum ThreadState
	{
		INITIALIZED,
		RUNNING,
		IDLE
	};

	Thread()
	{ }

	virtual void        Init(func entry, void *arg);
	virtual void		Start();
	virtual void		Join();
	virtual void        Detach();
	virtual ThreadState	getState() const { return (_state); }

protected:
	func		_entry;
	ThreadState	_state;
	pthread_t	_th;
	void		*_arg;
};

#endif /* THREAD_H */
