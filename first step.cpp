#include <random>
#include <iostream>

using namespace std;



int random(int maxNum){
	
	random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,maxNum-1); // distribution in range [1, 6]

    return dist6(rng);
    
}


struct mainStruct{
	
	int ghost1X , ghost1Y;
	int ghost2X , ghost2Y;
	int ghost3X , ghost3Y;
	
	int pacmanX, pacmanY;
	
	
	
};






int main() {

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
	
	
	int numRoads=random(dimensions/2);
	
	for(int i=0 ;i<numRoads;i++){
		
		int startOfRoad=random(dimensions);
		
		for(int j=0;j<dimensions;j++){
			mainArray[j][startOfRoad]='*';
		}
			
		int testForBreak=random(2);
		
		if(testForBreak==1){
			int breakOfRoad=random(dimensions);
			
			int leftOrRight=random(2);
			
			if(leftOrRight==0){
				for(int j=0;j<startOfRoad;j++){
					mainArray[breakOfRoad][j]='*';
				}
			}
			else{
				for(int j=startOfRoad;j<dimensions;j++){
					mainArray[breakOfRoad][j]='*';
				}
			}	
		}
	}
	
	
	
   
   for(int i=0 ;i<dimensions;i++){
		
		for(int j=0;j<dimensions;j++){
			
			cout<<mainArray[i][j];
			
		}
		cout<<'\n';
	}
	
   //delet array?
   
   return 0; 
}



