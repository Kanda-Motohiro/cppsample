class Mock: public Klass {
public:
    virtual void hello() { printf("mock\n"); }
};
namespace std {
template <>
shared_ptr<Klass>
make_shared<Klass>() {
    auto out = make_shared<Mock>();
    return std::dynamic_pointer_cast<Klass>(out);
}
};

