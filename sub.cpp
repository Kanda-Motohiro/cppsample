#include "klass.h"
#include "mock.h"

std::shared_ptr<Klass> sub()
{
    auto out = std::make_shared<Klass>();
    return out;
    //auto out = std::make_shared<Mock>();
    //return std::dynamic_pointer_cast<Klass>(out);
}
