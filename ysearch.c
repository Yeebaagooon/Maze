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
			case kbGetProtoUnitID("Implode Sphere"):
			{
				xAddDatabaseBlock(dImplode, true);
				xSetInt(dImplode, xImplodeID, j);
				xSetInt(dImplode, xImplodeOwner, kbUnitGetOwner(id));
				break;
			}
			case kbGetProtoUnitID("Implode Sphere Effect"):
			{
				if(kbUnitGetOwner(id) != 0){
					trUnitSelectClear();
					trUnitSelectByID(id);
					trMutateSelected(kbGetProtoUnitID("Kronny Birth"));
				}
				break;
			}
			case kbGetProtoUnitID("Monument"):
			{
				if(kbUnitGetOwner(id) != 0){
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitOverrideAnimation(4,0, true,true,-1);
					xAddDatabaseBlock(dMonuments, true);
					xSetInt(dMonuments, xMonumentName, j);
					xSetInt(dMonuments, xMonumentID, id);
					xSetVector(dMonuments, xMonumentPos, kbGetBlockPosition(""+j));
					xSetInt(dMonuments, xDecorMin, trGetNextUnitScenarioNameNumber());
					trVectorQuestVarSet("Monument", xGetVector(dMonuments, xMonumentPos));
					trVectorQuestVarSet("dir", xsVectorSet(0, 0, GPShieldRadius));
					float baseCos = xsCos(6.283185 / 15);
					float baseSin = xsSin(6.283185 / 15);
					for(a=1; <= 15) {
						trVectorQuestVarSet("base", trVectorQuestVarGet("Monument") + trVectorQuestVarGet("dir"));
						UnitCreate(0, "UI Range Indicator Norse SFX", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), 0);
						trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
					}
				}
				break;
			}
			case kbGetProtoUnitID("Manticore Barb"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trMutateSelected(kbGetProtoUnitID("Kronny Birth SFX"));
				trUnitSetAnimationPath("0,1,0,0,0,0");
				xAddDatabaseBlock(dVDManticore, true);
				xSetInt(dVDManticore, xVBName, j);
				xSetVector(dVDManticore, xVBPos, kbGetBlockPosition(""+j));
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
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
					break;
				}
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("black")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("black"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build here");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
					break;
				}
				if(AutoEscape){
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("HadesBuildable1")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("HadesBuildable1"))){
						trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build here in auto escape mode");
						trUnitSelectClear();
						trUnitSelectByID(id);
						if(trCurrentPlayer() == kbUnitGetOwner(id)){
							playSound("cantdothat.wav");
						}
						trUnitDestroy();
						break;
					}
				}
				xAddDatabaseBlock(dTowers, true);
				xSetInt(dTowers, xTowerName, j);
				xSetInt(dTowers, xTowerOwner, kbUnitGetOwner(id));
				if(AutoEscape){
					GodPowerChance(j);
				}
				break;
			}
			case kbGetProtoUnitID("Sky Passage"):
			{
				if(kbUnitGetOwner(id) != 0){
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
						trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
						trUnitSelectClear();
						trUnitSelectByID(id);
						if(trCurrentPlayer() == kbUnitGetOwner(id)){
							playSound("cantdothat.wav");
						}
						trUnitDestroy();
						break;
					}
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("black")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("black"))){
						trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build here");
						trUnitSelectClear();
						trUnitSelectByID(id);
						if(trCurrentPlayer() == kbUnitGetOwner(id)){
							playSound("cantdothat.wav");
						}
						trUnitDestroy();
						break;
					}
					if(AutoEscape){
						if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("HadesBuildable1")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("HadesBuildable1"))){
							trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build here in auto escape mode");
							trUnitSelectClear();
							trUnitSelectByID(id);
							if(trCurrentPlayer() == kbUnitGetOwner(id)){
								playSound("cantdothat.wav");
							}
							trUnitDestroy();
							break;
						}
					}
					xAddDatabaseBlock(dBuildings, true);
					xSetInt(dBuildings, xUnitName, j);
					xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
				}
				if(AutoEscape){
					if(trTime() > 240){
						GodPowerChance(j);
						AI_Send_Death_Squad(j);
						//debugLog("SP");
					}
				}
				break;
			}
			case kbGetProtoUnitID("Palace"):
			{
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
					break;
				}
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("black")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("black"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build here");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
					break;
				}
				if(AutoEscape){
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("HadesBuildable1")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("HadesBuildable1"))){
						trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build here in auto escape mode");
						trUnitSelectClear();
						trUnitSelectByID(id);
						if(trCurrentPlayer() == kbUnitGetOwner(id)){
							playSound("cantdothat.wav");
						}
						trUnitDestroy();
						break;
					}
				}
				xAddDatabaseBlock(dBuildings, true);
				xSetInt(dBuildings, xUnitName, j);
				xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
				xSetPointer(dPlayerData, kbUnitGetOwner(id));
				if(AutoEscape){
					GodPowerChance(j);
				}
				break;
			}
			case kbGetProtoUnitID("Shifting Sands Out"):
			{
				if(kbUnitGetOwner(id) != 0){
					for(n = 0 ; < 9){
						UnitCreate(kbUnitGetOwner(id), "Tower", xsVectorGetX(kbGetBlockPosition(""+j)), xsVectorGetZ(kbGetBlockPosition(""+j)));
					}
					trUnitSelectClear();
				}
				break;
			}
			case kbGetProtoUnitID("Shifting Sands In"):
			{
				if(kbUnitGetOwner(id) != 0){
					for(n = 0 ; < 9){
						UnitCreate(kbUnitGetOwner(id), "Tower", xsVectorGetX(kbGetBlockPosition(""+j)), xsVectorGetZ(kbGetBlockPosition(""+j)));
					}
					trUnitSelectClear();
				}
				break;
			}
			case kbGetProtoUnitID("Meteor"):
			{
				trUnitSelectClear();
				DamageBuildingCountRazes(kbUnitGetOwner(id),j,5.0,700.0);
				break;
			}
			case kbGetProtoUnitID("Tower Mirror"):
			{
				if(kbUnitGetOwner(id) != 0){
					xAddDatabaseBlock(dMirrorTower, true);
					xSetInt(dMirrorTower, xMirrorTowerID, id);
					xSetInt(dMirrorTower, xMirrorTowerOwner, kbUnitGetOwner(id));
					xSetInt(dMirrorTower, xMTLastShot, trTimeMS()-6000);
					trUnitSelectClear();
					xAddDatabaseBlock(dBuildings, true);
					xSetInt(dBuildings, xUnitName, j);
					xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
				}
				/*xSetInt(dMirrorTower, xMTDecorID,UnitCreate(0, "Dwarf", 1,1));
				xUnitSelect(dMirrorTower, xMTDecorID);
				trImmediateUnitGarrison(""+j);
				xUnitSelect(dMirrorTower, xMTDecorID);
				trUnitChangeProtoUnit("Vortex landing");*/
				//
				break;
			}
			case kbGetProtoUnitID("SPCMeteor"):
			{
				trUnitSelectClear();
				DamageBuildingCountRazes(kbUnitGetOwner(id),j,6.0,700.0);
				trUnitSelectClear();
				DamageUnitCountKills(kbUnitGetOwner(id),kbGetBlockPosition(""+j),6.0,500.0);
				break;
			}
			case kbGetProtoUnitID("Lightning Sparks"):
			{
				trUnitSelectClear();
				DamageBuildingCountRazes(kbUnitGetOwner(id),j,1.0,200.0);
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
			case kbGetProtoUnitID("Tornado"):
			{
				xAddDatabaseBlock(dTornado, true);
				xSetInt(dTornado, xTornadoName, j);
				xSetInt(dTornado, xTornadoOwner, kbUnitGetOwner(id));
				break;
			}
			/*case kbGetProtoUnitID("Healing SFX"):
			{
				//8s
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}*/
			case kbGetProtoUnitID("Pegasus"):
			{
				if(kbUnitGetOwner(id) != 0){
					xSetPointer(dPlayerData, kbUnitGetOwner(id));
					if(xGetBool(dPlayerData, xPlayerRunner) == false){
						trUnitSelectClear();
						trUnitSelectByID(id);
						trUnitChangeProtoUnit("Guardian XP");
					}
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
				spyEffect(kbGetProtoUnitID("Revealer"), 0, xsVectorSet(0,0,0), vector(0,0,0));
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
						gadgetRefresh("unitStatPanel");
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
			case kbGetProtoUnitID("Gold Mine Dwarven"):
			{
				/*if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType(RoadTerrain))){
					BuildCliff(kbGetBlockPosition(""+j));
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Undermine Building Destruction SFX");
				}
				else{
					int timesave = trTimeMS();
					int checknext = 0;
					int playersave = 0;
					for(p = 1 ; <= cNumberNonGaiaPlayers){
						for(slot = 0; < 4){
							checknext = trGetGPData(p,4,slot); //time MS of last cast
							if(trTimeMS()-checknext < timesave){ //get closest value to current time then determine player who cast and regrant
								timesave = checknext;
								playersave = p;
							}
						}
					}
					trChatSendToPlayer(0, playersave, "<color=1,0,0>Invalid placement - road required.</color>");
					grantGodPowerNoRechargeNextPosition(playersave, "create gold", 1);
					if(trCurrentPlayer() == playersave){
						playSound("cantdothat.wav");
					}
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Undermine Building Destruction SFX");
				}*/
				BuildCliff(kbGetBlockPosition(""+j));
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitChangeProtoUnit("Undermine Building Destruction SFX");
				break;
			}
			case kbGetProtoUnitID("Earth Dragon Hole"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitChangeProtoUnit("Dust Large");
				break;
			}
			case kbGetProtoUnitID("Frost Drift"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitChangeProtoUnit("Curse SFX");
				for(p = 1 ; <= cNumberNonGaiaPlayers){
					if(trCheckGPActive("Frost", p) == true){
						DamageUnitCountKills(p,kbGetBlockPosition(""+j),6.0,5000.0);
					}
				}
				break;
			}
			case kbGetProtoUnitID("Ice Sheet"):
			{
				trUnitSelectClear();
				xAddDatabaseBlock(dDestroyMe, true);
				xSetInt(dDestroyMe, xDestroyName, j);
				xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+9000);
				break;
			}
			case kbGetProtoUnitID("Ice Block"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				for(p = 1 ; <= cNumberNonGaiaPlayers){
					if(trCheckGPActive("Frost", p) == true){
						DamageUnitCountKills(p,kbGetBlockPosition(""+j),1.0,5000.0);
					}
				}
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitChangeProtoUnit("Ragnorok SFX");
				break;
			}
			case kbGetProtoUnitID("Chicken Exploding"):
			{
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType(RoadTerrain)) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType(RoadTerrain))){
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Tower");
					for(p = 1 ; < cNumberNonGaiaPlayers){
						if(trCheckGPActive("Chicken Storm", p) == true){
							trUnitSelectClear();
							trUnitSelectByID(id);
							trUnitConvert(p);
						}
					}
				}
				else{
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Dust Medium");
				}
				
				break;
			}
			case kbGetProtoUnitID("Hero Ragnorok"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitChangeProtoUnit("Villager Atlantean Hero");
				//trQuestVarSet("P"+kbUnitGetOwner(id)+"RagTime", trTime()+20);
				BoltUnitCountKills(kbUnitGetOwner(id), kbGetBlockPosition(""+j), 24.0, 1000);
				break;
			}
			case kbGetProtoUnitID("Tartarian Gate"):
			{
				if(Pregame == false){
					trQuestVarModify("Volcanoes", "+", 1);
					xAddDatabaseBlock(dVolcanoDB, true);
					xSetVector(dVolcanoDB, xVolcanoPos, kbGetBlockPosition(""+j));
					xSetVector(dVolcanoDB, xVolcanoPos, xGetVector(dVolcanoDB, xVolcanoPos)/2); //tile pos
					xSetInt(dVolcanoDB, xVolcanoName, j);
					xSetInt(dVolcanoDB, xVolcanoTiles, 0);
					xSetInt(dVolcanoDB, xVolcanoTime, trTimeMS());
					xSetInt(dVolcanoDB, xVolcanoLink, 1*trQuestVarGet("Volcanoes"));
					xSetInt(dVolcanoDB, xVolcanoNextTime, trTimeMS());
					//Link frontier
					xAddDatabaseBlock(dVolcanoFrontierDB, true);
					xSetInt(dVolcanoFrontierDB, xVFPosX, xsVectorGetX(xGetVector(dVolcanoDB, xVolcanoPos)));
					xSetInt(dVolcanoFrontierDB, xVFPosZ, xsVectorGetZ(xGetVector(dVolcanoDB, xVolcanoPos)));
					xSetInt(dVolcanoFrontierDB, xVFTime, trTimeMS());
					xSetBool(dVolcanoFrontierDB, xVFPainted, false);
					xSetInt(dVolcanoFrontierDB, xVFLink, 1*trQuestVarGet("Volcanoes"));
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Spy Eye");
					trUnitSelectClear();
					trUnitSelectByID(id);
					trMutateSelected(kbGetProtoUnitID("Tartarian Gate"));
					trUnitSelectClear();
					trUnitSelectByID(id);
					trSetSelectedScale(0.5,-0.5,0.5);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitOverrideAnimation(2,0,true,true,-1,-1);
				}
				break;
			}
			case kbGetProtoUnitID("Tartarian Gate Spawn"):
			{
				if(Pregame == false){
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitDestroy();
				}
				break;
			}
			case kbGetProtoUnitID("Bolt Strike"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}
			case kbGetProtoUnitID("Wall Connector"):
			{
				if(kbUnitGetOwner(id) != 0){
					if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
						trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
						trUnitSelectClear();
						trUnitSelectByID(id);
						if(trCurrentPlayer() == kbUnitGetOwner(id)){
							playSound("cantdothat.wav");
						}
						trUnitDestroy();
					}
					else{
						xAddDatabaseBlock(dBuildings, true);
						xSetInt(dBuildings, xUnitName, j);
						xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
					}
				}
				break;
			}
			case kbGetProtoUnitID("Wall Short"):
			{
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
				}
				else{
					xAddDatabaseBlock(dBuildings, true);
					xSetInt(dBuildings, xUnitName, j);
					xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
				}
				break;
			}
			case kbGetProtoUnitID("Wall Medium"):
			{
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
				}
				else{
					xAddDatabaseBlock(dBuildings, true);
					xSetInt(dBuildings, xUnitName, j);
					xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
				}
				break;
			}
			case kbGetProtoUnitID("Wall Long"):
			{
				if((trGetTerrainType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainType("Hades4Passable")) && (trGetTerrainSubType(xsVectorGetX(kbGetBlockPosition(""+j)/2),xsVectorGetZ(kbGetBlockPosition(""+j)/2)) == getTerrainSubType("Hades4Passable"))){
					trChatSendToPlayer(0, kbUnitGetOwner(id), "<color=1,0.2,0>You cannot build on lava");
					trUnitSelectClear();
					trUnitSelectByID(id);
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
					}
					trUnitDestroy();
				}
				else{
					xAddDatabaseBlock(dBuildings, true);
					xSetInt(dBuildings, xUnitName, j);
					xSetInt(dBuildings, xPlayerOwner, kbUnitGetOwner(id));
				}
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
