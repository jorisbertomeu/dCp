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
# include	<list>
# include	<math.h>

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

  static std::string			getFilename(const std::string& s) {
    char sep = '/';
#ifdef _WIN32
    sep = '\\';
#endif

    size_t i = s.rfind(sep, s.length());
    if (i != std::string::npos) {
      return(s.substr(i + 1, s.length() - i));
    }
    return("");
  };

  static std::string humanReadableByteCount(long bytes, bool si) {
    char pre[3];
    int unit = si ? 1000 : 1024;
    if (bytes < unit) return std::string(std::to_string(bytes) + " B");
    int exp = (int) (log(bytes) / log(unit));
    pre[0] = (si ? "kMGTPE" : "KMGTPE")[exp-1];
    pre[1] = (si ? '\0' : 'i');
    pre[2] = 0;
    return std::string(std::to_string((bytes / pow(unit, exp))) + " " + pre + "B");
  };
};

#endif
