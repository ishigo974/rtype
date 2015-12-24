#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

# include <string>
# include <deque>
# include <iostream>

# ifdef WIN32
#  include <windows.h>
#  include <tchar.h>

template <typename T>
class DLLoader
{
public:
  static T getInstanceOf(std::string const& path, std::string const& entry)
  {
    T           (*ext_creator)();
    HMODULE     dlhandle;
	LPCSTR		lpcstr;

	lpcstr = static_cast<LPCSTR>(path.c_str());
    dlhandle = LoadLibrary(_T(path.c_str()));
	if (dlhandle == NULL)
	{
		std::cerr << GetLastError() << " " << path << std::endl;
		throw std::runtime_error("Could not find handle " + path);
	}
    ext_creator = reinterpret_cast<T ( * )()>(GetProcAddress(dlhandle, entry.c_str()));
    _handles.push_back(dlhandle);
    if ( ext_creator == NULL )
    {
      FreeLibrary( dlhandle );
	  std::cerr << "Error code : " << GetLastError() << std::endl
		  << "path: " << path << std::endl
		  << "entry: " << entry << std::endl;
      throw std::runtime_error( "Could not find creator function." );
    }
    return (ext_creator());
  }

  static void CleanHandles()
  {
    for ( std::deque<void *>::iterator it = _handles.begin(); it != _handles.end(); it++ )
      FreeLibrary(static_cast<HMODULE>(*it));
  }

private:
  static std::deque<void *> _handles;
};

# else
#  include <dlfcn.h>

template <typename T>
class DLLoader
{
public:
  static T getInstanceOf(std::string const& path, std::string const& entry)
  {
    T           (*ext_creator)();
    void        *dlhandle;

    dlhandle = dlopen( path.c_str(), RTLD_LAZY );
    if ( dlhandle == NULL )
        throw std::runtime_error( "Could not find handle " + path );

    ext_creator = reinterpret_cast<T ( * )()>(dlsym( dlhandle, entry.c_str()));
    _handles.push_back( dlhandle );

    if ( ext_creator == NULL )
    {
        dlclose( dlhandle );
        throw std::runtime_error( "Could not find creator function." );
    }
    return (ext_creator());
  }

  static void cleanHandles()
  {
    for ( std::deque<void *>::iterator it = _handles.begin(); it != _handles.end(); it++ )
        dlclose((*it));
  }

private:
  static std::deque<void *> _handles;
};

# endif /* !WIN32 */

template <typename T>
std::deque<void *>  DLLoader<T>::_handles;

#endif /* !DLLOADER_HPP_ */
