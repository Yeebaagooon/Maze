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

