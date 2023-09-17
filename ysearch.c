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
					GodPowerChance(j);
					AI_Send_Death_Squad(j);
				}
				break;
			}
			case kbGetProtoUnitID("Meteor"):
			{
				trUnitSelectClear();
				//trUnitSelectByID(id);
				DamageBuildingCountRazes(kbUnitGetOwner(id),kbGetBlockPosition(""+j),6.0,2000.0);
				//trDamageUnitsInArea(p, "Building", 6, 2000);
				//trDamageUnitsInArea(p, "Unit", 6, 200);
				break;
			}
			case kbGetProtoUnitID("Lightning Sparks"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				for(p = 1 ; <= cNumberNonGaiaPlayers){
					xSetPointer(dPlayerData, p);
					if(xGetBool (dPlayerData, xPlayerRunner)){
						trDamageUnitsInArea(p, "Building", 1, 200);
						trDamageUnitsInArea(p, "Unit", 1, 50);
						/*
						HALP KB STUFF to add to kill count
						int kbnum = 0;
						xsSetContextPlayer(5);
						kbnum = kbUnitQueryCreate("id");
						kbUnitQuerySetPlayerID(kbnum, true);
						kbUnitQuerySetMaximumDistance(3);
						kbUnitQuerySetPosition(kbGetBlockPosition(""+id, true));
						kbUnitQuerySetUnitType(-1);
						kbLookAtAllUnitsOnMap();
						int counts = kbUnitQueryExecute(kbnum);
						for(inte = 0; < counts){
							trUnitSelectClear();
							trUnitSelectByID(kbUnitQueryGetResult(kbnum, inte));
							if(trUnitPercentDamaged() >= 100){
								trQuestVarSet("P"+(1*trQuestVarGet("M9"))+"AddKills", trQuestVarGet("P"+(1*trQuestVarGet("M9"))+"AddKills") + 1);
							}
						}
						kbUnitQueryDestroy(id);
						trUnitSelectClear();
						trUnitSelectByID(UnitID);
						xsSetContextPlayer(0);
						*/
					}
				}
				break;
			}
			case kbGetProtoUnitID("Lightning Scorch"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				for(p = 1 ; <= cNumberNonGaiaPlayers){
					xSetPointer(dPlayerData, p);
					//trDamageUnitsInArea(p, "Building", 1, 2000);
					trDamageUnitsInArea(p, "Unit", 1, 2000);
				}
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
