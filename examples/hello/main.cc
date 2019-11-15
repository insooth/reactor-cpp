#include <iostream>

#include "reactor-cpp/reactor-cpp.hh"

using namespace reactor;

class Hello : public Reactor {
 private:
  // actions
  Timer timer{"timer", this, 1_s, 2_s};

  // reactions
  Reaction r_hello{"hello", 1, this, [this]() { hello(); }};

 public:
  Hello(Environment* env) : Reactor("Hello", env) {}

  void assemble() override { r_hello.declare_trigger(&timer); }

  void hello() { std::cout << "Hello World!" << std::endl; }
};

int main() {
  Environment e{4};

  Hello hello{&e};
  e.assemble();

  auto t = e.startup();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  e.shutdown();
  t.join();

  return 0;
}
