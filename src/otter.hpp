#include <string>
#include <cstddef>

class Otter {
public:
    Otter();
    Otter(std::string name);
    ~Otter();

    void eat();
    void cleanFur();
    bool operator==(const Otter& comparee) const;
    bool operator!=(const Otter& comparee) const;

private:
    std::string name_;
    bool hungry_;
    bool clean_;


};