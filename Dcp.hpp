#ifndef		__DCP_HPP__
# define	__DCP_HPP__

# include	<File.hpp>
# include	<Parameters.hpp>

class		Dcp
{
private:
  /* Common attributes */
  std::vector<int>	_idxUnknown;
  std::vector<File*>	_fileList;
  std::string		_destination;
  /* Functors */
  void (*_simpleCopyCallback)(ssize_t, ssize_t, void *, std::string);
  
public:
  explicit	Dcp() {

  };

  virtual	~Dcp() {

  };

public:
  void		init(std::vector<int> idxUnknown, int ac, char **argv,
		     void (*simpleCopyCallback)(ssize_t, ssize_t, void *, std::string)) {
    struct stat		s;

    this->_idxUnknown = idxUnknown;
    this->_simpleCopyCallback = simpleCopyCallback;
    
    for (std::vector<int>::iterator it = idxUnknown.begin(); it != idxUnknown.end(); ++it) {
      if (std::distance(idxUnknown.begin(), it) == (idxUnknown.size() - 1))
	this->_destination = std::string(argv[*it]);
      else {
	if (stat(argv[*it], &s) == 0)
	  {
	    if ( s.st_mode & S_IFDIR) {
	      std::cout << "Omitting directory \"" << std::string(argv[*it]) << "\"" << std::endl;
	    } else if (s.st_mode & S_IFREG) { //ITS FILE
	      this->_fileList.push_back(new File(std::string(argv[*it])));	
	    } else { //ITS OTHER
	      throw std::logic_error(std::string("Symlink? not supported yet .. Sorry"));
	    }
	  } else { //DOES NOT EXIST
	  std::cout << "File \"" << std::string(argv[*it]) << "\" does not exist" << std::endl;
	}
      }
    }
  };

  void		run(Parameters p) {
    if (this->_fileList.size() == 0)
      p.showUsage();
    for (std::vector<File*>::iterator it = this->_fileList.begin(); it != this->_fileList.end(); ++it) {
      try {
	(*it)->copyTo(this->_destination, this->_simpleCopyCallback);
      } catch (const std::exception &e) {
	std::cout << "Error while copying \"" << (*it)->getFilename() << "\" => " << e.what() << std::endl;
      }
    }
  };
};

#endif
