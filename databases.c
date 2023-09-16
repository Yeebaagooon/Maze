int dDestroyMe = 0;
int xDestroyName = 0;
int xDestroyTime = 0;

int spysearch = 0;
int spyreset = 0;
int spyProto = 0;
int spyUnit = 1;
int spyDest = 2;
int spyScale = 3;
int spyActive = 4;
int spyAnim = 5;

int xPlayerUnitID = 0;
int xPlayerAlive = 0;
int xPlayerRunner = 0;
int xRoleDefined = 0;
int xTowerBuild = 0;
int xPlayerLevel = 0;
int xPlayerNextLevel = 0;
int xPlayerWallLevel = 0;

int dEnemies = 0;
int xUnitID = 0;
int xIdleTimeout = 0;

/*DB HELP
dPlayerData = xInitDatabase("playerData");
xDrillPower = xInitAddInt(dPlayerData, "drillpower", 10);
xHullHP = xInitAddInt(dPlayerData, "hullhp", 1000);
xsEnableRule("fill_database");


rule fill_database
inactive
highFrequency

for(p=1; < cNumberNonGaiaPlayers) {
	xAddDatabaseBlock(dPlayerData);
}
//This sets up basic stats for all players
xSetPointer(dPlayerData, 1);
xSetInt(dPlayerData, xDrillPower, 10);
//Sets the drill power for that player (1)
xsDisableSelf();

xSetPointer(dPlayerData, 1);
xGetInt(dPlayerData, xDrillPower)
//Retrieves the drill power for that player (1)

*/

//MAZE DB
int xUnitName = 0;
int dMazeDB= 0;
int xCellXPos= 0;
int xCellZPos = 0;
int xCellConnected = 0;
int xCellConnectedL = 0;
int xCellConnectedR = 0;
int xCellConnectedU = 0;
int xCellConnectedD = 0;
int xLUCL = 0;
int xLUCR = 0;
int xCellConnections= 0;

int dFrontier = 0;
int xDirectionToBuild = 0;



rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xPlayerUnitID = xInitAddInt(dPlayerData, "lol", 0);
	xPlayerAlive = xInitAddBool(dPlayerData, "alive", true);
	xPlayerRunner = xInitAddBool(dPlayerData, "runner", true);
	xRoleDefined = xInitAddBool(dPlayerData, "role chosen", false);
	xLUCL = xInitAddInt(dPlayerData, "reward", 0);
	xLUCR = xInitAddInt(dPlayerData, "reward", 0);
	xTowerBuild = xInitAddFloat(dPlayerData, "tower build points", 3.333);
	xPlayerLevel = xInitAddInt(dPlayerData, "level", 1);
	xPlayerNextLevel = xInitAddInt(dPlayerData, "k to next l", 5);
	xPlayerWallLevel = xInitAddInt(dPlayerData, "wall level", 1);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	dMazeDB = xInitDatabase("MazeDB");
	xCellXPos = xInitAddInt(dMazeDB, "CellX");
	xCellZPos = xInitAddInt(dMazeDB, "CellZ");
	xCellConnected = xInitAddBool(dMazeDB, "Connected", false);
	xCellConnectedL = xInitAddBool(dMazeDB, "Connected", false);
	xCellConnectedR = xInitAddBool(dMazeDB, "Connected", false);
	xCellConnectedU = xInitAddBool(dMazeDB, "Connected", false);
	xCellConnectedD = xInitAddBool(dMazeDB, "Connected", false);
	xCellConnections = xInitAddInt(dMazeDB, "Connections", 0);
	
	dFrontier = xInitDatabase("Frontier DB");
	xCellXPos = xInitAddInt(dFrontier, "CellX");
	xCellZPos = xInitAddInt(dFrontier, "CellZ");
	xDirectionToBuild = xInitAddString(dFrontier, "dir", "nil");
	xCellConnected = xInitAddBool(dFrontier, "Connected", false);
	
	dEnemies = xInitDatabase("Enemies DB");
	xUnitID = xInitAddInt(dEnemies, "id", -1);
	xIdleTimeout = xInitAddInt(dEnemies, "id", 0);
	
}


int dSpyRequests = 0;
int xSpyRequestProto = 0;
int xSpyRequestDest = 0;
int xSpyRequestScale = 0;
int xSpyRequestAnim = 0;
int xSpyRequestEvent = 0;
//int xSpyRequestExtra = 0;

rule initialise_spy_database
active
highFrequency
{
	xsDisableSelf();
	xsSetContextPlayer(0);
	dSpyRequests = xInitDatabase("spyRequests", 32);
	xSpyRequestProto = xInitAddInt(dSpyRequests, "proto");
	xSpyRequestAnim = xInitAddInt(dSpyRequests, "anim");
	xSpyRequestScale = xInitAddVector(dSpyRequests, "scale");
	xSpyRequestDest = xInitAddVector(dSpyRequests, "dest");
	xSpyRequestEvent = xInitAddInt(dSpyRequests, "event");
	//xSpyRequestExtra = xInitAddInt(dSpyRequests, "extra", -1);
}

/*
Assumes that the target unit is already selected
*/
void spyEffect(int proto = 0, int anim = 0, vector dest = vector(0,0,0), vector scale = vector(1,1,1), int event = -1) {
	int newest = xAddDatabaseBlock(dSpyRequests);
	xSetInt(dSpyRequests, xSpyRequestProto, proto, newest);
	xSetInt(dSpyRequests, xSpyRequestAnim, anim, newest);
	xSetVector(dSpyRequests, xSpyRequestDest, dest, newest);
	xSetVector(dSpyRequests, xSpyRequestScale, scale, newest);
	xSetInt(dSpyRequests, xSpyRequestEvent, event, newest);
	//xSetInt(dSpyRequests, xSpyRequestExtra, extra, newest);
	trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
	//unitTransform("Prisoner", "Ball of fire");
}

//Zeno MG code
/*
if (xGetDatabaseCount(dMountainGiants) > 0) {
	xDatabaseNext(dMountainGiants);
	id = xGetInt(dMountainGiants,xUnitID);
	trUnitSelectClear();
	trUnitSelectByID(id);
	p = xGetInt(dMountainGiants,xPlayerOwner);
	db = databaseName(p);
	if (trUnitAlive() == false) {
		trQuestVarSet("giantKills", 1 + trQuestVarGet("giantKills"));
		trUnitChangeProtoUnit("Mountain Giant");
		xFreeDatabaseBlock(dMountainGiants);
	} else if (trTimeMS() > xGetInt(dMountainGiants, xSpecialNext)) {
		switch(xGetInt(dMountainGiants, xSpecialStep))
		{
			case 0:
			{
				if (kbUnitGetAnimationActionType(id) == 39) {
					xsSetContextPlayer(p);
					target = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(id));
					xsSetContextPlayer(0);
					xSetVector(dMountainGiants,xSpecialTarget,kbGetBlockPosition(""+target));
					
					xSetInt(dMountainGiants, xSpecialNext, trTimeMS() + 1800);
					xSetInt(dMountainGiants, xSpecialStep, 1);
					trUnitOverrideAnimation(39,0,false,false,-1);
				}
			}
			case 1:
			{
				end = xGetVector(dMountainGiants,xSpecialTarget);
				db = opponentDatabaseName(p);
				for(x=xGetDatabaseCount(db); >0) {
					xDatabaseNext(db);
					xUnitSelectByID(db,xUnitID);
					if (trUnitAlive() == false) {
						removeOpponentUnit(p);
					} else if (unitDistanceToVector(xGetInt(db,xUnitName), end) < 4) {
						damageOpponentUnit(p, 100 + 100 * trQuestVarGet("stage"));
						if (xGetBool(db, xIsHero) && trCurrentPlayer() == xGetInt(db, xPlayerOwner)) {
							trCameraShake(0.7, 0.7);
						}
					}
				}
				trArmyDispatch("1,0","Dwarf",1,xsVectorGetX(end),0,xsVectorGetZ(end),45,true);
				trArmyDispatch("1,0","Dwarf",1,xsVectorGetX(end),0,xsVectorGetZ(end),135,false);
				trArmySelect("1,0");
				trUnitChangeProtoUnit("Tartarian Gate Flame");
				xSetInt(dMountainGiants, xSpecialStep, 2);
				xSetInt(dMountainGiants, xSpecialNext, xGetInt(dMountainGiants, xSpecialNext) + 1200);
				
			}
			case 2:
			{
				xSetInt(dMountainGiants, xSpecialStep, 0);
				xSetInt(dMountainGiants, xSpecialNext, trTimeMS() + 15000);
				trUnitOverrideAnimation(-1,0,false,true,-1);
			}
		}
	}
}
*/
