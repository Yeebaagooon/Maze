/*
BUG
multi level

Stop mine on cliff - xTest that this fix works

TEMPLE SHIT
<train row="0" page="1" column="0">Hero Norse</train>
<train row="0" page="1" column="0">Oracle Scout</train>
<train row="0" page="1" column="0">Pegasus</train>
<train row="0" page="1" column="0">Priest</train>
---
<train row="0" page="1" column="1">Anubite</train>
<train row="0" page="1" column="1">Automaton</train>
<train row="0" page="1" column="1">Centaur</train>
<train row="0" page="1" column="1">Cyclops</train>
<train row="0" page="1" column="1">Einheriar</train>
<train row="0" page="1" column="1">Flying Medic</train>
<train row="0" page="1" column="1">Minotaur</train>
<train row="0" page="1" column="1">Promethean</train>
<train row="0" page="1" column="1">Sphinx</train>
<train row="0" page="1" column="1">Troll</train>
<train row="0" page="1" column="1">Valkyrie</train>
<train row="0" page="1" column="1">Wadjet</train>
---
<train row="0" page="1" column="2">Battle Boar</train>
<train row="0" page="1" column="2">Behemoth</train>
<train row="0" page="1" column="2">Hydra</train>
<train row="0" page="1" column="2">Manticore</train>
<train row="0" page="1" column="2">Nemean Lion</train>
<train row="0" page="1" column="2">Petsuchos</train>
<train row="0" page="1" column="2">Satyr</train>
<train row="0" page="1" column="2">Scarab</train>
<train row="0" page="1" column="2">Scorpion Man</train>
<train row="0" page="1" column="2">Stymphalian Bird</train>
---
<train row="0" page="1" column="3">Argus</train>
<train row="0" page="1" column="3">Colossus</train>
<train row="0" page="1" column="3">Heka Gigantes</train>
<train row="0" page="1" column="3">Lampades</train>
<train row="0" page="1" column="3">Medusa</train>
<train row="0" page="1" column="3">Mountain Giant</train>
<train row="0" page="1" column="3">Roc</train>
---
<train row="0" page="1" column="4">Avenger</train>
<train row="0" page="1" column="4">Chimera</train>
<train row="0" page="1" column="4">Frost Giant</train>
<train row="0" page="1" column="4">Mummy</train>
<train row="0" page="1" column="4">Phoenix</train>
---
<train row="0" page="1" column="5">Fenris Wolf</train>
<train row="0" page="1" column="5">Fire Giant</train>

*/


//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int MapSkin = 0;
string MapVersion = "Test Version";
string MapName = "Maze Escape";
bool ForceAutoOff = false;
bool Visible = false;
int MaxRelics = 5;

string CliffTerrain = "CliffGreekA";
string RoadTerrain = "OlympusTile";


bool AutoEscape = false;
int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;
int CyclePlayers = 0;
int AutoHunterLevel = 1;
vector AIVector = vector(0,0,0);
int GPBlockTime = 0;
int GPShieldRadius = 30;
//MapSize
int MapFactor(){
	if(MapSize == 398){
		return(1);
	}
	if(MapSize == 530){
		return(2);
	}
	if(MapSize == 662){
		return(3);
	}
}
int SwitchMapSize(int small = 18, int medium = 24, int large = 30){
	if(MapFactor() == 1){
		return(small);
	}
	if(MapFactor() == 2){
		return(medium);
	}
	if(MapFactor() == 3){
		return(large);
	}
}

const int gCellSize = 11;
const int gCellPadding = 2;
const int EVENT_REMOVE_CAM_TRACKS = 26;

bool Pregame = false;
bool AllowHunterChoice = false;
int PregameTimeout = 20;
int ChoiceTimeout = 120;
int HunterNumber = 0;
int RunnerCount = 0;
int HunterCount = 0;
int DestroyAbove = 1;
int gGameEndTime = 9999;
string rangedunit = "error";
string handunit = "error";
float timediff = 0.0;
float timelast = 0.0;
int RunnersDead = 0;
int YeebSpecialAttackChance = 100;


int CountBuildings(int p = 0){
	int count = trPlayerUnitCountSpecific(p, "Tower")+trPlayerUnitCountSpecific(p, "Sky Passage")+trPlayerUnitCountSpecific(p, "Gate")+trPlayerUnitCountSpecific(p, "Wall Connector")+trPlayerUnitCountSpecific(p, "Wall Short")+trPlayerUnitCountSpecific(p, "Wall Medium")+trPlayerUnitCountSpecific(p, "Wall Long");
	return(count);
}

/*NOTES

Put the choice area in hunter area so all have LOS
*/

void DamageBuildingCountRazes(int p = 1, int targetid = 0, float distance = 10.0, float damage = 100){
	int count = 0;
	int diff = 0;
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		if((otherp != p && kbIsPlayerAlly(p) == false) && (trCheckGPActive("Restoration", p) == false)){
			//count
			trQuestVarSet("LastAdd", p);
			trQuestVarSet("CountAdd"+otherp, CountBuildings(otherp));
			
			//dmg
			trUnitSelectClear();
			trUnitSelect(""+targetid);
			trDamageUnitsInArea(otherp, "Building", distance, damage);
			
			//count
			trDelayedRuleActivation("CountExtras");
		}
	}
}

/*void DamageBuildingPercentCountRazes(int p = 1, vector pos = vector(0,0,0), float distance = 10.0, float damage = 100){
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		xsSetContextPlayer(otherp);
		if(otherp != p && kbIsPlayerAlly(p) == false && trCheckGPActive("Restoration", otherp) == false){
			int kbid = kbUnitQueryCreate("damagebuildperc");
			kbUnitQuerySetPlayerID(kbid, otherp);
			kbUnitQuerySetPosition(kbid, pos);
			kbUnitQuerySetUnitType(kbid, 937);
			kbUnitQuerySetState(kbid, 2);
			kbUnitQuerySetMaximumDistance(kbid, distance);
			int count = kbUnitQueryExecute(kbid);
			for(a = 0 ; < count){
				int UnitID = kbUnitQueryGetResult(kbid, a);
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				if(trUnitPercentDamaged() < 100.0){
					trDamageUnitPercent(damage);
				}
				if(trUnitPercentDamaged() >= 100.0){
					trDamageUnitPercent(100.0);
					trQuestVarModify("P"+p+"AddKills", "+", 1);
				}
			}
			kbUnitQueryDestroy(kbid);
		}
	}
	debugLog("DistancePercent: " + distance);
}*/

void DamageUnitCountKills(int p = 1, vector pos = vector(0,0,0), float distance = 10.0, float damage = 100){
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		xsSetContextPlayer(otherp);
		if(otherp != p && kbIsPlayerAlly(p) == false && trCheckGPActive("Restoration", p) == false){
			int kbid = kbUnitQueryCreate("damageunitabs");
			kbUnitQuerySetPlayerID(kbid, otherp);
			kbUnitQuerySetPosition(kbid, pos);
			kbUnitQuerySetUnitType(kbid, 935);
			kbUnitQuerySetState(kbid, 2);
			kbUnitQuerySetMaximumDistance(kbid, distance);
			int count = kbUnitQueryExecute(kbid);
			for(a = 0 ; < count){
				int UnitID = kbUnitQueryGetResult(kbid, a);
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				if(trUnitPercentDamaged() < 100.0){
					trDamageUnit(damage);
				}
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				if(trUnitPercentDamaged() >= 100.0){
					trDamageUnitPercent(100.0);
					trQuestVarModify("P"+p+"AddKills", "+", 1);
				}
			}
			kbUnitQueryDestroy(kbid);
		}
	}
	xsSetContextPlayer(0);
}

void BoltUnitCountKills(int p = 1, vector pos = vector(0,0,0), float distance = 10.0, float damage = 100){
	trChatSetStatus(false);
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		xsSetContextPlayer(otherp);
		if(otherp != p && kbIsPlayerAlly(p) == false && trCheckGPActive("Restoration", p) == false){
			int kbid = kbUnitQueryCreate("damageunitabs");
			kbUnitQuerySetPlayerID(kbid, otherp);
			kbUnitQuerySetPosition(kbid, pos);
			kbUnitQuerySetUnitType(kbid, 935);
			kbUnitQuerySetState(kbid, 2);
			kbUnitQuerySetMaximumDistance(kbid, distance);
			int count = kbUnitQueryExecute(kbid);
			for(a = 0 ; < count){
				int UnitID = kbUnitQueryGetResult(kbid, a);
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				trTechInvokeGodPower(0, "bolt", vector(0,0,0), vector(0,0,0));
				if(trUnitPercentDamaged() < 100.0){
					trDamageUnit(damage);
				}
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				if(trUnitPercentDamaged() >= 100.0){
					trDamageUnitPercent(100.0);
					trQuestVarModify("P"+p+"AddKills", "+", 1);
				}
			}
			kbUnitQueryDestroy(kbid);
		}
	}
	xsSetContextPlayer(0);
	trDelayedRuleActivation("EnableChat");
}

void DamageUnitPercentCountKills(int p = 1, vector pos = vector(0,0,0), float distance = 10.0, float damage = 100){
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		xsSetContextPlayer(otherp);
		if(otherp != p && kbIsPlayerAlly(p) == false && trCheckGPActive("Restoration", p) == false){
			int kbid = kbUnitQueryCreate("damageunitperc");
			kbUnitQuerySetPlayerID(kbid, otherp);
			kbUnitQuerySetPosition(kbid, pos);
			kbUnitQuerySetUnitType(kbid, 935);
			kbUnitQuerySetState(kbid, 2);
			kbUnitQuerySetMaximumDistance(kbid, distance);
			int count = kbUnitQueryExecute(kbid);
			for(a = 0 ; < count){
				int UnitID = kbUnitQueryGetResult(kbid, a);
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				if(trUnitPercentDamaged() < 100.0){
					trDamageUnitPercent(damage);
				}
				if(trUnitPercentDamaged() >= 100.0){
					trDamageUnitPercent(100.0);
					trQuestVarModify("P"+p+"AddKills", "+", 1);
				}
			}
			kbUnitQueryDestroy(kbid);
		}
	}
}
