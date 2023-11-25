#pragma once
#ifndef ACCONTAINER_H
#define ACCONTAINER_H

#include <map>
#include <string>
#include "ac_parts.h"
class Part;

class Container
{
  public:
    std::map<std::string,Part> m_cMapParts {}; // part ID will point to the part object stored in the map

    Container() = default;

    void add_part(Part& part)
    {
      m_cMapParts[std::to_string(part.get_id())] = part;
    }
    
    void display_parts()
    {
      for(std::size_t i{1}; i != m_cMapParts.size(); ++i)
      {
        std::cout << m_cMapParts[std::to_string(i)].get_name();
      }
    }

    std::map<std::string,Part> get_map() {return m_cMapParts;}
};

#endif // !ACCONTAINER_H
