#include "base.h"

std::shared_ptr<Base> sub()
{
    auto out = std::make_shared<Base>();
    return out;
}
