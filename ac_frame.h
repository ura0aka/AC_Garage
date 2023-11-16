#pragma once 
#ifndef ACFRAME_H
#define ACFRAME_H

#include "ac_items.h"
#include "inventory.h"
#include <vector>
#include <limits>
class Item;
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
    }

    ~AC() {};

    Inventory *m_PlayerInventory;

    // Unit
    Item *m_rArmUnit, *m_lArmUnit; 
    Item *m_rBackUnit, *m_lBackUnit;
    // Frame & Inner
    FramePart *m_Head, *m_Arms, *m_Core, *m_Legs;
    std::vector<FramePart*> m_vFrameParts {};
    Item *m_Booster, *m_FCS, *m_Generator, *m_Expansion;
    int m_nAP {};
    int m_nWeight {};
    int m_nENLoad {};
    int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense {};
    
    void calculate_stats()
    {
      m_nAP=0, m_nKineticDefense=0, m_nEnergyDefense=0, m_nExplosiveDefense=0;
      m_vFrameParts.push_back(m_Head);
      m_vFrameParts.push_back(m_Core);
      m_vFrameParts.push_back(m_Arms);
      m_vFrameParts.push_back(m_Legs);
      for(auto p : m_vFrameParts)
      {
        m_nAP += p->m_nArmorPoints;
        m_nKineticDefense += p->m_nKineticDefense;
        m_nEnergyDefense += p->m_nEnergyDefense;
        m_nExplosiveDefense += p->m_nExplosiveDefense;
      }
    }

    void display_mech()
    {
      calculate_stats();
      std::cout << "===========================\n" << ">> {Your AC} : \n" << "[UNIT]" << "\nR-Arm Unit: " << m_rArmUnit->get_name() <<
        "\nL-Arm Unit: " << m_lArmUnit->get_name() <<  "\nR-Back Unit: " << m_rBackUnit->get_name() <<
        "\nL-Back Unit: " << m_lBackUnit->get_name() << '\n';
      std::cout << "\n[FRAME]" << "\nHead: " << m_Head->derived_get_name() << "\nCore: " << m_Core->derived_get_name() <<
        "\nArms: " << m_Arms->derived_get_name() << "\nLegs: " << m_Legs->derived_get_name() << '\n';
      std::cout << "\n[INNER]" << "\nBooster: " << m_Booster->get_name() << "\nFCS: " << m_FCS->get_name() <<
        "\nGenerator: " << m_Generator->get_name() << "\nExpansion: " << m_Expansion->get_name() << '\n';
      std::cout << "\nTotal AP: " << m_nAP << "\nAnti-Kinetic Defense: " << m_nKineticDefense <<
        "\nAnti-Energy Defense: " << m_nEnergyDefense << "\nAnti-Explosive Defense: " << m_nExplosiveDefense
        << "\n===========================\n" ;
    }

    void add_part()
    {
      std::cout << "\n>> Which part to add? \n";
      std::cout << "\n[UNIT]\n1.R-Arm Unit\n2.L-Arm Unit\n3.R-Back Unit\n4.L-Back Unit";
      std::cout << "\n[FRAME]\n5.Head\n6.Core\n7.Arms\n8.Legs";
      std::cout << "\n[INNER]\n9.Booster\n10.FCS\n11.Generator\n12.Expansion\n";
      int nOption = prompt_for_numeric<int>("\nEnter number:");

      Item* c_tempItem;
      FramePart* c_tempFramePart;
      switch(nOption)
      {
        std::cout << ">> Choose which part you want to equip. \n";
        case 1:
        {
          if(m_rArmUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_rArmUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(R_ARM_UNIT);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_rArmUnit = c_tempItem;
          break;
        }
        case 2:
        {
          if(m_lArmUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_lArmUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(L_ARM_UNIT);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_lArmUnit = c_tempItem;
          break;
        }
        case 3:
        {
          if(m_rBackUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_rBackUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(R_BACK_UNIT);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_rBackUnit = c_tempItem;
          break;
        }
        case 4:
        {
          if(m_lBackUnit!=nullptr)
          {
            m_PlayerInventory->add_part(m_lBackUnit); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(L_BACK_UNIT);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_lBackUnit = c_tempItem;
          break;
        }
        case 5:
        {
          if(m_Head!=nullptr)
          {
            m_PlayerInventory->add_part(m_Head); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(HEAD);
          c_tempFramePart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Head = c_tempFramePart;
          break;
        }
        case 6:
        {
          if(m_Core!=nullptr)
          {
            m_PlayerInventory->add_part(m_Core); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(CORE);
          c_tempFramePart = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Core = c_tempFramePart;
          break;
        }
        case 7:
        {
          if(m_Arms!=nullptr)
          {
            m_PlayerInventory->add_part(m_Arms); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(ARMS);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Arms = c_tempFramePart;
          break;
        }
        case 8:
        {
          if(m_Legs!=nullptr)
          {
            m_PlayerInventory->add_part(m_Legs); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(LEGS);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Legs = c_tempFramePart;
          break;
        }
        case 9:
        {
          if(m_Booster!=nullptr)
          {
            m_PlayerInventory->add_part(m_Booster); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(BOOSTER);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Booster = c_tempItem;
          break;
        }
        case 10:
        {
          if(m_FCS!=nullptr)
          {
            m_PlayerInventory->add_part(m_FCS); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(FCS);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_FCS = c_tempItem;
          break;
        }
        case 11:
        {
          if(m_Generator!=nullptr)
          {
            m_PlayerInventory->add_part(m_Generator); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(GENERATOR);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Generator = c_tempItem;
          break;
        }
        case 12:
        {
          if(m_Expansion!=nullptr)
          {
            m_PlayerInventory->add_part(m_Expansion); // send existing part back to inventory
          }
          m_PlayerInventory->display_sorted(EXPANSION);
          c_tempItem = m_PlayerInventory->select_part(prompt_for_numeric<int>("\nEnter part ID: "));
          m_Expansion = c_tempItem;
          break;
        }

        default: break;
      }
    }
};

#endif // !ACFRAME_H
