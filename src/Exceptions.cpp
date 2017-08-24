#include <cerrno>
#include <cstring>
#include "Exceptions.hh"

 namespace exception
 {
   LoadingDataException::LoadingDataException(std::string const& data_type, std::string const& data_path)
     : std::runtime_error("Failed to load " + data_type + " data with path = " + data_path)
   {}

   LoadingDataException::~LoadingDataException() throw()
   {}

   IrrlichtException::IrrlichtException(std::string const& string)
     : std::runtime_error("Irrlicht got an error on call of : " + string + " function")
   {}

   IrrlichtException::~IrrlichtException() throw()
   {}
 }
