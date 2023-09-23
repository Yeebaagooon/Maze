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

//Mountain giants
int dMountainGiants = 0;
int xMountainGiantID = 0;
int xPlayerOwner = 0;
int xSpecialNext = 0;
int xSpecialStep = 0;
int xSpecialTarget = 0;
int xSpecialTargetID = 0;

//Towers
int dTowers = 0;
int xTowerName = 0;

//EQ
int dEarthquake = 0;
int xEarthquakeName = 0;
int xEarthquakeOwner = 0;
int xEarthquakeTimeout = 0;

//Hekas giants
int dHekas = 0;
int xHekaID = 0;

//Lampades
int dLampades = 0;
int xLampadesID = 0;

//birds
int dBirds = 0;
int xBirdID = 0;
int xYeebID = 0;
int xYeebAnim = 0;

//terain
int dTerrainResetDB = 0;
int xMinX = 0;
int xMaxX = 0;
int xMinZ = 0;
int xMaxZ = 0;
int xTimeReset = 0;
int xXDir = 0;

//volcano
int dVolcanoDB = 0;
int xVolcanoName = 0;
int xVolcanoPos = 0;
int xVolcanoTiles = 0;
int xVolcanoTime = 0;
int xVolcanoLink = 0;
int xVolcanoNextTime = 0;

int dVolcanoFrontierDB = 0;
int xVFPosX = 0;
int xVFPosZ = 0;
int xVFTime = 0;
int xVFPainted = 0;
int xVFLink = 0;

int dTerrainRepaintDB = 0;
int xTileX = 0;
int xTileZ = 0;
int xTime = 0;

int dBuildings = 0;


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
	
	dMountainGiants = xInitDatabase("MG DB");
	xMountainGiantID = xInitAddInt(dMountainGiants, "id", -1);
	xPlayerOwner = xInitAddInt(dMountainGiants, "owner", 0);
	xSpecialNext = xInitAddInt(dMountainGiants, "time", 0);
	xSpecialStep = xInitAddInt(dMountainGiants, "status", 0);
	xSpecialTarget = xInitAddVector(dMountainGiants, "target", vector(0,0,0));
	xSpecialTargetID = xInitAddInt(dMountainGiants, "status", 0);
	
	dTowers = xInitDatabase("towerdb");
	xTowerName = xInitAddInt(dTowers, "name", -1);
	xPlayerOwner = xInitAddInt(dTowers, "owner", 0);
	
	dEarthquake = xInitDatabase("eqdb");
	xEarthquakeName = xInitAddInt(dEarthquake, "name", -1);
	xEarthquakeOwner = xInitAddInt(dEarthquake, "owner", -1);
	xEarthquakeTimeout = xInitAddInt(dEarthquake, "timeout", 1);
	
	dHekas = xInitDatabase("Heka DB");
	xHekaID = xInitAddInt(dHekas, "id", -1);
	xPlayerOwner = xInitAddInt(dHekas, "owner", 0);
	xSpecialNext = xInitAddInt(dHekas, "time", 0);
	xSpecialStep = xInitAddInt(dHekas, "status", 0);
	xSpecialTarget = xInitAddVector(dHekas, "target", vector(0,0,0));
	xSpecialTargetID = xInitAddInt(dHekas, "status", 0);
	
	dLampades = xInitDatabase("Lampade DB");
	xLampadesID = xInitAddInt(dLampades, "id", -1);
	xPlayerOwner = xInitAddInt(dLampades, "owner", 0);
	xSpecialNext = xInitAddInt(dLampades, "time", 0);
	xSpecialStep = xInitAddInt(dLampades, "status", 0);
	xSpecialTarget = xInitAddVector(dLampades, "target", vector(0,0,0));
	xSpecialTargetID = xInitAddInt(dLampades, "status", 0);
	
	dBirds = xInitDatabase("Lampade DB");
	xBirdID = xInitAddInt(dBirds, "id", -1);
	xPlayerOwner = xInitAddInt(dBirds, "owner", 0);
	xSpecialNext = xInitAddInt(dBirds, "time", 0);
	xSpecialStep = xInitAddInt(dBirds, "status", 0);
	xSpecialTarget = xInitAddVector(dBirds, "target", vector(0,0,0));
	xSpecialTargetID = xInitAddInt(dBirds, "status", 0);
	xYeebID = xInitAddInt(dBirds, "yeebid", 0);
	xYeebAnim = xInitAddInt(dBirds, "yeebid", 0);
	
	
	dTerrainResetDB = xInitDatabase("terraindb");
	xMinX = xInitAddInt(dTerrainResetDB, "minx", 0);
	xMaxX = xInitAddInt(dTerrainResetDB, "maxx", 0);
	xMinZ = xInitAddInt(dTerrainResetDB, "minz", 0);
	xMaxZ = xInitAddInt(dTerrainResetDB, "maxz", 0);
	xTimeReset = xInitAddInt(dTerrainResetDB, "timereset", 0);
	xXDir = xInitAddBool(dTerrainResetDB, "xXDir", true);
	
	dVolcanoDB = xInitDatabase("volcanoDB");
	xVolcanoPos = xInitAddVector(dVolcanoDB, "startpos", vector(0,0,0));
	xVolcanoTiles = xInitAddInt(dVolcanoDB, "tilecount", 0);
	xVolcanoTime = xInitAddInt(dVolcanoDB, "timesinceinvoke", 0);
	xVolcanoLink = xInitAddInt(dVolcanoDB, "linkint", 0);
	xVolcanoNextTime = xInitAddInt(dVolcanoDB, "nextlava", 0);
	
	dVolcanoFrontierDB = xInitDatabase("volcanofrontDB");
	xVolcanoName = xInitAddInt(dVolcanoDB, "name", -1);
	xVFPosX = xInitAddInt(dVolcanoFrontierDB, "posxvf", 0);
	xVFPosZ = xInitAddInt(dVolcanoFrontierDB, "poszvf", 0);
	xVFTime = xInitAddInt(dVolcanoFrontierDB, "timemade", 0);
	xVFPainted = xInitAddBool(dVolcanoFrontierDB, "painted", false);
	xVFLink = xInitAddInt(dVolcanoFrontierDB, "linkint", 0);
	
	dTerrainRepaintDB = xInitDatabase("terrainreset");
	xTileX = xInitAddInt(dTerrainRepaintDB, "x", 0);
	xTileZ = xInitAddInt(dTerrainRepaintDB, "z", 0);
	xTime = xInitAddInt(dTerrainRepaintDB, "time", 0);
	
	dBuildings = xInitDatabase("buildingdb");
	xUnitName = xInitAddInt(dBuildings, "name", -1);
	xPlayerOwner = xInitAddInt(dBuildings, "owner", 0);
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

void BuildCliff(vector target = vector(0,0,0)){
	int TilesX = 0;
	int TilesZ = 0;
	target = xsVectorSet(xsVectorGetX(target)/2,5,xsVectorGetZ(target)/2);
	int XTPlus = 0;
	int XTNeg = 0;
	bool HitPlus = false;
	bool HitNegative = false;
	while(HitPlus == false){
		XTPlus = XTPlus+1;
		if(trGetTerrainType(xsVectorGetX(target)+XTPlus,xsVectorGetZ(target)) == getTerrainType(CliffTerrain)){
			HitPlus = true;
		}
	}
	while(HitNegative == false){
		XTNeg = XTNeg-1;
		if(trGetTerrainType(xsVectorGetX(target)+XTNeg,xsVectorGetZ(target)) == getTerrainType(CliffTerrain)){
			HitNegative = true;
		}
	}
	TilesX = XTPlus-XTNeg;
	
	int YTPlus = 0;
	int YTNeg = 0;
	bool YHitPlus = false;
	bool YHitNegative = false;
	while(YHitPlus == false){
		YTPlus = YTPlus+1;
		if(trGetTerrainType(xsVectorGetX(target),xsVectorGetZ(target)+YTPlus) == getTerrainType(CliffTerrain)){
			YHitPlus = true;
		}
	}
	while(YHitNegative == false){
		YTNeg = YTNeg-1;
		if(trGetTerrainType(xsVectorGetX(target),xsVectorGetZ(target)+YTNeg) == getTerrainType(CliffTerrain)){
			YHitNegative = true;
		}
	}
	TilesZ = YTPlus-YTNeg;
	
	if(TilesZ < TilesX){
		//paint z
		trPaintTerrain(xsVectorGetX(target)-1,xsVectorGetZ(target)+YTNeg-1,xsVectorGetX(target)+1,xsVectorGetZ(target)+YTPlus+1,getTerrainType(CliffTerrain), getTerrainSubType(CliffTerrain));
		trChangeTerrainHeight(xsVectorGetX(target),xsVectorGetZ(target)+YTNeg,xsVectorGetX(target)+1,xsVectorGetZ(target)+YTPlus+1,5);
		xAddDatabaseBlock(dTerrainResetDB, true);
		xSetInt(dTerrainResetDB, xMinX, xsVectorGetX(target)-1);
		xSetInt(dTerrainResetDB, xMinZ, xsVectorGetZ(target)+YTNeg-1);
		xSetInt(dTerrainResetDB, xMaxX, xsVectorGetX(target)+1);
		xSetInt(dTerrainResetDB, xMaxZ, xsVectorGetZ(target)+YTPlus+1);
		xSetInt(dTerrainResetDB, xTimeReset, trTime()+10);
		xSetBool(dTerrainResetDB, xXDir, true);
	}
	else{
		//paint x
		trPaintTerrain(xsVectorGetX(target)+XTNeg-1,xsVectorGetZ(target)-1,xsVectorGetX(target)+XTPlus+1,xsVectorGetZ(target)+1,getTerrainType(CliffTerrain), getTerrainSubType(CliffTerrain));
		trChangeTerrainHeight(xsVectorGetX(target)+XTNeg,xsVectorGetZ(target),xsVectorGetX(target)+XTPlus+1,xsVectorGetZ(target)+1,5);
		xAddDatabaseBlock(dTerrainResetDB, true);
		xSetInt(dTerrainResetDB, xMinX, xsVectorGetX(target)+XTNeg-1);
		xSetInt(dTerrainResetDB, xMinZ, xsVectorGetZ(target)-1);
		xSetInt(dTerrainResetDB, xMaxX, xsVectorGetX(target)+XTPlus+1);
		xSetInt(dTerrainResetDB, xMaxZ, xsVectorGetZ(target)+1);
		xSetInt(dTerrainResetDB, xTimeReset, trTime()+10);
		xSetBool(dTerrainResetDB, xXDir, false);
	}
	refreshPassability();
}
