#include	<Dcp.hpp>

void		tmpCopyCallback(ssize_t written, ssize_t total_written, void *o, std::string to)
{
  File		*from = reinterpret_cast<File*>(o);
  unsigned long	percent = ((unsigned long) total_written * 100) / from->getSize();
  static int	ts = time(NULL);
  static long	saved[2] = {written, from->getSize()};
  
  
  if (ts < time(NULL)) {
    ts = time(NULL);
    saved[1] = saved[0];
    saved[0] = 0;
  } else
    saved[0] += written;
  printf("\rCopying %ld/%ld bytes (%s) from %s to %s (%lu%%) - ~%s/s           ", total_written, from->getSize(), Utils::humanReadableByteCount(from->getSize(), true).c_str(), from->getFilename().c_str(), to.c_str(), percent, Utils::humanReadableByteCount(saved[1], true).c_str());
  fflush(stdout);
  //usleep(1000);
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
