#pragma once
#ifndef ACPARTS_H
#define ACPARTS_H

#include "ac_datafile.h"
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
enum partsCategoryID {
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

class Datafile;

class Part {
public:
  Part() = default;

  Part(int category, std::string name, int cost, int weight, int en_load,
       std::string manufacturer, bool is_equipped = false)
      : m_nCategoryID(category), m_sPartName(name), m_nPartCost(cost),
        m_nPartWeight(weight), m_nEnLoad(en_load),
        m_sManufacturer(manufacturer), m_bIsEquipped(is_equipped) {
    switch (m_nCategoryID) {
    case R_ARM_UNIT: {
      m_sPartCategory = "Right Arm Unit";
      break;
    }
    case L_ARM_UNIT: {
      m_sPartCategory = "Left Arm Unit";
      break;
    }
    case R_BACK_UNIT: {
      m_sPartCategory = "Right Back Unit";
      break;
    }
    case L_BACK_UNIT: {
      m_sPartCategory = "Left Back Unit";
      break;
    }
    // TODO: add specific stat variables for generator, fcs, expansion, etc...
    //(probably need to make a separate class for the inner parts)
    case HEAD: {
      m_sPartCategory = "Head";
      break;
    }
    case ARMS: {
      m_sPartCategory = "Arms";
      break;
    }
    case CORE: {
      m_sPartCategory = "Core";
      break;
    }
    case LEGS: {
      m_sPartCategory = "Legs";
      break;
    }
    case BOOSTER: {
      m_sPartCategory = "Booster";
      break;
    }
    case FCS: {
      m_sPartCategory = "FCS";
      break;
    }
    case GENERATOR: {
      m_sPartCategory = "Generator";
      break;
    }
    case EXPANSION: {
      m_sPartCategory = "Expansion";
      break;
    }
    }
    m_nPartID = m_nIdGenerator += 1;
  }

  virtual void display_stats() const {
    std::cout << ">> [" << m_sPartCategory << "] \n";
    std::cout << ">> Name: " << m_sPartName << "\n>> Cost: " << m_nPartCost
              << " COAM" << "\n>> Weight: " << m_nPartWeight
              << "\n>> EN load: " << m_nEnLoad
              << "\n>> Manufacturer: " << m_sManufacturer << '\n';
  }

  virtual void save(Datafile &df) {
    // save common part properties
    df[this->get_name()]["Category ID"].set_int(this->get_type());
    df[this->get_name()]["ID"].set_int(this->get_id());
    df[this->get_name()]["Part Name"].set_string(this->get_name());
    df[this->get_name()]["Category"].set_string(this->get_category());
    df[this->get_name()]["Cost"].set_int(this->get_cost());
    df[this->get_name()]["Weight"].set_int(this->get_weight());
    df[this->get_name()]["EN Load"].set_int(this->get_enload());
    df[this->get_name()]["Manufacturer"].set_string(this->get_manu());
  }

  virtual void load(Datafile &df, const std::string &sFileName) {
    std::cout << "Reading from file ..." << std::endl;
    Datafile::read_from_file(df, sFileName);
    m_sPartName = df.get_propertyValue(df, sFileName, "Part Name");
    std::cout << ">> Loading... " << m_sPartName << '\n';
    m_nCategoryID =
        std::stoi(df.get_propertyValue(df, sFileName, "Category ID"));
    m_nPartID = std::stoi(df.get_propertyValue(df, sFileName, "ID"));
    m_sPartCategory = df.get_propertyValue(df, sFileName, "Category");
    m_nPartCost = std::stoi(df.get_propertyValue(df, sFileName, "Cost"));
    m_nPartWeight = std::stoi(df.get_propertyValue(df, sFileName, "Weight"));
    m_nEnLoad = std::stoi(df.get_propertyValue(df, sFileName, "EN Load"));
    m_sManufacturer = df.get_propertyValue(df, sFileName, "Manufacturer");
    m_bIsEquipped = 0;
  }

  virtual int get_AttackPower() const { return m_nAttackPower; }
  virtual int get_Impact() const { return m_nImpact; }
  virtual int get_TotalRounds() const { return m_nTotalRounds; }
  virtual int get_AP() const { return m_nArmorPoints; }
  virtual int get_Kin() const { return m_nKineticDefense; }
  virtual int get_En() const { return m_nEnergyDefense; }
  virtual int get_Exp() const { return m_nExplosiveDefense; }

  std::string get_name() {
    std::string s_temp = (this == nullptr) ? "<EMPTY>\n" : m_sPartName;
    return s_temp;
  }
  std::uint32_t get_id() { return m_nPartID; }
  int get_cost() { return m_nPartCost; }
  int get_weight() { return m_nPartWeight; }
  int get_enload() { return m_nEnLoad; }
  std::string get_manu() { return m_sManufacturer; }
  int get_type() { return m_nCategoryID; }
  std::string get_category() { return m_sPartCategory; }

protected:
  std::uint32_t m_nPartID{};
  static inline std::uint32_t m_nIdGenerator{0};
  std::string m_sPartName{};
  int m_nCategoryID{};
  std::string m_sPartCategory{};
  int m_nPartCost, m_nPartWeight, m_nEnLoad{};
  std::string m_sManufacturer{};
  bool m_bIsEquipped{};

  // == only used to be overridden ==
  int m_nAttackPower, m_nImpact, m_nTotalRounds{};
  bool m_bIsMelee{};

  int m_nArmorPoints{};
  int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense{};
};

class WeaponUnit : public Part {
  // Everything that is a weapon (arm units & back units)
public:
  int m_nAttackPower, m_nImpact, m_nTotalRounds{};
  bool m_bIsMelee{};

  WeaponUnit() = default;

  WeaponUnit(int ap, int impact, int total_rounds, bool is_melee, int category,
             std::string name, int cost, int weight, int en_load,
             std::string manufacturer, bool is_equipped = false)
      : Part(category, name, cost, weight, en_load, manufacturer, is_equipped),
        m_nAttackPower(ap), m_nImpact(impact), m_nTotalRounds(total_rounds),
        m_bIsMelee(is_melee) {}

  void display_stats() const override {
    Part::display_stats();
    if (Part::m_nCategoryID == L_ARM_UNIT && m_bIsMelee == true)
      std::cout << ">> ATK Power: " << m_nAttackPower
                << "\n>> Impact: " << m_nImpact << '\n';
    else
      std::cout << ">> ATK Power: " << m_nAttackPower
                << "\n>> Impact: " << m_nImpact
                << "\n>> Total Rounds: " << m_nTotalRounds << '\n';
  }

  void save(Datafile &df) override {
    std::cout << ">> Saved weapon unit. ";
    Part::save(df);
    // constitutes as arm or back unit
    df[this->get_name()][this->get_category()]["Attack Power"].set_int(
        this->get_AttackPower());
    df[this->get_name()][this->get_category()]["Impact"].set_int(
        this->get_Impact());
    df[this->get_name()][this->get_category()]["Total Rounds"].set_int(
        this->get_TotalRounds());
  }

  void load(Datafile &df, const std::string &sFileName) override {
    Part::load(df, sFileName);
    m_nAttackPower =
        std::stoi(df.get_propertyValue(df, sFileName, "Attack Power"));
    m_nImpact = std::stoi(df.get_propertyValue(df, sFileName, "Impact"));
    m_nTotalRounds =
        std::stoi(df.get_propertyValue(df, sFileName, "Total Rounds"));
    m_bIsMelee = 0;
  }

  int get_AttackPower() const override { return m_nAttackPower; }
  int get_Impact() const override { return m_nImpact; }
  int get_TotalRounds() const override { return m_nTotalRounds; }
};

class FramePart : public Part {
  // everything that is part of the AC body (Head,Core,Arms,Legs)
public:
  int m_nArmorPoints{};
  int m_nKineticDefense, m_nEnergyDefense, m_nExplosiveDefense{};

  FramePart() = default;

  FramePart(int ap, int kin_def, int en_def, int exp_def, int category,
            std::string name, int cost, int weight, int en_load,
            std::string manufacturer, bool is_equipped = false)
      : Part(category, name, cost, weight, en_load, manufacturer, is_equipped),
        m_nArmorPoints(ap), m_nKineticDefense(kin_def),
        m_nEnergyDefense(en_def), m_nExplosiveDefense(exp_def) {}

  void display_stats() const override {
    Part::display_stats();
    std::cout << ">> Armor Points: " << m_nArmorPoints
              << "\n>> Kinetic Defense: " << m_nKineticDefense
              << "\n>> Energy Defense: " << m_nEnergyDefense
              << "\n>> Explosive Defense: " << m_nExplosiveDefense << '\n';
  }

  void save(Datafile &df) override {
    Part::save(df);
    df[this->get_name()][this->get_category()]["Armor Points"].set_int(
        this->get_AP());
    df[this->get_name()][this->get_category()]["Kinetic Defense"].set_int(
        this->get_Kin());
    df[this->get_name()][this->get_category()]["Energy Defense"].set_int(
        this->get_En());
    df[this->get_name()][this->get_category()]["Explosive Defense"].set_int(
        this->get_Exp());
  }

  void load(Datafile &df, const std::string &sFileName) override {
    Part::load(df, sFileName);
    m_nArmorPoints =
        std::stoi(df.get_propertyValue(df, sFileName, "Armor Points"));
    m_nKineticDefense =
        std::stoi(df.get_propertyValue(df, sFileName, "Kinetic Defense"));
    m_nEnergyDefense =
        std::stoi(df.get_propertyValue(df, sFileName, "Energy Defense"));
    m_nExplosiveDefense =
        std::stoi(df.get_propertyValue(df, sFileName, "Explosive Defense"));
  }

  int get_AP() const override { return m_nArmorPoints; }
  int get_Kin() const override { return m_nKineticDefense; }
  int get_En() const override { return m_nEnergyDefense; }
  int get_Exp() const override { return m_nExplosiveDefense; }
};

// == TODO: later, just implement the last of the more specific classes for
// inner parts

class Booster : public Part {
  // booster class made separately
public:
  int m_nThrust, m_nUpThrust, m_nQbThrust{};
  float m_fQbReload{};

  Booster() = default;

  Booster(int thrust, int up_thrust, int qb_thrust, float qb_reload,
          int category, std::string name, int cost, int weight, int en_load,
          std::string manufacturer, bool is_equipped = false)
      : Part(category, name, cost, weight, en_load, manufacturer, is_equipped),
        m_nThrust(thrust), m_nUpThrust(up_thrust), m_nQbThrust(qb_thrust),
        m_fQbReload(qb_reload) {}

  void display_stats() const override {
    Part::display_stats();
    std::cout << ">> Thrust: " << m_nThrust
              << "\n>> Upward Thrust: " << m_nUpThrust
              << "\n QB Thrust: " << m_nQbThrust
              << "\n QB Reload time: " << m_fQbReload << "s \n";
  }

  void save(Datafile &df) override {
    Part::save(df);
    df[this->get_name()][this->get_category()]["Thrust"].set_int(
        this->get_Thrust());
    df[this->get_name()][this->get_category()]["Up Thrust"].set_int(
        this->get_UpThrust());
    df[this->get_name()][this->get_category()]["QB Thrust"].set_int(
        this->get_QbThrust());
    df[this->get_name()][this->get_category()]["QB Reload Time"].set_real(
        this->get_QbReload());
  }

  void load(Datafile &df, const std::string &sFileName) override {
    Part::load(df, sFileName);
    m_nThrust = std::stoi(df.get_propertyValue(df, sFileName, "Thrust"));
    m_nUpThrust = std::stoi(df.get_propertyValue(df, sFileName, "Up Thrust"));
    m_nQbThrust = std::stoi(df.get_propertyValue(df, sFileName, "QB Thrust"));
    m_fQbReload =
        std::stof(df.get_propertyValue(df, sFileName, "QB Reload Time"));
  }

  int get_Thrust() const { return m_nThrust; }
  int get_UpThrust() const { return m_nUpThrust; }
  int get_QbThrust() const { return m_nQbThrust; }
  float get_QbReload() const { return m_fQbReload; }
};

class FCS : public Part {};

class Generator : public Part {};

#endif // !ACPARTS_H
