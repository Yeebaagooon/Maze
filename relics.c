/*

//relics types
int dRelicTypes = 0;
int xRelicPointer = 0;
int xRelicType = 0;
int xRelicDecor = 0;
int xRelicDecorScale = 0;
int xRelicDecorAnim = 0;
int xRelicDecorAnimPath = 0;
int xRelicDecorRefresh = 0;

//actual relics
int dRelics = 0;
int xRelicID = 0;
int xRelicSFXID = 0;
int xRelicProperty = 0;

AUTO RELIC THOUGHT:
Split by time, use databsase to store characteristics etc

0-5
tower hp
tower attack
citizen hp
citizen speed
tower build time
Lighthouse
wall level up
mythic curse

5-10
sky passage stat
sky passage stat
lightning storm
citizen regen
pegasus

10-15
2nd citizen
tower range
temp invuln
50 build time
CHicken storm tower
10 crush armour
Kill in area GP (frost)

15-20
temp invuln
tower projectile
mirror tower


20+
bird power

*/

const int RELIC_ATTACK_5 = 0;
const int RELIC_HP_200 = 1;
const int RELIC_SKY_HP = 2;
const int RELIC_LIGHTHOUSE = 3;
const int RELIC_CITIZEN_SPEED_1 = 4;
const int RELIC_CITIZEN_HP_300 = 5;
const int RELIC_WALLS = 6;
const int RELIC_SANDSTORM = 7;
//---
const int RELIC_LIGHTNING = 8;
const int RELIC_CITIZEN_REGEN_5 = 9;
const int RELIC_PEGASUS = 10;
const int RELIC_HP_500 = 11;
const int RELIC_ATTACK_10 = 12;
const int RELIC_WALL_POWER = 13;
const int RELIC_JOURNEY = 14;
//---
const int RELIC_SECOND_CITIZEN = 15;
const int RELIC_RANGE_5 = 16;
const int RELIC_POWER_RESTORATION = 17;
const int RELIC_BUILD_TIME_50 = 18;
const int RELIC_POWER_CHICKEN = 19;
const int RELIC_ARMOUR_10 = 20;
const int RELIC_POWER_FROST = 21;
//---
const int RELIC_MIRROR_TOWER = 22;
const int RELIC_TOWER_PROJECTILE = 23;
const int RELIC_POWER_BIRDS = 24;
const int RELIC_EXTRA_SKY_PASSAGE = 25;
const int RELIC_CITIZEN_HP_1000 = 26;
const int RELIC_ATTACK_20 = 27;
const int RELIC_POWER_IMPLODE = 28;


const int MAX_RELIC_CLASS = 28;
const int RELIC_SHIELD = 47;

void RelicEffect(int p = 0, int effect = 0){
	trQuestVarSet("qv", 0);
	xSetPointer(dPlayerData, p);
	int temp = 0;
	switch(effect){
		case RELIC_ATTACK_5:
		{
			trModifyProtounit("Tower", p, 31, 5);
		}
		case RELIC_HP_200:
		{
			trModifyProtounit("Tower", p, 0, 200);
		}
		case RELIC_SKY_HP:
		{
			trModifyProtounit("Sky Passage", p, 0, 1000);
		}
		case RELIC_LIGHTHOUSE:
		{
			xSetPointer(dPlayerData, p);
			yFindLatest("qv", "Villager Atlantean Hero", p);
			temp = UnitCreate(p, "Lighthouse", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
			trUnitSelectClear();
			trUnitSelectByQV("qv");
			trImmediateUnitGarrison(""+temp);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Lighthouse");
		}
		case RELIC_CITIZEN_SPEED_1:
		{
			trModifyProtounit("Villager Atlantean Hero", p, 1, 1);
		}
		case RELIC_CITIZEN_HP_300:
		{
			trModifyProtounit("Villager Atlantean Hero", p, 0, 300);
		}
		case RELIC_WALLS:
		{
			UpgradeTest(p, 3);
		}
		case RELIC_SANDSTORM:
		{
			grantGodPowerNoRechargeNextPosition(p, "Sandstorm", 1);
		}
		case RELIC_LIGHTNING:
		{
			grantGodPowerNoRechargeNextPosition(p, "Lightning Storm", 1);
		}
		case RELIC_CITIZEN_REGEN_5:
		{
			xSetFloat(dPlayerData,xCitizenRegen,xGetFloat(dPlayerData, xCitizenRegen)+5.0);
		}
		case RELIC_PEGASUS:
		{
			UpgradeTest(p, 18);
			trModifyProtounit("Pegasus", p, 0, 500);
			trModifyProtounit("Pegasus", p, 1, 2);
			trModifyProtounit("Pegasus", p, 2, 8);
		}
		case RELIC_HP_500:
		{
			trModifyProtounit("Tower", p, 0, 500);
		}
		case RELIC_ATTACK_10:
		{
			trModifyProtounit("Tower", p, 31, 10);
		}
		case RELIC_WALL_POWER:
		{
			grantGodPowerNoRechargeNextPosition(p, "create gold", 1);
		}
		case RELIC_JOURNEY:
		{
			grantGodPowerNoRechargeNextPosition(p, "Journey", 1);
		}
		case RELIC_SECOND_CITIZEN:
		{
			UpgradeTest(p, 43);
		}
		case RELIC_RANGE_5:
		{
			trModifyProtounit("Tower", p, 2, 5);
			trModifyProtounit("Tower", p, 11, 5);
		}
		case RELIC_POWER_RESTORATION:
		{
			grantGodPowerNoRechargeNextPosition(p, "Restoration", 1);
		}
		case RELIC_BUILD_TIME_50:
		{
			xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.5);
			modifyProtounitAbsolute("Tower", p, 4, xGetFloat(dPlayerData, xTowerBuild));
		}
		case RELIC_POWER_CHICKEN:
		{
			grantGodPowerNoRechargeNextPosition(p, "Chicken Storm", 1);
		}
		case RELIC_ARMOUR_10:
		{
			trModifyProtounit("Tower", p, 26, 0.1);
		}
		case RELIC_POWER_FROST:
		{
			grantGodPowerNoRechargeNextPosition(p, "Frost", 1);
		}
		case RELIC_MIRROR_TOWER:
		{
			xSetPointer(dPlayerData, p);
			yFindLatest("qv", "Villager Atlantean Hero", p);
			temp = UnitCreate(p, "Tower Mirror", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
			trUnitSelectClear();
			trUnitSelectByQV("qv");
			trImmediateUnitGarrison(""+temp);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Tower Mirror");
		}
		case RELIC_TOWER_PROJECTILE:
		{
			trModifyProtounit("Tower", p, 13, 1);
		}
		case RELIC_POWER_BIRDS:
		{
			grantGodPowerNoRechargeNextPosition(p, "Rain", 1);
		}
		case RELIC_EXTRA_SKY_PASSAGE:
		{
			trModifyProtounit("Sky Passage", p, 10, 1);
		}
		case RELIC_CITIZEN_HP_1000:
		{
			trModifyProtounit("Villager Atlantean Hero", p, 0, 1000);
		}
		case RELIC_ATTACK_20:
		{
			trModifyProtounit("Tower", p, 31, 20);
		}
		case RELIC_POWER_IMPLODE:
		{
			grantGodPowerNoRechargeNextPosition(p, "Implode", 1);
		}
		case RELIC_SHIELD:
		{
			xSetPointer(dPlayerData, p);
			yFindLatest("qv", "Villager Atlantean Hero", p);
			temp = UnitCreate(p, "Tower", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
			trUnitSelectClear();
			trUnitSelectByQV("qv");
			trImmediateUnitGarrison(""+temp);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Monument");
		}
	}
}

void RelicDecor(string proto = "" ,string path = "0,0,0,0,0,0", vector size = vector(1,1,1), int anim = 2, int THISISANINT = 0){
	xSetString(dRelicTypes, xRelicDecor, proto);
	xSetString(dRelicTypes, xRelicDecorAnimPath, path);
	xSetVector(dRelicTypes, xRelicDecorScale, size);
	xSetInt(dRelicTypes, xRelicDecorAnim, anim);
	//xSetInt(dRelicTypes, xRelicRefreshBool, THISISANINT);
}

void RelicSetName(string desc = "error"){
	xSetString(dRelicTypes, xRelicDescription, desc);
}

void RelicSetClass(int num = 0){
	xSetInt(dRelicTypes, xRelicType, num);
}

void CreateRelic(int type = 0){
	//builds a random relic on the map of specified class
	int old = xGetPointer(dRelicTypes);
	int temp = trGetNextUnitScenarioNameNumber();
	int index = 0;
	int Safety = 0;
	bool Allow = false;
	while(Allow == false){
		trQuestVarSetFromRand("x", 0 , MapSize);
		trQuestVarSetFromRand("z", 0 , MapSize);
		Safety = Safety +1;
		temp = UnitCreate(0, "Dwarf", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"));
		if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+temp)/2),xsVectorGetZ(kbGetBlockPosition(""+temp)/2)) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+temp)/2),xsVectorGetZ(kbGetBlockPosition(""+temp)/2)) == getTerrainSubType(RoadTerrain))){
			trUnitSelectClear();
			trUnitSelect(""+temp);
			bool inLOS = false;
			for(p = 1; < cNumberNonGaiaPlayers){
				if(trUnitHasLOS(p) && trPlayerDefeated(p) == false){
					trUnitDestroy();
					inLOS = true;
				}
			}
			if(inLOS == false){
				//UNIT CREATED - SET TARGET
				if(trCountUnitsInArea(""+temp, 0, "Relic", 40) == 0){
					trUnitDestroy();
					Allow = true;
				}
				trUnitDestroy();
			}
		}
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitDestroy();
		if(Safety > 500){
			debugLog("BREAK RELIC CREATE");
			break;
		}
	}
	temp = UnitCreate(0, "Dwarf", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"));
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Titan Atlantean");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Relic");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trSetRelicType(461);
	//Force to gaias book
	for(a = xGetDatabaseCount(dRelicTypes); > 0){
		xDatabaseNext(dRelicTypes);
		if(xGetInt(dRelicTypes, xRelicType) == type){
			index = xGetPointer(dRelicTypes);
			break;
		}
	}
	
	
	xAddDatabaseBlock(dRelics, true);
	xSetInt(dRelics, xRelicID, temp);
	xSetInt(dRelics, xRelicProperty, type);
	xSetInt(dRelics, xFreeRelicPointer, index);
	xSetInt(dRelics, xRelicSFXID, temp+2);
	xSetInt(dRelics, xRelicLastRefresh, trTimeMS());
	
	xUnitSelect(dRelics, xRelicSFXID);
	trUnitChangeProtoUnit("Spy Eye");
	xUnitSelect(dRelics, xRelicSFXID);
	trMutateSelected(kbGetProtoUnitID(xGetString(dRelicTypes, xRelicDecor)));
	trSetSelectedScale(xsVectorGetX(xGetVector(dRelicTypes, xRelicDecorScale)),xsVectorGetY(xGetVector(dRelicTypes, xRelicDecorScale)),xsVectorGetZ(xGetVector(dRelicTypes, xRelicDecorScale)));
	if(xGetString(dRelicTypes, xRelicDecorAnimPath) != "no path"){
		xUnitSelect(dRelics, xRelicSFXID);
		trUnitSetAnimationPath(xGetString(dRelicTypes, xRelicDecorAnimPath));
	}
	xUnitSelect(dRelics, xRelicSFXID);
	trUnitOverrideAnimation(xGetInt(dRelicTypes, xRelicDecorAnim),0, true,true,-1);
	xSetPointer(dRelicTypes, old);
}

rule Make_Relic_Types
inactive
highFrequency
{
	//--BUILD RELIC --- 0
	int index = 0;
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_ATTACK_5);
	RelicSetName("+5 tower attack");
	RelicDecor("Fire Giant", "no path", vector(0,0,0),2,0);
	//--BUILD RELIC --- 1
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_HP_200);
	RelicSetName("+200 tower hitpoints");
	RelicDecor("Trojan Horse", "no path", vector(0.1,0.2,0.1),18,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_SKY_HP);
	RelicSetName("+1000 sky passage hitpoints");
	RelicDecor("Sky Passage", "no path", vector(0,0,0),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_LIGHTHOUSE);
	RelicSetName("Creates a lighthouse");
	RelicDecor("Lighthouse", "0,1,0,1,0,0", vector(0.1,0.1,0.1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_CITIZEN_SPEED_1);
	RelicSetName("+1 citizen speed");
	RelicDecor("Villager Atlantean", "no path", vector(1,1,1),15,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_CITIZEN_HP_300);
	RelicSetName("+300 citizen hp");
	RelicDecor("Flying Purple Hippo", "no path", vector(0,0,0),1,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_WALLS);
	RelicSetName("Walls level up");
	RelicDecor("Wall Connector", "3,2,0,0,0,0", vector(1,0.01,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_SANDSTORM);
	RelicSetName("Shifting sands power (creates 9 towers at both points)");
	RelicDecor("Shifting Sands Out", "no path", vector(1,1,1),2,0);
	
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_LIGHTNING);
	RelicSetName("Lightning god power");
	RelicDecor("Mist", "no path", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_CITIZEN_REGEN_5);
	RelicSetName("+5 citizen regen");
	RelicDecor("Healing SFX", "no path", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_PEGASUS);
	RelicSetName("Spawns a pegasus with improved stats to scout for you");
	RelicDecor("Pegasus", "no path", vector(0.5,0.5,0.5),0,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_HP_500);
	RelicSetName("+500 tower hp");
	RelicDecor("Trojan Horse", "no path", vector(0.1,0.2,0.1),18,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_ATTACK_10);
	RelicSetName("+10 tower attack");
	RelicDecor("Fire Giant", "no path", vector(0,0,0),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_WALL_POWER);
	RelicSetName("Create wall god power");
	RelicDecor("Dig Pile", "no path", vector(0.5,0.5,0.5),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_JOURNEY);
	RelicSetName("Walk on cliffs power");
	RelicDecor("Gate Ram", "no path", vector(0.05,0.01,0.05),2,1);
	
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_SECOND_CITIZEN);
	RelicSetName("Spawns a secondary citizen");
	RelicDecor("Villager Atlantean", "no path", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_RANGE_5);
	RelicSetName("+5 tower range and LOS");
	RelicDecor("Arrow Signal", "no path", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_POWER_RESTORATION);
	RelicSetName("Temporary invulnerability power");
	RelicDecor("Increase Prosperity Small", "no path", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_BUILD_TIME_50);
	RelicSetName("Towers build 50 percent faster");
	RelicDecor("Timeshift in", "0,0,1,1,0,0", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_POWER_CHICKEN);
	RelicSetName("Tower spam power");
	RelicDecor("Chicken", "no path", vector(2,2,2),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_ARMOUR_10);
	RelicSetName("+10 tower crush armour");
	RelicDecor("Weapons", "no path", vector(1.5,1.5,1.5),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_POWER_FROST);
	RelicSetName("Deals 5000 damage in a large area");
	RelicDecor("Snow Drift Tower", "no path", vector(1,1,1),2,0);
	
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_MIRROR_TOWER);
	RelicSetName("Grants a mirror tower that kill insta kill every 5 seconds");
	RelicDecor("Tower Mirror", "no path", vector(0.2,0.2,0.2),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_TOWER_PROJECTILE);
	RelicSetName("+1 tower projectile");
	RelicDecor("Volley", "no path", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_POWER_BIRDS);
	RelicSetName("Bird tower power");
	RelicDecor("Hawk", "no path", vector(2,2,2),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_EXTRA_SKY_PASSAGE);
	RelicSetName("Grants an extra sky passage");
	RelicDecor("Garrison Flag Sky Passage", "no path", vector(1,1,1),2,0);
	
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_CITIZEN_HP_1000);
	RelicSetName("+1000 citizen hp");
	RelicDecor("Flying Purple Hippo", "no path", vector(0,0,0),1,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_ATTACK_20);
	RelicSetName("+20 tower attack");
	RelicDecor("Fire Giant", "no path", vector(0,0,0),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_POWER_IMPLODE);
	RelicSetName("Void power");
	RelicDecor("Implode Sphere Effect", "0,1,0,1,0,0", vector(1,1,1),2,0);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_SHIELD);
	RelicSetName("God power shield");
	RelicDecor("Monument", "no path", vector(0,0,0),4,0);
	
	xsDisableSelf();
}

rule RelicsExist
inactive
highFrequency
{
	if(xGetDatabaseCount(dRelics) > 0){
		int old = 0;
		xDatabaseNext(dRelics);
		xUnitSelect(dRelics, xRelicID);
		/*if(xGetInt(dRelics, xRelicRefreshBool) == 1){
			if(trTimeMS() > xGetInt(dRelics, xRelicLastRefresh)){
				xSetInt(dRelics, xRelicLastRefresh, trTimeMS()+3000);
				trUnitOverrideAnimation(xGetInt(dRelicTypes, xRelicDecorAnim),0, true,true,-1);
			}
		}*/
		//Dunno wtf is going on here, says its a string but is not!!
		if(trUnitIsSelected()){
			uiClearSelection();
			old = xGetPointer(dRelicTypes);
			xSetPointer(dRelicTypes, xGetInt(dRelics, xFreeRelicPointer));
			trMessageSetText(xGetString(dRelicTypes, xRelicDescription), 5000);
			xSetPointer(dRelicTypes, old);
		}
		if (trUnitGetIsContained("Unit")) {
			for(p=1; < cNumberNonGaiaPlayers) {
				if (trUnitIsOwnedBy(p)) {
					//player pickup
					old = xGetPointer(dRelicTypes);
					xSetPointer(dRelicTypes, xGetInt(dRelics, xFreeRelicPointer));
					RelicEffect(p, xGetInt(dRelics, xRelicProperty));
					ColouredChatToPlayer(p, "1,0,1", xGetString(dRelicTypes, xRelicDescription));
					xSetPointer(dRelicTypes, old);
					xUnitSelect(dRelics, xRelicSFXID);
					trUnitChangeProtoUnit("Heavenlight");
					xUnitSelect(dRelics, xRelicID);
					trUnitChangeProtoUnit("Osiris Box Glow");
					if(trCurrentPlayer() == p){
						playSound("\cinematics\10_in\clearedcity.wav");
					}
					xFreeDatabaseBlock(dRelics);
				}
			}
		}
	}
}
