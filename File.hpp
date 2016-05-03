#ifndef		_FILE_HPP_
# define	_FILE_HPP_

# include	<iostream>
# include	<string>
# include	<fstream>
# include	<stdexcept>

# include	<fcntl.h>
# include	<unistd.h>
# include	<errno.h>
# include	<sys/stat.h>

class		File
{
private:
  std::string	_filename;
  long		_filesize;

  /* Constructor - Destructor */
public:
  explicit	File() {
    this->_filesize = -1;
  };

  explicit	File(const std::string &str) {
    this->_filesize = -1;
    this->from(str);
  };
  
  virtual	~File() {

  };

  /* Common publics methods */
public:
  void		from(const std::string &str) {
    this->_filename = str;
    std::ifstream in(str.c_str(), std::ifstream::ate | std::ifstream::binary);
    if ((this->_filesize = (long) (in.tellg())) <= -1)
      throw std::logic_error(std::string("File " + str + " not found"));
  };

  void		debug() const {
    std::cout << "DEBUG" << std::endl << std::endl;
    std::cout << "Filename : " << this->_filename << std::endl;
    std::cout << "File size : " << this->_filesize << std::endl;
  };

  void		copyTo(std::string str, void (*ptrf)(ssize_t, ssize_t, void *, std::string)) {
    int		fd_to, fd_from;
    char	buf[4096];
    ssize_t	nread, total_written = 0;
    int		saved_errno;
    struct stat s;
    
    fd_from = open(this->_filename.c_str(), O_RDONLY);
    if (fd_from < 0)
      throw std::logic_error("Error while opening target file");

    if (stat(str.c_str(), &s) == 0) //Check for dest
      {
	if ( s.st_mode & S_IFDIR) { //ITS DIR
	  if (str.c_str()[str.size() - 1] == '/')
	    str += this->_filename;
	  else
	    str += "/" + this->_filename;
	} else if (s.st_mode & S_IFREG) { //ITS FILE
	  
	} else { //ITS OTHER
	  
	}
      } else { //DOES NOT EXIST
      
    }
    fd_to = open(str.c_str(), O_WRONLY | O_CREAT, 0666);
    if (fd_to < 0)
      throw std::logic_error(std::string("Error while opening destination file \"" + str + "\""));

    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
      {
	char *out_ptr = buf;
	ssize_t nwritten;

	do {
	  nwritten = write(fd_to, out_ptr, nread);
	  total_written += nwritten;
	  ptrf(nwritten, total_written, this, str);
	  if (nwritten >= 0)
	    {
	      nread -= nwritten;
	      out_ptr += nwritten;
	    }
	  else if (errno != EINTR)
	    {
	      close(fd_from);
	      if (fd_to >= 0)
		close(fd_to);
	    }
	} while (nread > 0);
      }
    
    if (nread == 0)
      {
	if (close(fd_to) < 0)
	  {
	    fd_to = -1;
	    close(fd_from);
	    if (fd_to >= 0)
	      close(fd_to);
	  }
	close(fd_from);
	printf("\n");
	return;
      }
    close(fd_from);
    if (fd_to >= 0)
      close(fd_to);
    throw std::logic_error("Unknown error");
  };

  /* Getters - Setters */
public:
  std::string	getFilename() const {
    return this->_filename;
  };

  long		getSize() const {
    return this->_filesize;
  };
};

#endif		/* _FILE_HPP_ */
