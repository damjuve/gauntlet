#pragma once

#include <stdexcept>
#include <string>

namespace exception
{
  class LoadingDataException : public std::runtime_error
  {
  public:
    LoadingDataException(std::string const& data_type, std::string const& data_path);
    virtual ~LoadingDataException() throw();
  };

  class IrrlichtException : public std::runtime_error
  {
  public:
    IrrlichtException(std::string const& string);
    virtual ~IrrlichtException() throw();
  };
}
