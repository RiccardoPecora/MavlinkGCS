#include "sayhello.h"

SayHello::SayHello() {}

void SayHello::greeting(std::string const& message) const
{
    std::cout<<message<<std::endl;
}
