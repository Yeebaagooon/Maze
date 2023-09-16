bool GodPowerChance(int name = 0, int override = 0){
	//chance of invoking GP for AI
	if(override == 0){
		trQuestVarSetFromRand("temp", 0, 100);
	}
	else{
		trQuestVarSet("temp", 0);
	}
	if(1*trQuestVarGet("temp") < MapFactor()){
		if(AutoHunterLevel == 2){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Undermine", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Undermine", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(AutoHunterLevel == 3){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Lightning Storm", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Lightning Storm", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(AutoHunterLevel == 4){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Earthquake", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Earthquake", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(AutoHunterLevel == 5){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Meteor", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Meteor", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(AutoHunterLevel >= 6){
			trQuestVarSetFromRand("temp", 5, 6);
			if(1*trQuestVarGet("temp") == 6){
				grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "SPCMeteor", MapFactor());
				trUnitSelectClear();
				trUnitSelect(""+name);
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "SPCMeteor", kbGetBlockPosition(""+name), vector(0,0,0));
			}
			if(1*trQuestVarGet("temp") == 6){
				grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Vortex", MapFactor());
				trUnitSelectClear();
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Vortex", kbGetBlockPosition(""+name), vector(0,0,0));
			}
		}
		return(true);
	}
}

rule AI_Activate
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 30){
		xsDisableSelf();
		trOverlayText("The hunter units are coming!", 4.0, 534, 300, 1000);
		xsSetContextPlayer(cNumberNonGaiaPlayers);
		aiSetAttackResponseDistance(800.0);
		xsSetContextPlayer(0);
		xsEnableRule("AI_Spawn");
		xsEnableRule("AI_DB_Check");
	}
}

rule AI_DB_Check
inactive
highFrequency
{
	int anim = 0;
	int x = 0;
	int z = 0;
	for(n = 1 ; < xsMin(8, xGetDatabaseCount(dEnemies))){
		xDatabaseNext(dEnemies);
		if(xGetInt(dEnemies, xIdleTimeout) < trTime()){
			anim = kbUnitGetAnimationActionType(kbGetBlockID(""+xGetInt(dEnemies, xUnitID)));
			if(anim == 9){
				//roll to check idle time
				trQuestVarSetFromRand("temp", 1 , 10);
				//override if clump
				x = trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "All", 20);
				if((x > 10) && (x < 20)){
					trQuestVarSetFromRand("temp", 3 , 4);
				}
				if(x > 20){
					trQuestVarSet("temp", 4);
				}
				if(1*trQuestVarGet("temp") <= 3){
					x = xsVectorGetX(kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID)));
					z = xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID)));
					trQuestVarSetFromRand("x", x-50 , x+50);
					trQuestVarSetFromRand("z", z-50 , z+50);
					xUnitSelect(dEnemies, xUnitID);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
					xSetInt(dEnemies, xIdleTimeout, 1*trQuestVarGet("x")/10+trTime()+30);
				}
				if(1*trQuestVarGet("temp") == 4){
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					xUnitSelect(dEnemies, xUnitID);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
					xSetInt(dEnemies, xIdleTimeout, 1*trQuestVarGet("x")/10+trTime()+30);
				}
				else{
					xSetInt(dEnemies, xIdleTimeout, trTime()+10);
				}
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

rule MGSpecial
inactive
highFrequency
{
	//Zeno MG code
	if (xGetDatabaseCount(dMountainGiants) > 0) {
		int id = 0;
		int p = 0;
		int target = 0;
		int temp = 0;
		vector end = vector(0,0,0);
		xDatabaseNext(dMountainGiants);
		id = xGetInt(dMountainGiants,xMountainGiantID);
		trUnitSelectClear();
		trUnitSelectByID(id);
		p = xGetInt(dMountainGiants,xPlayerOwner);
		//db = databaseName(p);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dMountainGiants);
		} else if (trTimeMS() > xGetInt(dMountainGiants, xSpecialNext)) {
			switch(xGetInt(dMountainGiants, xSpecialStep))
			{
				case 0:
				{
					if (kbUnitGetAnimationActionType(id) == 48) {
						//Centaur or satyr special is 49
						xsSetContextPlayer(p);
						target = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(id));
						xsSetContextPlayer(0);
						xSetVector(dMountainGiants,xSpecialTarget,kbGetBlockPosition(""+target));
						xSetInt(dMountainGiants, xSpecialNext, trTimeMS() + 1800);
						xSetInt(dMountainGiants, xSpecialStep, 1);
						xSetInt(dMountainGiants, xSpecialTargetID, target);
						//	trUnitOverrideAnimation(39,0,false,false,-1);
					}
				}
				case 1:
				{
					if (kbUnitGetAnimationActionType(id) == 48) {
						end = xGetVector(dMountainGiants,xSpecialTarget);
						xUnitSelect(dMountainGiants, xSpecialTargetID);
						for(q = 1; <= cNumberNonGaiaPlayers){
							xSetPointer(dPlayerData, q);
							if(xGetBool(dPlayerData, xPlayerRunner)){
								trDamageUnitsInArea(q, "All", 2, 1000);
							}
						}
						trUnitSelectClear();
						temp = UnitCreate(0, "Dwarf", xsVectorGetX(end),xsVectorGetZ(end));
						trUnitSelect(""+temp);
						trImmediateUnitGarrison(""+xGetInt(dMountainGiants, xSpecialTargetID));
						trUnitSelectClear();
						trUnitSelect(""+temp);
						trUnitChangeProtoUnit("Wall Connector Destruction SFX");
						xSetInt(dMountainGiants, xSpecialStep, 0);
						xSetInt(dMountainGiants, xSpecialNext, xGetInt(dMountainGiants, xSpecialNext) + 5);
					}
					else{
						//Player disengages
						xSetInt(dMountainGiants, xSpecialStep, 0);
						xSetInt(dMountainGiants, xSpecialNext, trTimeMS() + 1);
						xSetInt(dMountainGiants, xSpecialTargetID, -1);
						//trUnitOverrideAnimation(-1,0,false,true,-1);
					}
				}
				case 2:
				{
					xSetInt(dMountainGiants, xSpecialStep, 0);
					xSetInt(dMountainGiants, xSpecialNext, trTimeMS() + 5000);
					//trUnitOverrideAnimation(-1,0,false,true,-1);
				}
			}
		}
	}
}

rule AI_Force_Power
inactive
highFrequency
{
	bool Done = false;
	int Safety = 0;
	int target = xsMin(250,xGetDatabaseCount(dTowers));
	while(Done == false){
		xDatabaseNext(dTowers);
		Safety = Safety+1;
		if(kbUnitVisible(kbGetBlockID(""+xGetInt(dTowers, xTowerName)))){
			if(GodPowerChance(xGetInt(dTowers, xTowerName), 1)){
				Done = true;
				debugLog("Successful force fire");
			}
		}
		if(Safety > target){
			Done = true;
			debugLog("GP try failed");
		}
	}
	xsDisableSelf();
}

rule TowerDB
inactive
highFrequency
{
	//Zeno MG code
	if (xGetDatabaseCount(dTowers) > 0) {
		xDatabaseNext(dTowers);
		int name = xGetInt(dTowers,xTowerName);
		trUnitSelectClear();
		trUnitSelect(""+name);
		//p = xGetInt(dTowers,xPlayerOwner);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dTowers);
		}
	}
}
