int PlayerCycle = 1;
int ActionChoice = 0;
int ChoiceEffect = 0;
string YesChoiceUnitName = "Swordsman";
string NoChoiceUnitName = "Lancer";


const int RunnerRewardL1 = 4;
const int RunnerRewardL2 = 11;
const int RunnerRewardL3 = 18;


const int HunterRewardL1 = 3;
const int HunterRewardL2 = 14;
const int HunterRewardL3 = 26;

string RewardText(int r = 0){
	string reward = "error";
	switch(r){
		//RUNNER REWARD LEVEL 1, 4-13
		case 3:
		{
			reward = "Walls level " + (xGetInt(dPlayerData, xPlayerWallLevel)+1);
		}
		case 4:
		{
			reward = "+0.5 citizen speed";
		}
		case 5:
		{
			reward = "+1 tower range";
		}
		case 6:
		{
			reward = "+2 tower attack";
		}
		case 7:
		{
			reward = "+2 tower LOS";
		}
		case 8:
		{
			reward = "Vision";
		}
		case 9:
		{
			reward = "Towers build 10 percent faster";
		}
		case 10:
		{
			reward = "+100 citizen hp";
		}
		//NEXT LEVEL
		case 11:
		{
			reward = "+250 citizen hp";
		}
		case 12:
		{
			reward = "+1 citizen speed";
		}
		case 13:
		{
			reward = "+2 tower range";
		}
		case 14:
		{
			reward = "+4 tower attack";
		}
		case 15:
		{
			reward = "+4 tower LOS";
		}
		case 16:
		{
			reward = "Vision";
		}
		case 17:
		{
			reward = "Lightning storm";
		}
		case 18:
		{
			reward = "Pegasus";
		}
	}
	return(reward);
}

string RewardTextHunter(int r = 0){
	string reward = "error";
	switch(r){
		//RUNNER REWARD LEVEL 1, 4-13
		case 3:
		{
			reward = "Temple timeshift 10 percent faster";
		}
		case 4:
		{
			reward = "+4 Temple LOS";
		}
		case 5:
		{
			reward = "+2 " + handunit + " LOS";
		}
		case 6:
		{
			reward = "+5 " + handunit + " crush attack";
		}
		case 7:
		{
			reward = "+4 " + rangedunit + " LOS";
		}
		case 8:
		{
			reward = "+5 " + rangedunit + " crush attack";
		}
		case 9:
		{
			if(rangedunit == "Mountain Giant"){
				reward = "+1 " + rangedunit + " speed";
			}
			else{
				reward = "+4 " + rangedunit + " range";
			}
		}
		case 10:
		{
			reward = "+0.5 " + handunit + " speed";
		}
		case 11:
		{
			reward = "+0.5 " + rangedunit + " speed";
		}
		case 12:
		{
			reward = ""+MapFactor() + "x Undermine power";
		}
		case 13:
		{
			reward = ""+MapFactor() + "x Vision power";
		}
		//LEVEL 2 REWARDS
		case 14:
		{
			reward = "Temple timeshift 25 percent faster";
		}
		case 15:
		{
			reward = "+6 Temple LOS";
		}
		case 16:
		{
			reward = "+5 " + handunit + " LOS";
		}
		case 17:
		{
			reward = "+15 " + handunit + " crush attack";
		}
		case 18:
		{
			reward = "+6 " + rangedunit + " LOS";
		}
		case 19:
		{
			reward = "+10 " + rangedunit + " crush attack";
		}
		case 20:
		{
			reward = "+4 " + rangedunit + " range";
		}
		case 21:
		{
			reward = "+1 " + handunit + " speed";
		}
		case 22:
		{
			reward = "+1 " + rangedunit + " speed";
		}
		case 23:
		{
			reward = ""+MapFactor() + "x Earthquake power";
		}
		case 24:
		{
			reward = ""+MapFactor() + "x Meteor power";
		}
		case 25:
		{
			reward = "+200 " + rangedunit + " hp";
		}
		case 26:
		{
			reward = "+400 " + handunit + " hp";
		}
	}
	return(reward);
}

int PlayerChoice(int p = 0, string prompt = "Question", string answerone = "Answer 1", int effectone = 0, string answertwo = "Answer 2", int effecttwo = 0){
	int temp = 0;
	//Check choice units alive
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"Yes")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
		debugLog("Choice selector dead");
	}
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"No")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"No", temp);
		debugLog("Choice selector dead");
	}
	trUnitSelectByQV("P"+p+"No");
	trUnitChangeProtoUnit(""+NoChoiceUnitName);
	trUnitSelectByQV("P"+p+"No");
	trSetSelectedScale(0,0,0);
	trUnitSelectByQV("P"+p+"Yes");
	trUnitChangeProtoUnit(""+YesChoiceUnitName);
	trUnitSelectByQV("P"+p+"Yes");
	trSetSelectedScale(0,0,0);
	trQuestVarSet("P"+p+"YesAction", effectone);
	trQuestVarSet("P"+p+"NoAction", effecttwo);
	if(trCurrentPlayer() == p){
		trShowChoiceDialog(prompt, answerone, p, answertwo, p+12);
		//camera
	}
	return(p);
}

void ChooseYes(int p = 0){
	if(trCurrentPlayer() == p){
		trackInsert();
		trackAddWaypoint();
		trackPlay(10,EVENT_REMOVE_CAM_TRACKS);
		trUnitSelectClear();
		uiFindType(""+YesChoiceUnitName);
		uiTransformSelectedUnit(""+YesChoiceUnitName + " Hero");
	}
}

void ChooseNo(int p = 0){
	p = p-12;
	if(trCurrentPlayer() == p){
		trackInsert();
		trackAddWaypoint();
		trackPlay(10,EVENT_REMOVE_CAM_TRACKS);
		trUnitSelectClear();
		uiFindType(""+NoChoiceUnitName);
		uiTransformSelectedUnit(""+NoChoiceUnitName + " Hero");
	}
}

rule DetectAnswers
highFrequency
active
{
	//Process saving, one player each trigger loop detected
	PlayerCycle = PlayerCycle+1;
	if(PlayerCycle > cNumberNonGaiaPlayers){
		PlayerCycle = 1;
	}
	int p = PlayerCycle;
	xSetPointer(dPlayerData, p);
	if(trPlayerUnitCountSpecific(p, ""+YesChoiceUnitName + " Hero") != 0){
		ChoiceEffect = 1*trQuestVarGet("P"+p+"YesAction");
		ActionChoice = p;
		if(xGetBool(dPlayerData, xPlayerRunner)){
			xsEnableRule("AnswerConsequences");
		}
		else{
			xsEnableRule("HunterConsequences");
		}
		trUnitSelectByQV("P"+p+"No");
		trUnitChangeProtoUnit("Cinematic Block");
		trUnitSelectByQV("P"+p+"Yes");
		trUnitChangeProtoUnit("Cinematic Block");
	}
	if(trPlayerUnitCountSpecific(p, ""+NoChoiceUnitName + " Hero") != 0){
		ChoiceEffect = 1*trQuestVarGet("P"+p+"NoAction");
		ActionChoice = p;
		if(xGetBool(dPlayerData, xPlayerRunner)){
			xsEnableRule("AnswerConsequences");
		}
		else{
			xsEnableRule("HunterConsequences");
		}
		trUnitSelectByQV("P"+p+"No");
		trUnitChangeProtoUnit("Cinematic Block");
		trUnitSelectByQV("P"+p+"Yes");
		trUnitChangeProtoUnit("Cinematic Block");
	}
}

rule AnswerConsequences
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	//[REMEMBER THIS IS OPEN AND MAY NEED PLAYER SPECIFIC TAG]
	if(ActionChoice != 0){
		int p = ActionChoice;
		xSetPointer(dPlayerData, p);
		switch(ChoiceEffect)
		{
			case 0:
			{
				debugLog("NO CONSEQUENCE SET");
			}
			case 1:
			{
				AllowHunterChoice = false;
				trMessageSetText("The host is now choosing hunter settings", 1);
				trCounterAbort("cdchoice");
				xsDisableRule("HuntersTimeout");
				PregameTimeout = 999999;
				xsEnableRule("ChooseHuntersRandom");
			}
			case 2:
			{
				AllowHunterChoice = true;
				trMessageSetText("The host is now choosing hunter settings", 1);
				trCounterAbort("cdchoice");
				xsDisableRule("HuntersTimeout");
				PregameTimeout = 999999;
				xsEnableRule("BeginChooseHunters");
			}
			case 3:
			{
				if(xGetInt(dPlayerData, xPlayerWallLevel) == 1){
					trTechSetStatus(p, 127, 4);
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
				}
				else if(xGetInt(dPlayerData, xPlayerWallLevel) == 2){
					trTechSetStatus(p, 411, 4);
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
					trModifyProtounit("Wall Connector", p, 0, 1000);
					trModifyProtounit("Wall Short", p, 0, 1000);
					trModifyProtounit("Wall Medium", p, 0, 1000);
					trModifyProtounit("Wall Long", p, 0, 1000);
					trModifyProtounit("Gate", p, 0, 1000);
				}
				else if(xGetInt(dPlayerData, xPlayerWallLevel) == 3){
					trTechSetStatus(p, 412, 4);
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
					trModifyProtounit("Wall Connector", p, 0, 2500);
					trModifyProtounit("Wall Short", p, 0, 2500);
					trModifyProtounit("Wall Medium", p, 0, 2500);
					trModifyProtounit("Wall Long", p, 0, 2500);
					trModifyProtounit("Gate", p, 0, 2500);
				}
				else if(xGetInt(dPlayerData, xPlayerWallLevel) == 4){
					trTechSetStatus(p, 413, 4);
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
					trModifyProtounit("Wall Connector", p, 0, 5000);
					trModifyProtounit("Wall Short", p, 0, 5000);
					trModifyProtounit("Wall Medium", p, 0, 5000);
					trModifyProtounit("Wall Long", p, 0, 5000);
					trModifyProtounit("Gate", p, 0, 5000);
				}
				/*trUnitSelectClear();
				trUnitSelectByID(0);
				trUnitChangeInArea(p,p, "Tower", "Titan Atlantean", MapSize);
				trUnitSelectClear();
				trUnitSelectByID(0);
				trUnitChangeInArea(p,p, "Titan Atlantean", "Tower", MapSize);
				unitTransform("Titan Gate Dead", "Tower");*/
			}
			case 4:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 1, 0.5);
			}
			case 5:
			{
				trModifyProtounit("Tower", p, 11, 1);
			}
			case 6:
			{
				trModifyProtounit("Tower", p, 31, 2);
			}
			case 7:
			{
				trModifyProtounit("Tower", p, 2, 2);
			}
			case 8:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
			}
			case 9:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.9);
				modifyProtounitAbsolute("Tower", p, 4, xGetFloat(dPlayerData, xTowerBuild));
			}
			case 10:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 100);
			}
			//NEXT LEVEL
			case 11:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 250);
			}
			case 12:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 1, 1);
			}
			case 13:
			{
				trModifyProtounit("Tower", p, 11, 2);
			}
			case 14:
			{
				trModifyProtounit("Tower", p, 31, 4);
			}
			case 15:
			{
				trModifyProtounit("Tower", p, 2, 4);
			}
			case 16:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
			}
			case 17:
			{
				grantGodPowerNoRechargeNextPosition(p, "Lightning Storm", 1);
			}
			case 18:
			{
				UnitCreate(p, "Pegasus", xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID))),xsVectorGetX(kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID))));
			}
		}
		trQuestVarSet("P"+ActionChoice+"YesAction", 0);
		trQuestVarSet("P"+ActionChoice+"NoAction", 0);
		ActionChoice = 0;
		//Safety
		unitTransform(""+YesChoiceUnitName + " Hero", "Cinematic Block");
		unitTransform(""+NoChoiceUnitName + " Hero", "Cinematic Block");
		if(xGetBool(dPlayerData, xPlayerRunner) == true){
			uiZoomToProto("Villager Atlantean Hero");
		}
		xsDisableSelf();
	}
}

rule HunterConsequences
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	//[REMEMBER THIS IS OPEN AND MAY NEED PLAYER SPECIFIC TAG]
	if(ActionChoice != 0){
		int p = ActionChoice;
		xSetPointer(dPlayerData, p);
		switch(ChoiceEffect)
		{
			case 0:
			{
				debugLog("NO CONSEQUENCE SET");
			}
			case 1:
			{
				//reserved
			}
			case 2:
			{
				//reserved
			}
			case 3:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.9);
				modifyProtounitAbsolute("Temple", p, 4, xGetFloat(dPlayerData, xTowerBuild));
			}
			case 4:
			{
				trModifyProtounit("Temple", p, 2, 4);
			}
			case 5:
			{
				trModifyProtounit(handunit, p, 2, 2);
			}
			case 6:
			{
				trModifyProtounit(handunit, p, 29, 5);
			}
			case 7:
			{
				trModifyProtounit(rangedunit, p, 2, 2);
			}
			case 8:
			{
				trModifyProtounit(rangedunit, p, 32, 5);
			}
			case 9:
			{
				if(rangedunit == "Mountain Giant"){
					trModifyProtounit(rangedunit, p, 1, 1);
				}
				else{
					trModifyProtounit(rangedunit, p, 11, 4);
				}
			}
			case 10:
			{
				trModifyProtounit(handunit, p, 1, 0.5);
			}
			case 11:
			{
				trModifyProtounit(rangedunit, p, 1, 0.5);
			}
			case 12:
			{
				grantGodPowerNoRechargeNextPosition(p, "Undermine", MapFactor());
			}
			case 13:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", MapFactor());
			}
			//TIER 2 HUNTER
			case 14:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.75);
				modifyProtounitAbsolute("Temple", p, 4, xGetFloat(dPlayerData, xTowerBuild));
			}
			case 15:
			{
				trModifyProtounit("Temple", p, 2, 6);
			}
			case 16:
			{
				trModifyProtounit(handunit, p, 2, 5);
			}
			case 17:
			{
				trModifyProtounit(handunit, p, 29, 15);
			}
			case 18:
			{
				trModifyProtounit(rangedunit, p, 2, 6);
			}
			case 19:
			{
				trModifyProtounit(rangedunit, p, 32, 10);
			}
			case 20:
			{
				trModifyProtounit(rangedunit, p, 11, 4);
			}
			case 21:
			{
				trModifyProtounit(handunit, p, 1, 1);
			}
			case 22:
			{
				trModifyProtounit(rangedunit, p, 1, 1);
			}
			case 23:
			{
				grantGodPowerNoRechargeNextPosition(p, "Earthquake", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 24:
			{
				grantGodPowerNoRechargeNextPosition(p, "Meteor", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 25:
			{
				trModifyProtounit(rangedunit, p, 0, 200);
			}
			case 26:
			{
				trModifyProtounit(handunit, p, 0, 400);
			}
		}
		trQuestVarSet("P"+ActionChoice+"YesAction", 0);
		trQuestVarSet("P"+ActionChoice+"NoAction", 0);
		ActionChoice = 0;
		//Safety
		unitTransform(""+YesChoiceUnitName + " Hero", "Cinematic Block");
		unitTransform(""+NoChoiceUnitName + " Hero", "Cinematic Block");
		//camera required
		xsDisableSelf();
	}
}

rule SetupChoiceUnits
highFrequency
inactive
{
	xsDisableSelf();
	int temp = 0;
	for(p=1 ; <= cNumberNonGaiaPlayers){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 3, 0);
		trQuestVarSet("P"+p+"No", temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, MapSize-1, 0);
		trQuestVarSet("P"+p+"Space", temp);
	}
}

//[TIMEOUT]
//gadgetUnreal("ShowChoiceBox");

