#ifndef TIMODULE_H_
#define TIMODULE_H_

#include <v8.h>


using namespace v8;

class TiModule
{
  public:
    virtual Handle<Value> startup() = 0;
};

#endif /* TIMODULE_H_ */
