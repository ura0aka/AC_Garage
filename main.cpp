#include <iostream>
#include "ac_parts.h"
#include "ac_frame.h"
#include "inventory.h"


int main()
{
  // WeaponUnit(Category,ATK,Impact,Total Rounds,IsMelee,Name,Cost,Weight,EN Load,Manufacturer,IsEquipped)

  // ARM UNITS
  WeaponUnit rwu1{105,65,540,0,R_ARM_UNIT,"RF-024 TURNER",55000,3560,102,"Balam Industries",0};
  WeaponUnit rwu3{900,840,53,0,R_ARM_UNIT,"SG-027 ZIMMERMAN",115000,4400,242,"Balam Industries",0};
  WeaponUnit rwu4{42,41,720,0,R_ARM_UNIT,"MG-014 LUDLOW",45000,2450,82,"Balam Industries",0};
  WeaponUnit lwu1{1615,900,0,1,L_ARM_UNIT,"VVC-774LS",339000,3260,328,"VCPL",0};
  WeaponUnit lwu3{105,65,540,0,L_ARM_UNIT,"RF-024 TURNER",55000,3560,102,"Balam Industries",0};
  WeaponUnit lwu4{42,41,720,0,L_ARM_UNIT,"MG-014 LUDLOW",45000,2450,82,"Balam Industries",0};
  WeaponUnit lwu6{900,840,53,0,L_ARM_UNIT,"SG-027 ZIMMERMAN",115000,4400,242,"Balam Industries",0};

  // BACK UNITS
  WeaponUnit rwu2{1058,807,30,0,R_BACK_UNIT,"VE-60SNA",283000,6150,826,"Arquebus ADD",0};
  WeaponUnit rwu6{244*6,150*2,124,0,R_BACK_UNIT,"BML-G1/P31DUO-02",144000,1900,182,"Furlong Dynamics",0};
  WeaponUnit rwu5{103*6,72*6,228,0,R_BACK_UNIT,"BML-G2/P03MLT-06",111000,3840,241,"Furlong Dynamics",0};
  WeaponUnit lwu5{1058,807,30,0,L_BACK_UNIT,"VE-60SNA",283000,6150,826,"Arquebus ADD",0};
  WeaponUnit lwu2{103*6,72*6,228,0,L_BACK_UNIT,"BML-G2/P03MLT-06",111000,3840,241,"Furlong Dynamics",0};
  // FramePart()
  FramePart hfp1{770,174,167,181,HEAD,"HC-2000/BC SHADE EYE",147000,3090,163,"RaD",0};
  FramePart hfp2{660,157,142,152,HEAD,"HC-2000 FINDER EYE",0,2670,125,"RaD",0};
  FramePart cfp2{2780,393,366,374,CORE,"CC-2000 ORBITER",0,12650,267,"RaD",0};
  FramePart cfp1{2850,370,370,370,CORE,"EL-PC-00 ALBA",531000,12000,315,"Elcano",0};
  FramePart afp1{1860,1860,204,195,ARMS,"NACHTREIHER/46E",138000,11420,302,"Schneider",0};
  FramePart afp2{1990,207,204,209,ARMS,"AC-2000 TOOL ARM",0,11300,216,"RaD",0};
  FramePart lfp1{3500,295,330,298,LEGS,"NACHTREIHER/42E",243000,14030,462,"Schneider",0};
  FramePart lfp2{3650,326,322,337,LEGS,"2C-2000 CRAWLER",0,16300,280,"RaD",0};

  FramePart bfp1{0,0,0,0,BOOSTER,"ALULA/21E",60000,1900,410,"Schneider",0};
  FramePart bfp2{0,0,0,0,BOOSTER,"BST-G1/P10",0,1300,130,"Furlong Dynamics",0};
  FramePart ffp1{0,0,0,0,FCS,"FC-006 ABBOT",135000,90,266,"Balam Industries",0};
  FramePart ffp2{0,0,0,0,FCS,"FCS-G1/P01",0,80,198,"Furlong Dynamics",0};
  FramePart gfp1{0,0,0,0,GENERATOR,"VP-20S",126000,3800,0,"Schneider ADD",0};
  FramePart gfp2{0,0,0,0,GENERATOR,"AG-J-098 JOSO",0,3420,2600,"BAWS",0};
  FramePart efp1{0,0,0,0,EXPANSION,"ASSAULT ARMOR",0,0,0,"-",0};
  
  Inventory c_Inventory;
  c_Inventory.add_part(&rwu3);
  c_Inventory.add_part(&lwu3);
  c_Inventory.add_part(&rwu4);
  c_Inventory.add_part(&lwu4);
  c_Inventory.add_part(&rwu6);
  c_Inventory.add_part(&lwu6);
  c_Inventory.add_part(&rwu5);
  c_Inventory.add_part(&lwu5);

  c_Inventory.add_part(&hfp1);
  c_Inventory.add_part(&cfp1);
  c_Inventory.add_part(&afp1);
  c_Inventory.add_part(&lfp1);
  c_Inventory.add_part(&bfp1);
  c_Inventory.add_part(&ffp1);
  c_Inventory.add_part(&gfp1);
  c_Inventory.add_part(&efp1);

  std::cout << ">> INVENTORY: \n"; 
  c_Inventory.display_inventory();

  AC mech_1{&rwu1,&lwu1,&rwu2,&lwu2,&hfp2,&cfp2,&afp2,&lfp2,&bfp2,&ffp2,&gfp2,nullptr}; // default AC
  mech_1.m_PlayerInventory = &c_Inventory;
  mech_1.display_mech();

  mech_1.add_part();
  
  mech_1.display_mech();
  std::cout << ">> INVENTORY: \n";
  c_Inventory.display_inventory();
  return 0;
}
