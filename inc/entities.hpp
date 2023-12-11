#pragma once

#include <vector>

class Entities{
    public:
    static unsigned int counter;
    static std::vector<unsigned int> aliveEntities;
    static std::vector<unsigned int> deadEntities;

    static unsigned int newID();

    static void deleteID(const unsigned int id);
};