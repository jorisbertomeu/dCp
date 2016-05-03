#include	<File.hpp>
#include	<Parameters.hpp>

void		tmpCopyCalllback(ssize_t written, ssize_t total_written, void *o, std::string to)
{
  File		*from = reinterpret_cast<File*>(o);
  unsigned int	percent = ((unsigned int) total_written * 100) / from->getSize();

  printf("\rCopying %d/%d bytes from %s to %s (%d%%)", total_written, from->getSize(), from->getFilename().c_str(), to.c_str(), percent);
  fflush(stdout);
}

int			main(int ac, char *argv[])
{
  File			file;
  Parameters		p;
  std::vector<int>	idxUnknown;
  std::vector<File*>	fileList;
  std::string		destination = "";
  struct stat		s;
  
  try {
    idxUnknown = p.parse(ac, argv);
    for (std::vector<int>::iterator it = idxUnknown.begin(); it != idxUnknown.end(); ++it) {
      if (std::distance(idxUnknown.begin(), it) == (idxUnknown.size() - 1))
	destination = std::string(argv[*it]);
      else {
	if (stat(argv[*it], &s) == 0)
	  {
	    if ( s.st_mode & S_IFDIR) {
	      std::cout << "Omitting directory \"" << std::string(argv[*it]) << "\"" << std::endl;
	    } else if (s.st_mode & S_IFREG) { //ITS FILE
	      fileList.push_back(new File(std::string(argv[*it])));	
	    } else { //ITS OTHER
	      
	    }
	  } else { //DOES NOT EXIST
	  std::cout << "File \"" << std::string(argv[*it]) << "\" does not exist" << std::endl;
	}
      }
    }
    if (fileList.size() == 0)
      p.showUsage();
    for (std::vector<File*>::iterator it = fileList.begin(); it != fileList.end(); ++it) {
      try {
	(*it)->copyTo(destination, tmpCopyCalllback);
      } catch (const std::exception &e) {
	std::cout << "Error while copying \"" << (*it)->getFilename() << "\"" << std::endl;
      }
    }
  } catch (const std::exception &e) {
    std::cout << "Error caught : " << e.what() << std::endl;
  }
}
