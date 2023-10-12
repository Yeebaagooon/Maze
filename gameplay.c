void LevelUpChoice(int p = 0){
	xSetPointer(dPlayerData, p);
	if(xGetBool(dPlayerData, xPlayerRunner)){
		PlayerChoice(p, "Choose a reward:", RewardText(xGetInt(dPlayerData, xLUCL)), xGetInt(dPlayerData,xLUCL), RewardText(xGetInt(dPlayerData, xLUCR)), xGetInt(dPlayerData,xLUCR));
	}
	else{
		PlayerChoice(p, "Choose a reward:", RewardTextHunter(xGetInt(dPlayerData, xLUCL)), xGetInt(dPlayerData,xLUCL), RewardTextHunter(xGetInt(dPlayerData, xLUCR)), xGetInt(dPlayerData,xLUCR));
	}
	if(trCurrentPlayer() == p){
		trClearCounterDisplay();
	}
	gadgetRefresh("unitStatPanel");
}

void LevelUp(int p = 0){
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"Space")) == -1){
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*20, MapSize, 0);
		trQuestVarSet("P"+p+"Space", temp);
		//	debugLog("Space selector dead");
	}
	if((AutoEscape == false) || (p != cNumberNonGaiaPlayers)){
		trUnitSelectByQV("P"+p+"Space");
		trUnitChangeProtoUnit("Maceman");
		trUnitSelectByQV("P"+p+"Space");
		trSetSelectedScale(0,0,0);
	}
	xSetPointer(dPlayerData, p);
	//RUNNER REWARDS
	if(xGetBool(dPlayerData, xPlayerRunner)){
		//	trChatSend(0, "<color=1,1,0>P" + p + " Level " + xGetInt(dPlayerData, xPlayerLevel));
		//Level 0-5 rewards
		if(Between(xGetInt(dPlayerData, xPlayerLevel), 0, 2)){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL1, (RunnerRewardL2-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL1, RunnerRewardL2);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL2){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 2){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL1, RunnerRewardL2-1);
					}
				}
			}
		}
		//Level 5-10rewards
		else if(xGetInt(dPlayerData, xPlayerLevel) == 3){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL2, (RunnerRewardL3-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL2, RunnerRewardL3);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL3){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 3){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL2, RunnerRewardL3-1);
					}
				}
			}
		}
		else if(xGetInt(dPlayerData, xPlayerLevel) == 4){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL3, (RunnerRewardL4-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL3, RunnerRewardL4);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL4){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 4){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL3, RunnerRewardL4-1);
					}
				}
			}
		}
		else if(xGetInt(dPlayerData, xPlayerLevel) == 5){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL4, (RunnerRewardL5-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL4, RunnerRewardL5);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL5){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 4){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL4, RunnerRewardL5-1);
					}
				}
			}
		}
		else if(xGetInt(dPlayerData, xPlayerLevel) == 6){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL5, (RunnerRewardL6-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL5, RunnerRewardL6);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL6){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 4){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL5, RunnerRewardL6-1);
					}
				}
			}
		}
		else if(xGetInt(dPlayerData, xPlayerLevel) == 7){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL6, (RunnerRewardL7-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL6, RunnerRewardL7);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL7){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 5){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL6, RunnerRewardL7-1);
					}
				}
			}
		}
		else if(xGetInt(dPlayerData, xPlayerLevel) == 8){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL7, (RunnerRewardL8-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL7, RunnerRewardL8);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL8){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 5){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL7, RunnerRewardL8-1);
					}
				}
			}
		}
		//high
		else if(xGetInt(dPlayerData, xPlayerLevel) > 8){
			trQuestVarSetFromRand("CL"+p, RunnerRewardL5, (RunnerRewardL8-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, RunnerRewardL5, RunnerRewardL8);
				if(1*trQuestVarGet("CR"+p) == RunnerRewardL8){
					if(xGetInt(dPlayerData, xPlayerWallLevel) <= 5){
						trQuestVarSet("CR"+p, 3);
					}
					else{
						trQuestVarSetFromRand("CR"+p, RunnerRewardL5, RunnerRewardL8-1);
					}
				}
			}
		}
	}
	else{
		//HUNTER REWARDS
		//Level 0-5 rewards
		if(Between(xGetInt(dPlayerData, xPlayerLevel), 0, 4)){
			trQuestVarSetFromRand("CL"+p, HunterRewardL1, (HunterRewardL2-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, HunterRewardL1, (HunterRewardL2-1));
			}
			if(AutoEscape){
				//Auto reward for hunter CPU AI
				xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
				ChoiceEffect = xGetInt(dPlayerData, xLUCL);
				ActionChoice = p;
				xsEnableRule("HunterConsequences");
				AutoHunterLevel=AutoHunterLevel+1;
				//trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
		else if(Between(xGetInt(dPlayerData, xPlayerLevel), 5, 8)){
			trQuestVarSetFromRand("CL"+p, HunterRewardL2, (HunterRewardL3-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, HunterRewardL2, (HunterRewardL3-1));
			}
			if(AutoEscape){
				//Auto reward for hunter CPU AI
				xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
				ChoiceEffect = xGetInt(dPlayerData, xLUCL);
				ActionChoice = p;
				xsEnableRule("HunterConsequences");
				AutoHunterLevel=AutoHunterLevel+1;
				//trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
		else if(Between(xGetInt(dPlayerData, xPlayerLevel), 9, 10)){
			trQuestVarSetFromRand("CL"+p, HunterRewardL3, (HunterRewardL4-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, HunterRewardL3, (HunterRewardL4-1));
			}
			if(AutoEscape){
				//Auto reward for hunter CPU AI
				xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
				ChoiceEffect = xGetInt(dPlayerData, xLUCL);
				ActionChoice = p;
				xsEnableRule("HunterConsequences");
				AutoHunterLevel=AutoHunterLevel+1;
				//trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
		else if(Between(xGetInt(dPlayerData, xPlayerLevel), 11, 12)){
			trQuestVarSetFromRand("CL"+p, HunterRewardL4, (HunterRewardL5-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, HunterRewardL4, (HunterRewardL5-1));
			}
			if(AutoEscape){
				//Auto reward for hunter CPU AI
				xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
				ChoiceEffect = xGetInt(dPlayerData, xLUCL);
				ActionChoice = p;
				xsEnableRule("HunterConsequences");
				AutoHunterLevel=AutoHunterLevel+1;
				//trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
		else if(Between(xGetInt(dPlayerData, xPlayerLevel), 12, 13)){
			trQuestVarSetFromRand("CL"+p, HunterRewardL5, (HunterRewardL6-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, HunterRewardL5, (HunterRewardL6-1));
			}
			if(AutoEscape){
				//Auto reward for hunter CPU AI
				xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
				ChoiceEffect = xGetInt(dPlayerData, xLUCL);
				ActionChoice = p;
				xsEnableRule("HunterConsequences");
				AutoHunterLevel=AutoHunterLevel+1;
				//trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
		else{
			//high
			trQuestVarSetFromRand("CL"+p, HunterRewardL3, (HunterRewardL5-1));
			trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
			while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
				trQuestVarSetFromRand("CR"+p, HunterRewardL3, (HunterRewardL5-1));
			}
			if(AutoEscape){
				//Auto reward for hunter CPU AI
				xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
				ChoiceEffect = xGetInt(dPlayerData, xLUCL);
				ActionChoice = p;
				xsEnableRule("HunterConsequences");
				AutoHunterLevel=AutoHunterLevel+1;
				//trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
	}
	//trChatSend(p, ""+1*trQuestVarGet("CL"+p) + " and " + 1*trQuestVarGet("CR"+p));
	xSetInt(dPlayerData, xLUCL, 1*trQuestVarGet("CL"+p));
	xSetInt(dPlayerData, xLUCR, 1*trQuestVarGet("CR"+p));
	if(trCurrentPlayer() == p){
		OverlayTextPlayerColor(p);
		trOverlayText("LEVEL UP - press space to choose a reward", 5.0, 404, 300, 3000);
		playSound("arkantosarrive.wav");
		trSetCounterDisplay("REWARD ACTIVE - PRESS SPACE");
	}
	gadgetRefresh("unitStatPanel");
}

rule Eternal_Loops
inactive
highFrequency
{
	if(Pregame == false){
		timediff = (trTimeMS() - timelast); // calculate timediff
		timelast = trTimeMS();
		int old = xsGetContextPlayer();
		CyclePlayers = CyclePlayers+1;
		if(CyclePlayers > cNumberNonGaiaPlayers){
			CyclePlayers = 1;
		}
		int p = CyclePlayers;
		trUnitSelectClear();
		trUnitSelectByID(0);
		trDamageUnitsInArea(p, "Temple", MapSize, -100000);
		xSetPointer(dPlayerData, p);
		trUnitSelectClear();
		trUnitSelectByID(0);
		trUnitChangeInArea(p,p, "Wall Long", "Gate", MapSize);
		trUnitChangeInArea(0,1, "Chicken Exploding", "Tower", MapSize);
		if(xGetBool(dPlayerData, xPlayerAlive)){
			if(playerIsPlaying(p)){
				if(xGetBool(dPlayerData, xPlayerRunner) == true){
					//lavacheck
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2) == getTerrainSubType("Hades4Passable"))){
						xUnitSelect(dPlayerData, xPlayerUnitID);
						trDamageUnit(0.1*timediff);
					}
					//runner stat checker
					if(trGetStatValue(p, 2)+trQuestVarGet("P"+p+"AddKills") > trQuestVarGet("P"+p+"UnitKills")){
						trQuestVarSet("P"+p+"UnitKills", trGetStatValue(p, 2)+trQuestVarGet("P"+p+"AddKills"));
						trSetCivilizationNameOverride(p, "Kills: " + 1*trQuestVarGet("P"+p+"UnitKills") + "/" + xGetInt(dPlayerData, xPlayerNextLevel));
						gadgetRefresh("unitStatPanel");
						if(xGetInt(dPlayerData, xPlayerNextLevel) <= 1*trQuestVarGet("P"+p+"UnitKills")){
							xSetInt(dPlayerData, xPlayerNextLevel, xGetInt(dPlayerData, xPlayerLevel)*5+xGetInt(dPlayerData, xPlayerNextLevel));
							xSetInt(dPlayerData, xPlayerLevel, xGetInt(dPlayerData, xPlayerLevel)+1);
							LevelUp(p);
							trSetCivilizationNameOverride(p, "Kills: " + 1*trQuestVarGet("P"+p+"UnitKills") + "/" + xGetInt(dPlayerData, xPlayerNextLevel));
							gadgetRefresh("unitStatPanel");
						}
					}
					if((trPlayerUnitCountSpecific(p, "Villager Atlantean Hero") == 0) && (trPlayerUnitCountSpecific(p, "Hero Ragnorok") == 0)){
						//Defeated
						EvilLaugh();
						PlayerLighting(p, 4.0);
						OverlayTextPlayerColor(p);
						trOverlayText(trStringQuestVarGet("p"+p+"name") + " has been " + DeadText(), 5.0, 404, 300, 3000);
						trSetPlayerDefeated(p);
						trPlayerKillAllBuildings(p);
						trPlayerKillAllGodPowers(p);
						trPlayerKillAllUnits(p);
						xSetBool(dPlayerData, xPlayerAlive, false);
						RunnersDead = RunnersDead+1;
					}
				}
			}
			else{
				//runner resign
				trSetPlayerDefeated(p);
				trPlayerKillAllBuildings(p);
				trPlayerKillAllGodPowers(p);
				trPlayerKillAllUnits(p);
				xSetBool(dPlayerData, xPlayerAlive, false);
				RunnersDead = RunnersDead+1;
				if(trCurrentPlayer() == p){
					%
					code("configSetInt(\"unbuildWoodCost\", 5);");
					code("configSetInt(\"unbuildWoodCost1\", 5);");
					code("configSetInt(\"unbuildWoodCost2\", 200);");
					code("configSetInt(\"unbuildGoldCost2\", 100);");
					%
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				//trPlayerGrantResources(p, "Wood", -500);
				//trPlayerGrantResources(p, "Wood", 5);
				//hunter stats
				if(trGetStatValue(p, 3)+trQuestVarGet("P"+p+"AddKills") > trQuestVarGet("P"+p+"BuildingKills")){
					trQuestVarSet("P"+p+"BuildingKills", trGetStatValue(p, 3)+trQuestVarGet("P"+p+"AddKills"));
					trSetCivilizationNameOverride(p, "Razes: " + 1*trQuestVarGet("P"+p+"BuildingKills") + "/" + xGetInt(dPlayerData, xPlayerNextLevel));
					gadgetRefresh("unitStatPanel");
					if(xGetInt(dPlayerData, xPlayerNextLevel) <= 1*trQuestVarGet("P"+p+"BuildingKills")){
						xSetInt(dPlayerData, xPlayerNextLevel, xGetInt(dPlayerData, xPlayerLevel)*5+xGetInt(dPlayerData, xPlayerNextLevel));
						//xSetInt(dPlayerData, xPlayerNextLevel, xGetInt(dPlayerData, xPlayerNextLevel)+1);
						xSetInt(dPlayerData, xPlayerLevel, xGetInt(dPlayerData, xPlayerLevel)+1);
						LevelUp(p);
					}
				}
				//hunter resign
				if(AutoEscape == false){
					if((playerIsPlaying(p) == false) || (trPlayerUnitCountSpecific(p, "Temple") == 0) ){
						PlayerColouredChat(p, "I am a resigning n00b");
						PlayerColouredChat(p, "Repeat hunter resigners will be locked out of the map");
						trSetPlayerDefeated(p);
						trPlayerKillAllBuildings(p);
						trPlayerKillAllGodPowers(p);
						trPlayerKillAllUnits(p);
						xSetBool(dPlayerData, xPlayerAlive, false);
						if(trCurrentPlayer() == p){
							%
							code("configSetInt(\"unbuildWoodCost\", 5);");
							code("configSetInt(\"unbuildWoodCost1\", 5);");
							code("configSetInt(\"unbuildWoodCost2\", 200);");
							code("configSetInt(\"unbuildGoldCost2\", 100);");
							%
						}
					}
				}
			}
		}
		if(trPlayerUnitCountSpecific(p, "Maceman Hero") > 0){
			trUnitSelectByQV("P"+p+"Space");
			trUnitChangeInArea(p,p, "Maceman Hero", "Cinematic Block", MapSize);
			/*			if(trCurrentPlayer() == p){
				uiZoomToProto("Villager Atlantean Hero");
			}*/
			if(trCurrentPlayer() == p){
				trackInsert();
				trackAddWaypoint();
				trackPlay(10,EVENT_REMOVE_CAM_TRACKS);
			}
			old = xsGetContextPlayer();
			xsSetContextPlayer(0);
			LevelUpChoice(p);
			xsSetContextPlayer(0);
			xSetInt(dPlayerData, xLUCL, 0);
			xSetInt(dPlayerData, xLUCR, 0);
			xsSetContextPlayer(old);
		}
		trModifyProtounit("Cyclops", p, 9, 1);
		trModifyProtounit("Lampades", p, 9, 1);
		//GOD POWERS
		if(xGetDatabaseCount(dEarthquake) > 0){
			for(a = xGetDatabaseCount(dEarthquake); > 0){
				xDatabaseNext(dEarthquake);
				if(trTimeMS() > xGetInt(dEarthquake, xEarthquakeTimeout)){
					xFreeDatabaseBlock(dEarthquake);
				}
				else{
					xUnitSelect(dEarthquake, xEarthquakeName);
					DamageBuildingCountRazes(xGetInt(dEarthquake, xEarthquakeOwner),xGetInt(dEarthquake, xEarthquakeName),30.0,0.17*timediff);
					//trDamageUnitsInArea(p, "Unit", 30, 0.03*timediff);
				}
			}
		}
		if(xGetDatabaseCount(dTornado) > 0){
			for(a = xGetDatabaseCount(dTornado); > 0){
				xDatabaseNext(dTornado);
				xUnitSelect(dTornado, xTornadoName);
				if(trUnitDead()){
					xFreeDatabaseBlock(dTornado);
				}
				else{
					DamageBuildingCountRazes(xGetInt(dTornado, xTornadoOwner),xGetInt(dTornado, xTornadoName),8.0,0.12*timediff);
					//trDamageUnitsInArea(p, "Unit", 30, 0.03*timediff);
				}
			}
		}
		if(trCheckGPActive("Restoration", p)){
			trUnitSelectClear();
			trUnitSelect("0");
			trDamageUnitsInArea(p, "All", MapSize, -10000);
		}
		if(xGetBool(dPlayerData, xJourneyOn)){
			if(trCheckGPActive("journey", p) == false){
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2) != getTerrainType(CliffTerrain)) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2) != getTerrainSubType(CliffTerrain))){
					trModifyProtounit("Villager Atlantean Hero", p, 55, 1);
					trModifyProtounit("Villager Atlantean", p, 55, 1);
					xSetBool(dPlayerData, xJourneyOn, false);
				}
			}
		}
		else if(xGetBool(dPlayerData, xJourneyOn) == false){
			if(trCheckGPActive("journey", p) == true){
				trModifyProtounit("Villager Atlantean Hero", p, 55, 4);
				trModifyProtounit("Villager Atlantean", p, 55, 4);
				xSetBool(dPlayerData, xJourneyOn, true);
			}
		}
		if(xGetDatabaseCount(dHawks) > 0){
			xDatabaseNext(dHawks);
			if(trTime() >= xGetInt(dHawks, xHawkTime)){
				xUnitSelect(dHawks, xHawkID);
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dHawks, xHawkID))/2),xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dHawks, xHawkID))/2)) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dHawks, xHawkID))/2),xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dHawks, xHawkID))/2)) == getTerrainSubType(RoadTerrain))){
					trUnitConvert(xGetInt(dHawks, xPlayerOwner));
					xUnitSelect(dHawks, xHawkID);
					trUnitChangeProtoUnit("Tower");
					trUnitSelectClear();
					xAddDatabaseBlock(dTowers, true);
					xSetInt(dTowers, xTowerName, xGetInt(dHawks, xHawkID));
					xSetInt(dTowers, xTowerOwner, xGetInt(dHawks, xPlayerOwner));
					xFreeDatabaseBlock(dHawks);
				}
			}
		}
		if(xGetDatabaseCount(dDestroyMe) > 0){
			xDatabaseNext(dDestroyMe);
			if(xGetInt(dDestroyMe, xDestroyTime) > trTimeMS()){
				xUnitSelect(dDestroyMe, xDestroyName);
				trUnitDestroy();
				xFreeDatabaseBlock(dDestroyMe);
			}
		}
	}
}

rule Loops_1_Second
inactive
highFrequency
{
	if(1*trQuestVarGet("LoopTimer") < trTime()){
		trQuestVarSet("LoopTimer", trTime()+1);
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(1*trQuestVarGet("P"+p+"RagTime") > trTime()){
				BoltUnitCountKills(p, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)), 24.0, 1000);
			}
			if(xGetFloat(dPlayerData, xCitizenRegen) > 0){
				trUnitSelectClear();
				trUnitSelect(""+0);
				trDamageUnitsInArea(p, "Villager Atlantean Hero", MapSize, xGetFloat(dPlayerData, xCitizenRegen)*-1);
				trDamageUnitsInArea(p, "Villager Atlantean", MapSize, xGetFloat(dPlayerData, xCitizenRegen)*-1);
			}
		}
	}
}

rule RainCheck
inactive
highFrequency
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(trCheckGPActive("Rain", p) == true){
			if(trTime() > 1*trQuestVarGet("P"+p+"RainTime")){
				//rain
				trQuestVarSet("P"+p+"RainTime", trTime()+10);
				for(a = xGetDatabaseCount(dTowers); > 0){
					xDatabaseNext(dTowers);
					if(xGetInt(dTowers, xTowerOwner) == p){
						xUnitSelect(dTowers, xTowerName);
						if(trUnitPercentComplete() == 100){
							xUnitSelect(dTowers, xTowerName);
							trUnitChangeProtoUnit("Hawk");
							xAddDatabaseBlock(dHawks, true);
							xSetInt(dHawks, xHawkID, xGetInt(dTowers, xTowerName));
							xSetInt(dHawks, xPlayerOwner, xGetInt(dTowers, xTowerOwner));
							xSetInt(dHawks, xHawkTime, trTime()+10);
							xFreeDatabaseBlock(dTowers);
						}
					}
				}
			}
			else{
				//recharge
				//grantGodPowerNoRechargeNextPosition(p, "Rain", 1);
				//trChatSendToPlayer(0, p, "<color=1,0,0>You cannot use rain yet!");
			}
		}
	}
}

rule GameEvents
inactive
highFrequency
{
	RunnerCount = 0;
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(playerIsPlaying(p)){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				RunnerCount = RunnerCount+1;
				trModifyProtounit("Revealer To Player", p, 2, 2*MapSize);
				//trQuestVarSet("qv", 0);
				//xSetInt(dPlayerData, xPlayerUnitID, yFindLatest("qv", "Villager Atlantean Hero", p));
			}
		}
	}
	xsDisableSelf();
	xsEnableRule("TimeShiftMsg");
	xsEnableRule("Loops_1_Second");
	xsEnableRule("HunterPower1Mins");
	xsEnableRule("HunterUnits2Mins");
	xsEnableRule("HunterPower3Mins");
	xsEnableRule("HunterUnits4Mins");
	xsEnableRule("HunterPower5Mins");
	xsEnableRule("HunterUnits6Mins");
	xsEnableRule("HunterPower7Mins");
	xsEnableRule("HunterPower8Mins");
	xsEnableRule("HunterPower9Mins");
	xsEnableRule("HunterUnits10Mins");
	xsEnableRule("HunterPower11Mins");
	xsEnableRule("HunterUnits13Mins");
	xsEnableRule("HunterUnits15Mins");
	xsEnableRule("HunterUnits17Mins");
	xsEnableRule("HunterUnits18Mins");
	xsEnableRule("HunterUnits20Mins");
	xsEnableRule("HunterUnits22Mins");
	xsEnableRule("TerrainResets");
	xsEnableRule("MGSpecial");
	xsEnableRule("HekaSpecial");
	xsEnableRule("LampadesSpecial");
	xsEnableRule("YeebSpecial");
	xsEnableRule("TowerDB");
	xsEnableRule("RunnersWin");
	xsEnableRule("HuntersWin");
	xsEnableRule("VolcanoLava");
	xsEnableRule("RepaintTerrain");
	xsEnableRule("BuildingDB");
	xsEnableRule("Help_Chat");
	xsEnableRule("RainCheck");
	rangedunit = "Centaur";
	handunit = "Scorpion Man";
	//Set GP vector to a corner
	trQuestVarSetFromRand("temp", 2,4,true);
	if(1*trQuestVarGet("temp") == 1){
		AIVector = vector(4,4,4);
	}
	if(1*trQuestVarGet("temp") == 2){
		AIVector = xsVectorSet(4,4,MapSize-4);
	}
	if(1*trQuestVarGet("temp") == 3){
		AIVector = xsVectorSet(MapSize-4,4,4);
	}
	if(1*trQuestVarGet("temp") == 4){
		AIVector = xsVectorSet(MapSize-4,4,MapSize-4);
	}
	//UnitCreate(2, "Stymphalian Bird", 6, 12);
	/*UnitCreate(2, "Tower", 310, 312);
	UnitCreate(2, "Tower", 310, 314);
	UnitCreate(2, "Tower", 310, 316);
	UnitCreate(2, "Tower", 310, 312);
	UnitCreate(2, "Tower", 312, 312);
	UnitCreate(2, "Tower", 314, 312);*/
	//trTechGodPower(1, "Restoration", 4);
	//trTechGodPower(1, "create gold", 4);
	if(AutoEscape){
		for(p = 1; < cNumberNonGaiaPlayers){
			grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
			//grantGodPowerNoRechargeNextPosition(p, "Rain", 2);
			//grantGodPowerNoRechargeNextPosition(p, "Tartarian Gate", 1);
		}
	}
	%
	code("configSetInt(\"unbuildWoodCost\", 0);");
	code("configSetInt(\"unbuildWoodCost1\", 0);");
	code("configSetInt(\"unbuildWoodCost2\", 0);");
	code("configSetInt(\"unbuildGoldCost2\", 0);");
	%
}

rule TimeShiftMsg
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 20){
		trMessageSetText("Ignore timeshift cost, it is free.", 5000);
		UpgradeTest(1, 22, false);
		xsDisableSelf();
	}
}

rule HunterPower1Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Reverse Time", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Deconstruction granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
	}
	xsDisableSelf();
}

rule HunterUnits2Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*2){
		rangedunit = "Satyr";
		handunit = "Cyclops";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trForbidProtounit(p, "Centaur");
				trForbidProtounit(p, "Scorpion Man");
				trUnforbidProtounit(p, "Cyclops");
				trUnforbidProtounit(p, "Satyr");
				trTechSetStatus(p, 80, 4);
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train cyclops and satyrs.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		if(AutoEscape){
			//trChatSend(0, "Firing GP");
			xsEnableRule("AI_Force_Power");
		}
		xsDisableSelf();
	}
}

rule HunterPower3Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*3){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Undermine", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Undermine granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				grantGodPowerNoRechargeNextPosition(p, "Restoration", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Restoration = all units and buildings invulnerable for 8 seconds", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits4Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*4){
		rangedunit = "Wadjet";
		handunit = "Battle Boar";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trForbidProtounit(p, "Cyclops");
				trForbidProtounit(p, "Satyr");
				trUnforbidProtounit(p, "Battle Boar");
				trUnforbidProtounit(p, "Wadjet");
				trTechSetStatus(p, 215, 4);
				trTechSetStatus(p, 440, 4);
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train battle boars and wadjets.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterPower5Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*5){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Vision", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Vision granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Vision granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits6Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*6){
		rangedunit = "Mountain Giant";
		handunit = "Sphinx";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trForbidProtounit(p, "Battle Boar");
				trForbidProtounit(p, "Wadjet");
				trUnforbidProtounit(p, "Scarab");
				trUnforbidProtounit(p, "Sphinx");
				trUnforbidProtounit(p, "Mountain Giant");
				trTechSetStatus(p, 74, 4);
				trTechSetStatus(p, 75, 4);
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train sphinxes, scarabs and mountain giants.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		trChatSend(0, "Watch out for mountain giants special attack!");
		if(AutoEscape){
			//trChatSend(0, "Firing GP");
			xsEnableRule("AI_Force_Power");
			trUnitSelectClear();
			trUnitSelect("0");
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Centaur", "Sphinx", MapSize);
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Scorpion Man", "Sphinx", MapSize);
		}
		xsDisableSelf();
	}
}

rule HunterPower7Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*7){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Eclipse", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Eclipse granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
				if(AutoEscape){
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Eclipse", xsVectorSet(MapSize,0,MapSize), vector(0,0,0));
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				if(AutoEscape){
					grantGodPowerNoRechargeNextPosition(p, "create gold", 1);
					if(trCurrentPlayer() == p){
						trMessageSetText("Gold mine = 30s temporary cliff wall", 8000);
						playSound("\cinematics\17_in\weirdthing.mp3");
					}
				}
			}
		}
		if(AutoEscape){
			trUnitSelectClear();
			trUnitSelect("0");
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Cyclops", "Sphinx", MapSize);
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Satyr", "Sphinx", MapSize);
			
		}
		xsDisableSelf();
	}
}

rule HunterPower8Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*8){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Tartarian Gate", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Volcano granted (tartarian gate). Will spew damaging lava.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
				if(AutoEscape){
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Eclipse", xsVectorSet(MapSize/2, 5.00, MapSize/2), vector(0,0,0));
				}
			}
		}
		if(AutoEscape){
			trUnitSelectClear();
			trUnitSelect("0");
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Battle Boar", "Sphinx", MapSize);
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Wadjet", "Sphinx", MapSize);
		}
		xsDisableSelf();
	}
}

rule HunterPower9Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*9){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Meteor", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Meteor granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits10Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*10){
		rangedunit = "Troll";
		handunit = "Behemoth";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trForbidProtounit(p, "Scarab");
				trForbidProtounit(p, "Sphinx");
				trUnforbidProtounit(p, "Behemoth");
				trUnforbidProtounit(p, "Troll");
				trTechSetStatus(p, 74, 4);
				trTechSetStatus(p, 75, 4);
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train trolls and behemoths.", 8000);
					playSound("ageadvance.wav");
				}
			}
			if(AutoEscape == false){
				if(xGetBool(dPlayerData, xPlayerRunner) == true){
					grantGodPowerNoRechargeNextPosition(p, "Pestilence", 1);
					if(trCurrentPlayer() == p){
						trMessageSetText("Pestilence granted.", 8000);
						playSound("\cinematics\17_in\weirdthing.mp3");
					}
				}
			}
		}
		if(AutoEscape){
			//	trChatSend(0, "Firing GP");
			xsEnableRule("AI_Force_Power");
		}
		xsDisableSelf();
	}
}

rule HunterPower11Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*11){
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Vision", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Vision granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Vision granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
		if(AutoEscape){
			trUnitSelectClear();
			trUnitSelect("0");
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Sphinx", "Behemoth", MapSize);
		}
		xsDisableSelf();
	}
}

rule HunterUnits13Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*13){
		rangedunit = "Troll";
		handunit = "Heka Gigantes";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trUnforbidProtounit(p, "Heka Gigantes");
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train hekas, they have a special tower smash ability.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		if(AutoEscape){
			//trChatSend(0, "Firing GP");
			xsEnableRule("AI_Force_Power");
		}
		xsDisableSelf();
	}
}

rule HunterUnits15Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*15){
		rangedunit = "Phoenix";
		handunit = "Heka Gigantes";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				if(AutoEscape){
					trUnforbidProtounit(p, "Phoenix");
					trUnforbidProtounit(p, "Phoenix From Egg");
					if(trCurrentPlayer() == p){
						trMessageSetText("You can now train phoenixes. They take less population room later.", 8000);
						playSound("ageadvance.wav");
					}
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				grantGodPowerNoRechargeNextPosition(p, "Rain", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Rain = Towers turn into birds that fly for 10s before changing back", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
		if(AutoEscape){
			trUnitSelectClear();
			trUnitSelect("0");
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Mountain Giant", "Phoenix", MapSize);
			trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Behemoth", "Phoenix", MapSize);
		}
		xsDisableSelf();
	}
}

rule HunterUnits17Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*17){
		rangedunit = "Phoenix";
		handunit = "Heka Gigantes";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				if(AutoEscape == false){
					trUnforbidProtounit(p, "Phoenix");
					trUnforbidProtounit(p, "Phoenix From Egg");
					if(trCurrentPlayer() == p){
						trMessageSetText("You can now train phoenixes.", 7000);
						playSound("ageadvance.wav");
					}
				}
			}
		}
	}
}

rule HunterUnits18Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*18){
		rangedunit = "Lampades";
		handunit = "Phoenix";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trForbidProtounit(p, "Heka Gigantes");
				trUnforbidProtounit(p, "Lampades");
				if(AutoEscape == false){
					trModifyProtounit("Phoenix", p, 6, -1);
					trModifyProtounit("Phoenix From Egg", p, 6, -1);
				}
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train lampades. Phoenix pop count reduced.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits20Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*20){
		rangedunit = "Phoenix";
		handunit = "Guardian XP";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trUnforbidProtounit(p, "Pegasus");
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train pegasi, these turn into Guardians.", 8000);
					playSound("ageadvance.wav");
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				trModifyProtounit("Tower", p, 13, 1);
				grantGodPowerNoRechargeNextPosition(p, "create gold", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Extra tower projectile and wall power granted.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits22Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*22){
		vector spawn = vector(0,0,0);
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(trPlayerUnitCountSpecific(p, "Temple") > 0){
				spawn = kbGetBlockPosition(""+1*trQuestVarGet("Temple"+p));
				UnitCreate(p, "Stymphalian Bird", xsVectorGetX(spawn),xsVectorGetZ(spawn));
				if(trCurrentPlayer() == p){
					trMessageSetText("Yeebaagooon has joined you for the final hunt!", 8000);
					playSound("ageadvance.wav");
				}
				trMinimapFlare(p, 10.0, spawn, false);
			}
			if(xGetBool(dPlayerData, xPlayerRunner)){
				if(trCurrentPlayer() == p){
					trOverlayText("Yeebaagooon has joined the hunters! Run!", 6.0);
				}
			}
		}
		if(AutoEscape){
			spawn = xsVectorSet(MapSize/2,0,MapSize/2);
			UnitCreate(cNumberNonGaiaPlayers, "Stymphalian Bird", xsVectorGetX(spawn),xsVectorGetZ(spawn));
			modifyProtounitAbsolute("Stymphalian Bird", cNumberNonGaiaPlayers, 2, MapSize);
		}
		xsDisableSelf();
	}
}

rule RunnersWin
inactive
highFrequency
{
	if(trTime() > gGameEndTime){
		for(p = 1 ; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner)){
				trSetPlayerWon(p);
			}
			else{
				trSetPlayerDefeated(p);
			}
			trChatSend(0, trStringQuestVarGet("p"+p+"name") + " level " + xGetInt(dPlayerData, xPlayerLevel));
		}
		xsEnableRule("GameEnd");
		trShowWinLose("The runners have won!");
	}
}

rule HuntersWin
inactive
highFrequency
{
	if(RunnersDead == RunnerCount){
		for(p = 1 ; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner)){
				trSetPlayerDefeated(p);
			}
			else{
				trSetPlayerWon(p);
			}
			trChatSend(0, trStringQuestVarGet("p"+p+"name") + " level " + xGetInt(dPlayerData, xPlayerLevel));
		}
		xsEnableRule("GameEnd");
		trShowWinLose("The hunters have won!");
		xsDisableSelf();
	}
}

rule GameEnd
inactive
highFrequency
{
	if(AutoEscape){
		trChatSend(0, "<color=1,0.5,0>You can host without an AI and have humans hunt each other!");
		trChatSend(0, "<color=1,0.5,0>You can also change map size for a bigger map");
	}
	else{
		trChatSend(0, "<color=1,0.5,0>The map also works as an auto escape if the last slot is CPU");
		trChatSend(0, "<color=1,0.5,0>You can also change map size for a bigger map");
	}
	trEndGame();
	%
	code("configSetInt(\"unbuildWoodCost1\", 5);");
	code("configSetInt(\"unbuildWoodCost\", 5);");
	code("configSetInt(\"unbuildWoodCost2\", 200);");
	code("configSetInt(\"unbuildGoldCost2\", 100);");
	%
}

rule CountExtras
inactive
highFrequency
{
	for(p=1 ; <= cNumberNonGaiaPlayers){
		if(1*trQuestVarGet("LastAdd") == p){
			for(q=1 ; <= cNumberNonGaiaPlayers){
				if(1*trQuestVarGet("CountAdd"+q) > 0){
					trQuestVarModify("P"+p+"AddKills", "+", 1*trQuestVarGet("CountAdd"+q));
					trQuestVarModify("P"+p+"AddKills", "-", CountBuildings(q));
					trQuestVarSet("CountAdd"+q, 0);
				}
			}
			break;
		}
	}
	trQuestVarSet("LastAdd", 0);
	xsDisableSelf();
}

rule TerrainResets
inactive
highFrequency
{
	if (xGetDatabaseCount(dTerrainResetDB) > 0) {
		xDatabaseNext(dTerrainResetDB);
		if(trTime() > xGetInt(dTerrainResetDB, xTimeReset)){
			if(xGetBool(dTerrainResetDB, xXDir)){
				trPaintTerrain(xGetInt(dTerrainResetDB, xMinX),xGetInt(dTerrainResetDB, xMinZ)+2,xGetInt(dTerrainResetDB, xMaxX),xGetInt(dTerrainResetDB, xMaxZ)-2,getTerrainType(RoadTerrain), getTerrainSubType(RoadTerrain));
				trChangeTerrainHeight(xGetInt(dTerrainResetDB, xMinX),xGetInt(dTerrainResetDB, xMinZ)+2,xGetInt(dTerrainResetDB, xMaxX)+1,xGetInt(dTerrainResetDB, xMaxZ)-1,0);
			}
			else{
				trPaintTerrain(xGetInt(dTerrainResetDB, xMinX)+2,xGetInt(dTerrainResetDB, xMinZ),xGetInt(dTerrainResetDB, xMaxX)-2,xGetInt(dTerrainResetDB, xMaxZ),getTerrainType(RoadTerrain), getTerrainSubType(RoadTerrain));
				trChangeTerrainHeight(xGetInt(dTerrainResetDB, xMinX)+2,xGetInt(dTerrainResetDB, xMinZ),xGetInt(dTerrainResetDB, xMaxX)-1,xGetInt(dTerrainResetDB, xMaxZ)+1,0);
			}
			xFreeDatabaseBlock(dTerrainResetDB);
			refreshPassability();
			playSound("godpowerfailed.wav");
		}
	}
}

rule EnableChat
inactive
highFrequency
{
	trChatSetStatus(false);
	xsDisableSelf();
}
