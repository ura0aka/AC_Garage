#pragma once
#ifndef ACPARTS_H
#define ACPARTS_H

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

class Part
{
  public:
    Part() = default;

    Part(int category, std::string name, int cost, int weight, int en_load, std::string manufacturer, bool is_equipped=false)
      : m_nCategoryID(category), m_sPartName(name), m_nPartCost(cost), m_nPartWeight(weight),
      m_nEnLoad(en_load), m_sManufacturer(manufacturer), m_bIsEquipped(is_equipped)
    {
      switch(m_nCategoryID)
      {
        case R_ARM_UNIT: {m_sPartCategory = "Right Arm Unit"; break;} 
        case L_ARM_UNIT: {m_sPartCategory = "Left Arm Unit"; break;} 
        case R_BACK_UNIT: {m_sPartCategory = "Right Back Unit"; break;}
        case L_BACK_UNIT: {m_sPartCategory = "Left Back Unit"; break;}
        // TODO: add specific stat variables for generator, fcs, expansion, etc... 
        //(probably need to make a separate class for the inner parts)
        case HEAD: {m_sPartCategory = "Head"; break;}
        case ARMS: {m_sPartCategory = "Arms"; break;}
        case CORE: {m_sPartCategory = "Core"; break;}
        case LEGS: {m_sPartCategory = "Legs"; break;}
        case BOOSTER: {m_sPartCategory = "Booster"; break;}
        case FCS: {m_sPartCategory = "FCS"; break;}
        case GENERATOR: {m_sPartCategory = "Generator"; break;}
        case EXPANSION: {m_sPartCategory = "Expansion"; break;}
      }
      m_nPartID = m_nIdGenerator += 1;
    }

    virtual void display_stats() const
    {
      std::cout << ">> [" << m_sPartCategory << "] \n";
      std::cout << ">> Name: " << m_sPartName << "\n>> Cost: " << m_nPartCost << " COAM" 
      << "\n>> Weight: " << m_nPartWeight << "\n>> EN load: " << m_nEnLoad 
      << "\n>> Manufacturer: " << m_sManufacturer << '\n';
    }

  protected:
    std::uint32_t m_nPartID {};
    static inline std::uint32_t m_nIdGenerator {0};
    std::string m_sPartName {};
    int m_nCategoryID {};
    std::string m_sPartCategory {};
    int m_nPartCost, m_nPartWeight, m_nEnLoad {};
    std::string m_sManufacturer {};
    bool m_bIsEquipped {};
};

class WeaponUnit : public Part
{
  public:
    int m_nAttackPower, m_nImpact, m_nTotalRounds {};
    bool m_bIsMelee {};

    WeaponUnit() = default;

    WeaponUnit(int ap, int impact, int total_rounds, bool is_melee, int category,
        std::string name, int cost, int weight, int en_load, std::string manufacturer, bool is_equipped=false)
    : Part(category,name,cost,weight,en_load,manufacturer,is_equipped),
    m_nAttackPower(ap), m_nImpact(impact), m_nTotalRounds(total_rounds), m_bIsMelee(is_melee)
    {

    }

    void display_stats() const override
    {
      Part::display_stats();
      if(Part::m_nCategoryID == L_ARM_UNIT && m_bIsMelee == true)
      {
        std::cout << ">> ATK Power: " << m_nAttackPower << "\n>> Impact: " << m_nImpact << '\n';
      }
      else
      {
        std::cout << ">> ATK Power: " << m_nAttackPower << "\n>> Impact: " << m_nImpact <<
        "\n>> Total Rounds: " << m_nTotalRounds << '\n';
      }
    }
    
};

class FramePart : public Part
{
  public:
    int m_nArmorPoints {};
    int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense {};

    FramePart() = default;

    FramePart(int ap, int kin_def, int en_def, int exp_def, int category,
       std::string name, int cost, int weight, int en_load, std::string manufacturer, bool is_equipped=false)
    : Part(category,name,cost,weight,en_load,manufacturer,is_equipped),
    m_nArmorPoints(ap), m_nKineticDefense(kin_def), m_nEnergyDefense(en_def), m_nExplosiveDefense(exp_def)
  {

  }

    void display_stats() const override
    {
      Part::display_stats();
      std::cout << ">> Armor Points: " << m_nArmorPoints <<
      "\n>> Kinetic Defense: " << m_nKineticDefense << " >> Energy Defense: " << m_nEnergyDefense
      << " >> Explosive Defense: " << m_nExplosiveDefense << '\n';
    }
};

#endif // !ACPARTS_H
