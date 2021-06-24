// #include <gtest/gtest.h>
// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
#include "server_interface.hpp"
#include <iostream>
#include "message.h"
#include <string>

int main()
{
  std::string input;
  kbnet::server_interface s(80);
  s.start();
  for(;;)
  {
    std::string bing;
    bing.resize(64);
    // std::cin >> input;
    // if (input == "q")
    // break;
    // std::cout << input;
// std::cout << "str" << std::endl;

if (s.m_incoming.empty())
continue;
std::cout << "word";
message msg = s.m_incoming.pop_front();
std::cout << ": ";

char* ptr = (char*)msg.body.data();
while(*ptr != '\0')
{
  std::cout << *ptr;
  ptr++;
}
std::cout << std::endl;
// msg >> bing;
// std::cout << bing << std::endl;
// printf("%s\n",msg.body.data());

  }
  return 0;

}