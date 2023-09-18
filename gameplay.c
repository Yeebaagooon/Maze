void LevelUpChoice(int p = 0){
	xSetPointer(dPlayerData, p);
	if(xGetBool(dPlayerData, xPlayerRunner)){
		PlayerChoice(p, "Choose a reward:", RewardText(xGetInt(dPlayerData, xLUCL)), xGetInt(dPlayerData,xLUCL), RewardText(xGetInt(dPlayerData, xLUCR)), xGetInt(dPlayerData,xLUCR));
	}
	else{
		PlayerChoice(p, "Choose a reward:", RewardTextHunter(xGetInt(dPlayerData, xLUCL)), xGetInt(dPlayerData,xLUCL), RewardTextHunter(xGetInt(dPlayerData, xLUCR)), xGetInt(dPlayerData,xLUCR));
	}
}

void LevelUp(int p = 0){
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"Space")) == -1){
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, MapSize-1, 0);
		trQuestVarSet("P"+p+"Space", temp);
		debugLog("Space selector dead");
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
		trChatSend(0, "<color=1,1,0>P" + p + " Level " + xGetInt(dPlayerData, xPlayerLevel));
		//Level 0-5 rewards
		if(xGetInt(dPlayerData, xPlayerLevel) < 5){
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
		else if(xGetInt(dPlayerData, xPlayerLevel) >= 5){
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
	}
	else{
		//HUNTER REWARDS
		//Level 0-5 rewards
		if(xGetInt(dPlayerData, xPlayerLevel) < 5){
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
				trChatSend(0, "Hunter level" + AutoHunterLevel);
			}
		}
		else if(xGetInt(dPlayerData, xPlayerLevel) >= 5){
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
				trChatSend(0, "Hunter level" + AutoHunterLevel);
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
	}
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
		if(xGetBool(dPlayerData, xPlayerAlive)){
			if(playerIsPlaying(p)){
				if(xGetBool(dPlayerData, xPlayerRunner) == true){
					//runner stat checker
					if(trGetStatValue(p, 2)+trQuestVarGet("P"+p+"AddKills") > trQuestVarGet("P"+p+"UnitKills")){
						trQuestVarSet("P"+p+"UnitKills", trGetStatValue(p, 2)+trQuestVarGet("P"+p+"AddKills"));
						trSetCivilizationNameOverride(p, "Kills: " + 1*trQuestVarGet("P"+p+"UnitKills") + "/" + xGetInt(dPlayerData, xPlayerNextLevel));
						gadgetRefresh("unitStatPanel");
						if(xGetInt(dPlayerData, xPlayerNextLevel) <= 1*trQuestVarGet("P"+p+"UnitKills")){
							xSetInt(dPlayerData, xPlayerNextLevel, xGetInt(dPlayerData, xPlayerLevel)*5+xGetInt(dPlayerData, xPlayerNextLevel));
							xSetInt(dPlayerData, xPlayerLevel, xGetInt(dPlayerData, xPlayerLevel)+1);
							LevelUp(p);
						}
					}
					if(trPlayerUnitCountSpecific(p, "Villager Atlantean Hero") == 0){
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
					code("configSetInt(\"unbuildWoodCost1\", 5);");
					code("configSetInt(\"unbuildWoodCost2\", 200);");
					code("configSetInt(\"unbuildGoldCost2\", 100);");
					%
				}
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				//hunter stats
				if(trGetStatValue(p, 3)+trQuestVarGet("P"+p+"AddKills") > trQuestVarGet("P"+p+"BuildingKills")){
					trQuestVarSet("P"+p+"BuildingKills", trGetStatValue(p, 3)+trQuestVarGet("P"+p+"BuildingKills"));
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
			if(trCurrentPlayer() == p){
				uiZoomToProto("Villager Atlantean Hero");
			}
			old = xsGetContextPlayer();
			xsSetContextPlayer(0);
			LevelUpChoice(p);
			xsSetContextPlayer(0);
			xSetInt(dPlayerData, xLUCL, 0);
			xSetInt(dPlayerData, xLUCR, 0);
			xsSetContextPlayer(old);
		}
		//GOD POWERS
		if(xGetDatabaseCount(dEarthquake) > 0){
			for(a = xGetDatabaseCount(dEarthquake); > 0){
				xDatabaseNext(dEarthquake);
				if(trTimeMS() > xGetInt(dEarthquake, xEarthquakeTimeout)){
					xFreeDatabaseBlock(dEarthquake);
				}
				else{
					xUnitSelect(dEarthquake, xEarthquakeName);
					DamageBuildingCountRazes(xGetInt(dEarthquake, xEarthquakeOwner),kbGetBlockPosition(""+xGetInt(dEarthquake, xEarthquakeName)),30.0,0.17*timediff);
					//trDamageUnitsInArea(p, "Unit", 30, 0.03*timediff);
				}
			}
		}
		if(trCheckGPActive("Restoration", p)){
			trUnitSelectClear();
			trUnitSelect("0");
			trDamageUnitsInArea(p, "All", MapSize, -10000);
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
			}
		}
	}
	xsDisableSelf();
	xsEnableRule("TimeShiftMsg");
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
	xsEnableRule("MGSpecial");
	xsEnableRule("HekaSpecial");
	xsEnableRule("TowerDB");
	xsEnableRule("RunnersWin");
	xsEnableRule("HuntersWin");
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
	/*UnitCreate(2, "Heka Gigantes", 4, 4);
	UnitCreate(1, "Tower", 10, 12);
	UnitCreate(1, "Tower", 10, 14);
	UnitCreate(1, "Tower", 10, 16);
	UnitCreate(1, "Tower", 10, 12);
	UnitCreate(1, "Tower", 12, 12);
	UnitCreate(1, "Tower", 14, 12);
	trTechGodPower(1, "Restoration", 4);
	trTechGodPower(1, "SPCMeteor", 4);*/
	if(AutoEscape){
		for(p = 1; < cNumberNonGaiaPlayers){
			grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
		}
	}
	%
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
			trChatSend(0, "Firing GP");
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
			else{
				grantGodPowerNoRechargeNextPosition(p, "Restoartion", 1);
				if(trCurrentPlayer() == p){
					trMessageSetText("Restoration = all units and buildings invulnerable", 8000);
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
			trChatSend(0, "Firing GP");
			xsEnableRule("AI_Force_Power");
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
				grantGodPowerNoRechargeNextPosition(p, "Meteor", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("Meteor granted.", 8000);
					playSound("\cinematics\17_in\weirdthing.mp3");
				}
				if(AutoEscape){
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Eclipse", xsVectorSet(MapSize/2, 5.00, MapSize/2), vector(0,0,0));
				}
			}
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
				grantGodPowerNoRechargeNextPosition(p, "SPC Meteor", MapFactor());
				if(trCurrentPlayer() == p){
					trMessageSetText("SPC Meteor granted.", 8000);
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
		}
		if(AutoEscape){
			trChatSend(0, "Firing GP");
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
			trChatSend(0, "Firing GP");
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
				trUnforbidProtounit(p, "Phoenix");
				trUnforbidProtounit(p, "Phoenix From Egg");
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train phoenixes. They take less population room later.", 8000);
					playSound("ageadvance.wav");
				}
			}
		}
		xsDisableSelf();
	}
}

rule HunterUnits18Mins
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 60*15){
		rangedunit = "Phoenix";
		handunit = "Heka Gigantes";
		for(p = 1; <= cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trUnforbidProtounit(p, "Phoenix");
				if(AutoEscape == false){
					trModifyProtounit("Phoenix", p, 6, -1);
					trModifyProtounit("Phoenix From Egg", p, 6, -1);
				}
				if(trCurrentPlayer() == p){
					trMessageSetText("You can now train phoenixes. Phoenix pop count reduced.", 8000);
					playSound("ageadvance.wav");
				}
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
	trEndGame();
	%
	code("configSetInt(\"unbuildWoodCost1\", 5);");
	code("configSetInt(\"unbuildWoodCost2\", 200);");
	code("configSetInt(\"unbuildGoldCost2\", 100);");
	%
}
