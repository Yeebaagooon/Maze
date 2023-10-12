rule Technologies
inactive
highFrequency
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		trTechSetStatus(p, 1, 4);
		trTechSetStatus(p, 2, 4);
		trTechSetStatus(p, 116, 4);
		trTechSetStatus(p, 29, 4);
		trTechSetStatus(p, 353, 4);
		trTechSetStatus(p, 394, 0);
		trTechSetStatus(p, 510, 0);
		trTechSetStatus(p, 145, 0);
		trTechSetStatus(p, 144, 0);
		trTechSetStatus(p, 143, 0);
		trTechSetStatus(p, 379, 0);
		trTechSetStatus(p, 304, 0);
		trTechSetStatus(p, 446, 0);
		trTechSetStatus(p, 28, 4);
		trTechSetStatus(p, 30, 4);
		trTechSetStatus(p, 350, 4);
		trTechSetStatus(p, 27, 4);
		trTechSetStatus(p, 126, 0);
		trTechSetStatus(p, 140, 0);
		trTechSetStatus(p, 127, 0); // stone wall
		trTechSetStatus(p, 411, 0); // bronze wall
		trTechSetStatus(p, 412, 0); // iron wall
		trTechSetStatus(p, 413, 0); // orimakalous wall
		for(n=930; >0) {
			trForbidProtounit(p,kbGetProtoUnitName(n));
		}
		trUnforbidProtounit(p, "Tower");
		trUnforbidProtounit(p, "Sky Passage");
		trUnforbidProtounit(p, "Gate");
		trUnforbidProtounit(p, "Wall Connector");
		trUnforbidProtounit(p, "Wall Short");
		trUnforbidProtounit(p, "Wall Medium");
		trUnforbidProtounit(p, "Wall Long");
	}
	trRateTrain(10);
	//  trUnforbidProtounit(1*p, "Maceman Hero");
	xsDisableSelf();
}

void MakeUnitFree(string unit = "", int p = 0){
	for(a = 16; < 20){
		modifyProtounitAbsolute(unit, p, a, 0);
		modifyProtounitAbsolute(unit, p, 6, 0);
	}
}

void ZeroArmour(string unit = "", int p = 0){
	for(a = 24; < 27){
		modifyProtounitAbsolute(unit, p, a, 0);
	}
}

void HunterUnit(string unit = "", int p = 0, int pop = 1){
	for(a = 16; < 20){
		modifyProtounitAbsolute(unit, p, a, 0);
		modifyProtounitAbsolute(unit, p, 6, pop);
	}
}

void SetBuildPoints(int a = 10){
	for(p = 1; <= cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		xSetFloat(dPlayerData, xTowerBuild, a/3);
		modifyProtounitAbsolute("Tower", p, 4, a/3);
		modifyProtounitAbsolute("Gate", p, 4, a/5);
		modifyProtounitAbsolute("Wall Connector", p, 4, a/5);
		modifyProtounitAbsolute("Wall Short", p, 4, a/5);
		modifyProtounitAbsolute("Wall Medium", p, 4, a/5);
		modifyProtounitAbsolute("Wall Long", p, 4, a/5);
		modifyProtounitAbsolute("Sky Passage", p, 4, a);
	}
}

void SetBuildPointsPlayer(int a = 10, int p =0){
	modifyProtounitAbsolute("Tower", p, 4, a/3);
	modifyProtounitAbsolute("Gate", p, 4, a/5);
	modifyProtounitAbsolute("Wall Connector", p, 4, a/5);
	modifyProtounitAbsolute("Wall Short", p, 4, a/5);
	modifyProtounitAbsolute("Wall Medium", p, 4, a/5);
	modifyProtounitAbsolute("Wall Long", p, 4, a/5);
	modifyProtounitAbsolute("Sky Passage", p, 4, a);
}

rule Stats
inactive
highFrequency
{
	trModifyProtounit("Dwarf", 0, 55, 4);
	modifyProtounitAbsolute("Tartarian Gate birth", 0, 8, 2.8);
	modifyProtounitAbsolute("Stymphalian Bird", 0, 2, 47);
	SetBuildPoints(10);
	for(p = 1; <= cNumberNonGaiaPlayers){
		modifyProtounitAbsolute("Old Man", p, 1, 10);
		modifyProtounitAbsolute("Huskarl", p, 8, 0.1);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 1, 5);
		modifyProtounitAbsolute("Villager Atlantean", p, 1, 5);
		modifyProtounitAbsolute("Cinematic Block", p, 2, 0);
		modifyProtounitAbsolute("Temple", p, 0, 1000000);
		modifyProtounitAbsolute("TUnnel", p, 0, 5000);
		modifyProtounitAbsolute("Temple", p, 4, 40);
		modifyProtounitAbsolute("Temple", p, 24, 1);
		modifyProtounitAbsolute("Temple", p, 25, 1);
		modifyProtounitAbsolute("Temple", p, 26, 1);
		modifyProtounitAbsolute("Maceman", p, 0, 9999999999999999999.0);
		modifyProtounitAbsolute("Maceman", p, 1, 0);
		modifyProtounitAbsolute("Maceman", p, 2, 0);
		modifyProtounitAbsolute("Maceman Hero", p, 0, 9999999999999999999.0);
		modifyProtounitAbsolute("Maceman Hero", p, 1, 0);
		modifyProtounitAbsolute("Maceman Hero", p, 2, 0);
		modifyProtounitAbsolute("Tower", p, 10, 1000);
		modifyProtounitAbsolute("Tower", p, 0, 500);
		modifyProtounitAbsolute("Behemoth", p, 0, 1500);
		modifyProtounitAbsolute("Heka Gigantes", p, 0, 2000);
		modifyProtounitAbsolute("Troll", p, 0, 1250);
		modifyProtounitAbsolute("Phoenix", p, 0, 1250);
		modifyProtounitAbsolute("Phoenix From Egg", p, 0, 1250);
		modifyProtounitAbsolute("Sphinx", p, 0, 700);
		modifyProtounitAbsolute("Wadjet", p, 0, 600);
		modifyProtounitAbsolute("Lampades", p, 0, 2500);
		modifyProtounitAbsolute("Lampades", p, 2, 30);
		modifyProtounitAbsolute("Lampades", p, 11, 24);
		modifyProtounitAbsolute("Behemoth", p, 29, 100);
		modifyProtounitAbsolute("Lampades", p, 32, 200);
		modifyProtounitAbsolute("Troll", p, 32, 50);
		modifyProtounitAbsolute("Satyr", p, 32, 10);
		modifyProtounitAbsolute("Wadjet", p, 32, 15);
		modifyProtounitAbsolute("Phoenix", p, 29, 250);
		modifyProtounitAbsolute("Phoenix", p, 32, 250);
		modifyProtounitAbsolute("Phoenix From Egg", p, 29, 250);
		modifyProtounitAbsolute("Phoenix From Egg", p, 32, 250);
		modifyProtounitAbsolute("Phoenix", p, 27, 200);
		modifyProtounitAbsolute("Phoenix", p, 30, 200);
		modifyProtounitAbsolute("Phoenix From Egg", p, 27, 200);
		modifyProtounitAbsolute("Phoenix From Egg", p, 30, 200);
		modifyProtounitAbsolute("Lightning Strike", p, 27, 0.0);
		modifyProtounitAbsolute("Lightning Strike", p, 28, 0.0);
		modifyProtounitAbsolute("Lightning Strike", p, 29, 0.0);
		modifyProtounitAbsolute("SPCMeteor", p, 27, 0.0);
		modifyProtounitAbsolute("SPCMeteor", p, 28, 0.0);
		modifyProtounitAbsolute("SPCMeteor", p, 29, 0.0);
		modifyProtounitAbsolute("Stymphalian Bird", p, 0, 1000000);
		modifyProtounitAbsolute("Stymphalian Bird", p, 1, 10);
		modifyProtounitAbsolute("Stymphalian Bird", p, 2, 47);
		modifyProtounitAbsolute("Stymphalian Bird", p, 11, 20);
		modifyProtounitAbsolute("Stymphalian Bird", p, 13, 0);
		modifyProtounitAbsolute("Raven", p, 0, 10000);
		modifyProtounitAbsolute("Raven", p, 1, 10);
		MakeUnitFree("Tower", p);
		MakeUnitFree("Troll", p);
		MakeUnitFree("Behemoth", p);
		MakeUnitFree("Sky Passage", p);
		MakeUnitFree("Gate", p);
		MakeUnitFree("Wall Connector", p);
		MakeUnitFree("Wall Short", p);
		MakeUnitFree("Wall Medium", p);
		MakeUnitFree("Wall Long", p);
		MakeUnitFree("Temple", p);
		MakeUnitFree("Maceman Hero", p);
		MakeUnitFree("Phoenix From Egg", p);
		MakeUnitFree("Heka Gigantes", p);
		MakeUnitFree("Phoenix", p);
		MakeUnitFree("Lampades", p);
		MakeUnitFree("Pegasus", p);
		HunterUnit("Scorpion Man", p, 1);
		HunterUnit("Centaur", p, 1);
		HunterUnit("Cyclops", p, 1);
		HunterUnit("Satyr", p, 1);
		HunterUnit("Battle Boar", p, 1);
		HunterUnit("Wadjet", p, 1);
		HunterUnit("Sphinx", p, 1);
		HunterUnit("Scarab", p, 1);
		HunterUnit("Phoenix", p, 3);
		HunterUnit("Phoenix From Egg", p, 3);
		HunterUnit("Mountain Giant", p, 1);
		HunterUnit("Heka Gigantes", p, 1);
		HunterUnit("Lampades", p, 2);
		HunterUnit("Pegasus", p, 3);
		HunterUnit("Guardian XP", p, 3);
		ZeroArmour("Guardian XP", p);
		trModifyProtounit("Dwarf", p, 55, 4);
		trModifyProtounit("Temple", p, 7, 150);
		trModifyProtounit("Animal Attractor", p, 55, 4);
		trModifyProtounit(""+YesChoiceUnitName, p, 55, 4);
		trModifyProtounit(""+YesChoiceUnitName, p, 1, -10);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, 0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, 0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 6, -100);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 16, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 17, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 18, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 19, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 16, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 17, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 18, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 19, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 55, 4);
		trModifyProtounit(""+NoChoiceUnitName, p, 1, -10);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, 0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, 0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 6, -100);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 16, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 17, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 18, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 19, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 16, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 17, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 18, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 19, -9999999999999999999.0);
		modifyProtounitAbsolute("Bolt Strike", p, 27, 0.0);
		modifyProtounitAbsolute("Bolt Strike", p, 28, 0.0);
		modifyProtounitAbsolute("Bolt Strike", p, 29, 0.0);
	}
	modifyProtounitAbsolute("Bolt Strike", 0, 27, 0.0);
	modifyProtounitAbsolute("Bolt Strike", 0, 28, 0.0);
	modifyProtounitAbsolute("Bolt Strike", 0, 29, 0.0);
	trModifyProtounit("Revealer to Player", 0, 2, MapSize+50);
	xsDisableSelf();
}



/*
The field ids are as follows:
Hitpoints=0
Speed=1
LOS=2
Train Points=3
Build Points=4
Max Contained=5
Population Count=6
Pop Cap Addition=7
Lifespan=8
Recharge Time=9
Build Limit=10
Range=11
Minimum Range=12
Num Projectiles=13
Healing Rate=14
Healing Range=15
Cost Gold=16
Cost Wood=17
Cost Food=18
Cost Favor=19
Carry Capacity Gold=20
Carry Capacity Wood=21
Carry Capacity Food=22
Carry Capacity Favor=23
Armor Hack=24
Armor Pierce=25
Armor Crush=26
Hand Attack Hack=27
Hand Attack Pierce=28
Hand Attack Crush=29
Ranged Attack Hack=30
Ranged Attack Pierce=31
Ranged Attack Crush=32
Movetype = 55
*/
