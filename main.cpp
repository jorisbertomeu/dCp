#include	<File.hpp>
#include	<iostream>

int		main(int ac, char *argv[])
{
  File		file;

  if (ac < 2) {
    std::cout << "Usage : dcp [-frsdv] <target> <dest>" << std::endl;
    return -1;
  }
  file.from("toto");
}
