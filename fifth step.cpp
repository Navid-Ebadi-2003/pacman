#include <random>
#include <stdio.h>
#include "conio.h"
#include <windows.h>
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
const int timeG=0;
const int timeP=0;



void movmentOfGhost(int &X, int &Y, int dimensions, int color){
	
		int move=random(4);
		
		paint(15);
		gotoxy(X,Y);
		cout <<'.'; 
		
		if(move==0){
			while(mainArray[Y-1][X]!='|' and Y>1){ 
				Y-=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';

				Sleep(timeG);
				paint(15);
				gotoxy(X,Y);
				cout <<'.'; 
				
				if(mainArray[Y][X-1]!='|' or mainArray[Y][X+1]!='|'){
					break;
				}
			}
		}
		else if(move==1){
			while(mainArray[Y][X+1]!='|' and X<dimensions-1){
				X+=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';

				Sleep(timeG);
				paint(15);
				gotoxy(X,Y);
				cout <<'.'; 
				
				if(mainArray[Y-1][X]!='|' or mainArray[Y+1][X]!='|'){
					break;
				}
			}
		}
		else if(move==2){
			while(mainArray[Y+1][X]!='|' and Y<dimensions-2){
				Y+=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';

				Sleep(timeG);
				paint(15);
				gotoxy(X,Y);
				cout <<'.'; 
				
				if(mainArray[Y][X-1]!='|' or mainArray[Y][X+1]!='|'){
					break;
				}
			}	
		}
		else{
			while(mainArray[Y][X-1]!='|' and X>0){
				X-=1;
				
				paint(color);
				gotoxy(X,Y);
				cout <<'g';

				Sleep(timeG);
				paint(15);
				gotoxy(X,Y);
				cout <<'.'; 
				
				if(mainArray[Y-1][X]!='|' or mainArray[Y+1][X]!='|'){
					break;
				}
			}
		}
		
		paint(color);
		gotoxy(X,Y);
		cout <<'g'; 	
	// end of ghost movement
}








int main() {

	//generate map
	
	int dimensions;
	
	cin>>dimensions;
	
	mainArray = new char*[dimensions];
	
	for(int i = 0; i < dimensions; i++){
		mainArray[i] = new char[dimensions];
	}
    
	
	for(int i=0 ;i<dimensions;i++){
		
		for(int j=0;j<dimensions;j++){
			
			mainArray[i][j]= '|';
			
		}
	}
	
	
	int numRoads=random(dimensions)+1;
	
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
	
	
	//end of the genarate map
	
	
	
	
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
	};
	
	movmentG ghost1;
	movmentG ghost2;
	movmentG ghost3;
	movmentG pacman;
	
	ghost1.Y=(dimensions/4)*3-1;
	ghost1.X=1;
	ghost2.Y=(dimensions/4)*3-1;
	ghost2.X=1;
	ghost3.Y=(dimensions/4)*3-1;
	ghost3.X=1;
	
	
	pacman.Y=dimensions/4-1;
	pacman.X=dimensions-2;
	
	char order;
	int score=0;
	
	while(true){
		
		movmentOfGhost(ghost1.X ,ghost1.Y,dimensions,4);
		movmentOfGhost(ghost2.X ,ghost2.Y,dimensions,1);
		movmentOfGhost(ghost3.X ,ghost3.Y,dimensions,2);
		
		

		if(kbhit()){
	
			order=getch();
		}
		
			paint(15);
			gotoxy(pacman.X,pacman.Y);
			cout<<' ';
		
				if(order=='w'){
					while(mainArray[pacman.Y-1][pacman.X]!='|' and pacman.Y>1){ 
						pacman.Y-=1;
						
						paint(6);
						gotoxy(pacman.X,pacman.Y);
						cout <<'p';
		
						Sleep(timeP);
						paint(15);
						gotoxy(pacman.X,pacman.Y);
						cout <<' '; 
						
						if(mainArray[pacman.Y][pacman.X-1]!='|' or mainArray[pacman.Y][pacman.X+1]!='|'){
							break;
						}
					}
				}
				else if(order=='d'){
					while(mainArray[pacman.Y][pacman.X+1]!='|' and pacman.X<dimensions-1){
						pacman.X+=1;
						
						paint(6);
						gotoxy(pacman.X,pacman.Y);
						cout <<'p';
		
						Sleep(timeP);
						paint(15);
						gotoxy(pacman.X,pacman.Y);
						cout <<' '; 
						
						if(mainArray[pacman.Y-1][pacman.X]!='|' or mainArray[pacman.Y+1][pacman.X]!='|'){
							break;
						}
					}
				}
				else if(order=='s'){
					while(mainArray[pacman.Y+1][pacman.X]!='|' and pacman.Y<dimensions-2){
						pacman.Y+=1;
						
						paint(6);
						gotoxy(pacman.X,pacman.Y);
						cout <<'p';
		
						Sleep(timeP);
						paint(15);
						gotoxy(pacman.X,pacman.Y);
						cout <<' '; 
						
						if(mainArray[pacman.Y][pacman.X-1]!='|' or mainArray[pacman.Y][pacman.X+1]!='|'){
							break;
						}
					}	
				}
				else{
					while(mainArray[pacman.Y][pacman.X-1]!='|' and pacman.X>0){
						pacman.X-=1;
						
						paint(6);
						gotoxy(pacman.X,pacman.Y);
						cout <<'p';
		
						Sleep(timeP);
						paint(15);
						gotoxy(pacman.X,pacman.Y);
						cout <<' '; 
						
						if(mainArray[pacman.Y-1][pacman.X]!='|' or mainArray[pacman.Y+1][pacman.X]!='|'){
							break;
						}
					}
				}
			
			paint(6);	
			gotoxy(pacman.X,pacman.Y);
			cout<<'p';
		
		
		Sleep(500);	
		
		
		paint(12);
		if(pacman.X==ghost1.X && pacman.Y==ghost1.Y){
			gotoxy(dimensions+10,dimensions+10);
			cout<<"game over";
			break;
		}
		else if(pacman.X==ghost2.X && pacman.Y==ghost2.Y){
			gotoxy(dimensions+10,dimensions+10);
			cout<<"game over";
			break;
		}
		else if(pacman.X==ghost3.X && pacman.Y==ghost3.Y){
			gotoxy(dimensions+10,dimensions+10);
			cout<<"game over";
			break;
		}	
		
		
		
			
	}
		
	
	
	
	
		
		
	
	
   //delet array?
   
   return 0; 
}



