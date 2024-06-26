#pragma once 
#ifndef ACFRAME_H
#define ACFRAME_H

#include "ac_parts.h"
#include "inventory.h"
#include <vector>
#include <limits>
#include <map>

class Part;
class WeaponUnit;
class FramePart;
class Inventory;

void clear_extra()
{
  // ignores all of the characters up until newline
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
T prompt_for_numeric(std::string message)
{
  while(1)
  {
    T tEntry;
    bool bIsNumeric {false};
    std::cout << message;
    if(std::cin >> tEntry)
    {
      bIsNumeric = true;
      if(tEntry < 0)
      {
        std::cerr << "ERROR: Cannot be (less than) < 0. \n";
        continue;
      }
      clear_extra();
      return tEntry;
    } else {
      bIsNumeric = false;
      std::cerr << "ERROR: Invalid entry. \n";
      std::cin.clear();
      clear_extra();
      continue;
    }
  }
}

class AC
{
  public:
    AC() = default;
  
    AC(WeaponUnit *r_arm_unit, WeaponUnit *l_arm_unit, WeaponUnit *r_back_unit, WeaponUnit *l_back_unit,
        FramePart *head, FramePart *core, FramePart *arms, FramePart *legs, FramePart *booster, FramePart *fcs,
        FramePart *generator, FramePart *expansion)
      : m_rArmUnit{r_arm_unit}, m_lArmUnit{l_arm_unit}, m_rBackUnit{r_back_unit}, m_lBackUnit{l_back_unit},
      m_Head{head}, m_Core{core}, m_Arms{arms}, m_Legs{legs}, m_Booster{booster}, m_FCS{fcs}, m_Generator{generator}, m_Expansion{expansion}
    {
      m_vPACParts[m_rArmUnit->get_id()] = m_rArmUnit; 
      m_vPACParts[m_lArmUnit->get_id()] = m_lArmUnit;
      m_vPACParts[m_rBackUnit->get_id()] = m_rBackUnit;
      m_vPACParts[m_lBackUnit->get_id()] = m_lBackUnit;
      m_vPACParts[m_Head->get_id()] = m_Head;
      m_vPACParts[m_Core->get_id()] = m_Core;
      m_vPACParts[m_Arms->get_id()] = m_Arms;
      m_vPACParts[m_Legs->get_id()] = m_Legs;
      m_vPACParts[m_Booster->get_id()] = m_Booster;
      m_vPACParts[m_FCS->get_id()] = m_FCS;
      m_vPACParts[m_Generator->get_id()] = m_Generator;
      m_vPACParts[m_Expansion->get_id()] = m_Expansion; // initially there is no expansion part, find a way to still add an empty object into the map without it crashing pls
    }

    ~AC() {};

    Inventory *m_PlayerInventory;
    std::map<std::uint32_t,Part*> m_vPACParts {}; // parts hashmap
    // Unit
    Part *m_rArmUnit, *m_lArmUnit; 
    Part *m_rBackUnit, *m_lBackUnit;
    // Frame & Inner
    Part *m_Head, *m_Arms, *m_Core, *m_Legs;
    Part *m_Booster, *m_FCS, *m_Generator, *m_Expansion;

    int m_nAP {};
    int m_nWeight {};
    int m_nENLoad {};
    int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense {};
    
    void count_stats()
    {
      m_nWeight = 0, m_nENLoad = 0;
      m_nAP=0, m_nKineticDefense=0, m_nEnergyDefense=0, m_nExplosiveDefense=0; // reset values
     
      // load all frame parts into a vector to calculate in a loop
      std::vector<Part*> m_vFrameParts {};
      m_vFrameParts.push_back(m_vPACParts[m_Head->get_id()]);
      m_vFrameParts.push_back(m_vPACParts[m_Core->get_id()]);
      m_vFrameParts.push_back(m_vPACParts[m_Arms->get_id()]);
      m_vFrameParts.push_back(m_vPACParts[m_Legs->get_id()]);

      for(const auto& part : m_vFrameParts)
      {    
        m_nAP += part->get_AP(); // hacked together, not very great-looking code, too bad
        m_nKineticDefense += part->get_Kin();
        m_nEnergyDefense += part->get_En();
        m_nExplosiveDefense += part->get_Exp();
        m_nWeight += part->get_weight();
        m_nENLoad += part->get_enload();
      }
    }

    void display_mech()
    {
      count_stats();
      std::cout << "===========================\n" << ">> {Your AC} : \n" << "[UNIT]" << "\nR-Arm Unit: " << m_vPACParts[m_rArmUnit->get_id()]->get_name() <<
        "\nL-Arm Unit: " << m_vPACParts[m_lArmUnit->get_id()]->get_name() <<  "\nR-Back Unit: " << m_vPACParts[m_rBackUnit->get_id()]->get_name() <<
        "\nL-Back Unit: " << m_vPACParts[m_lBackUnit->get_id()]->get_name() << '\n';
      std::cout << "\n[FRAME]" << "\nHead: " << m_vPACParts[m_Head->get_id()]->get_name() << "\nCore: " << m_vPACParts[m_Core->get_id()]->get_name() <<
        "\nArms: " << m_vPACParts[m_Arms->get_id()]->get_name() << "\nLegs: " << m_vPACParts[m_Legs->get_id()]->get_name() << '\n';
      std::cout << "\n[INNER]" << "\nBooster: " << m_vPACParts[m_Booster->get_id()]->get_name() << "\nFCS: " << m_vPACParts[m_FCS->get_id()]->get_name() <<
        "\nGenerator: " << m_vPACParts[m_Generator->get_id()]->get_name() << "\nExpansion: " << m_vPACParts[m_Expansion->get_id()]->get_name() << '\n';
      std::cout << "\nTotal AP: " << m_nAP << "\nAnti-Kinetic Defense: " << m_nKineticDefense <<
        "\nAnti-Energy Defense: " << m_nEnergyDefense << "\nAnti-Explosive Defense: " << m_nExplosiveDefense
        << "\nTotal Weight: " << m_nWeight << "\nTotal EN Load: " << m_nENLoad
        << "\n===========================\n" ;
    }


    void add_part()
    {
      std::cout << "\n>> Which part to add? \n";
      std::cout << "\n[UNIT]\n1.R-Arm Unit\n2.L-Arm Unit\n3.R-Back Unit\n4.L-Back Unit";
      std::cout << "\n[FRAME]\n5.Head\n6.Core\n7.Arms\n8.Legs";
      std::cout << "\n[INNER]\n9.Booster\n10.FCS\n11.Generator\n12.Expansion\n";
      int nOption = prompt_for_numeric<int>("\nEnter number:");
      std::cout << ">> Choose which part you want to equip. \n";
      Part* c_tempPart; 
      switch(nOption)
      {
        case 1:
        {
          if(m_rArmUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_rArmUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(R_ARM_UNIT);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_rArmUnit->get_id()] = c_tempPart; // replace previous part with new one
          break;
        }
        case 2:
        {
          if(m_lArmUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_lArmUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(L_ARM_UNIT);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_lArmUnit->get_id()] = c_tempPart;
          break;
        }
        case 3:
        {
          if(m_rBackUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_rBackUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(R_BACK_UNIT);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_rBackUnit->get_id()] = c_tempPart;
          break;
        }
        case 4:
        {
          if(m_lBackUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_lBackUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(L_BACK_UNIT);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_lBackUnit->get_id()] = c_tempPart;
          break;
        }
        case 5:
        {
          if(m_Head!=nullptr)
          {
            m_PlayerInventory->add_part(m_Head); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(HEAD);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Head->get_id()] = c_tempPart;
          break;
        }
        case 6:
        {
          if(m_Core!=nullptr)
          {
            m_PlayerInventory->add_part(m_Core); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(CORE);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Core->get_id()] = c_tempPart;
          break;
        }
        case 7:
        {
          if(m_Arms!=nullptr)
          {
            m_PlayerInventory->add_part(m_Arms); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(ARMS);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Arms->get_id()] = c_tempPart;
          break;
        }
        case 8:
        {
          if(m_Legs!=nullptr)
          {
            m_PlayerInventory->add_part(m_Legs); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(LEGS);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Legs->get_id()] = c_tempPart;
          break;
        }
        case 9:
        {
          if(m_Booster!=nullptr)
          {
            m_PlayerInventory->add_part(m_Booster); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(BOOSTER);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Booster->get_id()] = c_tempPart;
          break;
        }
        case 10:
        {
          if(m_FCS!=nullptr)
          {
            m_PlayerInventory->add_part(m_FCS); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(FCS);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_FCS->get_id()] = c_tempPart;
          break;
        }
        case 11:
        {
          if(m_Generator!=nullptr)
          {
            m_PlayerInventory->add_part(m_Generator); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(GENERATOR);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Generator->get_id()] = c_tempPart;
          break;
        }
        case 12:
        {
          if(m_Expansion!=nullptr)
          {
            m_PlayerInventory->add_part(m_Expansion); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(EXPANSION);
          c_tempPart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_vPACParts[m_Expansion->get_id()] = c_tempPart;
          break;
        }

        default: break;
      }
    }
};

#endif // !ACFRAME_H
