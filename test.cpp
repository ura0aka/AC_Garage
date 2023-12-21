#include <iostream>

class Parent
{
  public:
    void sleep()
    {
      std::cout << "Sleep \n";
    }
};

class Child : public Parent
{
  public:
    void school()
    {
      std::cout << "School \n";
    }
};

int main()
{
  Parent *pParent = new Parent;
  Child *pChild = new Child;

  Child *p1 = (Child*) pParent; // not safe, assigns address of base class object to derived class
  Parent *p2 = (Parent*) pChild; // safe

  Parent *p = dynamic_cast<Parent*>(pChild);




}
