#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "ac_items.h"
#include "ac_frame.h"
#include <vector>
#include <iterator>
#include <algorithm>

class AC;

class Inventory
{
  public:
    std::vector<Item*> m_vParts {};

    Inventory() = default;
    ~Inventory() {};
    
    void add_part(Item* p_cPartAdded)
    {
      // check if part is already in inventory
      std::vector<Item*>::iterator it = std::find(m_vParts.begin(),m_vParts.end(),p_cPartAdded);
      if(it != m_vParts.end())
      {
        // shouldn't really happen b/c once an item is purchased from the shop it's gone.
      }
      m_vParts.push_back(p_cPartAdded);
    }

    void display_sorted(int t_nCategory)
    {
      for(auto* c_item : m_vParts)
      {
        if(c_item->get_type() == t_nCategory)
        {
          std::cout << "[" << c_item->get_category() << "]\n";
          std::cout << "ID: " << c_item->get_id() << '\n';
          c_item->display_stats();
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

    Item* select_part(int p_nPartID)
    {
      for(std::size_t i {0}; i!=m_vParts.size(); ++i)
      {
        int nTempID = m_vParts[i]->get_id();
        if(nTempID == p_nPartID)
        {
          Item* cMovedItem = std::move(m_vParts[i]);
          m_vParts.erase(m_vParts.begin()+i);
          return cMovedItem; 
        }
      }
    }

};


#endif // ! INVENTORY_H

