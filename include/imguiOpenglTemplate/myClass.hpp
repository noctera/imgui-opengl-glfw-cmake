#include <string>
namespace test {
  class MyClass {
  public:
    MyClass(std::string name);
    void printName();

  private:
    std::string name;
  };
}  // namespace test
