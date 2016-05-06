#include	<Dcp.hpp>

void		tmpCopyCallback(ssize_t written, ssize_t total_written, void *o, std::string to)
{
  File		*from = reinterpret_cast<File*>(o);
  unsigned int	percent = ((unsigned int) total_written * 100) / from->getSize();

  printf("\rCopying %ld/%ld bytes from %s to %s (%d%%)", total_written, from->getSize(), from->getFilename().c_str(), to.c_str(), percent);
  fflush(stdout);
}

int			main(int ac, char *argv[])
{
  File			file;
  Parameters		p;
  Dcp			app;
  
  try {
    app.init(p.parse(ac, argv), ac, argv, tmpCopyCallback);
    app.run(p);
  } catch (const std::exception &e) {
    std::cout << "Error caught : " << e.what() << std::endl;
  }
}
