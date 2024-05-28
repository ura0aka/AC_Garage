#include <iostream>
#include <fstream>

void readRandFile(const std::string& sFileName)
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
        std::cout << line << std::endl;
      }
    }
}


int main()
{
  readRandFile("AC_saveFile/HC-2000 FINDER EYE.dat");
  return 0;
}