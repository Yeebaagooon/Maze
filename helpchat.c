rule Help_Chat
inactive
highFrequency
{
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(trCurrentPlayer() == p){
			if((trChatHistoryContains("HELP", p)) || (trChatHistoryContains("what does", p)) || (trChatHistoryContains("power do", p))){
				trChatHistoryClear();
				//POWER HELP
				for(x=0; < 4) {
					if(trGetGPData(p,0,x) == 84){
						if(trGetGPData(p,1,x) >0){
							ColouredIconChat("1,0.5,0", "icons\god power create gold icon 64", " - Create Wall");
							trChatSend(0, "<color=1,1,1>Creates a 30 second impassable cliff");
						}
					}
					if(trGetGPData(p,0,x) == 463){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power curse icon 64", " - Mythic Curse");
							trChatSend(0, "<color=1,1,1>Instantly kills a small number of myth units");
						}
					}
					if(trGetGPData(p,0,x) == 134){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power restoration icon 64", " - Invulnerability");
							trChatSend(0, "<color=1,1,1>For 8 seconds most attacks do no damage and everything healed");
						}
					}
					if(trGetGPData(p,0,x) == 156){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power rain icon 64", " - Tower reshuffle");
							trChatSend(0, "<color=1,1,1>Your towers turn into birds for 10 seconds, and then back to towers");
							trChatSend(0, "<color=1,0,0><u>WARNING:</u><color=1,1,1>This will leave you with no towers for 10 seconds!");
						}
					}
					if(trGetGPData(p,0,x) == 419){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power tartarian gate icons 64", " - Volcano");
							trChatSend(0, "<color=1,1,1>Spews lava that lasts for one minute and cannot be built on");
						}
					}
					if(trGetGPData(p,0,x) == 231){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power shifting sand icon 64", " - Sandy Towers");
							trChatSend(0, "<color=1,1,1>Creates 9 towers at each cast point");
						}
					}
					if(trGetGPData(p,0,x) == 388){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\animal chicken icon 64", " - Tower Spam");
							trChatSend(0, "<color=1,1,1>Creates a huge number of towers");
						}
					}
					if(trGetGPData(p,0,x) == 57){
						if(trGetGPData(p,1,x) >0){
							ColouredIconChat("1,0.5,0", "icons\god power frost icon 64", " - Frost");
							trChatSend(0, "<color=1,1,1>Deals 5000 damage in a large area");
						}
					}
					if(trGetGPData(p,0,x) == 442){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power implode icons 64", " - Void Sphere");
							trChatSend(0, "<color=1,1,1>Kills any enemy sucked in to the implode");
						}
					}
					if(trGetGPData(p,0,x) == 548){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power journey icon", " - Great Journey");
							trChatSend(0, "<color=1,1,1>Increases villager speed and allows them to walk on cliff");
						}
					}
					if(trGetGPData(p,0,x) == 61){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power meteor icon 64", " - Meteor");
							trChatSend(0, "<color=1,1,1>Does 700 damage per meteor");
						}
					}
					if(trGetGPData(p,0,x) == 239){
						if(trGetGPData(p,1,x) > 0){
							ColouredIconChat("1,0.5,0", "icons\god power earthquake icon 64", " - Earthquake");
							trChatSend(0, "<color=1,1,1>Deals 500 damage over a massive area");
						}
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
