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
		//	trUnitChangeInArea(0,1, "Chicken Exploding", "Tower", MapSize);
		if(xGetBool(dPlayerData, xPlayerAlive)){
			if(playerIsPlaying(p)){
				if(xGetBool(dPlayerData, xPlayerRunner) == true){
					//lavacheck
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)))/2) == getTerrainSubType("Hades4Passable"))){
						xUnitSelect(dPlayerData, xPlayerUnitID);
						trDamageUnit(0.1*timediff);
						if(trGetWorldDifficulty() == 3){
							trDamageUnit(0.1*timediff);
						}
					}
					//runner stat checker
					if(trGetStatValue(p, 2)+trQuestVarGet("P"+p+"AddKills") > trQuestVarGet("P"+p+"UnitKills")){
						trQuestVarSet("P"+p+"UnitKills", trGetStatValue(p, 2)+trQuestVarGet("P"+p+"AddKills"));
						trSetCivilizationNameOverride(p, "Kills: " + 1*trQuestVarGet("P"+p+"UnitKills") + "/" + xGetInt(dPlayerData, xPlayerNextLevel));
						gadgetRefresh("unitStatPanel");
						if(xGetInt(dPlayerData, xPlayerNextLevel) <= 1*trQuestVarGet("P"+p+"UnitKills")){
							xSetInt(dPlayerData, xPlayerNextLevel, xGetInt(dPlayerData, xPlayerLevel)*5+xGetInt(dPlayerData, xPlayerNextLevel));
							xSetInt(dPlayerData, xPlayerLevel, xGetInt(dPlayerData, xPlayerLevel)+1);
							//LevelUp(p);
							trQuestVarModify("P"+p+"LevelsUnspent", "+", 1);
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
						//LevelUp(p);
						trQuestVarModify("P"+p+"LevelsUnspent", "+", 1);
					}
				}
				//hunter resign
				if(AutoEscape == false){
					if((playerIsPlaying(p) == false) || (trPlayerUnitCountSpecific(p, "Temple") == 0) ){
						PlayerColouredChat(p, "I am a resigning n00b");
						trSetPlayerDefeated(p);
						trPlayerKillAllBuildings(p);
						trPlayerKillAllGodPowers(p);
						trPlayerKillAllUnits(p);
						xSetBool(dPlayerData, xPlayerAlive, false);
						if(trCurrentPlayer() == p){
							uiMessageBox("Resigning ruins the fun for everyone, shame on you.");
							/*%
							code("configSetInt(\"unbuildWoodCost\", 5);");
							code("configSetInt(\"unbuildWoodCost1\", 5);");
							code("configSetInt(\"unbuildWoodCost2\", 200);");
							code("configSetInt(\"unbuildGoldCost2\", 100);");
							%*/
						}
					}
				}
			}
		}
		if(trPlayerUnitCountSpecific(p, "Maceman Hero") > 0){
			trUnitSelectByQV("P"+p+"Space");
			trUnitChangeInArea(p,p, "Maceman Hero", "Cinematic Block", MapSize);
			trUnitChangeInArea(p,p, "Roc", "Cinematic Block", MapSize);
			trUnitChangeInArea(p,p, "Prisoner", "Cinematic Block", MapSize);
			
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
		trModifyProtounit("Heka Gigantes", p, 9, 1);
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
		
		//LEVELING
		if((1*trQuestVarGet("P"+p+"LevelsUnspent") > 0) && (trPlayerUnitCountSpecific(p, "Maceman") == 0)){
			trQuestVarModify("P"+p+"LevelsUnspent", "-", 1);
			trQuestVarModify("P"+p+"ActualLevel", "+", 1);
			int temp = 0;
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(p, "Cinematic Block", p*20, MapSize, 0);
			trQuestVarSet("P"+p+"Space", temp);
			if((AutoEscape == false) || (p != cNumberNonGaiaPlayers)){
				trUnitSelectByQV("P"+p+"Space");
				trUnitChangeProtoUnit("Maceman");
				trUnitSelectByQV("P"+p+"Space");
				trSetSelectedScale(0,0,0);
			}
			temp = UnitCreateChange(p, "Roc", p*3, MapSize-1);
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Space");
			trImmediateUnitGarrison(""+temp);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trSetSelectedScale(0,0,0);
			xsEnableRule("RocChange");
			xSetPointer(dPlayerData, p);
			//RUNNER REWARDS
			if(xGetBool(dPlayerData, xPlayerRunner)){
				//	trChatSend(0, "<color=1,1,0>P" + p + " Level " + 1*trQuestVarGet("P"+p+"ActualLevel"));
				//Level 0-5 rewards
				if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 1, 2)){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 3){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 4){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 5){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 6){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 7){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 8){
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
				else if(1*trQuestVarGet("P"+p+"ActualLevel") == 9){
					trQuestVarSetFromRand("CL"+p, RunnerRewardL8, (RunnerRewardL9-1));
					trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
					while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
						trQuestVarSetFromRand("CR"+p, RunnerRewardL8, RunnerRewardL9);
						if(1*trQuestVarGet("CR"+p) == RunnerRewardL9){
							if(xGetInt(dPlayerData, xPlayerWallLevel) <= 5){
								trQuestVarSet("CR"+p, 3);
							}
							else{
								trQuestVarSetFromRand("CR"+p, RunnerRewardL8, RunnerRewardL9-1);
							}
						}
					}
				}
				//high
				else if(1*trQuestVarGet("P"+p+"ActualLevel") > 9){
					trQuestVarSetFromRand("CL"+p, RunnerRewardL7, (RunnerRewardL10));
					trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
					while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
						trQuestVarSetFromRand("CR"+p, RunnerRewardL7, RunnerRewardL10);
					}
				}
			}
			else{
				//HUNTER REWARDS
				//Level 0-5 rewards
				if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 0, 4)){
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
				else if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 5, 8)){
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
				else if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 9, 10)){
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
				else if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 11, 12)){
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
				else if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 12, 13)){
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
				else if(Between(1*trQuestVarGet("P"+p+"ActualLevel"), 14, 15)){
					trQuestVarSetFromRand("CL"+p, HunterRewardL6, (HunterRewardL7-1));
					trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
					while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
						trQuestVarSetFromRand("CR"+p, HunterRewardL6, (HunterRewardL7-1));
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
					trQuestVarSetFromRand("CL"+p, HunterRewardL5, (HunterRewardL7));
					trQuestVarSet("CR"+p, 1*trQuestVarGet("CL"+p));
					while(1*trQuestVarGet("CL"+p) == 1*trQuestVarGet("CR"+p)){
						trQuestVarSetFromRand("CR"+p, HunterRewardL5, (HunterRewardL7));
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
		if(xGetDatabaseCount(dImplode) > 0){
			for(a = xGetDatabaseCount(dImplode); > 0){
				xDatabaseNext(dImplode);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dImplode, xImplodeID));
				//db = databaseName(p);
				if (trUnitAlive() == false) {
					xFreeDatabaseBlock(dImplode);
				}
				else{
					for(x = 1; < cNumberNonGaiaPlayers){
						trDamageUnitsInArea(x, "All", 4, -100);
					}
					DamageUnitCountKills(xGetInt(dImplode, xImplodeOwner),kbGetBlockPosition(""+xGetInt(dImplode, xImplodeID)),0.5,40000.0);
				}
			}
		}
		gadgetRefresh("unitStatPanel");
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
	xsEnableRule("HunterUnits16Mins");
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
	xsEnableRule("CreateInitialRelics");
	xsEnableRule("MirrorTowerDB");
	xsEnableRule("Vanishbase_Search");
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
	//UnitCreate(1, "Manticore", 6, 12);
	//trTechGodPower(1, "Vision", 40);
	//trTechGodPower(1, "Sandstorm", 40);
	if(AutoEscape){
		for(p = 1; < cNumberNonGaiaPlayers){
			//grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
			//TITAN STATS
			if(trGetWorldDifficulty() == 3){
				modifyProtounitAbsolute("Tower", p, 0, 300);
				modifyProtounitAbsolute("Tower", p, 31, 10);
				modifyProtounitAbsolute("Villager Atlantean Hero", p, 0, 200);
			}
			if(trGetWorldDifficulty() == 0){
				trModifyProtounit("Vision Revealer", p, 2, 10);
			}
		}
	}
	%
	code("configSetInt(\"unbuildWoodCost\", 0);");
	code("configSetInt(\"unbuildWoodCost1\", 0);");
	code("configSetInt(\"unbuildWoodCost2\", 0);");
	code("configSetInt(\"unbuildGoldCost2\", 0);");
	%
}

rule CreateInitialRelics
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 2){
		if(AutoEscape){
			MaxRelics = cNumberNonGaiaPlayers+4-trGetWorldDifficulty();
			if(cNumberNonGaiaPlayers < 4){
				MaxRelics = MaxRelics+4;
			}
			for(a = 0; <= MaxRelics){
				trQuestVarSetFromRand("temp",0,RELICS_GROUP_1); //0,7
				CreateRelic(1*trQuestVarGet("temp"));
			}
			if(trGetWorldDifficulty() < 3){
				CreateRelic(RELIC_SHIELD);
			}
			xsEnableRule("Monument_Search");
			//CreateRelic(RELIC_PALACE_RANGE_10);
		}
		xsDisableSelf();
	}
}

rule TimeShiftMsg
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 20){
		//20
		trMessageSetText("Ignore timeshift cost, it is free.", 5000);
		//grantGodPowerNoRechargeNextPosition(1, "Implode",1);
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
			else{
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
			trMessageSetText("It is worth exploring the map, you may find relics that are to your advantage.", 9000);
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
			else{
				if(AutoEscape){
					if(trCurrentPlayer() == p){
						trMessageSetText("I'd suggest timeshifting towers to explore the map.", 8000);
					}
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
		if(AutoEscape){
			if(trPlayerUnitCountSpecific(0, "Relic") < MaxRelics){
				for(a = trPlayerUnitCountSpecific(0, "Relic"); < MaxRelics){
					trQuestVarSetFromRand("temp",(RELICS_GROUP_1+1),RELICS_GROUP_2);
					CreateRelic(1*trQuestVarGet("temp"));
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
			if(trGetWorldDifficulty() >= 1){
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Centaur", "Sphinx", MapSize);
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Scorpion Man", "Sphinx", MapSize);
			}
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
					if(trGetWorldDifficulty() == 3){
						trSetDisableGPBlocking(false);
					}
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
			if(trGetWorldDifficulty() >= 2){
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Cyclops", "Sphinx", MapSize);
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Satyr", "Sphinx", MapSize);
			}
			
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
			if(trGetWorldDifficulty() >= 2){
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Battle Boar", "Sphinx", MapSize);
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Wadjet", "Sphinx", MapSize);
			}
			CreateRelic(RELIC_SHIELD);
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
		if(trGetWorldDifficulty() == 3){
			trSetDisableGPBlocking(true);
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
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				if(AutoEscape == false){
					grantGodPowerNoRechargeNextPosition(p, "Pestilence", 1);
					if(trCurrentPlayer() == p){
						trMessageSetText("Pestilence granted.", 8000);
						playSound("\cinematics\17_in\weirdthing.mp3");
					}
				}
				else{
					trModifyProtounit("Palace", p, 13, 1);
					if(trCurrentPlayer() == p){
						trMessageSetText("Extra palace projectile granted.", 8000);
					}
				}
			}
		}
		if(AutoEscape){
			if(trPlayerUnitCountSpecific(0, "Relic") < MaxRelics){
				for(a = trPlayerUnitCountSpecific(0, "Relic"); < MaxRelics){
					trQuestVarSetFromRand("temp",(RELICS_GROUP_2+1),RELICS_GROUP_3);
					CreateRelic(1*trQuestVarGet("temp"));
				}
			}
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
			if(trGetWorldDifficulty() >= 2){
				trUnitChangeInArea(cNumberNonGaiaPlayers, cNumberNonGaiaPlayers, "Sphinx", "Behemoth", MapSize);
			}
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
		handunit = "Heka Gigantes";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				grantGodPowerNoRechargeNextPosition(p, "Rain", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Rain = Towers turn into birds that fly for 10s before changing back", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				grantGodPowerNoRechargeNextPosition(p, "Earthquake", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Earthquake granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
			}
		}
		if(AutoEscape){
			trUnitSelectClear();
			trUnitSelect("0");
			if(trPlayerUnitCountSpecific(0, "Relic") < MaxRelics){
				for(a = trPlayerUnitCountSpecific(0, "Relic"); < MaxRelics){
					trQuestVarSetFromRand("temp",(RELICS_GROUP_3+1),MAX_RELIC_CLASS);
					CreateRelic(1*trQuestVarGet("temp"));
				}
			}
			
		}
		xsDisableSelf();
	}
}

rule HunterUnits17Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*17){
		int temp = 0;
		handunit = "Heka Gigantes";
		if(AutoEscape){
			if(trGetWorldDifficulty() >= 1){
				grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Snow Storm", 1);
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Snow Storm", xsVectorSet(MapSize,0,MapSize), vector(0,0,0));
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Snow Storm", xsVectorSet(MapSize/2,0,MapSize/2), vector(0,0,0));
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Snow Storm", xsVectorSet(5,0,MapSize/2), vector(0,0,0));
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Snow Storm", xsVectorSet(5,0,5), vector(0,0,0));
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Snow Storm", xsVectorSet(MapSize/2,0,5), vector(0,0,0));
				playSound("\xpack\xcinematics\1_in\wolfhowl.mp3");
				if(trGetWorldDifficulty() == 3){
					trSetDisableGPBlocking(false);
				}
				for(p = 1; < cNumberNonGaiaPlayers){
					xSetPointer(dPlayerData, p);
					//spawn
					if(playerIsPlaying(p)){
						for(wolfcount = 0 ; < 7){
							temp = UnitCreate(cNumberNonGaiaPlayers, "Fenris Wolf",(MapSize/2)+5,(MapSize/2)+5);
							xAddDatabaseBlock(dEnemies, true);
							xSetInt(dEnemies, xUnitID, temp);
							xSetInt(dEnemies, xIdleTimeout, trTime()+30);
							trUnitSelectClear();
							trUnitSelect(""+temp);
							trUnitMoveToPoint(xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID))),1,xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID))),-1,true);
						}
					}
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits16Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*16){
		int temp = 0;
		trQuestVarSetFromRand("specialunit", 1, 2);
		if(1*trQuestVarGet("specialunit") == 1){
			rangedunit = "Lampades";
			for(p = 1; <= cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				if(xGetBool(dPlayerData, xPlayerRunner) == false){
					trForbidProtounit(p, "Heka Gigantes");
					trUnforbidProtounit(p, "Lampades");
					if(trCurrentPlayer() == p){
						trMessageSetText("You can now train lampades.", 8000);
						playSound("ageadvance.wav");
					}
				}
				else{
					if(trCurrentPlayer() == p){
						trMessageSetText("Watch out for lampades - their special attack does heavy area damage", 8000);
					}
				}
			}
		}
		else{
			rangedunit = "Manticore";
			for(p = 1; <= cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				if(xGetBool(dPlayerData, xPlayerRunner) == false){
					trForbidProtounit(p, "Battle Boar");
					trForbidProtounit(p, "Behemoth");
					trForbidProtounit(p, "Hydra");
					trForbidProtounit(p, "Nemean Lion");
					trForbidProtounit(p, "Petsuchos");
					trForbidProtounit(p, "Satyr");
					trForbidProtounit(p, "Scarab");
					trForbidProtounit(p, "Scorpion Man");
					trForbidProtounit(p, "Stymphalian Bird");
					trUnforbidProtounit(p, "Manticore");
					if(trCurrentPlayer() == p){
						trMessageSetText("You can now train manticores.", 8000);
						playSound("ageadvance.wav");
					}
				}
				else{
					if(trCurrentPlayer() == p){
						trMessageSetText("Watch out for manticores - they render terrain unbuildable with their attacks", 8000);
					}
				}
			}
		}
		if(AutoEscape){
			for(a = trPlayerUnitCount(cNumberNonGaiaPlayers) ; < 60){
				temp = UnitCreate(cNumberNonGaiaPlayers, rangedunit,(MapSize/2)+5,(MapSize/2)+5);
				xAddDatabaseBlock(dEnemies, true);
				xSetInt(dEnemies, xUnitID, temp);
				xSetInt(dEnemies, xIdleTimeout, trTime()+30);
				trQuestVarSetFromRand("x", 0 , MapSize);
				trQuestVarSetFromRand("z", 0 , MapSize);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
			}
			if(trGetWorldDifficulty() == 3){
				trSetDisableGPBlocking(true);
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
		handunit = "Guardian XP";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				modifyProtounitAbsolute("Revealer to Player", 0, 2, 10);
				trUnforbidProtounit(p, "Pegasus");
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train pegasi, these turn into Guardians.", 8000);
					playSound("ageadvance.wav");
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				trModifyProtounit("Tower", p, 13, 1);
				trModifyProtounit("Palace", p, 13, 1);
				grantGodPowerNoRechargeNextPosition(p, "create gold", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Extra tower projectile and wall power granted.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		if(AutoEscape){
			MaxRelics = MaxRelics+2;
			if(trPlayerUnitCountSpecific(0, "Relic") < MaxRelics){
				for(a = trPlayerUnitCountSpecific(0, "Relic"); < MaxRelics){
					trQuestVarSetFromRand("temp",(RELICS_GROUP_3+1),MAX_RELIC_CLASS);
					CreateRelic(1*trQuestVarGet("temp"));
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
		modifyProtounitAbsolute("Stymphalian Bird", 0, 2, 47);
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(trPlayerUnitCountSpecific(p, "Temple") > 0){
				yFindLatestReverse("spawnpoint"+p, "Temple", p);
				modifyProtounitAbsolute("Stymphalian Bird", p, 2, 47);
				spawn = kbGetBlockPosition(""+1*trQuestVarGet("spawnpoint"+p));
				UnitCreateChange(0, "Revealer to Player", xsVectorGetX(spawn),xsVectorGetZ(spawn));
				UnitCreate(p, "Stymphalian Bird", xsVectorGetX(spawn),xsVectorGetZ(spawn));
				if(trCurrentPlayer() == p){
					trMessageSetText("Yeebaagooon has joined you for the final hunt!", 8000);
					playSound("ageadvance.wav");
				}
				for(x = 1; <= cNumberNonGaiaPlayers){
					trMinimapFlare(x, 10.0, spawn, false);
				}
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
			if(trGetWorldDifficulty() >= 2){
				YeebSpecialAttackChance = 20;
			}
			if(trGetWorldDifficulty() == 3){
				UnitCreate(cNumberNonGaiaPlayers, "Stymphalian Bird", xsVectorGetX(spawn),xsVectorGetZ(spawn));
				YeebSpecialAttackChance = 12;
			}
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

rule RocChange
inactive
highFrequency
{
	unitTransform("Roc", "Prisoner");
	xsDisableSelf();
}
