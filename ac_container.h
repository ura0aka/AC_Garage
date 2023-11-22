#pragma once
#ifndef ACCONTAINER_H
#define ACCONTAINER_H

#include <vector>
#include "ac_parts.h"
class Part;

class Container
{
  public:
    void add(Part* part)
    {
      m_vParts.push_back(part);
    }

    void displayParts() const
    {
      for(const auto& part : m_vParts)
      {
        part->display_stats();
      }
    }
    
    void count_stats()
    {
      int m_nAP {};
      int m_nWeight {};
      int m_nENLoad {};
      int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense {};
      
      for(const auto& part : m_vParts)
      {
        if(part->get_type() <= 4 && part->get_type() >= 7)
        {
          m_nAP += part->get_AP(); // hackable but really really terrible code holy shit
          m_nKineticDefense += part->get_Kin();
          m_nEnergyDefense += part->get_En();
          m_nExplosiveDefense += part->get_Exp();
          m_nWeight += part->get_weight();
          m_nENLoad += part->get_enload();
        }
      }
    }

    void clear()
    {
      for(auto& part : m_vParts)
      {
        delete part;
      }
      m_vParts.clear();
    }

  private:
    std::vector<Part*> m_vParts {};
};

#endif // !ACCONTAINER_H
