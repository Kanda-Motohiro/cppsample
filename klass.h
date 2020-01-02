#include <memory>
#include <stdio.h>
class Klass {
public:
    int id;
    Klass() { id = 0x888; }
    virtual void hello() { printf("%s class\n", id==0x777?"mock":"base"); }
};
