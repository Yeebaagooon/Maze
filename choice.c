int PlayerCycle = 1;
int ActionChoice = 0;
int ChoiceEffect = 0;
string YesChoiceUnitName = "Swordsman";
string NoChoiceUnitName = "Lancer";

void SoundSet(string sound = "cantdothat.wav"){
	if(trCurrentPlayer() == xGetPointer(dPlayerData)){
		playSound(sound);
	}
}

const int RunnerRewardL1 = 4;
const int RunnerRewardL2 = 11;
const int RunnerRewardL3 = 19;
const int RunnerRewardL4 = 24;
const int RunnerRewardL5 = 34;
const int RunnerRewardL6 = 38;
const int RunnerRewardL7 = 43;
const int RunnerRewardL8 = 45;
const int RunnerRewardL9 = 49;
const int RunnerRewardL10 = 53;

string RewardText(int r = 0){
	string reward = "You waited too long";
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
			reward = "+1 tower range and LOS";
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
			reward = "+200 citizen hp";
		}
		case 12:
		{
			reward = "+0.75 citizen speed";
		}
		case 13:
		{
			reward = "+2 tower range and LOS";
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
			reward = "Barrage";
		}
		case 18:
		{
			reward = "Pegasus";
		}
		//NEXT LEVEL
		case 19:
		{
			reward = "+100 tower hp";
		}
		case 20:
		{
			reward = "Temporary invulnerability power";
		}
		case 21:
		{
			reward = "+300 citizen hp";
		}
		case 22:
		{
			reward = "Great Journey power (walk over cliff)";
		}
		case 23:
		{
			if(AutoEscape){
				reward = "Mythic Curse power";
			}
			else{
				reward = "Flare current hunter temple positions";
			}
		}
		//NEXT LEVEL
		case 24:
		{
			reward = "+150 tower hp";
		}
		case 25:
		{
			reward = "+300 citizen hp";
		}
		case 26:
		{
			reward = "Mythic Curse power";
		}
		case 27:
		{
			reward = "Temporary Wall power";
		}
		case 28:
		{
			reward = "Vision";
		}
		case 29:
		{
			reward = "Lightning Storm power";
		}
		case 30:
		{
			reward = "+2 tower range and LOS";
		}
		case 31:
		{
			reward = "+4 tower attack";
		}
		case 32:
		{
			reward = "+4 tower LOS";
		}
		case 33:
		{
			reward = "Towers build 15 percent faster";
		}
		//NEXT LEVEL
		//Huskarl to reveal map layout
		case 34:
		{
			reward = "Reveal maze layout";
		}
		case 35:
		{
			reward = "+2 hp/s citizen regen";
		}
		case 36:
		{
			reward = "+12 citizen LOS";
		}
		case 37:
		{
			reward = "+1 citizen speed";
		}
		//NEXT LEVEL
		case 38:
		{
			reward = "+4 tower range and LOS";
		}
		case 39:
		{
			reward = "+5 tower attack";
		}
		case 40:
		{
			reward = "+6 tower LOS";
		}
		case 41:
		{
			reward = "+250 tower hp";
		}
		case 42:
		{
			reward = "Towers build 20 percent faster";
		}
		//NEXT LEVEL
		case 43:
		{
			reward = "Secondary citizen";
		}
		case 44:
		{
			reward = "+500 tower hp";
		}
		//NEXT LEVEL
		case 45:
		{
			reward = "2x Lightning Storm power";
		}
		case 46:
		{
			reward = "2x Temporary Wall power";
		}
		case 47:
		{
			reward = "3x Vision";
		}
		case 48:
		{
			reward = "2x Temporary invulnerability power";
		}
		//Unique to highest level only
		case 49:
		{
			reward = "+2500 sky passage hp";
		}
		case 50:
		{
			reward = "+8 tower attack";
		}
		case 51:
		{
			reward = "+5 hp/s citizen regen";
		}
		case 52:
		{
			reward = "+1 tower projectile";
		}
		case 53:
		{
			if(AutoEscape){
				reward = "Flare nearest relic";
			}
			else{
				reward = "Death tower (5s recharge)";
			}
		}
	}
	return(reward);
}


const int HunterRewardL1 = 3;
const int HunterRewardL2 = 14;
const int HunterRewardL3 = 27;
const int HunterRewardL4 = 37;
const int HunterRewardL5 = 40;
const int HunterRewardL6 = 50;
const int HunterRewardL7 = 54;

string RewardTextHunter(int r = 0){
	string reward = "You waited too long";
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
			reward = ""+MapFactor() + "x Volcano power";
		}
		case 24:
		{
			reward = ""+MapFactor() + "x SPC Meteor power";
		}
		case 25:
		{
			reward = "+200 " + rangedunit + " hp";
		}
		case 26:
		{
			reward = "+400 " + handunit + " hp";
		}
		//Next Level
		case 27:
		{
			reward = "+250 " + rangedunit + " hp";
		}
		case 28:
		{
			reward = "+500 " + handunit + " hp";
		}
		case 29:
		{
			reward = "+1 " + handunit + " speed";
		}
		case 30:
		{
			reward = "+1 " + rangedunit + " speed";
		}
		case 31:
		{
			reward = "+20 " + handunit + " crush attack";
		}
		case 32:
		{
			reward = "Reveal maze layout";
		}
		case 33:
		{
			reward = "+15 " + rangedunit + " crush attack";
		}
		case 34:
		{
			reward = ""+MapFactor() + "x Volcano power";
		}
		case 35:
		{
			reward = ""+MapFactor() + "x Meteor power";
		}
		case 36:
		{
			reward = ""+MapFactor() + "x Tornado power";
		}
		//level up
		case 37:
		{
			reward = ""+MapFactor() + "x vision power";
		}
		case 38:
		{
			reward = "Flare current runner positions";
		}
		case 39:
		{
			reward = "Heka Gigantes unit (tower smash ability)";
		}
		case 40:
		{
			reward = "Temple timeshift 25 percent faster";
		}
		//level up
		case 41:
		{
			reward = "+300 " + rangedunit + " hp";
		}
		case 42:
		{
			reward = "+600 " + handunit + " hp";
		}
		case 43:
		{
			reward = "+1.5 " + handunit + " speed";
		}
		case 44:
		{
			reward = "+1.5 " + rangedunit + " speed";
		}
		case 45:
		{
			reward = "+30 " + handunit + " crush attack";
		}
		case 46:
		{
			reward = "+20 " + rangedunit + " crush attack";
		}
		case 47:
		{
			reward = ""+MapFactor() + "x Volcano power";
		}
		case 48:
		{
			reward = ""+MapFactor() + "x Meteor power";
		}
		case 49:
		{
			reward = "Raven scout unit (10,000 hp)";
		}
		//Next level
		case 50:
		{
			reward = ""+MapFactor() + "x Earthquake power";
		}
		case 51:
		{
			reward = "3x Lampades";
		}
		case 52:
		{
			reward = "3x Manticore";
		}
		case 53:
		{
			reward = "3x Phoenix";
		}
		case 54:
		{
			reward = "Guardian";
		}
		
	}
	return(reward);
}

int PlayerChoice(int p = 0, string prompt = "Question", string answerone = "Answer 1", int effectone = 0, string answertwo = "Answer 2", int effecttwo = 0){
	int temp = 0;
	//Check choice units alive
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"Yes")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreateChange(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
	}
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"No")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreateChange(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"No", temp);
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

void UpgradeTest(int p = 1, int x = 0, bool Hunter = false){
	ActionChoice = p;
	ChoiceEffect = x;
	if(Hunter){
		xsEnableRule("HunterConsequences");
	}
	else{
		xsEnableRule("AnswerConsequences");
	}
}

rule AnswerConsequences
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	//[REMEMBER THIS IS OPEN AND MAY NEED PLAYER SPECIFIC TAG]
	if(ActionChoice != 0){
		int id = 0;
		int p = ActionChoice;
		xSetPointer(dPlayerData, p);
		trQuestVarSet("qv", 0);
		switch(ChoiceEffect)
		{
			case 0:
			{
				//debugLog("NO CONSEQUENCE SET");
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
					trModifyProtounit("Wall Connector", p, 0, 1100);
					trModifyProtounit("Wall Short", p, 0, 1100);
					trModifyProtounit("Wall Medium", p, 0, 1100);
					trModifyProtounit("Wall Long", p, 0, 1100);
					trModifyProtounit("Gate", p, 0, 1200);
					trModifyProtounit("Wall Connector", p, 26, 0.05);
					trModifyProtounit("Wall Short", p, 26, 0.05);
					trModifyProtounit("Wall Medium", p, 26, 0.05);
					trModifyProtounit("Wall Long", p, 26, 0.05);
					trModifyProtounit("Gate", p, 26, 0.05);
				}
				else if(xGetInt(dPlayerData, xPlayerWallLevel) == 3){
					trTechSetStatus(p, 412, 4);
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
					trModifyProtounit("Wall Connector", p, 0, 2500);
					trModifyProtounit("Wall Short", p, 0, 2500);
					trModifyProtounit("Wall Medium", p, 0, 2500);
					trModifyProtounit("Wall Long", p, 0, 2500);
					trModifyProtounit("Gate", p, 0, 2500);
					trModifyProtounit("Wall Connector", p, 26, 0.05);
					trModifyProtounit("Wall Short", p, 26, 0.05);
					trModifyProtounit("Wall Medium", p, 26, 0.05);
					trModifyProtounit("Wall Long", p, 26, 0.05);
					trModifyProtounit("Gate", p, 26, 0.05);
				}
				else if(xGetInt(dPlayerData, xPlayerWallLevel) == 4){
					trTechSetStatus(p, 413, 4);
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
					trModifyProtounit("Wall Connector", p, 0, 5000);
					trModifyProtounit("Wall Short", p, 0, 5000);
					trModifyProtounit("Wall Medium", p, 0, 5000);
					trModifyProtounit("Wall Long", p, 0, 5000);
					trModifyProtounit("Gate", p, 0, 5000);
					trModifyProtounit("Wall Connector", p, 26, 0.05);
					trModifyProtounit("Wall Short", p, 26, 0.05);
					trModifyProtounit("Wall Medium", p, 26, 0.05);
					trModifyProtounit("Wall Long", p, 26, 0.05);
					trModifyProtounit("Gate", p, 26, 0.05);
				}
				else if(xGetInt(dPlayerData, xPlayerWallLevel) == 5){
					//atlantis
					xSetInt(dPlayerData, xPlayerWallLevel, xGetInt(dPlayerData, xPlayerWallLevel)+1);
					trModifyProtounit("Wall Connector", p, 0, 10000);
					trModifyProtounit("Wall Short", p, 0, 10000);
					trModifyProtounit("Wall Medium", p, 0, 10000);
					trModifyProtounit("Wall Long", p, 0, 10000);
					trModifyProtounit("Gate", p, 0, 10000);
					trModifyProtounit("Wall Connector", p, 26, 0.05);
					trModifyProtounit("Wall Short", p, 26, 0.05);
					trModifyProtounit("Wall Medium", p, 26, 0.05);
					trModifyProtounit("Wall Long", p, 26, 0.05);
					trModifyProtounit("Gate", p, 26, 0.05);
				}
				/*trUnitSelectClear();
				trUnitSelectByID(0);
				trUnitChangeInArea(p,p, "Tower", "Titan Atlantean", MapSize);
				trUnitSelectClear();
				trUnitSelectByID(0);
				trUnitChangeInArea(p,p, "Titan Atlantean", "Tower", MapSize);
				unitTransform("Titan Gate Dead", "Tower");*/
				SoundSet("wall.wav");
			}
			case 4:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 1, 0.5);
				trModifyProtounit("Villager Atlantean", p, 1, 0.5);
				SoundSet("researchcomplete.wav");
			}
			case 5:
			{
				trModifyProtounit("Tower", p, 11, 1);
				trModifyProtounit("Tower", p, 2, 1);
				SoundSet("researchcomplete.wav");
			}
			case 6:
			{
				trModifyProtounit("Tower", p, 31, 2);
				SoundSet("researchcomplete.wav");
			}
			case 7:
			{
				trModifyProtounit("Tower", p, 2, 2);
				SoundSet("researchcomplete.wav");
			}
			case 8:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 9:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.9);
				modifyProtounitAbsolute("Tower", p, 4, xGetFloat(dPlayerData, xTowerBuild));
				SoundSet("researchcomplete.wav");
			}
			case 10:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 100);
				trModifyProtounit("Villager Atlantean", p, 0, 100);
				SoundSet("researchcomplete.wav");
			}
			//NEXT LEVEL
			case 11:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 200);
				trModifyProtounit("Villager Atlantean", p, 0, 200);
				SoundSet("researchcomplete.wav");
			}
			case 12:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 1, 0.75);
				trModifyProtounit("Villager Atlantean" , p, 1, 0.75);
				SoundSet("researchcomplete.wav");
			}
			case 13:
			{
				trModifyProtounit("Tower", p, 11, 2);
				trModifyProtounit("Tower", p, 2, 2);
				SoundSet("researchcomplete.wav");
			}
			case 14:
			{
				trModifyProtounit("Tower", p, 31, 4);
				SoundSet("researchcomplete.wav");
			}
			case 15:
			{
				trModifyProtounit("Tower", p, 2, 4);
				SoundSet("researchcomplete.wav");
			}
			case 16:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 17:
			{
				grantGodPowerNoRechargeNextPosition(p, "Barrage", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 18:
			{
				xSetPointer(dPlayerData, p);
				id = yFindLatest("qv", "Villager Atlantean Hero", p);
				UnitCreateChange(p, "Pegasus", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
				SoundSet("pegasusselect1.wav");
			}
			case 19:
			{
				trModifyProtounit("Tower", p, 0, 100);
				SoundSet("researchcomplete.wav");
			}
			case 20:
			{
				grantGodPowerNoRechargeNextPosition(p, "Restoration", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 21:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 300);
				trModifyProtounit("Villager Atlantean", p, 0, 300);
				SoundSet("researchcomplete.wav");
			}
			case 22:
			{
				grantGodPowerNoRechargeNextPosition(p, "Journey", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 23:
			{
				if(AutoEscape){
					grantGodPowerNoRechargeNextPosition(p, "Change Chimera", 1);
					SoundSet("\cinematics\17_in\weirdthing.mp3");
				}
				else{
					for(a = 1; <= HunterNumber){
						trMinimapFlare(p, 10.0, kbGetBlockPosition(""+1*trQuestVarGet("Temple"+a)), false);
					}
				}
			}
			case 24:
			{
				trModifyProtounit("Tower", p, 0, 150);
				SoundSet("researchcomplete.wav");
			}
			case 25:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 0, 300);
				trModifyProtounit("Villager Atlantean", p, 0, 300);
				SoundSet("researchcomplete.wav");
			}
			case 26:
			{
				grantGodPowerNoRechargeNextPosition(p, "Change Chimera", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 27:
			{
				grantGodPowerNoRechargeNextPosition(p, "create gold", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 28:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 29:
			{
				grantGodPowerNoRechargeNextPosition(p, "Lightning Storm", 1);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 30:
			{
				trModifyProtounit("Tower", p, 11, 2);
				trModifyProtounit("Tower", p, 2, 2);
				SoundSet("researchcomplete.wav");
			}
			case 31:
			{
				trModifyProtounit("Tower", p, 31, 4);
				SoundSet("researchcomplete.wav");
			}
			case 32:
			{
				trModifyProtounit("Tower", p, 2, 4);
				SoundSet("researchcomplete.wav");
			}
			case 33:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.85);
				modifyProtounitAbsolute("Tower", p, 4, xGetFloat(dPlayerData, xTowerBuild));
				SoundSet("researchcomplete.wav");
			}
			case 34:
			{
				xSetPointer(dPlayerData, p);
				yFindLatest("qv", "Villager Atlantean Hero", p);
				id = UnitCreateChange(p, "Revealer To Player", MapSize/2,MapSize/2);
				xAddDatabaseBlock(dDestroyMe, true);
				xSetInt(dDestroyMe, xDestroyName, id);
				xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+2000);
				trModifyProtounit("Revealer To Player",p,2,MapSize);
				SoundSet("visionswoosh.wav");
			}
			case 35:
			{
				xSetFloat(dPlayerData,xCitizenRegen,xGetFloat(dPlayerData, xCitizenRegen)+2.0);
				SoundSet("researchcomplete.wav");
			}
			case 36:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 2, 12);
				trModifyProtounit("Villager Atlantean", p, 2, 12);
				SoundSet("researchcomplete.wav");
			}
			case 37:
			{
				trModifyProtounit("Villager Atlantean Hero", p, 1, 1);
				trModifyProtounit("Villager Atlantean", p, 1, 1);
				SoundSet("researchcomplete.wav");
			}
			//NEXT LEVEL
			case 38:
			{
				trModifyProtounit("Tower", p, 11, 4);
				trModifyProtounit("Tower", p, 2, 4);
				SoundSet("researchcomplete.wav");
			}
			case 39:
			{
				trModifyProtounit("Tower", p, 31, 5);
				SoundSet("researchcomplete.wav");
			}
			case 40:
			{
				trModifyProtounit("Tower", p, 2, 6);
				SoundSet("researchcomplete.wav");
			}
			case 41:
			{
				trModifyProtounit("Tower", p, 0, 250);
				SoundSet("researchcomplete.wav");
			}
			case 42:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.8);
				modifyProtounitAbsolute("Tower", p, 4, xGetFloat(dPlayerData, xTowerBuild));
				SoundSet("researchcomplete.wav");
			}
			//NEXT LEVEL
			case 43:
			{
				xSetPointer(dPlayerData, p);
				yFindLatest("qv", "Villager Atlantean Hero", p);
				id = 1*trQuestVarGet("qv");
				UnitCreateChange(p, "Villager Atlantean", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
				SoundSet("villagercreate.wav");
			}
			case 44:
			{
				trModifyProtounit("Tower", p, 0, 500);
				SoundSet("researchcomplete.wav");
			}
			//NEXT LEVEL
			case 45:
			{
				grantGodPowerNoRechargeNextPosition(p, "Lightning Storm", 2);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 46:
			{
				grantGodPowerNoRechargeNextPosition(p, "create gold", 2);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 47:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", 3);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 48:
			{
				grantGodPowerNoRechargeNextPosition(p, "Restoration", 2);
				SoundSet("\cinematics\17_in\weirdthing.mp3");
			}
			case 49:
			{
				trModifyProtounit("Sky Passage", p, 0, 2500);
				SoundSet("researchcomplete.wav");
			}
			case 50:
			{
				trModifyProtounit("Tower", p, 28, 8);
				SoundSet("researchcomplete.wav");
			}
			case 51:
			{
				xSetFloat(dPlayerData,xCitizenRegen,xGetFloat(dPlayerData, xCitizenRegen)+5.0);
				SoundSet("researchcomplete.wav");
			}
			case 52:
			{
				trModifyProtounit("Tower", p, 13, 1);
				SoundSet("researchcomplete.wav");
			}
			case 53:
			{
				if(AutoEscape){
					if(xGetDatabaseCount(dRelicTypes) == 0){
						trChatSendToPlayer(0, p, "<color=1,0.5,0>No more relics remain!");
					}
					else{
						xSetPointer(dPlayerData, p);
						float dist = 0.0;
						float closest = 100000.0;
						int closestint = 0;
						for(a = xGetDatabaseCount(dRelics); > 0){
							xDatabaseNext(dRelics);
							trUnitSelectClear();
							xUnitSelect(dRelics, xRelicID);
							dist = trUnitDistanceToUnit(""+xGetInt(dPlayerData, xPlayerUnitID));
							if(dist < closest){
								closest = dist;
								closestint = xGetInt(dRelics, xRelicID);
							}
						}
						trMinimapFlare(p, 20, kbGetBlockPosition(""+closestint) , false);
					}
				}
				else{
					xSetPointer(dPlayerData, p);
					yFindLatest("qv", "Villager Atlantean Hero", p);
					id = UnitCreateChange(p, "Tower Mirror", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					trUnitSelectClear();
					trUnitSelectByQV("qv");
					trImmediateUnitGarrison(""+id);
					trUnitSelectClear();
					trUnitSelect(""+id);
					trUnitChangeProtoUnit("Tower Mirror");
					SoundSet("mirrortower.wav");
				}
			}
		}
		trQuestVarSet("P"+ActionChoice+"YesAction", 0);
		trQuestVarSet("P"+ActionChoice+"NoAction", 0);
		ActionChoice = 0;
		//Safety
		unitTransform(""+YesChoiceUnitName + " Hero", "Cinematic Block");
		unitTransform(""+NoChoiceUnitName + " Hero", "Cinematic Block");
		if(trCurrentPlayer() == p){
			if(xGetBool(dPlayerData, xPlayerRunner) == true){
				uiZoomToProto("Villager Atlantean Hero");
			}
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
		int id = 0;
		int p = ActionChoice;
		xSetPointer(dPlayerData, p);
		int temp = 0;
		trQuestVarSet("qv", 0);
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
				grantGodPowerNoRechargeNextPosition(p, "Tartarian Gate", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 24:
			{
				grantGodPowerNoRechargeNextPosition(p, "SPCMeteor", MapFactor());
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
			case 27:
			{
				trModifyProtounit(rangedunit, p, 0, 250);
			}
			case 28:
			{
				trModifyProtounit(handunit, p, 0, 500);
			}
			case 29:
			{
				trModifyProtounit(handunit, p, 1, 1);
			}
			case 30:
			{
				trModifyProtounit(rangedunit, p, 1, 1);
			}
			case 31:
			{
				trModifyProtounit(handunit, p, 29, 20);
			}
			case 32:
			{
				id = UnitCreateChange(p, "Revealer To Player", MapSize/2,MapSize/2);
				xAddDatabaseBlock(dDestroyMe, true);
				xSetInt(dDestroyMe, xDestroyName, id);
				xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+2000);
				trModifyProtounit("Revealer To Player",p,2,MapSize);
			}
			case 33:
			{
				trModifyProtounit(handunit, p, 32, 15);
			}
			case 34:
			{
				grantGodPowerNoRechargeNextPosition(p, "Tartarian Gate", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 35:
			{
				grantGodPowerNoRechargeNextPosition(p, "Meteor", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 36:
			{
				grantGodPowerNoRechargeNextPosition(p, "Tornado", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 37:
			{
				grantGodPowerNoRechargeNextPosition(p, "Vision", MapFactor());
			}
			case 38:
			{
				if(AutoEscape == false){
					for(a = 1; <= cNumberNonGaiaPlayers){
						xSetPointer(dPlayerData, a);
						if(xGetBool(dPlayerData, xPlayerRunner)){
							trMinimapFlare(p, 10.0, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)), false);
						}
					}
				}
			}
			case 39:
			{
				if(AutoEscape){
					temp = UnitCreateChange(cNumberNonGaiaPlayers, "Heka Gigantes",(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, trTime()+30);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				else{
					temp = yFindLatest("qv", "Temple", p);
					UnitCreateChange(p, "Heka Gigantes", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					if(trCurrentPlayer() == p){
						trMinimapFlare(p, 5.0, kbGetBlockPosition(""+1*trQuestVarGet("qv")), false);
					}
				}
			}
			case 40:
			{
				xSetFloat(dPlayerData,xTowerBuild,xGetFloat(dPlayerData, xTowerBuild)*0.75);
				modifyProtounitAbsolute("Temple", p, 4, xGetFloat(dPlayerData, xTowerBuild));
			}
			case 41:
			{
				trModifyProtounit(rangedunit, p, 0, 300);
			}
			case 42:
			{
				trModifyProtounit(handunit, p, 0, 600);
			}
			case 43:
			{
				trModifyProtounit(handunit, p, 1, 1.5);
			}
			case 44:
			{
				trModifyProtounit(rangedunit, p, 1, 1.5);
			}
			case 45:
			{
				trModifyProtounit(handunit, p, 29, 30);
			}
			case 46:
			{
				trModifyProtounit(handunit, p, 32, 20);
			}
			case 47:
			{
				grantGodPowerNoRechargeNextPosition(p, "Tartarian Gate", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 48:
			{
				grantGodPowerNoRechargeNextPosition(p, "Meteor", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 49:
			{
				if(AutoEscape){
					temp = UnitCreateChange(cNumberNonGaiaPlayers, "Heka Gigantes",(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, trTime()+30);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				else{
					temp = yFindLatest("qv", "Temple", p);
					UnitCreateChange(p, "Raven", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					if(trCurrentPlayer() == p){
						trMinimapFlare(p, 5.0, kbGetBlockPosition(""+1*trQuestVarGet("qv")), false);
					}
				}
			}
			case 50:
			{
				grantGodPowerNoRechargeNextPosition(p, "Earthquake", MapFactor());
				if(AutoEscape){
					xsEnableRule("AI_Force_Power");
				}
			}
			case 51:
			{
				if(AutoEscape){
					temp = UnitCreateChange(cNumberNonGaiaPlayers, "Lampades",(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, trTime()+30);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				else{
					temp = yFindLatest("qv", "Temple", p);
					UnitCreateChange(p, "Lampades", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					UnitCreateChange(p, "Lampades", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					UnitCreateChange(p, "Lampades", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					if(trCurrentPlayer() == p){
						trMinimapFlare(p, 5.0, kbGetBlockPosition(""+1*trQuestVarGet("qv")), false);
					}
				}
			}
			case 52:
			{
				if(AutoEscape){
					temp = UnitCreateChange(cNumberNonGaiaPlayers, "Manticore",(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, trTime()+30);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				else{
					temp = yFindLatest("qv", "Temple", p);
					UnitCreateChange(p, "Manticore", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					UnitCreateChange(p, "Manticore", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					UnitCreateChange(p, "Manticore", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					if(trCurrentPlayer() == p){
						trMinimapFlare(p, 5.0, kbGetBlockPosition(""+1*trQuestVarGet("qv")), false);
					}
				}
			}
			case 53:
			{
				if(AutoEscape){
					temp = UnitCreateChange(cNumberNonGaiaPlayers, "Phoenix",(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, trTime()+30);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				else{
					temp = yFindLatest("qv", "Temple", p);
					UnitCreateChange(p, "Phoenix", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					UnitCreateChange(p, "Phoenix", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					UnitCreateChange(p, "Phoenix", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					if(trCurrentPlayer() == p){
						trMinimapFlare(p, 5.0, kbGetBlockPosition(""+1*trQuestVarGet("qv")), false);
					}
				}
			}
			case 54:
			{
				if(AutoEscape){
					temp = UnitCreateChange(cNumberNonGaiaPlayers, "Guardian XP",(MapSize/2)+5,(MapSize/2)+5);
					xAddDatabaseBlock(dEnemies, true);
					xSetInt(dEnemies, xUnitID, temp);
					xSetInt(dEnemies, xIdleTimeout, trTime()+30);
					trQuestVarSetFromRand("x", 0 , MapSize);
					trQuestVarSetFromRand("z", 0 , MapSize);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
				}
				else{
					temp = yFindLatest("qv", "Temple", p);
					UnitCreateChange(p, "Guardian XP", xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("qv"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("qv"))));
					if(trCurrentPlayer() == p){
						trMinimapFlare(p, 5.0, kbGetBlockPosition(""+1*trQuestVarGet("qv")), false);
					}
				}
			}
		}
		if(AutoEscape == false){
			SoundSet("researchcomplete.wav");
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
		UnitCreateChange(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreateChange(p, "Cinematic Block", p*3, 3, 0);
		trQuestVarSet("P"+p+"No", temp);
	}
}

//[TIMEOUT]
//gadgetUnreal("ShowChoiceBox");

