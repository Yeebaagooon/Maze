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
insta wall
tower range
great journey


15-20
temp invuln
tower projectile


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
const int RELIC_MYTHIC_CURSE = 7;

const int MAX_RELIC_CLASS = 7;

void RelicEffect(int p = 0, int effect = 0){
	trQuestVarSet("qv", 0);
	int temp = 0;
	switch(effect){
		case 0:
		{
			trModifyProtounit("Tower", p, 31, 5);
		}
		case 1:
		{
			trModifyProtounit("Tower", p, 0, 200);
		}
		case RELIC_SKY_HP:
		{
			trModifyProtounit("Sky Passage", p, 0, 500);
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
		case RELIC_MYTHIC_CURSE:
		{
			grantGodPowerNoRechargeNextPosition(p, "Change Chimera", 1);
		}
	}
}

void RelicDecor(string proto = "" ,string path = "0,0,0,0,0,0", vector size = vector(1,1,1), int anim = 2, bool statusofrefresh = false){
	xSetString(dRelicTypes, xRelicDecor, proto);
	xSetString(dRelicTypes, xRelicDecorAnimPath, path);
	xSetVector(dRelicTypes, xRelicDecorScale, size);
	xSetInt(dRelicTypes, xRelicDecorAnim, anim);
	//xSetBool(dRelicTypes, xRelicDecor, statusofrefresh);
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
	trQuestVarSetFromRand("x", 0 , 20);
	trQuestVarSetFromRand("z", 0 , 20);
	UnitCreate(0, "Dwarf", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"));
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
	RelicDecor("Valkyrie", "no path", vector(0,0,0),18,false);
	//--BUILD RELIC --- 1
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_HP_200);
	RelicSetName("+200 tower hitpoints");
	RelicDecor("Trojan Horse", "no path", vector(0.1,0.1,0.1),18,false);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_SKY_HP);
	RelicSetName("+500 sky passage hitpoints");
	RelicDecor("Sky Passage", "no path", vector(0,0,0),2,false);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_LIGHTHOUSE);
	RelicSetName("Creates a lighthouse");
	RelicDecor("Lighthouse", "0,1,0,1,0,0", vector(0.1,0.1,0.1),2,false);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_CITIZEN_SPEED_1);
	RelicSetName("+1 citizen speed");
	RelicDecor("Villager Atlantean", "no path", vector(1,1,1),15,false);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_CITIZEN_HP_300);
	RelicSetName("+300 citizen hp");
	RelicDecor("Flying Purple Hippo", "no path", vector(0,0,0),1,false); //12 if fail
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_WALLS);
	RelicSetName("Walls level up");
	RelicDecor("Wall Connector", "3,2,0,0,0,0", vector(1,0.01,1),2,false);
	//--BUILD RELIC
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_MYTHIC_CURSE);
	RelicSetName("Mythic curse god power");
	RelicDecor("Curse SFX", "no path", vector(1,1,1),2,true);
	
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
		/*if(xGetBool(dRelics, xRelicDecorRefresh) == true){
			if(trTimeMS() > xGetInt(dRelics, xRelicLastRefresh)){
				xSetInt(dRelics, xRelicLastRefresh, trTimeMS()+3000);
				trUnitOverrideAnimation(xGetInt(dRelicTypes, xRelicDecorAnim),0, true,true,-1);
			}
		}*/
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
						playSound("\cinematics\17_in\weirdthing.mp3");
					}
					xFreeDatabaseBlock(dRelics);
				}
			}
		}
	}
}
