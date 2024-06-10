#pragma once
#include "ac_parts.h"
#ifndef PLAYER_H
#define PLAYER_H

#include "ac_frame.h"
#include "ac_datafile.h"
class AC;
class Datafile;

std::string getPlayerInput(const std::string& message)
{
  std::string sInput;
  while(true)
  {
    std::cout << message;
    std::getline(std::cin, sInput);

    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << ">> ERROR: Invalid input, please try again." << std::endl;
    }
    else
      break;   
  }
  return sInput;
}

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
    std::string sDirName = getPlayerInput(">> Enter the file name where to save your AC desing: ");

    // first erase all files to overwrite if files already present in directory
    if(std::filesystem::exists(sDirName))
    {
      for(const auto& entry : std::filesystem::directory_iterator(sDirName))
      {
        if(std::filesystem::is_regular_file(entry.status()))
        {
          std::filesystem::remove(entry.path());
          std::cout << ">> Erased: " << entry.path() << std::endl;
        }
      }
    }
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
      std::cout << "Saved part:" << part->get_name() << '\n';
      part->save(df); 
      std::string temp_fileName = part->get_name() + ".dat"; // new file for each part
      std::cout << ">> File created: " << temp_fileName << std::endl;
      std::string sFilePath = sDirName + "/" + temp_fileName;
      df.write_to_file(df,sFilePath);
    }
  }


  void load_mech_data(Datafile &df, const std::string& sFileName)
  {
    int nTempID;
    Datafile::read_from_file(df,sFileName);
    nTempID = std::stoi(df.get_propertyValue(df,sFileName, "Category ID"));
    std::cout << ">> Category ID: " << nTempID << std::endl;
    switch(nTempID)
    {
      case 0:
      {
        Part* tempPart = m_cPlayerAC->m_rArmUnit;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 1:
      {
        Part* tempPart = m_cPlayerAC->m_lArmUnit;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 2:
      {
        Part* tempPart = m_cPlayerAC->m_rBackUnit;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 3:
      {
        Part* tempPart = m_cPlayerAC->m_lBackUnit;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 4:
      {
        Part* tempPart = m_cPlayerAC->m_Head;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 5:
      {
        Part* tempPart = m_cPlayerAC->m_Arms;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 6:
      {
        Part* tempPart = m_cPlayerAC->m_Core;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 7:
      {
        Part* tempPart = m_cPlayerAC->m_Legs;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 8:
      {
        Part* tempPart = m_cPlayerAC->m_Booster;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 9:
      {
        Part* tempPart = m_cPlayerAC->m_FCS;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 10:
      {
        Part* tempPart = m_cPlayerAC->m_Generator;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
      case 11:
      {
        Part* tempPart = m_cPlayerAC->m_Expansion;
        tempPart->load(df,sFileName);
        m_cPlayerAC->m_vPACParts[tempPart->get_id()] = tempPart;
        break;
      }
    }
  }


  void read_mech_data(Datafile &df)
  {
    std::string sDirName = getPlayerInput(">> Enter the name of the save file: ");
    if(!std::filesystem::exists(sDirName))
    {
      std::cerr << ">> ERROR: Could not locate directory: " << sDirName << std::endl;
      return;
    }

    for(const auto& entry : std::filesystem::directory_iterator(sDirName))
    {
      if(std::filesystem::is_regular_file(entry.status()))
      {
        std::string tempFileName = entry.path();
        std::cout << ">> Found file:" << tempFileName << std::endl;
        load_mech_data(df, tempFileName);
      }
    }

  }


  private:
    std::string m_sPlayerName {};
    AC *m_cPlayerAC {};
    int m_nPlayerCredits {};
};

#endif // !PLAYER_H
