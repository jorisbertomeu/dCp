//
// Utils.hpp for  in /home/Dieu/Desktop/Work/BMTech/Linux
// 
// Made by Dieu Dieu
// Login   <Dieu@epitech.net>
// 
// Started on  Mon Jan 18 15:20:12 2016 Dieu Dieu
// Last update Mon Jan 18 15:20:14 2016 Dieu Dieu
//

#ifndef		_UTILS_HPP_
# define	_UTILS_HPP_

# include	<vector>
# include	<string>
# include	<sstream>
# include	<stdexcept>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

class		Utils
{
public:
  static std::list<std::string> *explode(const std::string& str, char sep)
  {
    std::list<std::string>	*tokens = new std::list<std::string>;
    std::istringstream		split(str);
    
    for (std::string each; std::getline(split, each, sep); tokens->push_back(each));
    return (tokens);
  };
};

#endif
