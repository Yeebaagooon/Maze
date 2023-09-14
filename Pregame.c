rule PregameBegin
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		//fade out when loaded
		Pregame = true;
		trMessageSetText("The host is now choosing hunter settings", 9000);
		PlayerChoice(1, "Please choose the hunter setup", "Allocate at random", 1, "Let people choose", 2);
		PregameTimeout = trTime()+10;
		trCounterAddTime("cdchoice", 10,0, "Hunters chosen at random", -1);
		xsEnableRule("HuntersTimeout");
		xsDisableSelf();
	}
}

rule PregameSkip
inactive
highFrequency
{
	for(p = 1; < cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xRoleDefined) == false){
				xSetBool(dPlayerData, xRoleDefined, true);
				xSetBool(dPlayerData, xPlayerRunner, true);
				RunnerCount = RunnerCount+1;
			}
		}
	}
	int comp = cNumberNonGaiaPlayers;
	xSetPointer(dPlayerData, comp);
	xSetBool(dPlayerData, xRoleDefined, true);
	xSetBool(dPlayerData, xPlayerRunner, false);
	HunterNumber = 1;
	xsDisableSelf();
	xsEnableRule("AssignmentCommonEnd");
}

rule HuntersTimeout
inactive
highFrequency
{
	if(trTime() >= PregameTimeout){
		gadgetUnreal("ShowChoiceBox");
		unitTransform(""+YesChoiceUnitName + " Hero", "Cinematic Block");
		unitTransform(""+NoChoiceUnitName + " Hero", "Cinematic Block");
		xsDisableSelf();
		xsEnableRule("ChooseHuntersRandom");
	}
}

rule BeginChooseHunters
inactive
highFrequency
{
	xsDisableSelf();
	DestroyAbove = trGetNextUnitScenarioNameNumber();
	//trPaintTerrain(CurrentCell(maxnumberx/2-1, cellsize, cellpadding)-1,CurrentCell(maxnumberz/2-1, cellsize, cellpadding)-1,CurrentCell(maxnumberx/2, cellsize, cellpadding)+cellpadding+1,CurrentCell(maxnumberz/2, cellsize, cellpadding)+cellpadding+1,getTerrainType("HadesBuildable1"), getTerrainSubType("HadesBuildable1"));
	PaintAtlantisArea(15,15,35,35,getTerrainType("IceA"),getTerrainSubType("IceA"));
	PaintAtlantisArea(15,23,19,27,getTerrainType("IceB"),getTerrainSubType("IceB"));
	PaintAtlantisArea(31,23,35,27,getTerrainType("IceB"),getTerrainSubType("IceB"));
	//Maybe a nice circle of columns and player flags
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xPlayerUnitID, trGetNextUnitScenarioNameNumber());
			UnitCreate(p, "Old Man", 50,48-cNumberNonGaiaPlayers+p*2,0);
		}
	}
	UnitCreate(0, "Villager Atlantean Hero", 34,50,90);
	UnitCreate(0, "Tartarian Gate Spawn", 66,50,270);
	trMessageSetText("Move your old man to your desired team", 6000);
	ChoiceTimeout = trTime()+25;
	trCounterAddTime("cdchoicehunt", 25,0, "Players randomised", -1);
	xsEnableRule("AssignRemaining");
	int PlayersA = 0;
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			PlayersA = PlayersA+1;
		}
	}
	if(PlayersA <= 5){
		HunterNumber = 1;
		ColouredIconChat("1,0.5,0", "icons\improvement monsterous rage icon 64", "this game requires " + HunterNumber + " hunters");
	}
	else if((PlayersA > 5) && (PlayersA <=7)){
		HunterNumber = 2;
		ColouredIconChat("1,0.5,0", "icons\improvement monsterous rage icon 64", " this game requires " + HunterNumber + " hunters");
	}
	else if((PlayersA > 7) && (PlayersA <=11)){
		HunterNumber = 3;
		ColouredIconChat("1,0.5,0", "icons\improvement monsterous rage icon 64", " this game requires " + HunterNumber + " hunters");
	}
	else if(PlayersA == 12){
		HunterNumber = 4;
		ColouredIconChat("1,0.5,0", "icons\improvement monsterous rage icon 64", " this game requires " + HunterNumber + " hunters");
	}
	int RunnersRequired = PlayersA-HunterNumber;
	float baseCos = xsCos(6.283185 / RunnersRequired);
	float baseSin = xsSin(6.283185 / RunnersRequired);
	trVectorQuestVarSet("start", vector(34,0,50));
	trVectorQuestVarSet("dir", vector(5,0,0));
	for(a=1; <= RunnersRequired) {
		trVectorQuestVarSet("build", trVectorQuestVarGet("start") + trVectorQuestVarGet("dir"));
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trQuestVarSet("RunnerCol" + a, trGetNextUnitScenarioNameNumber());
		UnitCreate(0, "Columns", trVectorQuestVarGetX("build"), trVectorQuestVarGetZ("build"));
	}
	
	baseCos = xsCos(6.283185 / HunterNumber);
	baseSin = xsSin(6.283185 / HunterNumber);
	trVectorQuestVarSet("start", vector(66,0,50));
	trVectorQuestVarSet("dir", vector(5,0,0));
	for(a=1; <= HunterNumber) {
		trVectorQuestVarSet("build", trVectorQuestVarGet("start") + trVectorQuestVarGet("dir"));
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trQuestVarSet("HunterCol" + a, trGetNextUnitScenarioNameNumber());
		UnitCreate(0, "Columns", trVectorQuestVarGetX("build"), trVectorQuestVarGetZ("build"));
	}
	//make the columns and flags
	//SPAWN PLAYERS
	xsEnableRule("CheckChoice");
}

rule CheckChoice
inactive
highFrequency
{
	if(Pregame == true){
		CyclePlayers = CyclePlayers+1;
		vector pos = vector(0,0,0);
		if(CyclePlayers > cNumberNonGaiaPlayers){
			CyclePlayers = 1;
		}
		int p = CyclePlayers;
		xSetPointer(dPlayerData, p);
		if(xGetBool(dPlayerData, xRoleDefined) == false){
			pos =  kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID));
			if(xsVectorGetX(pos) < 40){
				//choose runner
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xPlayerUnitID));
				trUnitChangeProtoUnit("Hero Death");
				xSetBool(dPlayerData, xRoleDefined, true);
				xSetBool(dPlayerData, xPlayerRunner, true);
				RunnerCount = RunnerCount+1;
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("RunnerCol"+RunnerCount));
				trUnitChangeProtoUnit("Flag");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("RunnerCol"+RunnerCount));
				trUnitConvert(p);
				trUnitSetAnimationPath("0,0,0,0,0,0");
			}
			if(xsVectorGetX(pos) > 62){
				//choose hunter
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xPlayerUnitID));
				trUnitChangeProtoUnit("Hero Death");
				xSetBool(dPlayerData, xRoleDefined, true);
				xSetBool(dPlayerData, xPlayerRunner, false);
				HunterCount = HunterCount+1;
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("HunterCol"+HunterCount));
				trUnitChangeProtoUnit("Flag");
				trUnitSelectClear();
				trUnitSelect(""+1*trQuestVarGet("HunterCol"+HunterCount));
				trUnitConvert(p);
				trUnitSetAnimationPath("0,0,0,0,0,0");
			}
		}
		if(HunterCount == HunterNumber){
			//end
			xsDisableSelf();
			trCounterAbort("cdchoicehunt");
			xsEnableRule("AssignEveryoneRunner");
			xsDisableRule("AssignRemaining");
			ChoiceTimeout = 999999;
		}
		if(RunnerCount == (cNumberNonGaiaPlayers-HunterNumber)){
			xsDisableSelf();
			trCounterAbort("cdchoicehunt");
			xsEnableRule("AssignEveryoneHunter");
			xsDisableRule("AssignRemaining");
			ChoiceTimeout = 999999;
		}
	}
}

rule AssignEveryoneRunner
inactive
highFrequency
{
	xsDisableSelf();
	xsEnableRule("AssignmentCommonEnd");
	
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xRoleDefined) == false){
				xSetBool(dPlayerData, xRoleDefined, true);
				xSetBool(dPlayerData, xPlayerRunner, true);
			}
		}
	}
}

rule AssignEveryoneHunter
inactive
highFrequency
{
	xsDisableSelf();
	xsEnableRule("AssignmentCommonEnd");
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xRoleDefined) == false){
				xSetBool(dPlayerData, xRoleDefined, true);
				xSetBool(dPlayerData, xPlayerRunner, false);
			}
		}
	}
}


rule AssignRemaining
inactive
highFrequency
{
	int a = 0;
	if((trTime()) >= ChoiceTimeout){
		xsDisableSelf();
		xsEnableRule("AssignmentCommonEnd");
		for(p = 1; <= cNumberNonGaiaPlayers){
			if(playerIsPlaying(p)){
				xSetPointer(dPlayerData, p);
				if(xGetBool(dPlayerData, xRoleDefined) == false){
					if(HunterCount == HunterNumber){
						xSetBool(dPlayerData, xRoleDefined, true);
						xSetBool(dPlayerData, xPlayerRunner, true);
					}
					else if(RunnerCount == (cNumberNonGaiaPlayers-HunterNumber)){
						xSetBool(dPlayerData, xRoleDefined, true);
						xSetBool(dPlayerData, xPlayerRunner, false);
					}
					else{
						trQuestVarSetFromRand("temp", 1, 3);
						xSetBool(dPlayerData, xRoleDefined, true);
						if(1*trQuestVarGet("temp") == 1){
							xSetBool(dPlayerData, xPlayerRunner, false);
							HunterCount = HunterCount+1;
						}
						else{
							xSetBool(dPlayerData, xPlayerRunner, true);
							RunnerCount = RunnerCount+1;
						}
						//randomise
					}
				}
			}
		}
	}
}



rule AssignmentCommonEnd
inactive
highFrequency
{
	xsDisableSelf();
	xsEnableRule("Removepregamestuff");
	xsEnableRule("SetGameDiplomacy");
	trLetterBox(true);
	trUIFadeToColor(0,0,0,750,100,true);
	for(p = 1; <= cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		xSetBool(dPlayerData, xRoleDefined, true);
		if(xGetBool(dPlayerData, xPlayerRunner) == false){
			if(trCurrentPlayer() == p){
				OverlayTextPlayerColor(p);
				trOverlayText("You are a Hunter", 8.0, 534, 300, 1000);
			}
		}
		else{
			if(trCurrentPlayer() == p){
				OverlayTextPlayerColor(p);
				trOverlayText("You are a Runner", 8.0, 534, 300, 1000);
			}
		}
	}
}

//Rule name everyone hunter/runner/random allocate whoever left

rule Removepregamestuff
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		xsDisableSelf();
		for(a = DestroyAbove; < trGetNextUnitScenarioNameNumber()){
			trUnitSelectClear();
			trUnitSelect(""+a);
			trUnitDestroy();
		}
	}
}

rule ChooseHuntersRandom
inactive
highFrequency
{
	trLetterBox(true);
	trUIFadeToColor(0,0,0,1,1,true);
	int Safety = 0;
	int PlayersA = 0;
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			PlayersA = PlayersA+1;
		}
	}
	if(PlayersA <= 5){
		HunterNumber = 1;
	}
	else if((PlayersA > 5) && (PlayersA <=7)){
		HunterNumber = 2;
	}
	else if((PlayersA > 7) && (PlayersA <=11)){
		HunterNumber = 3;
	}
	else if(PlayersA == 12){
		HunterNumber = 4;
	}
	int CurrentHunters = 0;
	//trChatSend(0, "Select " + HunterNumber + " hunters");
	
	int a = 0;
	while(CurrentHunters < HunterNumber){
		Safety = Safety+1;
		if(Safety > 100){
			break;
		}
		trQuestVarSetFromRand("temp", 1, cNumberNonGaiaPlayers);
		a = 1*trQuestVarGet("temp");
		if(playerIsPlaying(a)){
			xSetPointer(dPlayerData, a);
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				xSetBool(dPlayerData, xPlayerRunner, false);
				CurrentHunters = CurrentHunters+1;
			}
		}
	}
	for(p = 1; <= cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		xSetBool(dPlayerData, xRoleDefined, true);
		if(xGetBool(dPlayerData, xPlayerRunner) == false){
			if(trCurrentPlayer() == p){
				OverlayTextPlayerColor(p);
				trOverlayText("You are a Hunter", 8.0, 534, 300, 1000);
			}
		}
		else{
			if(trCurrentPlayer() == p){
				OverlayTextPlayerColor(p);
				trOverlayText("You are a Runner", 8.0, 534, 300, 1000);
			}
		}
	}
	xsDisableSelf();
	playSound("\cinematics\15_in\gong.wav");
	xsEnableRule("SetGameDiplomacy");
}

rule SetGameDiplomacy
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		Pregame = false;
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			//Do the QVs
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trQuestVarModify("Hunters", "+", 1);
				trQuestVarSet("Hunter"+1*trQuestVarGet("Hunters"), p);
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				trQuestVarModify("Runners", "+", 1);
				trQuestVarSet("Runner"+1*trQuestVarGet("Runners"), p);
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				//I am a hunter, set everyone else to enemy
				for(q = 1; <= cNumberNonGaiaPlayers){
					xSetPointer(dPlayerData, q);
					if(xGetBool(dPlayerData, xPlayerRunner) == true){
						trPlayerSetDiplomacy(p, q, "Enemy");
						trPlayerSetDiplomacy(q, p, "Enemy");
					}
				}
			}
		}
		//Ally already set to everyone by default so this should cover it
		xsDisableSelf();
		xsEnableRule("PaintTerrain");
		xsEnableRule("SecondaryInstructions");
	}
}

rule SecondaryInstructions
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				if(HunterNumber > 1){
					if(trCurrentPlayer() == p){
						characterDialog("Create units at the temple and kill all runner citizens to win", "You have " + 1*(HunterNumber-1) + " fellow hunters", "icons\improvement monsterous rage icon 64");
					}
				}
				else{
					if(trCurrentPlayer() == p){
						characterDialog("Create units at the temples and kill all runner citizens to win", "You are hunting on your own", "icons\improvement monsterous rage icon 64");
					}
				}
			}
			else{
				if(AutoEscape){
					if(trCurrentPlayer() == p){
						characterDialog("If your citizen dies you lose", "Build and timeshift towers and sky passages to escape the computer", "icons\villager x male hero icons 64");
					}
				}
				else{
					if(trCurrentPlayer() == p){
						characterDialog("If your citizen dies you lose", "Build and timeshift towers and sky passages to escape the hunters", "icons\villager x male hero icons 64");
					}
				}
			}
		}
		trPlayerResetBlackMapForAllPlayers();
		trSetFogAndBlackmap(true, true);
		xsDisableSelf();
		xsEnableRule("START_GAME");
	}
}

rule START_GAME
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 3){
		Pregame = false;
		xsDisableSelf();
		trLetterBox(false);
		trUIFadeToColor(0,0,0,500,100,false);
		//Hunter Temples
		if(HunterNumber == 1){
			UnitCreate(1*trQuestVarGet("Hunter1"), "Temple",(MapSize/2)-10,(MapSize/2)-10, 315);
			UnitCreate(1*trQuestVarGet("Hunter1"), "Temple",(MapSize/2)+10,(MapSize/2)+10, 135);
		}
		if(HunterNumber == 2){
			UnitCreate(1*trQuestVarGet("Hunter1"), "Temple",(MapSize/2)+10,(MapSize/2)-10, 225);
			UnitCreate(1*trQuestVarGet("Hunter2"), "Temple",(MapSize/2)-10,(MapSize/2)-10, 315);
			UnitCreate(1*trQuestVarGet("Hunter1"), "Temple",(MapSize/2)-10,(MapSize/2)+10, 45);
			UnitCreate(1*trQuestVarGet("Hunter2"), "Temple",(MapSize/2)+10,(MapSize/2)+10, 135);
		}
		if(HunterNumber == 3){
			UnitCreate(1*trQuestVarGet("Hunter1"), "Temple",(MapSize/2)+10,(MapSize/2)-10, 225);
			UnitCreate(1*trQuestVarGet("Hunter2"), "Temple",(MapSize/2)-10,(MapSize/2)-10, 315);
			UnitCreate(1*trQuestVarGet("Hunter3"), "Temple",(MapSize/2)-10,(MapSize/2)+10, 45);
		}
		if(HunterNumber == 4){
			UnitCreate(1*trQuestVarGet("Hunter1"), "Temple",(MapSize/2)+10,(MapSize/2)-10, 225);
			UnitCreate(1*trQuestVarGet("Hunter2"), "Temple",(MapSize/2)-10,(MapSize/2)-10, 315);
			UnitCreate(1*trQuestVarGet("Hunter3"), "Temple",(MapSize/2)-10,(MapSize/2)+10, 45);
			UnitCreate(1*trQuestVarGet("Hunter4"), "Temple",(MapSize/2)+10,(MapSize/2)+10, 135);
		}
		
		//Runners
		for(a = 1; <= 1*trQuestVarGet("Runners")){
			trQuestVarSetFromRand("pos", 0, SwitchMapSize()-1);
			if(iModulo(4, a) == 0){
				UnitCreate(1*trQuestVarGet("Runner"+a), "Villager Atlantean Hero",1*trQuestVarGet("pos")*22+10,12);
			}
			else if(iModulo(3, a) == 0){
				UnitCreate(1*trQuestVarGet("Runner"+a), "Villager Atlantean Hero",10,1*trQuestVarGet("pos")*22+12);
			}
			else if(iModulo(2, a) == 0){
				UnitCreate(1*trQuestVarGet("Runner"+a), "Villager Atlantean Hero",1*trQuestVarGet("pos")*22+10,MapSize-12);
			}
			else{
				UnitCreate(1*trQuestVarGet("Runner"+a), "Villager Atlantean Hero",MapSize-12,1*trQuestVarGet("pos")*22+10);
			}
		}
		
		//Timer
		gGameEndTime = trTime()+1500;
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetBool(dPlayerData, xRoleDefined, true);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				if(trCurrentPlayer() == p){
					RedTimer("Runners win", 1500, "cdgametimer", -1);
				}
			}
			else{
				if(trCurrentPlayer() == p){
					GreenTimer("Runners win", 1500, "cdgametimer", -1);
				}
			}
		}
		
		//Camera and groups
		trBlockAllSounds(true);
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				
				if(trCurrentPlayer() == p){
					uiFindType("Villager Atlantean Hero");
					uiCreateNumberGroup(1);
					uiClearSelection();
					uiZoomToProto("Villager Atlantean Hero");
				}
			}
			else{
				trUnforbidProtounit(p, "Centaur");
				trUnforbidProtounit(p, "Scorpion Man");
				if(trCurrentPlayer() == p){
					uiFindType("Temple");
					uiCreateNumberGroup(1);
					uiClearSelection();
					if(HunterNumber < 3){
						uiFindType("Temple");
						uiFindType("Temple");
						uiCreateNumberGroup(2);
						uiClearSelection();
					}
					uiZoomToProto("Temple");
				}
			}
			if(playerIsPlaying(p) == false){
				xSetBool(dPlayerData, xPlayerAlive, false);
			}
		}
		trBlockAllSounds(false);
		trUnblockAllSounds();
		xsEnableRule("ETERNAL_LOOPS");
		trSetDisableGPBlocking(true);
		for(p = 1 ; < cNumberNonGaiaPlayers){
			trUnitSelectClear();
			trUnitSelectByID(0);
			trUnitChangeInArea(p,p, "Temple", "Temple", MapSize);
		}
		if(AutoEscape){
			xsEnableRule("AI_Activate");
		}
	}
}
