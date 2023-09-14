rule ETERNAL_LOOPS
inactive
highFrequency
{
	if(Pregame == false){
		CyclePlayers = CyclePlayers+1;
		if(CyclePlayers > cNumberNonGaiaPlayers){
			CyclePlayers = 1;
		}
		int p = CyclePlayers;
		trUnitSelectClear();
		trUnitSelectByID(0);
		trDamageUnitsInArea(p, "Temple", MapSize, -100000);
		xSetPointer(dPlayerData, p);
		if(trPlayerUnitCountSpecific(p, "Wall Long") > 0){
			trUnitSelectClear();
			trUnitSelectByID(0);
			trUnitChangeInArea(p,p, "Wall Long", "Gate", MapSize);
		}
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
	}
}
