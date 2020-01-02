#include "base.h"

std::shared_ptr<Base> new_base()
{
    auto out = std::make_shared<Base>();
    return out;
}
