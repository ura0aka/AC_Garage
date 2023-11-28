#pragma once
#include "ac_parts.h"
#ifndef PLAYER_H
#define PLAYER_H

#include "ac_frame.h"
#include "ac_datafile.h"
class AC;
class Datafile;

class Player
{
  public: 
    Player() = default;
    
    Player(AC &mech_build, int credits)
      : m_cPlayerAC{&mech_build}, m_nPlayerCredits{credits}
    {}
  
  void player_display_mech()
  {
    m_cPlayerAC->display_mech();
  }

  void player_display_stats()
  {
    std::cout << ">> Player: " << m_sPlayerName << "\n>> Credits: " << m_nPlayerCredits << '\n';
  }

  void save_mech_data(Datafile &df)
  {
    for(const auto& part : m_cPlayerAC->m_vPACParts)
    {
      if(part == nullptr)
      {
        std::cout << "< Empty, skipping...  >\n";
        continue;
      }
      df[part->get_name()]["ID"].set_int(part->get_id());
      df[part->get_name()]["Part Name"].set_string(part->get_name());
      df[part->get_name()]["Category"].set_string(part->get_category());
      df[part->get_name()]["Weight"].set_int(part->get_weight());
      df[part->get_name()]["Cost"].set_int(part->get_cost());
      df[part->get_name()]["EN Load"].set_int(part->get_enload());
      df[part->get_name()]["Manufacturer"].set_string(part->get_manu());
      if(part->get_type() <= 3)
      {
        // constitutes as arm or back unit
        df[part->get_name()][part->get_category()]["Attack Power"].set_int(part->get_AttackPower());
        df[part->get_name()][part->get_category()]["Impact"].set_int(part->get_Impact());
        df[part->get_name()][part->get_category()]["Total Rounds"].set_int(part->get_TotalRounds());
      }
      if(part->get_type() <= 11 && part->get_type() > 3 )
      {
        // constitutes as all frame parts (head,core,arms,legs)
        df[part->get_name()][part->get_category()]["Armor Points"].set_int(part->get_AP());
        df[part->get_name()][part->get_category()]["Kinetic Defense"].set_int(part->get_Kin());
        df[part->get_name()][part->get_category()]["Energy Defense"].set_int(part->get_En());
        df[part->get_name()][part->get_category()]["Explosive Defense"].set_int(part->get_Exp());
      }
      std::cout << "Saved part:" << part->get_name() << '\n';

    }
    df.write_to_file(df, "AC_saveFile.dat");
  }

  private:
    std::string m_sPlayerName {};
    AC *m_cPlayerAC {};
    int m_nPlayerCredits {};
};

#endif // !PLAYER_H
