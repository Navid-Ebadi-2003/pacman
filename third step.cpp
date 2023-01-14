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










int main() {

	//generate map
	
	int dimensions;
	
	cin>>dimensions;

	char** mainArray = new char*[dimensions];
	
	for(int i = 0; i < dimensions; ++i){
		mainArray[i] = new char[dimensions];
	}
    
	
	for(int i=0 ;i<dimensions;i++){
		
		for(int j=0;j<dimensions;j++){
			
			mainArray[i][j]= '|';
			
		}
	}
	
	
	int numRoads=random(dimensions*3/4)+1;
	
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
	
	
	//print map
   
   gotoxy(0,0);
   
   for(int i=0 ;i<dimensions;i++){
		
		for(int j=0;j<dimensions;j++){
			
			cout<<mainArray[i][j];
			
		}
		cout<<'\n';
	}
	
	//end of the genarate map
	
	
	
	
	
	
	//ghost movement
	
	
	struct movmentG {
		
		int Y;
		int X;	
	};
	
	movmentG ghost1;
	movmentG ghost2;
	movmentG ghost3;
	
	ghost1.Y=(dimensions/4)*3-1;
	ghost1.X=1;
	
	const int time=400;
	
	
	while(true){
		
		int move=random(4);
		
		if(move==0){
			while(mainArray[ghost1.Y-1][ghost1.X]!='|' and ghost1.Y>1){ 
				ghost1.Y-=1;
				
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'g';

				Sleep(time);
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'.'; 
				
				if(mainArray[ghost1.Y][ghost1.X-1]!='|' or mainArray[ghost1.Y][ghost1.X+1]!='|'){
					break;
				}
			}
		}
		else if(move==1){
			while(mainArray[ghost1.Y][ghost1.X+1]!='|' and ghost1.X<dimensions-1){
				ghost1.X+=1;
				
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'g';

				Sleep(time);
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'.'; 
				
				if(mainArray[ghost1.Y-1][ghost1.X]!='|' or mainArray[ghost1.Y+1][ghost1.X]!='|'){
					break;
				}
			}
		}
		else if(move==2){
			while(mainArray[ghost1.Y+1][ghost1.X]!='|' and ghost1.Y<dimensions-2){
				ghost1.Y+=1;
				
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'g';

				Sleep(time);
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'.'; 
				
				if(mainArray[ghost1.Y][ghost1.X-1]!='|' or mainArray[ghost1.Y][ghost1.X+1]!='|'){
					break;
				}
			}	
		}
		else{
			while(mainArray[ghost1.Y][ghost1.X-1]!='|' and ghost1.X>0){
				ghost1.X-=1;
				
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'g';

				Sleep(time);
				gotoxy(ghost1.X,ghost1.Y);
				cout <<'.'; 
				
				if(mainArray[ghost1.Y-1][ghost1.X]!='|' or mainArray[ghost1.Y+1][ghost1.X]!='|'){
					break;
				}
			}
		}

		//movementOfGhost(ghost1.X,ghost1.Y); ???
		// 3 while at same time ???
    }
	
	 // end of ghost movement
	
	
	
	
	
   //delet array?
   
   return 0; 
}



