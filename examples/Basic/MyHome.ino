#include <MyHome.h>


MyHome myhome;

void setup () {
  myhome.register_pin("In-built led 1", 2);
  myhome.register_pin("In-built led 2", 16);
  
}

void loop () {
  myhome.handle();
}
