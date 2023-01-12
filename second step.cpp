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
	
	
	int numRoads=random(dimensions-1)+1;
	
	for(int i=0 ;i<numRoads;i++){
		
		int startOfRoad=random(dimensions);
		
		for(int j=0;j<dimensions;j++){
			mainArray[j][startOfRoad]='.';
		}
			
		int testForBreak=random(2);
		
		if(testForBreak==1){
			int breakOfRoad=random(dimensions);
			
			int leftOrRight=random(2);
			
			if(leftOrRight==0){
				for(int j=0;j<startOfRoad;j++){
					mainArray[breakOfRoad][j]='.';
				}
			}
			else{
				for(int j=startOfRoad;j<dimensions;j++){
					mainArray[breakOfRoad][j]='.';
				}
			}	
		}
	}
	
	//pacman and ghosts start road
	
	for(int i=0;i<dimensions;i++){
		mainArray[(dimensions/4)*3-1][i]='.';
		mainArray[(dimensions/4)-1][i]='.';
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
	
	int ghostY=(dimensions/4)*3-1;
	int ghostX=0;
	
	const int time=400;
	
	while(1==1){
		
		int move=random(4);
		
		if(move==0){
			while(mainArray[ghostY-1][ghostX]=='.' and ghostY>1){  //there is a problem in ghostY>0 that i cant find.
				ghostY-=1;
				
				gotoxy(ghostX,ghostY);
				cout <<'g';

				Sleep(time);
				gotoxy(ghostX,ghostY);
				cout <<'.'; 
				
				if(mainArray[ghostY][ghostX-1]=='.' or mainArray[ghostY][ghostX+1]=='.'){
					break;
				}
			}
		}
		else if(move==1){
			while(mainArray[ghostY][ghostX+1]=='.'){
				ghostX+=1;
				
				gotoxy(ghostX,ghostY);
				cout <<'g';

				Sleep(time);
				gotoxy(ghostX,ghostY);
				cout <<'.'; 
				
				if(mainArray[ghostY-1][ghostX]=='.' or mainArray[ghostY+1][ghostX]=='.'){
					break;
				}
			}
		}
		else if(move==2){
			while(mainArray[ghostY+1][ghostX]=='.' and ghostY<dimensions-1){
				ghostY+=1;
				
				gotoxy(ghostX,ghostY);
				cout <<'g';

				Sleep(time);
				gotoxy(ghostX,ghostY);
				cout <<'.'; 
				
				if(mainArray[ghostY][ghostX-1]=='.' or mainArray[ghostY][ghostX+1]=='.'){
					break;
				}
			}	
		}
		else{
			while(mainArray[ghostY][ghostX-1]=='.'){
				ghostX-=1;
				
				gotoxy(ghostX,ghostY);
				cout <<'g';

				Sleep(time);
				gotoxy(ghostX,ghostY);
				cout <<'.'; 
				
				if(mainArray[ghostY-1][ghostX]=='.' or mainArray[ghostY+1][ghostX]=='.'){
					break;
				}
			}
		}
    }
	
	 // end of ghost movement
	
	
	
	
	
   //delet array?
   
   return 0; 
}



