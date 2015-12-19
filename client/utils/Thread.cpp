//
// Thread.cpp for Plazza in /home/fourdr_b/rendu/cpp_plazza
// 
// Made by fourdr_b
// Login   <fourdr_b@epitech.net>
// 
// Started on  Wed Jul  1 13:08:06 2015 fourdr_b
// Last update Wed Jul  1 13:08:08 2015 fourdr_b
//

#include "Thread.hpp"

void Thread::Start()
{
	pthread_create(&_th, NULL, _entry, _arg);
	_state = RUNNING;
}

void Thread::Join()
{
	pthread_join(_th, NULL);
	_state = IDLE;
}

void Thread::Init( Thread::func entry, void *arg )
{
	_entry = entry;
	_arg = arg;
	_state = INITIALIZED;
}

void Thread::Detach()
{
	pthread_detach(_th);
}
