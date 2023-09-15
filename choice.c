int PlayerCycle = 1;
int ActionChoice = 0;
int ChoiceEffect = 0;
string YesChoiceUnitName = "Swordsman";
string NoChoiceUnitName = "Lancer";


const int RunnerRewardL1 = 4;
const int RunnerRewardL2 = 10;

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
	if(trPlayerUnitCountSpecific(p, ""+YesChoiceUnitName + " Hero") != 0){
		ChoiceEffect = 1*trQuestVarGet("P"+p+"YesAction");
		ActionChoice = p;
		xsEnableRule("AnswerConsequences");
		trUnitSelectByQV("P"+p+"No");
		trUnitChangeProtoUnit("Cinematic Block");
		trUnitSelectByQV("P"+p+"Yes");
		trUnitChangeProtoUnit("Cinematic Block");
	}
	if(trPlayerUnitCountSpecific(p, ""+NoChoiceUnitName + " Hero") != 0){
		ChoiceEffect = 1*trQuestVarGet("P"+p+"NoAction");
		ActionChoice = p;
		xsEnableRule("AnswerConsequences");
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
			}
			case 10:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 100);
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

