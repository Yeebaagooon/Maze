rule AI_Activate
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 30){
		xsDisableSelf();
		int old = xsGetContextPlayer();
		trOverlayText("The hunter units are coming!", 4.0, 534, 300, 1000);
		xsSetContextPlayer(cNumberNonGaiaPlayers);
		aiSetAttackResponseDistance(80.0);
		xsSetContextPlayer(old);
		xsEnableRule("AI_Spawn");
		xsEnableRule("AI_DB_Check");
	}
}

rule AI_DB_Check
inactive
highFrequency
{
	int anim = 0;
	for(n = 1 ; < xsMin(8, xGetDatabaseCount(dEnemies))){
		xDatabaseNext(dEnemies);
		if(xGetInt(dEnemies, xIdleTimeout) < trTime()){
			anim = kbUnitGetAnimationActionType(kbGetBlockID(""+xGetInt(dEnemies, xUnitID)));
			if(anim == 9){
				trQuestVarSetFromRand("x", 0 , MapSize);
				trQuestVarSetFromRand("z", 0 , MapSize);
				xUnitSelect(dEnemies, xUnitID);
				trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				xSetInt(dEnemies, xIdleTimeout, 1*trQuestVarGet("x")/10+trTime()+30);
			}
		}
		xUnitSelect(dEnemies, xUnitID);
		if(trUnitDead()){
			xFreeDatabaseBlock(dEnemies);
		}
	}
	//if dead, remove
}

rule AI_Spawn
inactive
highFrequency
{
	if(1*trQuestVarGet("SpawnTime") < trTime()){
		trQuestVarSet("SpawnTime", trTime()+1);
		int temp = -1;
		if(trPlayerGetPopulation(cNumberNonGaiaPlayers) < 100){
			//spawn
			temp = UnitCreate(cNumberNonGaiaPlayers, rangedunit,(MapSize/2)+5,(MapSize/2)+5);
			xAddDatabaseBlock(dEnemies, true);
			xSetInt(dEnemies, xUnitID, temp);
			xSetInt(dEnemies, xIdleTimeout, 0);
			trQuestVarSetFromRand("x", 0 , MapSize);
			trQuestVarSetFromRand("z", 0 , MapSize);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
			temp = UnitCreate(cNumberNonGaiaPlayers, handunit,(MapSize/2)-5,(MapSize/2)-5);
			xAddDatabaseBlock(dEnemies, true);
			xSetInt(dEnemies, xUnitID, temp);
			xSetInt(dEnemies, xIdleTimeout, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
		}
	}
	
}
