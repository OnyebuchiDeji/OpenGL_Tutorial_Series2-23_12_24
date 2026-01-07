#pragma once
#include "../config.h"
#include <iostream>


struct SearchResult
{
    size_t position;
    int flag;
};

template<typename T>
class ComponentSet
{
private:
    SearchResult binary_search(uint32_t entity)
    {
        //  Early Exit: No Components in Set
        if (m_Entities.size() == 0){
            SearchResult a;
            a.position = 0;
            a.flag = 1;
            return a;
        } 

        SearchResult a;
        a.position = 0;
        a.flag = std::min<int>(1,
            std::max<int>(-1, m_Entities[a.position] - entity));
        if (a.flag == 0){
            return a;
        }

        SearchResult b;
        b.position = m_Entities.size() - 1;
        b.flag = std::min<int>(1,
            std::max<int>(-1, m_Entities[b.position] - entity));
        if (b.flag == 0){
            return b;
        }
        
        while ((a.flag * b.flag < 0) && ((b.position - a.position) > 1)){
            SearchResult c;
            c.position = (a.position + b.position) / 2;
            c.flag = std::min<int>(1,
                std::max<int>(-1, m_Entities[c.position] - entity));

            if (c.flag == 0){ return c; }

            if (a.flag * c.flag < 0) { b = c;}

            else { a = c; }
        }
        if (b.flag == 0){ return b;}

        return a;
    }
    
public:
    std::vector<T> m_Components;
    std::vector<uint32_t> m_Entities;

    size_t insert(uint32_t entity, T component)
    {
        SearchResult query = binary_search(entity);
        if (query.flag == 0) {
            m_Components[query.position] = component;
            return query.position;
        }
        
        //  Add a new entry, this is a kinda dodgy method
        m_Entities.push_back(entity);
        m_Components.push_back(component);

        //  Now shuffle to make space
        size_t i = m_Entities.size() - 1;
        while (i > 0 && m_Entities[i - 1] >= entity){
            m_Entities[i] = m_Entities[i - 1];
            m_Components[i] = m_Components[i - 1];
            --i;    //  This was discovered through debugging.
        }
        m_Entities[i] = entity;
        m_Components[i] = component;
        // ---------End of Shuffle Code.
        return i;
    }

    void remove(uint32_t entity){
        SearchResult query = binary_search(entity);
        if (query.flag != 0) {
            return;
        }
        m_Entities.erase(m_Entities.begin() + query.position);
        m_Components.erase(m_Components.begin() + query.position);
    }

    T& get_component(uint32_t entity){
        SearchResult query = binary_search(entity);

        if (query.flag != 0) {
            std::cout << "Something Went Horribly Wrong.\n";
        }
        
        return m_Components[query.position];
    }
};