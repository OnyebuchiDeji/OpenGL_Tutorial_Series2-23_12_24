#pragma once
#include "../config.h"
#include "../components/registry.h"

class Factory {

public:
    Factory(ComponentRegistry& componentRegistry, uint32_t& shader);
    
    ~Factory();

    void make_object();

    std::vector<unsigned int> m_GarbageBin;

private:

    unsigned int m_EntitesMade = 0;

    ComponentRegistry& m_ComponentRegistry;
    uint32_t& m_Shader;

    unsigned int allocate_id();

};