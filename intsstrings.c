/*
BUG

Camera post level reward
IceC in top corner for choice units? also other corner for hunters


g("configSetInt(\"unbuildWoodCost2\", 200);");
g("configSetInt(\"unbuildGoldCost2\", 100);");
to revert timeshift cost after player resigns/game ends
*/


//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Maze Escape";
bool ForceAutoOff = false;
bool Visible = true;


bool AutoEscape = false;
int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;
int CyclePlayers = 0;
int AutoHunterLevel = 1;
vector AIVector = vector(0,0,0);
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



/*NOTES

Put the choice area in hunter area so all have LOS
*/

void DamageBuildingCountRazes(int p = 1, vector pos = vector(0,0,0), float distance = 10.0, float damage = 100){
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		xsSetContextPlayer(otherp);
		if(otherp != p && kbIsPlayerAlly(p) == false){
			int kbid = kbUnitQueryCreate("damage");
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
					trDamageUnit(damage);
				}
				trUnitSelectClear();
				trUnitSelectByID(UnitID);
				if(trUnitPercentDamaged() >= 100.0){
					trDamageUnitPercent(100.0);
					trChatSend(0, "Add a kill");
				}
			}
			kbUnitQueryDestroy(kbid);
		}
	}
	xsSetContextPlayer(0);
}

void DamageBuildingPercentCountRazes(int p = 1, vector pos = vector(0,0,0), float distance = 10.0, float damage = 100){
	for(otherp = 1 ; <= cNumberNonGaiaPlayers){
		xsSetContextPlayer(otherp);
		if(otherp != p && kbIsPlayerAlly(p) == false){
			int kbid = kbUnitQueryCreate("damage");
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
					trChatSend(0, "Add a kill");
				}
			}
			kbUnitQueryDestroy(kbid);
		}
	}
}
