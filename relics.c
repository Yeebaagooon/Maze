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
mythic curse

5-10
wall level up
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

const int MAX_RELIC_CLASS = 2;

void RelicEffect(int p = 0, int effect = 0){
	debugLog(""+effect);
	switch(effect){
		case 0:
		{
			trModifyProtounit("Tower", p, 31, 5);
		}
		case 1:
		{
			trModifyProtounit("Tower", p, 0, 200);
		}
		case 2:
		{
			trModifyProtounit("Sky Passage", p, 0, 500);
		}
	}
}

void RelicDecor(string proto = "" ,string path = "0,0,0,0,0,0", vector size = vector(1,1,1), int anim = 2, bool refreshing = false){
	xSetString(dRelicTypes, xRelicDecor, proto);
	debugLog(""+proto);
	xSetString(dRelicTypes, xRelicDecorAnimPath, path);
	xSetVector(dRelicTypes, xRelicDecorScale, size);
	xSetInt(dRelicTypes, xRelicDecorAnim, anim);
	xSetBool(dRelicTypes, xRelicDecorRefresh, refreshing);
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
	debugLog(""+xGetInt(dRelicTypes, xRelicDecorAnim));
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
	RelicDecor("Medusa", "no path", vector(0,0,0),18,false);
	//--BUILD RELIC --- 1
	index = xAddDatabaseBlock(dRelicTypes, true);
	xSetInt(dRelicTypes, xRelicPointer, index);
	RelicSetClass(RELIC_SKY_HP);
	RelicSetName("+500 sky passage hitpoints");
	RelicDecor("Automaton", "no path", vector(0,0,0),18,false);
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
