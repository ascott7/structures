#include "otter.hpp"

Otter::Otter()
    :name_{"phokey"}, hungry_{true}, clean_{false}
{
    // nothing to do
}

Otter::Otter(std::string name)
    :name_{name}, hungry_{true}, clean_{false}
{
    // nothing to do
}

Otter::~Otter()
{
    // nothing to do
}

void Otter::eat()
{
    hungry_ = false;
}

void Otter::cleanFur()
{
    clean_ = true;
}

bool Otter::operator==(const Otter& comparee)
{
    return clean_ == comparee.clean_ && hungry_ == comparee.hungry_;
}

bool Otter::operator!=(const Otter& comparee)
{
    return !(*this == comparee);
}