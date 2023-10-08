rule Help_Chat
inactive
highFrequency
{
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(trCurrentPlayer() == p){
			if((trChatHistoryContains("HELP", p)) || (trChatHistoryContains("what does", p)) || (trChatHistoryContains("power", p))){
				trChatHistoryClear();
				//POWER HELP
				for(x=0; < 4) {
					if(trGetGPData(p,0,x) == 84){
						ColouredIconChat("1,0.5,0", "icons\god power create gold icon 64", " - Create Wall");
						trChatSend(0, "<color=1,1,1>Creates a 30 second impassable cliff");
					}
					if(trGetGPData(p,0,x) == 463){
						ColouredIconChat("1,0.5,0", "icons\god power curse icon 64", " - Mythic Curse");
						trChatSend(0, "<color=1,1,1>Instantly kills a small number of myth units");
					}
					if(trGetGPData(p,0,x) == 134){
						ColouredIconChat("1,0.5,0", "icons\god power restoration icon 64", " - Invulnerability");
						trChatSend(0, "<color=1,1,1>For 8 seconds most attacks do no damage and everything healed");
					}
					if(trGetGPData(p,0,x) == 156){
						ColouredIconChat("1,0.5,0", "icons\god power rain icon 64", " - Tower reshuffle");
						trChatSend(0, "<color=1,1,1>Your towers turn into birds for 10 seconds, and then back to towers");
						trChatSend(0, "<color=1,0,0><u>WARNING:</u><color=1,1,1>This will leave you with no towers for 10 seconds!");
					}
					if(trGetGPData(p,0,x) == 419){
						ColouredIconChat("1,0.5,0", "icons\god power tartarian gate icons 64", " - Volcano");
						trChatSend(0, "<color=1,1,1>Spews lava that lasts for one minute and cannot be built on");
					}
				}
			}
			if(trChatHistoryContains("Upgrade", p)){
				trChatHistoryClear();
				trChatSend(0, "<color=1,1,1>Kill enemy units to win upgrades");
			}
		}
	}
}
