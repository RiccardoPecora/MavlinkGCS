#ifndef SAYHELLO_H
#define SAYHELLO_H

#include <string>
#include <iostream>

class SayHello
{
public:
    SayHello();
    void greeting(std::string const& message) const;
};

#endif // SAYHELLO_H
