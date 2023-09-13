//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Maze Escape";

//This needs to dynamically change

int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;
int CyclePlayers = 0;
//MapSize
int MapFactor(){
	if(MapSize == 398){
		return(1);
	}
	if(MapSize == 530){
		return(2);
	}
	if(MapSize == 662){
		return(3);
	}
}

bool Pregame = false;
bool AllowHunterChoice = false;
int PregameTimeout = 20;
int ChoiceTimeout = 120;
int HunterNumber = 0;
int RunnerCount = 0;
int HunterCount = 0;
int DestroyAbove = 1;
int gGameEndTime = 9999;

const int EVENT_REMOVE_CAM_TRACKS = 26;



/*NOTES

Put the choice area in hunter area so all have LOS
*/
