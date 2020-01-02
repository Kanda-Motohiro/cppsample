class Mock: public Base {
public:
    void do_something() override { printf("mock class\n"); }
};

namespace std {
template <>
shared_ptr<Base>
make_shared<Base>() {
    auto out = make_shared<Mock>();
    return std::dynamic_pointer_cast<Base>(out);
}
};
