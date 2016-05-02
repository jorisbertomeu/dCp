#include	<File.hpp>

void		tmpCopyCalllback(ssize_t written, void *o, std::string to)
{
  File		*from = reinterpret_cast<File*>(o);
  
  std::cout << "Copy " << written << " bytes from " << from->getFilename() << " to " << to << std::endl;
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
    file.debug();
  } catch (const std::exception &e) {
    std::cout << "Error caught : " << e.what() << std::endl;
  }
}
