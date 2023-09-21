rule ysearch
active
highFrequency
{
	int id = 0;
	int unittype = 0;
	int temp = 0;
	int closest = 0;
	int closestid = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
	for(j = spysearch; < trGetNextUnitScenarioNameNumber()) {
		id = kbGetBlockID(""+j, true);
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
					if (aiPlanSetUserVariableInt(1*xsVectorGetX(dest),1*xsVectorGetY(dest),1*xsVectorGetZ(dest),j) == false) {
						//	debugLog("spy error N/A: " + 1*xsVectorGetX(dest) + "," + 1*xsVectorGetY(dest) + "," + 1*xsVectorGetZ(dest));
					}
					xFreeDatabaseBlock(dSpyRequests);
					spyreset = 0;
				} else {
					//	debugLog("Spy Buffer is empty");
				}
				break;
			}
			case kbGetProtoUnitID("Mountain Giant"):
			{
				xAddDatabaseBlock(dMountainGiants, true);
				xSetInt(dMountainGiants, xMountainGiantID, id);
				xSetInt(dMountainGiants, xPlayerOwner, kbUnitGetOwner(id));
				xSetInt(dMountainGiants, xSpecialNext, 0);
				xSetInt(dMountainGiants, xSpecialStep, 0);
				xSetVector(dMountainGiants, xSpecialTarget, vector(0,0,0));
				xSetInt(dMountainGiants, xSpecialTargetID, 0);
				break;
			}
			case kbGetProtoUnitID("Heka Gigantes"):
			{
				xAddDatabaseBlock(dHekas, true);
				xSetInt(dHekas, xHekaID, id);
				xSetInt(dHekas, xPlayerOwner, kbUnitGetOwner(id));
				xSetInt(dHekas, xSpecialNext, 0);
				xSetInt(dHekas, xSpecialStep, 0);
				xSetVector(dHekas, xSpecialTarget, vector(0,0,0));
				xSetInt(dHekas, xSpecialTargetID, 0);
				break;
			}
			case kbGetProtoUnitID("Lampades"):
			{
				xAddDatabaseBlock(dLampades, true);
				xSetInt(dLampades, xLampadesID, id);
				xSetInt(dLampades, xPlayerOwner, kbUnitGetOwner(id));
				xSetInt(dLampades, xSpecialNext, 0);
				xSetInt(dLampades, xSpecialStep, 0);
				xSetVector(dLampades, xSpecialTarget, vector(0,0,0));
				xSetInt(dLampades, xSpecialTargetID, 0);
				break;
			}
			case kbGetProtoUnitID("Attack Revealer"):
			{
				if(AutoEscape){
					if(kbUnitGetOwner(id) == cNumberNonGaiaPlayers){
						GodPowerChance(j);
						AI_Send_Death_Squad(j);
					}
				}
				break;
			}
			case kbGetProtoUnitID("Tower"):
			{
				xAddDatabaseBlock(dTowers, true);
				xSetInt(dTowers, xTowerName, j);
				xSetInt(dTowers, xPlayerOwner, kbUnitGetOwner(id));
				if(AutoEscape){
					GodPowerChance(j);
				}
				break;
			}
			case kbGetProtoUnitID("Sky Passage"):
			{
				if(AutoEscape){
					if(trTime() > 240){
						GodPowerChance(j);
						AI_Send_Death_Squad(j);
						debugLog("SP");
					}
				}
				break;
			}
			case kbGetProtoUnitID("Meteor"):
			{
				trUnitSelectClear();
				DamageBuildingCountRazes(kbUnitGetOwner(id),kbGetBlockPosition(""+j),6.0,20000.0);
				break;
			}
			case kbGetProtoUnitID("SPCMeteor"):
			{
				trUnitSelectClear();
				DamageBuildingCountRazes(kbUnitGetOwner(id),kbGetBlockPosition(""+j),6.0,20000.0);
				trUnitSelectClear();
				DamageUnitCountKills(kbUnitGetOwner(id),kbGetBlockPosition(""+j),6.0,20000.0);
				break;
			}
			case kbGetProtoUnitID("Lightning Sparks"):
			{
				trUnitSelectClear();
				DamageBuildingCountRazes(kbUnitGetOwner(id),kbGetBlockPosition(""+j),1.0,200.0);
				break;
			}
			case kbGetProtoUnitID("Lightning Scorch"):
			{
				trUnitSelectClear();
				DamageUnitCountKills(kbUnitGetOwner(id),kbGetBlockPosition(""+j),1.0,200.0);
				break;
			}
			case kbGetProtoUnitID("Earthquake"):
			{
				xAddDatabaseBlock(dEarthquake, true);
				xSetInt(dEarthquake, xEarthquakeName, j);
				xSetInt(dEarthquake, xEarthquakeOwner, kbUnitGetOwner(id));
				xSetInt(dEarthquake, xEarthquakeTimeout, trTimeMS()+12000);
				break;
			}
			case kbGetProtoUnitID("Healing SFX"):
			{
				//8s
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}
			case kbGetProtoUnitID("Pegasus"):
			{
				xSetPointer(dPlayerData, kbUnitGetOwner(id));
				if(xGetBool(dPlayerData, xPlayerRunner) == false){
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Guardian XP");
				}
				break;
			}
			case kbGetProtoUnitID("Stymphalian Bird"):
			{
				int index = xAddDatabaseBlock(dBirds, true);
				xSetInt(dBirds, xLampadesID, id);
				xSetInt(dBirds, xPlayerOwner, kbUnitGetOwner(id));
				xSetInt(dBirds, xSpecialNext, 0);
				xSetInt(dBirds, xSpecialStep, 0);
				xSetVector(dBirds, xSpecialTarget, vector(0,0,0));
				xSetInt(dBirds, xSpecialTargetID, 0);
				xSetInt(dBirds, xYeebID, 0);
				xSetInt(dBirds, xYeebAnim, 0);
				trUnitSelectClear();
				trUnitSelectByID(id);
				spyEffect(kbGetProtoUnitID("Pharaoh Of Osiris XP"), 2, xsVectorSet(dBirds, xYeebID, index), vector(3,3,3));
				spyEffect(kbGetProtoUnitID("Mist"), 2, xsVectorSet(0,0,0), vector(1,1,1));
				spyEffect(kbGetProtoUnitID("Mist"), 2, xsVectorSet(0,0,0), vector(1,1,1));
				spyEffect(kbGetProtoUnitID("Mist"), 2, xsVectorSet(0,0,0), vector(1,1,1));
				spyEffect(kbGetProtoUnitID("Mist"), 2, xsVectorSet(0,0,0), vector(1,1,1));
				spyEffect(kbGetProtoUnitID("Flying Purple Hippo"), 15, xsVectorSet(0,0,0), vector(0,0,0));
				trUnitSelectClear();
				trUnitSelectByID(id);
				trSetSelectedScale(0.1,0.1,0.1);
				xUnitSelect(dBirds, xYeebID);
				trUnitConvert(kbUnitGetOwner(id));
				if(AutoEscape){
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, j);
					xSetInt(dEnemies, xIdleTimeout, trTime()+1);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				break;
			}
			case kbGetProtoUnitID("Chimera"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitChangeProtoUnit("Hero Death");
				for(p = 1 ; <= cNumberNonGaiaPlayers){
					if(trCheckGPActive("Change Chimera", p) == true){
						trQuestVarModify("P"+p+"AddKills", "+", 1);
					}
				}
				if(trUnitVisToPlayer()){
					playSound("\cinematics\a\lostsouls.mp3");
				}
				break;
			}
			case kbGetProtoUnitID("Barrage"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				DamageUnitCountKills(kbUnitGetOwner(id),kbGetBlockPosition(""+j),3.0,400.0);
				break;
			}
		}
		if (xGetDatabaseCount(dSpyRequests) > 0) {
			spyreset = spyreset + 1;
			if (spyreset >= 10) {
				//debugLog("Spy reset. Failed requests: " + xGetDatabaseCount(dSpyRequests));
				xClearDatabase(dSpyRequests);
				spyreset = 0;
			}
		}
	}
	spysearch = trGetNextUnitScenarioNameNumber();
}

rule UnblockSound
inactive
highFrequency
{
	trUnBlockAllAmbientSounds();
	trUnblockAllSounds();
	xsDisableSelf();
}
