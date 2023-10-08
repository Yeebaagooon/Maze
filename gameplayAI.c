bool GodPowerChance(int name = 0, int override = 0){
	//chance of invoking GP for AI
	if(override == 0){
		trQuestVarSetFromRand("temp", 0, 100);
	}
	else{
		trQuestVarSet("temp", 0);
	}
	if(1*trQuestVarGet("temp") < MapFactor()){
		if(Between(AutoHunterLevel,2,4)){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Undermine", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Undermine", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(Between(AutoHunterLevel,5,6)){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Lightning Storm", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Lightning Storm", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(Between(AutoHunterLevel,7,8)){
			if(trCheckGPActive("Tornado", cNumberNonGaiaPlayers) == false){
				grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Tornado", MapFactor());
				trUnitSelectClear();
				trUnitSelect(""+name);
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Tornado", kbGetBlockPosition(""+name), vector(0,0,0));
			}
		}
		if(Between(AutoHunterLevel,9,10)){
			grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Tartarian Gate", MapFactor());
			trUnitSelectClear();
			trUnitSelect(""+name);
			trTechInvokeGodPower(cNumberNonGaiaPlayers, "Tartarian Gate", kbGetBlockPosition(""+name), vector(0,0,0));
		}
		if(AutoHunterLevel > 10){
			trQuestVarSetFromRand("temp", 1, AutoHunterLevel);
			if(1*trQuestVarGet("temp") <= 2){
				grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Tartarian Gate", MapFactor());
				trUnitSelectClear();
				trUnitSelect(""+name);
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Tartarian Gate", kbGetBlockPosition(""+name), vector(0,0,0));
			}
			else if(1*trQuestVarGet("temp") <= 6){
				if(trCheckGPActive("Meteor", cNumberNonGaiaPlayers) == false){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Meteor", MapFactor());
					trUnitSelectClear();
					trUnitSelect(""+name);
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Meteor", kbGetBlockPosition(""+name), vector(0,0,0));
				}
			}
			else if(1*trQuestVarGet("temp") < 9){
				if(trCheckGPActive("Earthquake", cNumberNonGaiaPlayers) == false){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Earthquake", MapFactor());
					trUnitSelectClear();
					trUnitSelect(""+name);
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Earthquake", kbGetBlockPosition(""+name), vector(0,0,0));
				}
			}
			else if(1*trQuestVarGet("temp") > 9){
				grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Vortex", MapFactor());
				trUnitSelectClear();
				trTechInvokeGodPower(cNumberNonGaiaPlayers, "Vortex", kbGetBlockPosition(""+name), vector(0,0,0));
			}
		}
		return(true);
		AIVector = kbGetBlockPosition(""+name);
	}
}

bool AI_Send_Death_Squad(int name = 0, int override = 0){
	int temp = 0;
	if(trTime() > 300){
		if(override == 0){
			trQuestVarSetFromRand("temp", 0, 300/(MapFactor()));
		}
		else{
			trQuestVarSet("temp", 0);
		}
		if(1*trQuestVarGet("temp") < 1){
			trQuestVarSetFromRand("temp", 1, 2);
			if(1*trQuestVarGet("temp") == 1){
				for(n = 1; < 5){
					temp = UnitCreate(cNumberNonGaiaPlayers, rangedunit,(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, 0);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(xsVectorGetX(kbGetBlockPosition(""+name)),5,xsVectorGetZ(kbGetBlockPosition(""+name)),-1,true);
				}
			}
			else{
				for(n = 1; < 5){
					temp = UnitCreate(cNumberNonGaiaPlayers, handunit,(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, 0);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(xsVectorGetX(kbGetBlockPosition(""+name)),5,xsVectorGetZ(kbGetBlockPosition(""+name)),-1,true);
				}
			}
			return(true);
		}
		else{
			return(false);
		}
	}
	else{
		return(false);
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
				//scatter behaviour
				x = trCountUnitsInArea(""+xGetInt(dEnemies, xUnitID), cNumberNonGaiaPlayers, "All", 20);
				if((x > 10) && (x < 20)){
					trUnitMoveToPoint(xsVectorGetX(AIVector),5,xsVectorGetZ(AIVector),-1,true);
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
		if(trPlayerGetPopulation(cNumberNonGaiaPlayers) < (90+20*cNumberNonGaiaPlayers)){
			//spawn
			temp = UnitCreate(cNumberNonGaiaPlayers, rangedunit,(MapSize/2)+5,(MapSize/2)+5);
			xAddDatabaseBlock(dEnemies, true);
			xSetInt(dEnemies, xUnitID, temp);
			xSetInt(dEnemies, xIdleTimeout, trTime()+30);
			trQuestVarSetFromRand("x", 0 , MapSize);
			trQuestVarSetFromRand("z", 0 , MapSize);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
			temp = UnitCreate(cNumberNonGaiaPlayers, handunit,(MapSize/2)-5,(MapSize/2)-5);
			xAddDatabaseBlock(dEnemies, true);
			xSetInt(dEnemies, xUnitID, temp);
			xSetInt(dEnemies, xIdleTimeout, trTime()+30);
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
						trUnitSelectClear();
						temp = UnitCreate(0, "Dwarf", xsVectorGetX(end),xsVectorGetZ(end));
						trUnitSelect(""+temp);
						trImmediateUnitGarrison(""+xGetInt(dMountainGiants, xSpecialTargetID));
						trUnitSelectClear();
						trUnitSelect(""+temp);
						trUnitChangeProtoUnit("Wall Connector Destruction SFX");
						DamageBuildingCountRazes(p,xGetInt(dMountainGiants,xSpecialTargetID),2.0,1000.0);
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

rule HekaSpecial
inactive
highFrequency
{
	//Zeno MG code
	if (xGetDatabaseCount(dHekas) > 0) {
		int id = 0;
		int p = 0;
		int target = 0;
		int temp = 0;
		vector end = vector(0,0,0);
		xDatabaseNext(dHekas);
		id = xGetInt(dHekas,xHekaID);
		trUnitSelectClear();
		trUnitSelectByID(id);
		p = xGetInt(dHekas,xPlayerOwner);
		//db = databaseName(p);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dHekas);
		} else if (trTimeMS() > xGetInt(dHekas, xSpecialNext)) {
			switch(xGetInt(dHekas, xSpecialStep))
			{
				case 0:
				{
					if (kbUnitGetAnimationActionType(id) == 6) {
						xsSetContextPlayer(p);
						target = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(id));
						xsSetContextPlayer(0);
						xSetVector(dHekas,xSpecialTarget,kbGetBlockPosition(""+target));
						xSetInt(dHekas, xSpecialNext, trTimeMS() + 1090);
						xSetInt(dHekas, xSpecialStep, 1);
						xSetInt(dHekas, xSpecialTargetID, target);
						trUnitOverrideAnimation(26,0,false,true,-1);
					}
				}
				case 1:
				{
					end = xGetVector(dHekas,xSpecialTarget);
					trUnitSelectClear();
					DamageBuildingCountRazes(p,xGetInt(dHekas,xSpecialTargetID),5.0,1000.0);
					xSetInt(dHekas, xSpecialNext, trTimeMS() + 1210);
					xSetInt(dHekas, xSpecialStep, 2);
				}
				case 2:
				{
					xSetInt(dHekas, xSpecialStep, 0);
					xSetInt(dHekas, xSpecialNext, trTimeMS() + 15000);
					trUnitOverrideAnimation(-1,0,false,true,-1);
				}
			}
		}
	}
}

rule LampadesSpecial
inactive
highFrequency
{
	//Zeno MG code
	if (xGetDatabaseCount(dLampades) > 0) {
		int id = 0;
		int p = 0;
		int target = 0;
		int temp = 0;
		vector end = vector(0,0,0);
		xDatabaseNext(dLampades);
		id = xGetInt(dLampades,xLampadesID);
		trUnitSelectClear();
		trUnitSelectByID(id);
		p = xGetInt(dLampades,xPlayerOwner);
		//db = databaseName(p);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dLampades);
		} else if (trTimeMS() > xGetInt(dLampades, xSpecialNext)) {
			switch(xGetInt(dLampades, xSpecialStep))
			{
				case 0:
				{
					if (kbUnitGetAnimationActionType(id) == 12) {
						xsSetContextPlayer(p);
						target = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(id));
						xsSetContextPlayer(0);
						xSetVector(dLampades,xSpecialTarget,kbGetBlockPosition(""+target));
						xSetInt(dLampades, xSpecialNext, trTimeMS() + 500);
						xSetInt(dLampades, xSpecialStep, 1);
						xSetInt(dLampades, xSpecialTargetID, target);
						trUnitOverrideAnimation(37,0,false,true,-1);
					}
				}
				case 1:
				{
					end = xGetVector(dLampades,xSpecialTarget);
					trUnitSelectClear();
					temp = UnitCreate(0, "Dwarf", xsVectorGetX(end),xsVectorGetZ(end));
					trUnitSelect(""+temp);
					trImmediateUnitGarrison(""+xGetInt(dLampades, xSpecialTargetID));
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Tartarian Gate birth");
					DamageBuildingCountRazes(p,xGetInt(dLampades,xSpecialTargetID),6.0,2000.0);
					xSetInt(dLampades, xSpecialNext, trTimeMS() + 500);
					xSetInt(dLampades, xSpecialStep, 2);
				}
				case 2:
				{
					xSetInt(dLampades, xSpecialStep, 0);
					xSetInt(dLampades, xSpecialNext, trTimeMS() + 20000);
					trUnitOverrideAnimation(-1,0,false,true,-1);
				}
			}
		}
	}
}

rule YeebSpecial
inactive
highFrequency
{
	//Zeno MG code
	if (xGetDatabaseCount(dBirds) > 0) {
		int id = 0;
		int p = 0;
		int target = 0;
		int temp = 0;
		int anim = 0;
		vector end = vector(0,0,0);
		xDatabaseNext(dBirds);
		id = xGetInt(dBirds,xBirdID);
		trUnitSelectClear();
		trUnitSelectByID(id);
		p = xGetInt(dBirds,xPlayerOwner);
		//db = databaseName(p);
		trDamageUnitPercent(-100);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dBirds);
		}
		else{
			anim = kbUnitGetAnimationActionType(id);
			if(anim != xGetInt(dBirds, xYeebAnim)){
				if (anim == 9) {
					trUnitSelectClear();
					xUnitSelect(dBirds, xYeebID);
					trUnitOverrideAnimation(2,0,true,true,-1);
					if(trUnitVisToPlayer()){
						playSound("soopselect"+(iModulo(4,trTimeMS())+1)+".wav");
					}
				}
				if ((anim == 11) || (anim == 10)) {
					trUnitSelectClear();
					xUnitSelect(dBirds, xYeebID);
					trUnitOverrideAnimation(15,0,true,true,-1);
					if(trUnitVisToPlayer()){
						playSound("soopmove"+(iModulo(4,trTimeMS())+1)+".wav");
					}
				}
				xSetInt(dBirds, xYeebAnim, anim);
			}
			if (trTimeMS() > xGetInt(dBirds, xSpecialNext)) {
				switch(xGetInt(dBirds, xSpecialStep))
				{
					case 0:
					{
						if (kbUnitGetAnimationActionType(id) == 12) {
							xsSetContextPlayer(p);
							target = trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(id));
							xsSetContextPlayer(0);
							xSetVector(dBirds,xSpecialTarget,kbGetBlockPosition(""+target));
							xSetInt(dBirds, xSpecialNext, trTimeMS() + 500);
							xSetInt(dBirds, xSpecialStep, 1);
							xSetInt(dBirds, xSpecialTargetID, target);
							trUnitOverrideAnimation(2,0,false,true,-1);
							xUnitSelect(dBirds, xYeebID);
							trUnitOverrideAnimation(25,0,false,true,-1);
							if(trUnitVisToPlayer()){
								playSound("soopattack.wav");
							}
							xSetInt(dBirds, xYeebAnim, anim);
						}
					}
					case 1:
					{
						end = xGetVector(dBirds,xSpecialTarget);
						trUnitSelectClear();
						temp = UnitCreate(0, "Dwarf", xsVectorGetX(end),xsVectorGetZ(end));
						trUnitSelect(""+temp);
						trImmediateUnitGarrison(""+xGetInt(dBirds, xSpecialTargetID));
						trUnitSelectClear();
						trUnitSelect(""+temp);
						trUnitChangeProtoUnit("Implode Sphere Effect");
						trUnitSelectClear();
						trUnitSelect(""+temp);
						trDamageUnitPercent(100);
						temp = UnitCreate(0, "Dwarf", xsVectorGetX(end),xsVectorGetZ(end));
						trUnitSelect(""+temp);
						trImmediateUnitGarrison(""+xGetInt(dBirds, xSpecialTargetID));
						trUnitSelectClear();
						trUnitSelect(""+temp);
						trUnitChangeProtoUnit("Osiris Box Glow");
						trUnitSelectClear();
						temp = UnitCreate(0, "Dwarf", xsVectorGetX(end),xsVectorGetZ(end));
						trUnitSelect(""+temp);
						trImmediateUnitGarrison(""+xGetInt(dBirds, xSpecialTargetID));
						trUnitSelectClear();
						trUnitSelect(""+temp);
						trUnitChangeProtoUnit("Arkantos God Out");
						trUnitSelectClear();
						DamageBuildingCountRazes(p,xGetInt(dBirds,xSpecialTargetID),10.0,20000.0);
						xSetInt(dBirds, xSpecialNext, trTimeMS() + 1000);
						xSetInt(dBirds, xSpecialStep, 2);
						xUnitSelect(dBirds, xSpecialTargetID);
						trDamageUnitPercent(100);
						if(trUnitVisToPlayer()){
							playSound("\cinematics\24_in\magic.mp3");
						}
					}
					case 2:
					{
						xSetInt(dBirds, xSpecialStep, 0);
						xSetInt(dBirds, xSpecialNext, trTimeMS() + 500);
						trUnitOverrideAnimation(-1,0,false,true,-1);
						xSetInt(dBirds, xYeebAnim, 0);
					}
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
				trQuestVarSetFromRand("temp", 1, AutoHunterLevel);
				int name = xGetInt(dTowers, xTowerName);
				if(1*trQuestVarGet("temp") <= 5){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Tartarian Gate", MapFactor());
					trUnitSelectClear();
					trUnitSelect(""+name);
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Tartarian Gate", kbGetBlockPosition(""+name), vector(0,0,0));
				}
				else if(1*trQuestVarGet("temp") <= 7){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Tornado", MapFactor());
					trUnitSelectClear();
					trUnitSelect(""+name);
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Tornado", kbGetBlockPosition(""+name), vector(0,0,0));
				}
				else if(1*trQuestVarGet("temp") < 10){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Meteor", MapFactor());
					trUnitSelectClear();
					trUnitSelect(""+name);
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Meteor", kbGetBlockPosition(""+name), vector(0,0,0));
				}
				else if(1*trQuestVarGet("temp") < 13){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Earthquake", MapFactor());
					trUnitSelectClear();
					trUnitSelect(""+name);
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Earthquake", kbGetBlockPosition(""+name), vector(0,0,0));
				}
				else if(1*trQuestVarGet("temp") >= 13){
					grantGodPowerNoRechargeNextPosition(cNumberNonGaiaPlayers, "Vortex", MapFactor());
					trUnitSelectClear();
					trTechInvokeGodPower(cNumberNonGaiaPlayers, "Vortex", kbGetBlockPosition(""+name), vector(0,0,0));
				}
				Done = true;
			}
		}
		if(Safety > target){
			Done = true;
		}
	}
	xsDisableSelf();
}

rule TowerDB
inactive
highFrequency
{
	//DAMAGE BECAUSE NOT EVERY LOOP, NEED EACH ONE TO HAVE A TIME LAST CHECKED
	//so the damage would be like trTimeMS() - xGetVar(lava, xPreviousTime)
	if (xGetDatabaseCount(dTowers) > 0) {
		xDatabaseNext(dTowers);
		xUnitSelect(dTowers, xTowerName);
		int p = xGetInt(dTowers,xPlayerOwner);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dTowers);
		}
		else{
			if(trCheckGPActive("Restoration", p) == false){
				int x = xsVectorGetX(kbGetBlockPosition(""+xGetInt(dTowers, xTowerName)))/2;
				int z = xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dTowers, xTowerName)))/2;
				if((trGetTerrainType(x,z) == 5) && (trGetTerrainSubType(x,z) == 7)){
					//Hades4Passable
					xUnitSelect(dTowers, xTowerName);
					trDamageUnit(1.001*timediff);
				}
			}
		}
	}
}

rule BuildingDB
inactive
highFrequency
{
	//Zeno MG code
	if (xGetDatabaseCount(dBuildings) > 0) {
		xDatabaseNext(dBuildings);
		xUnitSelect(dBuildings, xUnitName);
		int p = xGetInt(dTowers,xPlayerOwner);
		if (trUnitAlive() == false) {
			xFreeDatabaseBlock(dBuildings);
		}
		else{
			if(trCheckGPActive("Restoration", p) == false){
				int x = xsVectorGetX(kbGetBlockPosition(""+xGetInt(dBuildings, xUnitName)))/2;
				int z = xsVectorGetZ(kbGetBlockPosition(""+xGetInt(dBuildings, xUnitName)))/2;
				if((trGetTerrainType(x,z) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(x,z) == getTerrainSubType("Hades4Passable"))){
					xUnitSelect(dBuildings, xUnitName);
					trDamageUnit(trTimeMS()-xGetInt(dTowers, xLastCheck)*0.01);
					
				}
			}
		}
		xSetInt(dTowers, xLastCheck, trTimeMS());
	}
}


rule VolcanoLava
inactive
highFrequency
{
	if (xGetDatabaseCount(dVolcanoDB) > 0) {
		int linkid = 0; //a pointer to link the volcanodb with the frontier db
		int Safety = 0;
		int posx = 0;
		int posz = 0;
		xDatabaseNext(dVolcanoDB);
		//Select the volcano source
		linkid = xGetInt(dVolcanoDB, xVolcanoLink);
		if((xGetInt(dVolcanoDB, xVolcanoTiles) < 200) && (xGetInt(dVolcanoDB, xVolcanoTime) < trTimeMS()+50000)){
			//can produce lava
			if(trTimeMS() > xGetInt(dVolcanoDB, xVolcanoNextTime)){
				xSetInt(dVolcanoDB, xVolcanoNextTime, trTimeMS()+100);
				//create lava
				trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dVolcanoFrontierDB));
				for(a = 0; < 1*trQuestVarGet("temp")){
					xDatabaseNext(dVolcanoFrontierDB);
				}
				while((xGetInt(dVolcanoFrontierDB, xVFLink) != linkid) && (xGetBool(dVolcanoFrontierDB, xVFPainted) == false)){
					xDatabaseNext(dVolcanoFrontierDB);
					Safety = Safety+1;
					if(Safety > 100){
						debugLog("Break Volcanolava");
						xFreeDatabaseBlock(dVolcanoDB);
						if (xGetDatabaseCount(dVolcanoFrontierDB) > 0) {
							for(a = xGetDatabaseCount(dVolcanoFrontierDB); > 0){
								xDatabaseNext(dVolcanoFrontierDB);
								if(xGetInt(dVolcanoFrontierDB, xVFLink) == linkid){
									xFreeDatabaseBlock(dVolcanoFrontierDB);
								}
							}
						}
						break;
					}
				}
				//find valid target
				posx = xGetInt(dVolcanoFrontierDB, xVFPosX);
				posz = xGetInt(dVolcanoFrontierDB, xVFPosZ);
				//paint area
				trPaintTerrain(xGetInt(dVolcanoFrontierDB, xVFPosX),xGetInt(dVolcanoFrontierDB, xVFPosZ),xGetInt(dVolcanoFrontierDB, xVFPosX),xGetInt(dVolcanoFrontierDB, xVFPosZ),getTerrainType("Hades4Passable"), getTerrainSubType("Hades4Passable"));
				xSetBool(dVolcanoFrontierDB, xVFPainted, true);
				xSetInt(dVolcanoDB, xVolcanoTiles, xGetInt(dVolcanoDB, xVolcanoTiles)+1);
				//add to terrain reset db
				xAddDatabaseBlock(dTerrainRepaintDB, true);
				xSetInt(dTerrainRepaintDB,xTileX,posx);
				xSetInt(dTerrainRepaintDB,xTileZ,posz);
				xSetInt(dTerrainRepaintDB,xTime,trTimeMS()+45000);
				
				//check frontier and add to db if valid target
				if((trGetTerrainType(xGetInt(dVolcanoFrontierDB, xVFPosX)+1,xGetInt(dVolcanoFrontierDB, xVFPosZ)) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xGetInt(dVolcanoFrontierDB, xVFPosX)+1,xGetInt(dVolcanoFrontierDB, xVFPosZ)) == getTerrainSubType(RoadTerrain))){
					xAddDatabaseBlock(dVolcanoFrontierDB, true);
					xSetInt(dVolcanoFrontierDB, xVFPosX, posx+1);
					xSetInt(dVolcanoFrontierDB, xVFPosZ, posz);
					xSetInt(dVolcanoFrontierDB, xVFTime, trTimeMS());
					xSetBool(dVolcanoFrontierDB, xVFPainted, false);
					xSetInt(dVolcanoFrontierDB, xVFLink, linkid);
				}
				if((trGetTerrainType(xGetInt(dVolcanoFrontierDB, xVFPosX)-1,xGetInt(dVolcanoFrontierDB, xVFPosZ)) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xGetInt(dVolcanoFrontierDB, xVFPosX)-1,xGetInt(dVolcanoFrontierDB, xVFPosZ)) == getTerrainSubType(RoadTerrain))){
					xAddDatabaseBlock(dVolcanoFrontierDB, true);
					xSetInt(dVolcanoFrontierDB, xVFPosX, posx-1);
					xSetInt(dVolcanoFrontierDB, xVFPosZ, posz);
					xSetInt(dVolcanoFrontierDB, xVFTime, trTimeMS());
					xSetBool(dVolcanoFrontierDB, xVFPainted, false);
					xSetInt(dVolcanoFrontierDB, xVFLink, linkid);
				}
				if((trGetTerrainType(xGetInt(dVolcanoFrontierDB, xVFPosX),xGetInt(dVolcanoFrontierDB, xVFPosZ)-1) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xGetInt(dVolcanoFrontierDB, xVFPosX),xGetInt(dVolcanoFrontierDB, xVFPosZ)-1) == getTerrainSubType(RoadTerrain))){
					xAddDatabaseBlock(dVolcanoFrontierDB, true);
					xSetInt(dVolcanoFrontierDB, xVFPosX, posx);
					xSetInt(dVolcanoFrontierDB, xVFPosZ, posz-1);
					xSetInt(dVolcanoFrontierDB, xVFTime, trTimeMS());
					xSetBool(dVolcanoFrontierDB, xVFPainted, false);
					xSetInt(dVolcanoFrontierDB, xVFLink, linkid);
				}
				if((trGetTerrainType(xGetInt(dVolcanoFrontierDB, xVFPosX),xGetInt(dVolcanoFrontierDB, xVFPosZ)+1) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xGetInt(dVolcanoFrontierDB, xVFPosX),xGetInt(dVolcanoFrontierDB, xVFPosZ)+1) == getTerrainSubType(RoadTerrain))){
					xAddDatabaseBlock(dVolcanoFrontierDB, true);
					xSetInt(dVolcanoFrontierDB, xVFPosX, posx);
					xSetInt(dVolcanoFrontierDB, xVFPosZ, posz+1);
					xSetInt(dVolcanoFrontierDB, xVFTime, trTimeMS());
					xSetBool(dVolcanoFrontierDB, xVFPainted, false);
					xSetInt(dVolcanoFrontierDB, xVFLink, linkid);
				}
				//now remove painted tiles from the frontiet bd
				if (xGetDatabaseCount(dVolcanoFrontierDB) > 0) {
					for(a = xGetDatabaseCount(dVolcanoFrontierDB); > 0){
						xDatabaseNext(dVolcanoFrontierDB);
						if((xGetInt(dVolcanoFrontierDB, xVFLink) == linkid) && (xGetBool(dVolcanoFrontierDB, xVFPainted) == true)){
							xFreeDatabaseBlock(dVolcanoFrontierDB);
						}
					}
				}
			}
			
		}
		else{
			//timeout, remove
			//debugLog("Lava limit reached");
			xUnitSelect(dVolcanoDB, xVolcanoName);
			trUnitDestroy();
			xFreeDatabaseBlock(dVolcanoDB);
			if (xGetDatabaseCount(dVolcanoFrontierDB) > 0) {
				for(a = xGetDatabaseCount(dVolcanoFrontierDB); > 0){
					xDatabaseNext(dVolcanoFrontierDB);
					if(xGetInt(dVolcanoFrontierDB, xVFLink) == linkid){
						xFreeDatabaseBlock(dVolcanoFrontierDB);
					}
				}
			}
		}
	}
}

rule RepaintTerrain
inactive
highFrequency
{
	if (xGetDatabaseCount(dTerrainRepaintDB) > 0) {
		xDatabaseNext(dTerrainRepaintDB);
		if(xGetInt(dTerrainRepaintDB, xTime) < trTimeMS()){
			//repaint
			trPaintTerrain(xGetInt(dTerrainRepaintDB, xTileX),xGetInt(dTerrainRepaintDB, xTileZ),xGetInt(dTerrainRepaintDB, xTileX),xGetInt(dTerrainRepaintDB, xTileZ),getTerrainType(RoadTerrain), getTerrainSubType(RoadTerrain));
			xFreeDatabaseBlock(dTerrainRepaintDB);
		}
		if (xGetDatabaseCount(dTerrainRepaintDB) == 0) {
			refreshPassability();
			playSound("godpowerfailed.wav");
		}
	}
}
