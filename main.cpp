#include <iostream>
#include "ac_items.h"
#include "ac_frame.h"
#include "inventory.h"


int main()
{
  // WeaponUnit(Category,ATK,Impact,Total Rounds,IsMelee,Name,Cost,Weight,EN Load,Manufacturer,IsEquipped)
  WeaponUnit rwu1{105,65,540,0,R_ARM_UNIT,"RF-024 TURNER",55000,3560,102,"Balam Industries",0};
  WeaponUnit rwu3{900,840,53,0,R_ARM_UNIT,"SG-027 ZIMMERMAN",115000,4400,242,"Balam Industries",0};

  WeaponUnit lwu1{1615,900,0,1,L_ARM_UNIT,"VVC-774LS",339000,3260,328,"VCPL",0};
  WeaponUnit lwu3{105,65,540,0,L_ARM_UNIT,"RF-024 TURNER",55000,3560,102,"Balam Industries",0};

  WeaponUnit rwu2{1058,807,30,0,R_BACK_UNIT,"VE-60SNA",283000,6150,826,"Arquebus ADD",0};
  WeaponUnit lwu2{103*6,72*6,228,0,L_BACK_UNIT,"BML-G2/P03MLT-06",111000,3840,241,"Furlong Dynamics",0};
  // FramePart()
  FramePart hfp1{770,174,167,181,HEAD,"HC-2000/BC SHADE EYE",147000,3090,163,"RaD",0};
  FramePart cfp1{2850,370,370,370,CORE,"EL-PC-00 ALBA",531000,12000,315,"Elcano",0};
  FramePart afp1{1860,1860,204,195,ARMS,"NACHTREIHER/46E",138000,11420,302,"Schneider",0};
  FramePart lfp1{3500,295,330,298,LEGS,"NACHTREIHER/42E",243000,14030,462,"Schneider",0};

  FramePart bfp1{0,0,0,0,BOOSTER,"ALULA/21E",60000,1900,410,"Schneider",0};
  FramePart ffp1{0,0,0,0,FCS,"FC-006 ABBOT",135000,90,266,"Balam Industries",0};
  FramePart gfp1{0,0,0,0,GENERATOR,"VP-20S",126000,3800,0,"Schneider ADD",0};
  FramePart efp1{0,0,0,0,EXPANSION,"ASSAULT ARMOR",0,0,0,"Allmind",0};
  
  Inventory c_Inventory;
  //c_Inventory.add_part(&rwu1);
  c_Inventory.add_part(&rwu3);
  c_Inventory.add_part(&rwu2);
  c_Inventory.add_part(&lwu1);
  c_Inventory.add_part(&lwu3);
  c_Inventory.add_part(&lwu2);

  std::cout << ">> INVENTORY: \n";
  c_Inventory.display_inventory();

  AC mech_1{&rwu1,&lwu1,&rwu2,&lwu2,&hfp1,&cfp1,&afp1,&lfp1,&bfp1,&ffp1,&gfp1,&efp1};
  mech_1.m_PlayerInventory = &c_Inventory;
  mech_1.display_mech();

  mech_1.add_part();
  
  mech_1.display_mech();
  std::cout << ">> INVENTORY: \n";

  c_Inventory.display_inventory();
  return 0;
}
