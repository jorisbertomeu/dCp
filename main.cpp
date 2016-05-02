#include	<File.hpp>

void		tmpCopyCalllback(ssize_t written, ssize_t total_written, void *o, std::string to)
{
  File		*from = reinterpret_cast<File*>(o);
  int		percent = ((int) total_written * 100) / from->getSize();

  printf("\rCopying %d/%d bytes from %s to %s (%d%%)", total_written, from->getSize(), from->getFilename().c_str(), to.c_str(), percent);
  fflush(stdout);
}

int		main(int ac, char *argv[])
{
  File		file;

  if (ac < 3) {
    std::cout << "Usage : dcp [-frsdv] <target> <dest>" << std::endl;
    return -1;
  }
  try {
    file.from(std::string(argv[1]));
    file.copyTo(argv[2], tmpCopyCalllback);
    // file.debug();
  } catch (const std::exception &e) {
    std::cout << "Error caught : " << e.what() << std::endl;
  }
}
