#include "RBSP.hpp"

#include <stdlib.h>

RBSP::RBSP()
{

}

RBSP::~RBSP()
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }
}