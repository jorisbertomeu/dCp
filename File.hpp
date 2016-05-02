#ifndef		_FILE_HPP_
# define	_FILE_HPP_

# include	<string>

class		File
{
private:
  std::string	_filename;

  /* Constructor - Destructor */
public:
  explicit	File() {

  };

  virtual	~File() {

  };

  /* Common publics methods */
public:
  void		from(const std::string &str) {
    this->_filename = str;
  };

  /* Getters - Setters */
public:
  std::string	getFilename() const {
    return this->_filename;
  };
};

#endif		/* _FILE_HPP_ */
