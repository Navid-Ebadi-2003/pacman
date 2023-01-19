#include <random>
#include <stdio.h>
#include "conio.h"
#include <windows.h>
#include<bits/stdc++.h>
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

	//generate map
	
	int dimensions;
	
	cout<<"enter dimensions: ";
	cin>>dimensions;
	gotoxy(0,0);
	cout<<"                    ";
	
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
	
	
		
	//print map
   
   gotoxy(0,0);
   
   for(int i=0 ;i<dimensions;i++){
		
		for(int j=0;j<dimensions;j++){
			
			cout<<mainArray[i][j];
			
		}
		cout<<'\n';
	}
	
	//end of the genarate map
	
	
	
	
	struct movmentG {
		
		int Y;
		int X;
		int lastMove;	
	};
	
	movmentG ghost1;
	movmentG ghost2;
	movmentG ghost3;
	movmentG pacman;
	
	int startPointGY=(dimensions/4)*3-1;
	int startPointGX=1;
	
	ghost1.Y=startPointGY;
	ghost1.X=startPointGX;
	ghost1.lastMove=random(4);
	
	ghost2.Y=startPointGY;
	ghost2.X=startPointGX;
	ghost2.lastMove=random(4);
	
	ghost3.Y=startPointGY;
	ghost3.X=startPointGX;
	ghost3.lastMove=random(4);
	
	
	int startPointPY=dimensions/4-1;
	int startPointPX=dimensions-2;
	
	pacman.Y=startPointPY;
	pacman.X=startPointPX;
	mainArray[pacman.Y][pacman.X]=' ';
	
	clock_t start,now,cherryPower;
	cherryPower=clock();
	start = clock();
	
	char order='z';
	int score=1;
	int heart=3;
	char formP='p';
	int paintP=6;
	bool power=false;
	
	while(true){
		
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
		int time=(now-start)/1000;
		int powerTime=(now-cherryPower)/1000;
		
		
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
		cout<<"time: "<<time<<'s';		
		
		
		
		
		bool testForEnd= true;
		
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
	
		Sleep(300);		
		
	}
		
	
	
	
	
		
	
   //delet array?
   
   return 0; 
}



