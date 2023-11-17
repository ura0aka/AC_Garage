#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "ac_parts.h"
#include "ac_frame.h"
#include <vector>
#include <iterator>
#include <algorithm>

class AC;

class Inventory
{
  public:
    std::vector<Part*> m_vParts {};

    Inventory() = default;
    ~Inventory() {};
    
    void add_part(Part* p_cPartAdded)
    {
      // check if part is already in inventory
      std::vector<Part*>::iterator it = std::find(m_vParts.begin(),m_vParts.end(),p_cPartAdded);
      if(it != m_vParts.end())
      {
        // shouldn't really happen b/c once a part is purchased from the shop it's gone.
      }
      m_vParts.push_back(p_cPartAdded);
    }

    void display_sorted(int t_nCategory)
    {
      for(auto* c_part : m_vParts)
      {
        if(c_part->get_type() == t_nCategory)
        {
          std::cout << "ID: " << c_part->get_id() << '\n';
          c_part->display_stats();
          std::cout << '\n';
        } 
      }
    }

    void display_inventory()
    {
      // magic number 12 because there are 12 different parts categories
      for(std::size_t i {0}; i!=12; ++i)
      {
        display_sorted(i);
      }
    }

    Part* select_part(int p_nPartID)
    {
      for(std::size_t i {0}; i!=m_vParts.size(); ++i)
      {
        int nTempID = m_vParts[i]->get_id();
        if(nTempID == p_nPartID)
        {
          Part* cMovedPart = std::move(m_vParts[i]);
          m_vParts.erase(m_vParts.begin()+i);
          return cMovedPart; 
        }
      }
    }

};


#endif // ! INVENTORY_H

