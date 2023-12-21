#pragma once
#ifndef DATAFILE_H
#define DATAFILE_H

#include <string>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <stack>
#include "ac_parts.h"

class Part;

class Datafile
{
  public:

    inline void set_string(const std::string& s_string, std::size_t n_part = 0)
    {
      // sets string value of property for the given index
      if(n_part >= m_vContent.size())
        m_vContent.resize(n_part + 1);
      m_vContent[n_part] = s_string;
    }

    inline const std::string get_string(const std::size_t n_part = 0) const
    {
      // retrieves string value of property (for a given index)
      if(n_part >= m_vContent.size())
        return "";
      else
        return m_vContent[n_part];
    }

    // == setters & getters (for all sorts of other data types) ==
    inline void set_real(const float f, const std::size_t n_part = 0)
    {
      set_string(std::to_string(f),n_part);
    }

    inline const float get_real(std::size_t n_part = 0)
    {
      return std::atof(get_string(n_part).c_str());
    }

    inline void set_int(const int n, const std::size_t n_part = 0)
    {
      set_string(std::to_string(n),n_part);
    }

    inline const int get_int(std::size_t n_part = 0)
    {
      return std::atoi(get_string(n_part).c_str());
    }

    inline std::size_t get_size() const {return m_vContent.size();}

    inline Datafile& operator[](const std::string& name)
    {
      // we check if node's map already contains the object with the given name
      if(m_mapObjects.count(name) == 0)
      {
        // if does not exist: create the object in map, then link the vector's index with the object name
        m_mapObjects[name] = m_vecObjects.size();
        // initialize empty object of type Datafile in the vector of objects, with the assigned name
        m_vecObjects.push_back({name, Datafile()});
      }
      // if exists: return the object by fetching its index from the map
      // then we use this fetched index to look up the element in the vector of objects
      // we return Datafile from the vector of objects (m_vecObjects)
      return m_vecObjects[m_mapObjects[name]].second;
    }
    
    /* data file format for parts in this project:
       "m_sPartName"
       {
        "ID" = m_nPartId
        "CategoryID" = m_nCategoryID
        "Cost" ...
        "Weight" ...
        "Etc."
        "m_sPartCategory"
        {
          Depending on the part category, add specific data fields in child node here
        }

       }
    */
    
    // == Writing to file ==
    inline static bool write_to_file(const Datafile& n, const std::string& sFileName,
        const std::string& sIndent = "\t")
    {
      std::size_t nIndentCount = 0; // tracks level of indentation in output

      // lambda function to let datafile write itself recursively
      std::function<void (const Datafile&, std::ofstream&)> write =
      [&](const Datafile& n, std::ofstream& file)
      {
        auto indent = [&](const std::string& sString, const std::size_t nCount)
        {
          // adds indents (tab spaces) to a string and returns it (for formatting purposes)
          std::string sOut;
          for(std::size_t n{0}; n < nCount; n++)
            sOut += sString;
          return sOut;
        };

        // iterate through each property in the node: (m_vecObjects = {string, datafile})
        for(auto const& property : n.m_vecObjects)
        {
          // check if property contains any sub properties
          if(property.second.m_vecObjects.empty())
          {
            // if it doesn't then: example: "PartID"(property.first()) = 5 
            file << indent(sIndent, nIndentCount) << property.first << " = ";
            std::size_t n_parts = property.second.get_size();
            for(std::size_t i{0}; i < n_parts; i++)
            {
              // not necessary but iterate through each value of property and add it to file
              file << property.second.get_string(i);
            }
            file << '\n';
          }
          else
          {
            file << indent(sIndent, nIndentCount) << property.first << '\n';
            // open braces to accomodate children and indent (for formatting)
            file << indent(sIndent, nIndentCount) << "{\n";
            nIndentCount ++;
            // write out node recursively
            write(property.second, file);
            file << indent(sIndent, nIndentCount) << "}\n\n";
          }
        }
        if(nIndentCount > 0)
          nIndentCount -- ;
      };

      std::ofstream file(sFileName);
      if(file.is_open())
      {
        write(n,file);
        return true;
      }
      return false; // could not open file or write to file
    }
    
    // == Reading from file ==
    inline static bool read_from_file(Datafile& n, const std::string& sFileName)
    {
      std::ifstream file(sFileName);
      if(file.is_open())
      {
        std::string sPropertyName = "";
        std::string sPropertyValue = "";
        // once code encounters: "{"; place property on stack to parse all of its children's data
        std::stack<std::reference_wrapper<Datafile>> stkPath;
        stkPath.push(n); // default property name (the actual name of the part)

        while(!file.eof())
        {
          // read line by line
          std::string line;
          std::getline(file, line);
          // lambda to trim whitespace from each line
          auto trim = [](std::string& s)
          {
            s.erase(0,s.find_first_not_of(" \t\n\r\f\v")); // erase portion of string from index zero to the specified 
            s.erase(s.find_last_not_of(" \t\n\r\f\v")+1);        
          };
          
          trim(line);


          if(!line.empty())
          {
            // if line contains the assignment symbol "=", then we have a property
            std::size_t x = line.find_first_of('=');
            if(x != std::string::npos)
            {
              // grab the property name at the beginning of the line...
              sPropertyName = line.substr(0,x);
              trim(sPropertyName);
              // grab the property value +1 index pos after assignment symbol
              sPropertyValue = line.substr(x+1,line.size());
              trim(sPropertyValue);

              if(line[0] == '{')
              {
                // if code encounters '{', we are pushing the node to stack
                stkPath.push(stkPath.top().get()[sPropertyName]);
              }
              else
              {
                if(line[0] == '}')
                {
                  // pop node from the stack since all of it's children's content has been read
                  stkPath.pop();
                }
                else
                {
                  // once the code will encounter a simple name in the file (property name)
                  sPropertyName = line;
                }
              }
            }
          }
        }

      }
    }

    inline std::string get_propertyValue(Datafile& n, const std::string& sFileName, const std::string& s_name)
    {
      std::ifstream file(sFileName);
      if(file.is_open())
      {
        std::string sPropertyName = "";
        std::string sPropertyValue = "";
        // once code encounters: "{"; place property on stack to parse all of its children's data
        std::stack<std::reference_wrapper<Datafile>> stkPath;
        stkPath.push(n); // default property name (the actual name of the part)

        while(!file.eof())
        {
          // read line by line
          std::string line;
          std::getline(file, line);
          // lambda to trim whitespace from each line
          auto trim = [](std::string& s)
          {
            s.erase(0,s.find_first_not_of(" \t\n\r\f\v")); // erase portion of string from index zero to the specified 
            s.erase(s.find_last_not_of(" \t\n\r\f\v")+1);        
          };
          
          trim(line);


          if(!line.empty())
          {
            // if line contains the assignment symbol "=", then we have a property
            std::size_t x = line.find_first_of('=');
            if(x != std::string::npos)
            {
              // grab the property name at the beginning of the line...
              sPropertyName = line.substr(0,x);
              trim(sPropertyName);
              if(sPropertyName == s_name)
              {
                // grab the property value +1 index pos after assignment symbol
                sPropertyValue = line.substr(x+1,line.size());
                trim(sPropertyValue);
                std::cout << ">>Part Name: " <<  sPropertyValue << '\n';
                return sPropertyValue;
              }  



              if(line[0] == '{')
              {
                // if code encounters '{', we are pushing the node to stack
                stkPath.push(stkPath.top().get()[sPropertyName]);
              }
              else
              {
                if(line[0] == '}')
                {
                  // pop node from the stack since all of it's children's content has been read
                  stkPath.pop();
                }
                else
                {
                  // once the code will encounter a simple name in the file (property name)
                  sPropertyName = line;
                }
              }
            }
          }
        }

      }
    }


  private:
    // list of strings that makes up the property value
    std::vector<std::string> m_vContent {};
    //
    std::vector<std::pair<std::string, Datafile>> m_vecObjects {};
    std::unordered_map<std::string, std::size_t> m_mapObjects {};
};

#endif // !DATAFILE_H
