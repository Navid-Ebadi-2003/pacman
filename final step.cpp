#include <random>
#include <stdio.h>
#include "conio.h"
#include <windows.h>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include <iostream>

using namespace std;



int random(int maxNum){
	
	random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,maxNum-1);

    return dist6(rng);
    
}



//location functions

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) 
{ 
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}





void paint(int color){
	
	HANDLE n = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(n, color);
	
}




char** mainArray;
//const int timeG=0;
//const int timeP=0;






void mapGenerator(int dimensions){
	
	mainArray = new char*[dimensions];
	
	for(int i = 0; i < dimensions; i++){
		mainArray[i] = new char[dimensions];
	}
    
	
	for(int i=0 ;i<dimensions;i++){
		
		for(int j=0;j<dimensions;j++){
			
			mainArray[i][j]= '|';
			
		}
	}
	
	
	int numRoads=random(dimensions/4)+(dimensions/4);
	
	for(int i=0 ;i<numRoads;i++){
		
		int startOfRoad=random(dimensions-2)+1;
		
		for(int j=0;j<dimensions;j++){
			mainArray[j][startOfRoad]='.';
		}
			
		int testForBreak=random(2);
		
		if(testForBreak==1){
			int breakOfRoad=random(dimensions-2)+1;
			
			int leftOrRight=random(2);
			
			if(leftOrRight==0){
				for(int j=1;j<startOfRoad;j++){
					mainArray[breakOfRoad][j]='.';
				}
			}
			else{
				for(int j=startOfRoad;j<dimensions-1;j++){
					mainArray[breakOfRoad][j]='.';
				}
			}	
		}
	}
	
	
	//pacman and ghosts start road
	
	for(int i=1;i<dimensions-1;i++){
		mainArray[(dimensions/4)*3-1][i]='.';
		mainArray[(dimensions/4)-1][i]='.';
	}	
	
	
	// up and down of map
	for(int i=0;i<dimensions;i++){
		mainArray[0][i]='|';
		mainArray[dimensions-1][i]='|';
	}
	
	
	//create cherry
	int cherry=0;
	while(cherry<dimensions/4){
		int chX=random(dimensions);
		int chY=random(dimensions);
		
		if(mainArray[chX][chY]=='.'){
			mainArray[chX][chY]='o';
			cherry+=1;
		}
		
	}
	
	
}







void movmentOfGhost(int &X, int &Y, int &move, int dimensions, int color){
		
		paint(15);
		gotoxy(X,Y);
		cout <<mainArray[Y][X];
		
		if(move==0){
			if(mainArray[Y-1][X]!='|' and Y>1){ 
				Y-=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';
				
				if(mainArray[Y][X-1]!='|' or mainArray[Y][X+1]!='|'){
					move=random(4);
				}
			}
			else{
				move=random(4);
			}
		}
		else if(move==1){
			if(mainArray[Y][X+1]!='|' and X<dimensions-1){
				X+=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';

				if(mainArray[Y-1][X]!='|' or mainArray[Y+1][X]!='|'){
					move=random(4);
				}
			}
			else{
				move=random(4);
			}
		}
		else if(move==2){
			if(mainArray[Y+1][X]!='|' and Y<dimensions-2){
				Y+=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';

				if(mainArray[Y][X-1]!='|' or mainArray[Y][X+1]!='|'){
					move=random(4);
				}
			}
			else{
				move=random(4);
			}	
		}
		else{
			if(mainArray[Y][X-1]!='|' and X>0){
				X-=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';
				
				if(mainArray[Y-1][X]!='|' or mainArray[Y+1][X]!='|'){
					move=random(4);
				}
			}
			else{
				move=random(4);
			}
		}
		
		paint(color);
		gotoxy(X,Y);
		cout <<'g'; 	
}







int main() {
	
	int dimensions;
	int gameCommand;
	string name;
	
	
	struct movmentGP {
		
		int Y;
		int X;
		int lastMove;	
	};
	
	movmentGP ghost1;
	movmentGP ghost2;
	movmentGP ghost3;
	movmentGP pacman;
	
	int startPointGY;
	int startPointGX;	
	int startPointPY;
	int startPointPX;
	
	char order='z';
	int score=1;
	int heart=3;
	char formP='p';
	int paintP=6;
	bool power=false;
	int goneTime=0;
	
	
	cout<<"1.new game"<<'\n'<<"2.load game"<<'\n'<<"3.scoreboard"<<'\n';
	cin>>gameCommand;
	system("cls");
	
	if(gameCommand==1){
	
		cout<<"enter a name: ";
		cin>>name;
		cout<<"enter dimensions: ";
		cin>>dimensions;
		system("cls");
		
		mapGenerator(dimensions);
		
		
		startPointGY=(dimensions/4)*3-1;
		startPointGX=1;
		startPointPY=dimensions/4-1;
		startPointPX=dimensions-2;		
		
		
		ghost1.Y=startPointGY;
		ghost1.X=startPointGX;
		ghost1.lastMove=random(4);
		
		ghost2.Y=startPointGY;
		ghost2.X=startPointGX;
		ghost2.lastMove=random(4);
		
		ghost3.Y=startPointGY;
		ghost3.X=startPointGX;
		ghost3.lastMove=random(4);
		
		
		pacman.Y=startPointPY;
		pacman.X=startPointPX;
		mainArray[pacman.Y][pacman.X]=' ';	
				
	}
	else if(gameCommand==2){
		
		cout<<"enter saved name: ";
		cin>>name;
		system("cls");
		
		ifstream savedFileData(name+"_Data.txt");
		if (savedFileData.is_open()){
	 		
	 		int counterD=1;
	 		int data;
	 		while(savedFileData>>data){
	 			
	 			switch(counterD){
	 				
	 				case 1:
	 					dimensions=data;
	 					break;
	 				case 2:
	 					pacman.X=data;
	 					break;
	 				case 3:
	 					pacman.Y=data;
	 					break;
	 				case 4:
	 					ghost1.X=data;
	 					break;
	 				case 5:
	 					ghost1.Y=data;
	 					break;
	 				case 6:
	 					ghost1.lastMove=data;
	 					break;
	 				case 7:
	 					ghost2.X=data;
	 					break;
	 				case 8:
	 					ghost2.Y=data;
	 					break;
	 				case 9:
	 					ghost2.lastMove=data;
	 					break;
	 				case 10:
	 					ghost3.X=data;
	 					break;
	 				case 11:
	 					ghost3.Y=data;
	 					break;
	 				case 12:
	 					ghost3.lastMove=data;
	 					break;
	 				case 13:
	 					score=data;
	 					break;
	 				case 14:
	 					heart=data;
	 					break;
	 				case 15:
	 					goneTime=data;
	 					break;
				 }
				 counterD++;
			 }
			 savedFileData.close();
		}
		else{
			cout<<'\n'<<"this file dosnt exist.";
		}
		
		
		mainArray = new char*[dimensions];
		for(int i = 0; i < dimensions; i++){
			mainArray[i] = new char[dimensions];
		}
		
		
		startPointGY=(dimensions/4)*3-1;
		startPointGX=1;
		startPointPY=dimensions/4-1;
		startPointPX=dimensions-2;	
		
		
		ifstream savedFileMap(name+"_Map.txt");
		if(savedFileMap.is_open()){
			
			char brick;
			int Mi=0;
			int Mj=0;
			while(savedFileMap >> brick){
				
				if(brick=='#'){
					mainArray[Mi][Mj]=' ';
				}
				else{
					mainArray[Mi][Mj]=brick;
				}

				Mj++;
				
				if(Mj==dimensions){
					Mi++;
					Mj=0;
				}	
			}

			savedFileMap.close();
		}
		else{
			cout<<'\n'<<"this file dosnt exist.";
		}		
	}

	

   
   //print map
   if(gameCommand==1 or gameCommand==2){
	   for(int i=0 ;i<dimensions;i++){
			
			for(int j=0;j<dimensions;j++){
				
				cout<<mainArray[i][j];	
			}
			cout<<'\n';
		}
	}
	

	
	clock_t start,now,cherryPower;
	cherryPower=clock();
	start = clock();
	int time;
	int powerTime;
	
	int pause;
	bool testForEnd=false; 	
	while(gameCommand==1 or gameCommand==2){
		
		movmentOfGhost(ghost1.X ,ghost1.Y,ghost1.lastMove,dimensions,4);
		movmentOfGhost(ghost2.X ,ghost2.Y,ghost2.lastMove,dimensions,1);
		movmentOfGhost(ghost3.X ,ghost3.Y,ghost3.lastMove,dimensions,2);

		if(kbhit()){
	
			order=getch();
		}
		
		paint(15);
		gotoxy(pacman.X,pacman.Y);
		cout<<' ';
		
		if(order=='w'){
			if(mainArray[pacman.Y-1][pacman.X]!='|' and pacman.Y>1){ 
				pacman.Y-=1;
						
				if(mainArray[pacman.Y][pacman.X]=='.'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=1;							
				}
				else if(mainArray[pacman.Y][pacman.X]=='o'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=5;
					cherryPower=clock();							
				}
			}
		}
		else if(order=='d'){
			if(mainArray[pacman.Y][pacman.X+1]!='|' and pacman.X<dimensions-1){
				pacman.X+=1;
						
				if(mainArray[pacman.Y][pacman.X]=='.'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=1;							
				}
				else if(mainArray[pacman.Y][pacman.X]=='o'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=5;
					cherryPower=clock();							
				}
			}
		}
		else if(order=='s'){
			if(mainArray[pacman.Y+1][pacman.X]!='|' and pacman.Y<dimensions-2){
				pacman.Y+=1;
						
				if(mainArray[pacman.Y][pacman.X]=='.'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=1;							
				}
				else if(mainArray[pacman.Y][pacman.X]=='o'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=5;
					cherryPower=clock();							
				}
			}	
		}
		else if(order=='a'){
			if(mainArray[pacman.Y][pacman.X-1]!='|' and pacman.X>0){
				pacman.X-=1;
						
				if(mainArray[pacman.Y][pacman.X]=='.'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=1;							
				}
				else if(mainArray[pacman.Y][pacman.X]=='o'){
					mainArray[pacman.Y][pacman.X]=' ';
					score+=5;
					cherryPower=clock();							
				}
			}
		}
		
		now=clock();
		time=(now-start)/1000;
		powerTime=(now-cherryPower)/1000;
		
		
		if(powerTime<5 and start!=cherryPower){
			formP='P';
			paintP=5;
			power=true;
		}
		else{
			formP='p';
			paintP=6;
			power=false;
		}
			
		paint(paintP);	
		gotoxy(pacman.X,pacman.Y);
		cout<<formP;
		
		
		paint(14);
		gotoxy(dimensions+5,0);
		cout<<"heart: "<<heart;	
		gotoxy(dimensions+5,1);
		cout<<"score: "<<score;	
		gotoxy(dimensions+5,2);
		cout<<"time: "<<time+goneTime<<'s';		
		
		
		
		
		testForEnd= true;
		
		for(int i=0;i<dimensions;i++){
			for(int j=0;j<dimensions;j++){
				if(mainArray[i][j]=='.' or mainArray[i][j]=='o'){
					testForEnd= false;
				}
			}
		}
		
		
		if(testForEnd==true){
			paint(10);
			gotoxy(dimensions+2,dimensions+2);
			cout<<"you win";
			break;
		}
		
		
		
		if(power==false){
	
			if(pacman.X==ghost1.X and pacman.Y==ghost1.Y){
				heart-=1;
				pacman.Y=startPointPY;
				pacman.X=startPointPX;
				order='z';	
			}
			else if(pacman.X==ghost2.X and pacman.Y==ghost2.Y){
				heart-=1;
				pacman.Y=startPointPY;
				pacman.X=startPointPX;
				order='z';
			}
			else if(pacman.X==ghost3.X and pacman.Y==ghost3.Y){
				heart-=1;
				pacman.Y=startPointPY;
				pacman.X=startPointPX;
				order='z';
			}			
		}
		else{
			
			if(pacman.X==ghost1.X and pacman.Y==ghost1.Y){
					ghost1.Y=startPointGY;
					ghost1.X=startPointGX;
					score+=10;	
			}
			else if(pacman.X==ghost2.X and pacman.Y==ghost2.Y){
					ghost2.Y=startPointGY;
					ghost2.X=startPointGX;
					score+=10;
			}
			else if(pacman.X==ghost3.X and pacman.Y==ghost3.Y){
					ghost3.Y=startPointGY;
					ghost3.X=startPointGX;
					score+=10;
			}
		}
		
		
		
		if(heart==0){
			paint(14);
			gotoxy(dimensions+5,0);
			cout<<"heart: "<<heart;
			paint(12);
			gotoxy(dimensions+2,dimensions+2);
			cout<<"game over";
			break;
		}
		
		
		if(order=='e'){
			paint(15);
			gotoxy(dimensions+5,5);
			cout<<"1.continue";
			gotoxy(dimensions+5,6);
			cout<<"2.save";
			gotoxy(dimensions+5,7);
			cout<<"3.discard";
			gotoxy(dimensions+5,8);
			cin>>pause;
			
			if(pause==2 or pause==3){
				break;
			}
			
			gotoxy(dimensions+5,5);
			cout<<"          ";
			gotoxy(dimensions+5,6);
			cout<<"          ";
			gotoxy(dimensions+5,7);
			cout<<"          ";
			gotoxy(dimensions+5,8);
			cout<<"          ";
			
			order='z';
		}
		
	
		Sleep(300);		
		
	}
	
	
	
	
	
		
	if(pause==2){
		
		ofstream savingFileData(name+"_Data.txt");
		
		savingFileData<<dimensions<<'\n';
		savingFileData<<pacman.X<<' '<<pacman.Y<<'\n';
		savingFileData<<ghost1.X<<' '<<ghost1.Y<<' '<<ghost1.lastMove<<'\n';
		savingFileData<<ghost2.X<<' '<<ghost2.Y<<' '<<ghost2.lastMove<<'\n';
		savingFileData<<ghost3.X<<' '<<ghost3.Y<<' '<<ghost3.lastMove<<'\n';
		savingFileData<<score<<' '<<heart<<' '<<time;
		
		savingFileData.close();	
		
		
		
		ofstream savingFileMap(name+"_Map.txt");
		
		for(int i=0;i<dimensions;i++){
			for(int j=0;j<dimensions;j++){
				if(mainArray[i][j]==' '){
					savingFileMap<<'#';
				}
				else{
				savingFileMap<<mainArray[i][j];
				}
			}
			savingFileMap<<'\n';
		}
		
		savingFileData.close();	
		
		paint(15);
		gotoxy(dimensions+5,dimensions+5);
		cout<<"it was saved";	
	}
	else if(pause==3){
		paint(15);
		gotoxy(dimensions+5,dimensions+5);
		cout<<"end game";	
	}
	
	
	
	
	int finalScore=(heart*50)+score-((time+goneTime)/4);
	if(finalScore<0){
		finalScore=0;
	}
	
	
	
	
	//scoreboard
	
	string rankN[5];
	int rankS[5];
	
	ifstream scoreboardN("scoreboardN.txt");
	
	string RN;
	int counterRN=0;
	while(scoreboardN>>RN){
		rankN[counterRN]=RN;
		counterRN++;
	}
	
	scoreboardN.close();
	
	ifstream scoreboardS("scoreboardS.txt");
	
	int RS;
	int counterRS=0;
	while(scoreboardS>>RS){
		rankS[counterRS]=RS;
		counterRS++;
	}
	
	scoreboardS.close();
	
	
	bool testForRank=false;
	
	if(testForEnd==true){
		
		for(int i=0;i<5;i++){
			if(finalScore>=rankS[i]){
				testForRank=true;
			}
		}
		
		int min=0;
		if(testForRank==true){
			for(int i=1;i<5;i++){
				if(rankS[i]<rankS[min]){
					min=i;
				}
			}
			rankS[min]=finalScore;
			rankN[min]=name;
		}
		
		
		
		
		
		
		ofstream scoreboardN;
		scoreboardN.open("scoreboardN.txt");
		
		for(int i=0;i<5;i++){
			scoreboardN<<rankN[i]<<' ';
		}
		
		scoreboardN.close();
		
		
		ofstream scoreboardS;
		scoreboardS.open("scoreboardS.txt");
		
		for(int i=0;i<5;i++){
			scoreboardS<<rankS[i]<<' ';
		}
		
		scoreboardS.close();
		
		gameCommand=3;
	
		gotoxy(0,dimensions+6);	
	}
	
	
	
	
	if(gameCommand==3){
		paint(3);
		
		cout<<"names:                  final score:"<<'\n';
		
		for(int j=0;j<5;j++){
			int max=0;
			for(int i=1;i<5;i++){
				if(rankS[i]>=rankS[max]){
					max=i;
				}
			}
			cout<<j+1<<'.'<<rankN[max]<<"                  "<<rankS[max]<<'\n';
			rankS[max]=0; 
		}
	}



   
   return 0; 
}



