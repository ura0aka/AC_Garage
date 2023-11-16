#pragma once
#ifndef ACITEM_H
#define ACITEM_H

#include <cstdint>
#include <string>
#include <iostream>

enum partsCategoryID
{
  R_ARM_UNIT = 0,
  L_ARM_UNIT = 1,
  R_BACK_UNIT = 2,
  L_BACK_UNIT = 3,
  HEAD = 4,
  ARMS = 5,
  CORE = 6,
  LEGS = 7,
  BOOSTER = 8,
  FCS = 9,
  GENERATOR = 10,
  EXPANSION = 11
};

class Item
{
  public:
    Item() = default;

    Item(int category, std::string name, int cost, int weight, int en_load, std::string manufacturer, bool is_equipped=false)
      : m_nCategoryID{category}, m_sItemName{name}, m_nItemCost{cost}, m_nWeight{weight},
      m_nENLoad{en_load}, m_sManufacturer{manufacturer}, m_bIsEquipped{is_equipped}
    {
      switch(m_nCategoryID)
      {
        case R_ARM_UNIT: {m_sCategory = "Right Arm Unit"; break;} 
        case L_ARM_UNIT: {m_sCategory = "Left Arm Unit"; break;} 
        case R_BACK_UNIT: {m_sCategory = "Right Back Unit"; break;}
        case L_BACK_UNIT: {m_sCategory = "Left Back Unit"; break;}
        // TODO: add specific stat variables for generator, fcs, expansion, etc... 
        //(probably need to make a separate class for the inner parts)
        case HEAD: {m_sCategory = "Head"; break;}
        case ARMS: {m_sCategory = "Arms"; break;}
        case CORE: {m_sCategory = "Core"; break;}
        case LEGS: {m_sCategory = "Legs"; break;}
        case BOOSTER: {m_sCategory = "Booster"; break;}
        case FCS: {m_sCategory = "FCS"; break;}
        case GENERATOR: {m_sCategory = "Generator"; break;}
        case EXPANSION: {m_sCategory = "Expansion"; break;}
      }
      m_nId = m_nIdGenerator += 1;
      
    }
    
    ~Item() {};

    void display_stats()
    {
      std::cout << ">> Name: " << m_sItemName << "\n>> Cost: " << m_nItemCost << " COAM" 
        << "\n>> Weight: " << m_nWeight << "\n>> EN load: " << m_nENLoad 
        << "\n>> Manufacturer: " << m_sManufacturer << '\n';  
    }

    void equip_item()
    {
      //TODO: do checks for each stat, etc ...
      m_bIsEquipped = true;
      std::cout << "Equipped. \n";
    }
    
    std::string get_name() 
    {
      if(this == nullptr)
      {
        return "<EMPTY>\n";
      }
      return m_sItemName;
    }
    std::uint32_t get_id() {return m_nId;}
    int get_cost() {return m_nItemCost;}
    int get_weight() {return m_nWeight;}
    int get_enload() {return m_nENLoad;}
    std::string get_manu() {return m_sManufacturer;}
    int get_type() {return m_nCategoryID;}
    std::string get_category() {return m_sCategory;}
    int get_AP() {return m_nAP;}
    int get_kinDef() {return m_nKineticDefense;}
    int get_enDef() {return m_nEnergyDefense;}
    int get_exDef() {return m_nExplosiveDefense;}

  private:
    std::string m_sItemName {};
    std::string m_sCategory {};
    static inline std::uint32_t m_nIdGenerator {0};
    std::uint32_t m_nId {};
    int m_nItemCost {};
    int m_nWeight {};
    int m_nENLoad {};
    std::string m_sManufacturer {};
    int m_nCategoryID {};
    bool m_bIsEquipped {};
    int m_nAP, m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense;
};


// == WEAPON UNITS (R/L arm & back) ==
class WeaponUnit : public Item
{
  // only difference between the righ/left weapon units is that left weapon units can be melee
  public:
  int m_nCategoryID {};
  std::string m_sCategory {};
  int m_nAP {};
  int m_nImpact {};
  int m_nTotalRounds {};
  bool m_bIsMelee {};
  bool m_bIsShield {};
  
  WeaponUnit() = default;

  WeaponUnit(int ap, int impact, int total_rounds, bool is_melee, int category,
      std::string name, int cost, int weight, int en_load, std::string manufacturer, bool is_equipped=false)
    : Item {category,name,cost,weight,en_load,manufacturer,is_equipped},
    m_nAP{ap}, m_nImpact{impact}, m_nTotalRounds{total_rounds}, m_bIsMelee{is_melee} 
  {
    m_sCategory = this->get_category(); // this is very horrible, to be fixed maybe 
  }

  ~WeaponUnit() {};

  void display_specific()
  {
    std::cout << ">> [" << m_sCategory << "] \n";
    display_stats();
    if(m_nCategoryID == L_ARM_UNIT && m_bIsMelee == true)
    {
      std::cout << ">> ATK Power: " << m_nAP << "\n>> Impact: " << m_nImpact << '\n';
    }
    if(m_nCategoryID == L_BACK_UNIT && m_bIsShield == true)
    {
      std::cout << ">> Energy Shield \n";
    }
    else
    {
      std::cout << ">> ATK Power: " << m_nAP << "\n>> Impact: " << m_nImpact <<
      "\n>> Total Rounds: " << m_nTotalRounds << '\n';
    }
  }

};

// == AC BODY UNITS (parts) [head,arms,core,legs,booster,fcs,generator] ==
class FramePart : public Item
{
  public:
    int m_nCategoryID {};
    std::string m_sCategory {};
    int m_nArmorPoints {};
    int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense {};
  
  FramePart() = default;

  FramePart(int ap, int kin_def, int en_def, int exp_def, int category,
      std::string name, int cost, int weight, int en_load, std::string manufacturer, bool is_equipped=false)
    : Item {category,name,cost,weight,en_load,manufacturer,is_equipped},
    m_nArmorPoints{ap}, m_nKineticDefense{kin_def}, m_nEnergyDefense{en_def}, m_nExplosiveDefense{exp_def}
  {
    m_sCategory = this->get_category();
  }

  ~FramePart() {};

  std::string derived_get_name()
  {
    // derived function from the base Item class
    std::string m_sName = get_name();
    return m_sName;
  }

  void display_specific()
  {
    std::cout << ">> [" << m_sCategory << "] \n";
    display_stats();
    std::cout << ">> Armor Points: " << m_nArmorPoints <<
      "\n>> Kinetic Defense: " << m_nKineticDefense << " >> Energy Defense: " << m_nEnergyDefense
      << " >> Explosive Defense: " << m_nExplosiveDefense << '\n';
  }

};



#endif // !ACITEM_H


