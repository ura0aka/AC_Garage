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
    for(auto bIter = m_cPlayerAC->m_vPACParts.begin(); bIter != m_cPlayerAC->m_vPACParts.end(); ++bIter)
    {
      const auto& part = bIter->second;
      if(part == nullptr)
      {
        std::cout << "<Empty>...Skipping\n";
        continue;
      }
      part->save(df); 
      std::cout << "Saved part:" << part->get_name() << '\n';
    }
    df.write_to_file(df, "AC_saveFile.dat");
  }

  // == old ahh code ==
  /*
  void save_mech_data(Datafile &df)
  {
    for(const auto& part : m_cPlayerAC->m_vPACParts)
    {
      if(part == nullptr)
      {
        std::cout << "<Empty>...Skipping\n";
        continue;
      }
      part->save(df);
      std::cout << "Saved part:" << part->get_name() << '\n';
    }
    df.write_to_file(df, "AC_saveFile.dat");
  }
  */

  void load_mech_data(Datafile &df, const std::string& sFileName)
  {
    m_cPlayerAC->m_vPACParts.erase(m_cPlayerAC->m_vPACParts.begin(),m_cPlayerAC->m_vPACParts.end());
    m_cPlayerAC->m_rArmUnit->load(df,sFileName);
  }

  private:
    std::string m_sPlayerName {};
    AC *m_cPlayerAC {};
    int m_nPlayerCredits {};
};

#endif // !PLAYER_H
