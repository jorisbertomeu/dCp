//
// Parameters.hpp for  in /home/Dieu/Desktop/Work/BMTech/Linux
// 
// Made by Dieu Dieu
// Login   <Dieu@epitech.net>
// 
// Started on  Mon Jan 18 15:20:21 2016 Dieu Dieu
// Last update Tue Jan 19 15:17:10 2016 Dieu Dieu
//

#ifndef		_PARAMETERS_HPP_
# define	_PARAMETERS_HPP_

# include	<string>
# include	<list>
# include	<map>
# include	<stdexcept>
# include	<unistd.h>
# include	<fstream>
# include	<sys/types.h>
# include	<sys/stat.h>

# include	<IParameters.hpp>

class		Parameters :	public IParameters
{
private:
  bool		_details;
  
public:
  explicit	Parameters() : IParameters(this) {
    setlocale(LC_ALL, "");
    this->_details = false;
    this->addParameter("--details:-d", &Parameters::parseDetails,
		       "More details about your copying");
    this->addParameter("--help:-h", &Parameters::showHelp,
		       "Show this Usage");
  };

  bool		getDetails() const {
    return (this->_details);
  };

private:
  int		parseDetails(int ac, char **argv, int idx) {
    (void) ac;
    (void) argv;
    (void) idx;
    
    this->_details = true;
    return (0);
  };
  
  int		showHelp(int ac, char **argv, int idx) {
    (void) ac;
    (void) argv;
    (void) idx;
    this->showUsage();
    exit(0);
    return (0);
  };

};

#endif
