#include	<File.hpp>

int		main(int ac, char *argv[])
{
  File		file;

  if (ac < 3) {
    std::cout << "Usage : dcp [-frsdv] <target> <dest>" << std::endl;
    return -1;
  }
  try {
    file.from(std::string(argv[1]));
    file.copyTo(argv[2]);
    file.debug();
  } catch (const std::exception &e) {
    std::cout << "Error caught : " << e.what() << std::endl;
  }
}
