#include <imguiOpenglTemplate/myClass.hpp>
#include <iostream>

namespace test {
  MyClass::MyClass(std::string _name) : name(_name){};

  void MyClass::printName() { std::cout << name << std::endl; }
}  // namespace test