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
  
  void save_mech_data()
  {
    // create directory to store each individual part for the AC
    std::string sDirName = "AC_saveFile";
    if(!std::filesystem::exists(sDirName))
    {
      if(std::filesystem::create_directory(sDirName))
        std::cout << ">> Save file directory created." << std::endl;
      else
      {
        std::cerr << ">> ERROR: Failed to create directory." << std::endl;
      }
    }

    for(auto bIter = m_cPlayerAC->m_vPACParts.begin(); bIter != m_cPlayerAC->m_vPACParts.end(); ++bIter)
    {
      Datafile df;
      const auto& part = bIter->second;
      if(part == nullptr)
      {
        std::cout << "<Empty>...Skipping\n";
        continue;
      }
      part->save(df); 
      std::cout << "Saved part:" << part->get_name() << '\n';
      std::string temp_fileName = part->get_name() + ".dat"; // new file for each part
      std::string sFilePath = sDirName + "/" + temp_fileName;
      df.write_to_file(df,sFilePath);
    }
  }


  int countLeadingTabs(const std::string& line)
  {
    int nCount = 0;
    for(char c : line)
    {
      if(c == '\t')
        nCount ++;
      else
        break;
    }
    return nCount;
  }

  void read_file(const std::string& sFileName)
  {
    std::ifstream file(sFileName);
    if(!file)
    {
      std::cerr << ">> ERROR: Unable to open file" << std::endl;
      return;
    }

    if(file.is_open())
    {
      while(!file.eof())
      {
        std::string line;
        std::getline(file, line);
        int nTabs = countLeadingTabs(line);
        std::cout << "Leading tabs: " << nTabs << std::endl;
        if(nTabs == 0)
        {
          // check if it's a part name or a bracket
          if(line != "{" || line != "}")
          {
            std::cout << ">> Found: " << line << std::endl;
            // -- separate into multiple files --
          }
        }
      }
    }
  }


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
