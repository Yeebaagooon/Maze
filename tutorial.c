int heightofroad = 0;

int CurrentCell(int num = 0, int cellsize = 6, int cellpadding = 1){
	return(num*cellsize+cellpadding+1);
}

void PaintCell(int cellx = 0, int cellz = 0, int cellsize = 0, int cellpadding = 0, string terrainpaint = "CliffEgyptianA"){
	int PaintType = getTerrainType(terrainpaint);
	int PaintSubType = getTerrainSubType(terrainpaint);
	trPaintTerrain(cellx*cellsize+cellpadding,cellz*cellsize+cellpadding,cellx*cellsize+cellsize-cellpadding,cellz*cellsize+cellsize-cellpadding,PaintType,PaintSubType, false);
	trChangeTerrainHeight(cellx*cellsize+cellpadding,cellz*cellsize+cellpadding,cellx*cellsize+cellsize-cellpadding,cellz*cellsize+cellsize-cellpadding,heightofroad,false);
}

vector BuildFrontier(vector pos = vector(0,0,0), int maxnumberx = 0, int maxnumberz = 0, int cellsize = 6, int cellpadding = 1, string terrainsetcliff = "CliffEgyptianA", string terrainsetroad = "DirtA", string terrainfrontier = "CityTileWaterPool"){
	//Build the frontier around the selected cell
	int CellX = xsVectorGetX(pos);
	int CellZ = xsVectorGetZ(pos);
	int nextcell = cellsize+cellpadding;
	int CliffType = getTerrainType(terrainsetcliff);
	int CliffSubType = getTerrainSubType(terrainsetcliff);
	int RoadType = getTerrainType(terrainsetroad);
	int RoadSubType = getTerrainSubType(terrainsetroad);
	int FrontierType = getTerrainType(terrainfrontier);
	int FrontierSubType = getTerrainSubType(terrainfrontier);
	int Safety = 0;
	
	//0 CELL CODE
	//CellZ*cellsize+cellpadding+1
	
	//Check if right cell is valid, if can build there and terrain type is cliff
	if(CellX < (maxnumberx-1)){
		if((trGetTerrainType(CurrentCell((CellX+1), cellsize, cellpadding),CurrentCell(CellZ, cellsize, cellpadding)) == CliffType) && (trGetTerrainSubType(CurrentCell((CellX+1), cellsize, cellpadding),CurrentCell(CellZ, cellsize, cellpadding)) == CliffSubType)){
			PaintCell(CellX+1, CellZ, cellsize, cellpadding, terrainfrontier);
			//add to frontier db
			xAddDatabaseBlock(dFrontier, true);
			xSetInt(dFrontier, xCellXPos, CellX+1);
			xSetInt(dFrontier, xCellZPos, CellZ);
			xSetString(dFrontier, xDirectionToBuild, "left");
		}
	}
	if(CellZ < (maxnumberz-1)){
		if((trGetTerrainType(CurrentCell(CellX, cellsize, cellpadding),CurrentCell((CellZ+1), cellsize, cellpadding)) == CliffType) && (trGetTerrainSubType(CurrentCell(CellX, cellsize, cellpadding),CurrentCell((CellZ+1), cellsize, cellpadding)) == CliffSubType)){
			PaintCell(CellX, CellZ+1, cellsize, cellpadding, terrainfrontier);
			//add to frontier db
			xAddDatabaseBlock(dFrontier, true);
			xSetInt(dFrontier, xCellXPos, CellX);
			xSetInt(dFrontier, xCellZPos, CellZ+1);
			xSetString(dFrontier, xDirectionToBuild, "down");
		}
	}
	if(CellX > 0){
		if((trGetTerrainType(CurrentCell((CellX-1), cellsize, cellpadding),CurrentCell(CellZ, cellsize, cellpadding)) == CliffType) && (trGetTerrainSubType(CurrentCell((CellX-1), cellsize, cellpadding),CurrentCell(CellZ, cellsize, cellpadding)) == CliffSubType)){
			PaintCell(CellX-1, CellZ, cellsize, cellpadding, terrainfrontier);
			//add to frontier db
			xAddDatabaseBlock(dFrontier, true);
			xSetInt(dFrontier, xCellXPos, CellX-1);
			xSetInt(dFrontier, xCellZPos, CellZ);
			xSetString(dFrontier, xDirectionToBuild, "right");
		}
	}
	if(CellZ > 0){
		if((trGetTerrainType(CurrentCell(CellX, cellsize, cellpadding),CurrentCell((CellZ-1), cellsize, cellpadding)) == CliffType) && (trGetTerrainSubType(CurrentCell(CellX, cellsize, cellpadding),CurrentCell((CellZ-1), cellsize, cellpadding)) == CliffSubType)){
			PaintCell(CellX, CellZ-1, cellsize, cellpadding, terrainfrontier);
			//add to frontier db
			xAddDatabaseBlock(dFrontier, true);
			xSetInt(dFrontier, xCellXPos, CellX);
			xSetInt(dFrontier, xCellZPos, CellZ-1);
			xSetString(dFrontier, xDirectionToBuild, "up");
		}
	}
	return(pos);
}

void ConnectingMaze(int maxnumberx = 0, int maxnumberz = 0, int cellsize = 6, int cellpadding = 1, string terrainsetcliff = "CliffEgyptianA", string terrainsetroad = "DirtA", string terrainfrontier = "CityTileWaterPool", vector startpos = vector(0,0,0)){
	int CliffType = getTerrainType(terrainsetcliff);
	int CliffSubType = getTerrainSubType(terrainsetcliff);
	int RoadType = getTerrainType(terrainsetroad);
	int RoadSubType = getTerrainSubType(terrainsetroad);
	int FrontierType = getTerrainType(terrainfrontier);
	int FrontierSubType = getTerrainSubType(terrainfrontier);
	int Safety = 0;
	vector nil = vector(0,0,0);
	int CellStartX = xsVectorGetX(startpos);
	int CellStartZ = xsVectorGetZ(startpos);
	if((CellStartX == 0) && (CellStartZ == 0)){
		//randomise starting cell if not set
		trQuestVarSetFromRand("StartX", 0, (maxnumberx-1));
		trQuestVarSetFromRand("StartZ", 0, (maxnumberz-1));
		CellStartX = 1*trQuestVarGet("StartX");
		CellStartZ = 1*trQuestVarGet("StartZ");
	}
	
	//Create the cell meshwork
	for(a = 0; < maxnumberx){
		for(b = 0; < maxnumberz){
			trPaintTerrain(a*cellsize,b*cellsize,a*cellsize+cellsize,b*cellsize+cellsize,CliffType,CliffSubType, false);
			//trPaintTerrain(a*cellsize+cellpadding,b*cellsize+cellpadding,a*cellsize+cellsize-cellpadding,b*cellsize+cellsize-cellpadding,0,0, false);
			xAddDatabaseBlock(dMazeDB, true);
			xSetInt(dMazeDB, xCellXPos, a);
			xSetInt(dMazeDB, xCellZPos, b);
			xSetBool(dMazeDB, xCellConnected, false);
			xSetInt(dMazeDB, xCellConnections, 0);
			xSetBool(dMazeDB, xCellConnectedL, false);
			xSetBool(dMazeDB, xCellConnectedR, false);
			xSetBool(dMazeDB, xCellConnectedU, false);
			xSetBool(dMazeDB, xCellConnectedD, false);
		}
	}
	
	//Set starting cell
	PaintCell(CellStartX, CellStartZ, cellsize, cellpadding, terrainsetroad);
	
	//Build frontier
	BuildFrontier(xsVectorSet(CellStartX,0,CellStartZ), maxnumberx, maxnumberz, cellsize, cellpadding, terrainsetcliff,terrainsetroad, terrainfrontier);
	
	//Now while frontier exists, cycle through frontier db and connect
	int HoldX = 0;
	int HoldZ = 0;
	while(xGetDatabaseCount(dFrontier) > 0){
		Safety = Safety+1;
		
		if(Safety > maxnumberx*maxnumberz){
			trChatSend(0, "Break");
			break;
		}
		
		//choose random frontier tile
		trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dFrontier));
		xSetPointer(dFrontier, 1*trQuestVarGet("temp"));
		
		//trPaintTerrain(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
		//cellpaint
		
		//now connect it
		if(xGetString(dFrontier, xDirectionToBuild) == "up"){
			//paint the cell
			trPaintTerrain(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
			trChangeTerrainHeight(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding+1,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize+cellsize-cellpadding+1,heightofroad,false);
			HoldX = xGetInt(dFrontier, xCellXPos);
			HoldZ = xGetInt(dFrontier, xCellZPos);
			xFreeDatabaseBlock(dFrontier);
			BuildFrontier(xsVectorSet(HoldX,0,HoldZ), maxnumberx, maxnumberz, cellsize, cellpadding, terrainsetcliff,terrainsetroad, terrainfrontier);
			//trChatSend(0, "Frontier extended to cell X" + HoldX + " Z" + HoldZ);
		}
		if(xGetString(dFrontier, xDirectionToBuild) == "down"){
			//paint the cell
			trPaintTerrain(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding-cellsize,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
			trChangeTerrainHeight(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding-cellsize,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding+1,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding+1,heightofroad,false);
			HoldX = xGetInt(dFrontier, xCellXPos);
			HoldZ = xGetInt(dFrontier, xCellZPos);
			xFreeDatabaseBlock(dFrontier);
			BuildFrontier(xsVectorSet(HoldX,0,HoldZ), maxnumberx, maxnumberz, cellsize, cellpadding, terrainsetcliff,terrainsetroad, terrainfrontier);
			//trChatSend(0, "Frontier extended to cell X" + HoldX + " Z" + HoldZ);
		}
		
		if(xGetString(dFrontier, xDirectionToBuild) == "left"){
			//paint the cell
			trPaintTerrain(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding-cellsize,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
			trChangeTerrainHeight(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding-cellsize,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize-cellpadding+1,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding+1,heightofroad,false);
			HoldX = xGetInt(dFrontier, xCellXPos);
			HoldZ = xGetInt(dFrontier, xCellZPos);
			xFreeDatabaseBlock(dFrontier);
			BuildFrontier(xsVectorSet(HoldX,0,HoldZ), maxnumberx, maxnumberz, cellsize, cellpadding, terrainsetcliff,terrainsetroad, terrainfrontier);
			//trChatSend(0, "Frontier extended to cell X" + HoldX + " Z" + HoldZ);
		}
		
		if(xGetString(dFrontier, xDirectionToBuild) == "right"){
			//paint the cell
			trPaintTerrain(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize+cellsize-cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
			trChangeTerrainHeight(xGetInt(dFrontier, xCellXPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellZPos)*cellsize+cellpadding,xGetInt(dFrontier, xCellXPos)*cellsize+cellsize+cellsize-cellpadding+1,xGetInt(dFrontier, xCellZPos)*cellsize+cellsize-cellpadding+1,heightofroad,false);
			HoldX = xGetInt(dFrontier, xCellXPos);
			HoldZ = xGetInt(dFrontier, xCellZPos);
			xFreeDatabaseBlock(dFrontier);
			BuildFrontier(xsVectorSet(HoldX,0,HoldZ), maxnumberx, maxnumberz, cellsize, cellpadding, terrainsetcliff,terrainsetroad, terrainfrontier);
			//trChatSend(0, "Frontier extended to cell X" + HoldX + " Z" + HoldZ);
		}
		
		
		
	}
	//Extra wall breaks
	//This is lazy, cna do invalid breaks to the edge and doesnt check to see if already broken
	
	
	int CellX = 0;
	int CellZ = 0;
	for(a = 0 ; < maxnumberx+maxnumberz*2){
		trQuestVarSetFromRand("CellX", 0, (maxnumberx-1));
		trQuestVarSetFromRand("CellZ", 0, (maxnumberz-1));
		trQuestVarSetFromRand("dir", 1, 4);
		CellX = 1*trQuestVarGet("CellX");
		CellZ = 1*trQuestVarGet("CellZ");
		switch(1*trQuestVarGet("dir"))
		{
			case 1:
			{
				if(CellZ < (maxnumberx-1)){
					//break L
					trPaintTerrain(1*trQuestVarGet("CellX")*cellsize+cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellpadding,1*trQuestVarGet("CellX")*cellsize+cellsize-cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					trChangeTerrainHeight(1*trQuestVarGet("CellX")*cellsize+cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellpadding,1*trQuestVarGet("CellX")*cellsize+cellsize-cellpadding+1,1*trQuestVarGet("CellZ")*cellsize+cellsize+cellsize-cellpadding+1,heightofroad,false);
				}
			}
			case 2:
			{
				if(CellZ > 0){
					//break R
					trPaintTerrain(1*trQuestVarGet("CellX")*cellsize+cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellpadding-cellsize,1*trQuestVarGet("CellX")*cellsize+cellsize-cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					trChangeTerrainHeight(1*trQuestVarGet("CellX")*cellsize+cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellpadding-cellsize,1*trQuestVarGet("CellX")*cellsize+cellsize-cellpadding+1,1*trQuestVarGet("CellZ")*cellsize+cellsize-cellpadding+1,heightofroad,false);
				}
			}
			case 3:
			{
				if(CellX > 0){
					//Break D
					trPaintTerrain(1*trQuestVarGet("CellX")*cellsize+cellpadding-cellsize,1*trQuestVarGet("CellZ")*cellsize+cellpadding,1*trQuestVarGet("CellX")*cellsize+cellsize-cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					trChangeTerrainHeight(1*trQuestVarGet("CellX")*cellsize+cellpadding-cellsize,1*trQuestVarGet("CellZ")*cellsize+cellpadding,1*trQuestVarGet("CellX")*cellsize+cellsize-cellpadding+1,1*trQuestVarGet("CellZ")*cellsize+cellsize-cellpadding+1,heightofroad,false);
				}
			}
			case 4:
			{
				if(CellX < (maxnumberx-1)){
					//Break Up
					trPaintTerrain(1*trQuestVarGet("CellX")*cellsize+cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellpadding,1*trQuestVarGet("CellX")*cellsize+cellsize+cellsize-cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					trChangeTerrainHeight(1*trQuestVarGet("CellX")*cellsize+cellpadding,1*trQuestVarGet("CellZ")*cellsize+cellpadding,1*trQuestVarGet("CellX")*cellsize+cellsize+cellsize-cellpadding+1,1*trQuestVarGet("CellZ")*cellsize+cellsize-cellpadding+1,heightofroad,false);
				}
			}
		}
	}
	
	//Blob detect
	for(x = 1; < maxnumberx){
		for(z = 1; < maxnumberz){
			if(trGetTerrainType(CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding) == CliffType){
				//trPaintTerrain(CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding,CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding,0,0);
				//cofnrim cliff corner, now check +-xz*4 for road
				if(trGetTerrainType(CurrentCell(x, cellsize, cellpadding),CurrentCell(z, cellsize, cellpadding)-cellpadding) == RoadType){
					if(trGetTerrainType(CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)) == RoadType){
						if(trGetTerrainType(CurrentCell(x, cellsize, cellpadding)-cellsize,CurrentCell(z, cellsize, cellpadding)-cellpadding) == RoadType){
							if(trGetTerrainType(CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellsize) == RoadType){
								//its a blob, delete it
								//trPaintTerrain(CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding,CurrentCell(x, cellsize, cellpadding)-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding,0,0);
								trPaintTerrain(CurrentCell(x, cellsize, cellpadding)-cellpadding-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding-cellpadding,CurrentCell(x, cellsize, cellpadding)-cellpadding+1,CurrentCell(z, cellsize, cellpadding)-cellpadding+1,RoadType, RoadSubType);
								trChangeTerrainHeight(CurrentCell(x, cellsize, cellpadding)-cellpadding-cellpadding,CurrentCell(z, cellsize, cellpadding)-cellpadding-cellpadding,CurrentCell(x, cellsize, cellpadding)-cellpadding+1,CurrentCell(z, cellsize, cellpadding)-cellpadding+1,heightofroad,false);
							}
						}
					}
				}
			}
		}
	}
	
	//HunterBase
	trPaintTerrain(CurrentCell(maxnumberx/2-1, cellsize, cellpadding)-1,CurrentCell(maxnumberz/2-1, cellsize, cellpadding)-1,CurrentCell(maxnumberx/2, cellsize, cellpadding)+cellpadding+1,CurrentCell(maxnumberz/2, cellsize, cellpadding)+cellpadding+1,RoadType, RoadSubType);
	trChangeTerrainHeight(CurrentCell(maxnumberx/2-1, cellsize, cellpadding)-1,CurrentCell(maxnumberz/2-1, cellsize, cellpadding)-1,CurrentCell(maxnumberx/2, cellsize, cellpadding)+cellpadding+2,CurrentCell(maxnumberz/2, cellsize, cellpadding)+cellpadding+2,heightofroad,false);
	UnitCreate(0, "Phoenix", 199,199);
}





void BasicMaze(int x = 0, int z = 0, int maxnumberx = 4, int maxnumberz = 4, int cellsize = 6, int cellpadding = 1, string terrainsetcliff = "CliffEgyptianA", string terrainsetroad = "CityTileWaterPool"){
	/*
	INSTRUCTIONS: Makes a basic maze, does not guarantee connections. Bug is to change all terrain to road type to avoid those odd grass A areas.
	xz = offset, currently doesnt do anything
	maxnumbers = number of 'cells'
	size of terrain, and padding for cliff boundary
	Then terrain types
	
	*/
	int CliffType = getTerrainType(terrainsetcliff);
	int CliffSubType = getTerrainSubType(terrainsetcliff);
	int RoadType = getTerrainType(terrainsetroad);
	int RoadSubType = getTerrainSubType(terrainsetroad);
	int Safety = 0;
	//Create the cell meshwork
	for(a = 0; < maxnumberx){
		for(b = 0; < maxnumberz){
			trPaintTerrain(a*cellsize,b*cellsize,a*cellsize+cellsize,b*cellsize+cellsize,CliffType,CliffSubType, false);
			trPaintTerrain(a*cellsize+cellpadding,b*cellsize+cellpadding,a*cellsize+cellsize-cellpadding,b*cellsize+cellsize-cellpadding,0,0, false);
			xAddDatabaseBlock(dMazeDB, true);
			xSetInt(dMazeDB, xCellXPos, a);
			xSetInt(dMazeDB, xCellZPos, b);
			xSetBool(dMazeDB, xCellConnected, false);
			xSetInt(dMazeDB, xCellConnections, 0);
			xSetBool(dMazeDB, xCellConnectedL, false);
			xSetBool(dMazeDB, xCellConnectedR, false);
			xSetBool(dMazeDB, xCellConnectedU, false);
			xSetBool(dMazeDB, xCellConnectedD, false);
		}
	}
	
	//Now look at each one and assign a connection
	for(c = xGetDatabaseCount(dMazeDB); > 0){
		xDatabaseNext(dMazeDB);
		while(xGetBool(dMazeDB, xCellConnected) == false){
			//randomise a direction and then connect
			trQuestVarSetFromRand("dir", 1, 4, true);
			//trChatSend(0, ""+1*trQuestVarGet("dir"));
			//1 +x, 2 +z, 3-x, 4-z
			//If bugs here, check the condition under build connection
			if((1*trQuestVarGet("dir") == 1) && (xGetInt(dMazeDB, xCellXPos) < (maxnumberx-1))){
				//build connection right
				if(trGetTerrainType(xGetInt(dMazeDB, xCellXPos)*cellsize+cellsize+cellpadding-1,xGetInt(dMazeDB, xCellZPos)*cellsize+cellpadding+1) != RoadType){
					trPaintTerrain(xGetInt(dMazeDB, xCellXPos)*cellsize+cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellpadding,xGetInt(dMazeDB, xCellXPos)*cellsize+cellsize+cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					xSetBool(dMazeDB, xCellConnected, true);
					xSetBool(dMazeDB, xCellConnectedR, true);
				}
			}
			
			if((1*trQuestVarGet("dir") == 3) && (xGetInt(dMazeDB, xCellXPos) > 0)){
				//build connection left
				if(trGetTerrainType(xGetInt(dMazeDB, xCellXPos)*cellsize-cellpadding+1,xGetInt(dMazeDB, xCellZPos)*cellsize+cellpadding+1) != RoadType){
					trPaintTerrain(xGetInt(dMazeDB, xCellXPos)*cellsize-cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellpadding,xGetInt(dMazeDB, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					xSetBool(dMazeDB, xCellConnected, true);
					xSetBool(dMazeDB, xCellConnectedL, true);
				}
			}
			
			if((1*trQuestVarGet("dir") == 4) && (xGetInt(dMazeDB, xCellZPos) > 0)){
				//build connection down
				if(trGetTerrainType(xGetInt(dMazeDB, xCellXPos)*cellsize+cellpadding+1, xGetInt(dMazeDB, xCellZPos)*cellsize-cellpadding+1) != RoadType){
					trPaintTerrain(xGetInt(dMazeDB, xCellXPos)*cellsize+cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize-cellpadding,xGetInt(dMazeDB, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellsize-cellpadding,RoadType,RoadSubType, false);
					xSetBool(dMazeDB, xCellConnected, true);
					xSetBool(dMazeDB, xCellConnectedD, true);
				}
				
			}
			
			if((1*trQuestVarGet("dir") == 2) && (xGetInt(dMazeDB, xCellZPos) < (maxnumberz-1))){
				//build connection up
				if(trGetTerrainType(xGetInt(dMazeDB, xCellXPos)*cellsize+cellpadding+1, xGetInt(dMazeDB, xCellZPos)*cellsize+cellsize+cellpadding-1) != RoadType){
					trPaintTerrain(xGetInt(dMazeDB, xCellXPos)*cellsize+cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellpadding,xGetInt(dMazeDB, xCellXPos)*cellsize+cellsize-cellpadding,xGetInt(dMazeDB, xCellZPos)*cellsize+cellsize+cellpadding,RoadType,RoadSubType, false);
					xSetBool(dMazeDB, xCellConnected, true);
					xSetBool(dMazeDB, xCellConnectedU, true);
				}
				
			}
			
			// NOW CHECK ALL CONNECTED
			Safety=Safety+1;
			/*if(Safety > maxnumberx*maxnumberz*2){
				break;
				trChatSend(0, "BREAK");
			}*/
		}
	}
}



rule PaintTerrain
highFrequency
inactive
{
	xsDisableSelf();
	//BasicMaze(0,0,24,24,4,1,"CliffEgyptianA");
	ConnectingMaze(18,18,11,3, "CliffGreekA", "OlympusTile");
	refreshPassability();
	UnitCreate(1, "Villager Atlantean Hero",5,5);
	
	/*
	Set start tile
	All valid adjacent tiles are coloured, these are fronteir
	paint one fronteir at random and remove from database
	Need to store where it came from for every number of the db
	
	*/
}


/*
rule ysearch
inactive
highFrequency
{
	int id = 0;
	int unittype = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
	for(i = spysearch; < trGetNextUnitScenarioNameNumber()) {
		id = kbGetBlockID(""+i, true);
		unittype = kbGetUnitBaseTypeID(id);
		switch(unittype)
		{
			case kbGetProtoUnitID("Spy Eye"):
			{
				if (xGetDatabaseCount(dSpyRequests) > 0) {
					scale = xGetVector(dSpyRequests, xSpyRequestScale);
					dest = xGetVector(dSpyRequests, xSpyRequestDest);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trMutateSelected(xGetInt(dSpyRequests, xSpyRequestProto));
					trSetSelectedScale(xsVectorGetX(scale),xsVectorGetY(scale),xsVectorGetZ(scale));
					trUnitOverrideAnimation(xGetInt(dSpyRequests, xSpyRequestAnim),0,true,false,-1);
					trEventFire(xGetInt(dSpyRequests, xSpyRequestEvent));
					if (aiPlanSetUserVariableInt(1*xsVectorGetX(dest),1*xsVectorGetY(dest),1*xsVectorGetZ(dest),i) == false) {
						debugLog("spy error N/A: " + 1*xsVectorGetX(dest) + "," + 1*xsVectorGetY(dest) + "," + 1*xsVectorGetZ(dest));
					}
					xFreeDatabaseBlock(dSpyRequests);
					spyreset = 0;
				} else {
					debugLog("Spy Buffer is empty");
				}
				break;
			}
			case kbGetProtoUnitID("House"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}
			case kbGetProtoUnitID("Hero Birth"):
			{
				debugLog("spysearch: " + i);
			}
		}
	}
	if (xGetDatabaseCount(dSpyRequests) > 0) {
		spyreset = spyreset + 1;
		if (spyreset >= 10) {
			debugLog("Spy reset. Failed requests: " + xGetDatabaseCount(dSpyRequests));
			xClearDatabase(dSpyRequests);
			spyreset = 0;
		}
	}
	spysearch = trGetNextUnitScenarioNameNumber();
}
*/
