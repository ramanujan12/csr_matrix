/*
  test the timer
*/

#include "timing.h"

int main(int argc, char** argv) {
  stopwatch sw;
  sw.start();
  sw.stop();
  
  std::cout << sw.s()  << std::endl;
  std::cout << sw.ms() << std::endl;
  std::cout << sw.us() << std::endl;
  std::cout << sw.ns() << std::endl;

  time_table tt;
  tt.add("first");
  tt.add("second");
  tt.add("third");
  tt.add("fourth");
  tt.add("some supid long string i want to test this thing with");
  std::cout << tt << std::endl;
}
