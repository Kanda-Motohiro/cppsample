#include "klass.h"
extern std::shared_ptr<Klass> sub();
int main()
{
    auto out = sub();
    out->hello();
}
