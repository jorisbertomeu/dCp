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
  std::string		destination;
  
  try {
    idxUnknown = p.parse(ac, argv);
    for (std::vector<int>::iterator it = idxUnknown.begin(); it != idxUnknown.end(); ++it) {
      if (std::distance(idxUnknown.begin(), it) == (idxUnknown.size() - 1))
	destination = std::string(argv[*it]);
      else {
	fileList.push_back(new File(std::string(argv[*it])));	
      }
    }
    for (std::vector<File*>::iterator it = fileList.begin(); it != fileList.end(); ++it) {
      (*it)->copyTo(destination, tmpCopyCalllback);
    }
    // file.from(std::string(argv[1]));
    // file.copyTo(argv[2], tmpCopyCalllback);
    // file.debug();
  } catch (const std::exception &e) {
    std::cout << "Error caught : " << e.what() << std::endl;
  }
}
