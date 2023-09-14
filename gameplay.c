void LevelUpChoice(int p = 0){
	PlayerChoice(p, "Choose a reward:", RewardText(xGetInt(dPlayerData, xLUCL)), xGetInt(dPlayerData,xLUCL), RewardText(xGetInt(dPlayerData, xLUCR)), xGetInt(dPlayerData,xLUCR));
}

void LevelUp(int p = 0){
	trUnitSelectByQV("P"+p+"Space");
	trUnitChangeProtoUnit("Maceman");
	trUnitSelectByQV("P"+p+"Space");
	trSetSelectedScale(0,0,0);
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xLUCL, 3);
	xSetInt(dPlayerData, xLUCR, 4);
	if(trCurrentPlayer() == p){
		OverlayTextPlayerColor(p);
		trOverlayText("LEVEL UP - press space to choose a reward", 5.0, 404, 300, 3000);
	}
}

rule ETERNAL_LOOPS
inactive
highFrequency
{
	if(Pregame == false){
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
					trPlayerGrantResources(p, "Wood", -10000.0);
					trPlayerGrantResources(p, "Gold", -10000.0);
					trPlayerGrantResources(p, "Wood", 200.0);
					trPlayerGrantResources(p, "Gold", 100.0);
					if(trPlayerUnitCountSpecific(p, "Villager Atlantean Hero") == 0){
						//Defeated
						EvilLaugh();
						PlayerLighting(p, 4.0);
						PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " has been " + DeadText());
						trSetPlayerDefeated(p);
						trPlayerKillAllBuildings(p);
						trPlayerKillAllGodPowers(p);
						trPlayerKillAllUnits(p);
						xSetBool(dPlayerData, xPlayerAlive, false);
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
			}
			if(xGetBool(dPlayerData, xPlayerRunner) == false){
				trPlayerGrantResources(p, "Wood", -10000.0);
				trPlayerGrantResources(p, "Wood", 5.0);
				//hunter resign
				if((playerIsPlaying(p) == false) || (trPlayerUnitCountSpecific(p, "Temple") == 0) ){
					PlayerColouredChat(p, "I am a resigning n00b");
					PlayerColouredChat(p, "Repeat hunter resigners will be locked out of the map");
					trSetPlayerDefeated(p);
					trPlayerKillAllBuildings(p);
					trPlayerKillAllGodPowers(p);
					trPlayerKillAllUnits(p);
					xSetBool(dPlayerData, xPlayerAlive, false);
				}
			}
		}
		if(trPlayerUnitCountSpecific(p, "Maceman Hero") > 0){
			trUnitSelectByQV("P"+p+"Space");
			trUnitChangeProtoUnit("Cinematic Block");
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
	}
}

rule Test
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 3){
		xsDisableSelf();
		LevelUp(1);
	}
}

