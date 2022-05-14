#include <bits/stdc++.h>
#include <chrono>
#include <cstring>
using namespace std;
using namespace std::chrono;
const int INF = 1e9+10;

//
int visited[8][8];          //This Matrix stores whether the block is visited or not, assigns 0 or 1 value
int level[8][8];            //This Matrix stores the minimum paths from src to ith row-jth col in int format
string addressBoard[8][8] = {""};  //This Matrix stores the path from src to the ith row-jth col in String format
string board[8][8] = {" "}; //Initialise all blocks as empty

int getXcoordinate(string s,int i){
    //Returns the X coordinate by converting character to integer
    return s[i] - 'a';
}
int getYcoordinate(string s,int j){
    //Returns the Y coordinate by converting character to integer
    return s[j] - '1';
}
string getcoordinatesFinal(char path,bool getX){
  string newPath="";
  if(getX){
  switch(path){
    case '0':
      newPath = "a"; 
      break;
    case '1':
      newPath = "b"; 
      break;
    case '2':
      newPath = "c"; 
      break;
    case '3':
      newPath = "d"; 
      break;
    case '4':
      newPath = "e"; 
      break;
    case '5':
      newPath = "f"; 
      break;
    case '6':
      newPath = "g"; 
      break;
    case '7':
      newPath = "h";
      break;
    default:
      cout<<"Error in Coordinates X final Conversion"<<endl;
    }
  }else{
    switch(path){
    case '0':
      newPath = "1"; 
      break;
    case '1':
      newPath = "2"; 
      break;
    case '2':
      newPath = "3"; 
      break;
    case '3':
      newPath = "4"; 
      break;
    case '4':
      newPath = "5"; 
      break;
    case '5':
      newPath = "6"; 
      break;
    case '6':
      newPath = "7"; 
      break;
    case '7':
      newPath = "8";
      break;
    default:
      cout<<"Error in Coordinates Y final Conversion"<<endl;
    }
  }
  return newPath;
}

//Returns the bool value for if the move is possible on the board or is it out of board length
bool isValid(int x, int y){
  return x>=0 && y>=0 && x<8 && y<8;
}

//The Elements from this Vector generate moves when added to i, in the movement at line no - 
vector<pair<int,int>> movements= {{-1,2},{1,2},
{2,1},{2,-1},
{1,-2},{-1,-2},
{-2,1},{-2,-1}
};

pair<string,int> solvePath(string knightPosition, string targetPosition){
    int sourceX = getXcoordinate(targetPosition,0);
    int sourceY = getYcoordinate(targetPosition,1);
    int destX = getXcoordinate(knightPosition,0);
    int destY = getYcoordinate(knightPosition,1);
    
    
    queue<pair<int,int>> q;
    q.push({sourceX,sourceY});
    visited[sourceX][sourceY] = 1;
    level[sourceX][sourceY] = 0;
    
    //Storing the address of 1st block ie source block
    //addressBoard[sourceX][sourceY].append(to_string(sourceX)+to_string(sourceY));
  
      while(!q.empty()){
      pair<int,int> v = q.front();
      int x = v.first;
      int y = v.second;
      q.pop();

      for(auto movement : movements){
        int moveX = movement.first + x;
        int moveY = movement.second + y;

        
        //NEW for optimisation
        if(moveX==destX && moveY==destY){
          level[moveX][moveY] = level[x][y] + 1;
          visited[moveX][moveY] = 1;
        
          //Storing the address of previous blocks
          
          addressBoard[moveX][moveY].append(addressBoard[x][y]); 
          
          break;
          
          }
        //NEW for optimisation

        
        if(!isValid(moveX,moveY)) continue;

        if(!visited[moveX][moveY]){
          q.push({moveX,moveY});
          level[moveX][moveY] = level[x][y] + 1; //keeps the record and updates the number of moves to reach target 
          visited[moveX][moveY] = 1;
          addressBoard[moveX][moveY] +=addressBoard[x][y]; 
          }
      }
      if(level[destX][destY] != INF){
        break;
      }
    }
  return make_pair(addressBoard[destX][destY],level[destX][destY]);//Returns the path and steps
}

void reset(){
  for(int i=0;i<8;++i){
    for(int j=0;j<8;++j){
      level[i][j] = INF;
      visited[i][j] = 0;      
      }
  }
}



void printBoard(string targetPosition,int steps){
  int destX = getXcoordinate(targetPosition,0);
  int destY = getYcoordinate(targetPosition,1);
  
  string path = addressBoard[destX][destY];
  cout<<path<<endl;
  
  string newPath="";
  for(int i = 0;i<path.length();i+=2){
    newPath += getcoordinatesFinal(path[i],true);
    newPath += getcoordinatesFinal(path[i+1],false);    
  }
  cout<<newPath<<endl;
  
  int step=steps;
  for(int i = path.size()-1;i>=0;i-=2){
        //X-Coordinate, convert integer-String to integer
        int y = path[i-1] - '0';
        int x = path[i] - '0';    
        board[x][y] = to_string(step);
        step--;
  }
  
  for(int row=7; row>=0; row--){
    cout<<row+1;
    for(int cell=0; cell<8; cell++){
      cout<<"  "<<board[row][cell]<<" ";
    }
    cout<<endl;
    cout<<endl;
  }
  cout<<"   A  B  C  D  E  F  G  H "<<endl;
}

void setBoard(){
  //i represents row and j represents coloumn
  for(int i = 7;i>=0;i--){
    for(int j=0;j<8;j++){
      string cellAddress = to_string(i)+to_string(j);
      addressBoard[i][j] = cellAddress;
    }
  }
}

/* Works for 2 Players only
bool Gameover(string playerPath,string s1,string s2){
int no;
int cpuAnswer = solvePath(s1,s2);
int userPath;
int factor = 2;
retry:
cout<<"Enter your Path: "<<endl;
  
//Calculating the time before giving input
auto start = high_resolution_clock::now();
cin>>userPath;
//Calculating the time after input is given
auto stop = high_resolution_clock::now();  
auto duration = duration_cast<microseconds>(stop - start);  
int score = factor/duration.count()*100000;

if(userPath==cpuAnswer){
    cout<<"Naissss Correct Answer! "<<endl;
    cout<<"Your Score: "<<score<<endl;
    return true;
}else if(userPath==cpuAnswer){
    cout<<"Oopsie Wrong Answer"<<endl;
    
    cout<<"1. Retry  2. Watch Answer"<<endl;
    cin>>no;
    if(no == 1){
        factor/=1.5;
        goto retry;
    }else{
        printBoard(s2,cpuAnswer);
    }

}*/
bool isPossible(int xCoordinate,int yCoordinate,string path){
  int last = getYcoordinate(path,path.length()-1); //Gives the last move y axis information
  int secondLast = getXcoordinate(path,path.length()-2); //Gives the last move x axis information
  if(xCoordinate>0 && xCoordinate<8){//Checks validity of X coordinate
    if(secondLast+2==xCoordinate || secondLast-1==xCoordinate || secondLast+1==xCoordinate || secondLast-2==xCoordinate){
      if(yCoordinate>0 && yCoordinate<8){//Checks validity of Y coordinate
        if(last+2==yCoordinate || last-1==yCoordinate || last+1==yCoordinate || last-2==yCoordinate){
          return true;
        }
      }
    }
  }
  return false;
  }
  

bool Gameover(string playerPath,string s1,string s2){

string cpuAnswer = solvePath(s1,s2).first;  
cout<<"\n"<<cpuAnswer<<endl;
if(playerPath==cpuAnswer){
    return true;
}else{
    return false;
  }
}

int setupGame(int no,string s1,string s2){
  string choiceBoard[4][8][8];
  
  
  //Goes through each player's turn
  bool answerFound = false;
  bool stopGame = false; //totally depends on answerFound value, exists so that we can stop the game at the right time
  int xCoordinate;
  int yCoordinate;
  
  int winner;
  
  int move = 1; //Represents which move it iss 
  
  string playerPath[] = {""};

  for(int i=0;i<no;i++){
    playerPath[i] = (s1);//Stores the starting position of each player, in chess language
  }
  string tempPath;//takes temporary input 
  while(!answerFound){
    for(int i=0;i<no;i++){
      cout<<"Enter your move "<<move<<" Player "<<i<<endl;
      retry://If the move given by player is wrong they will retry to give their move
      cin>>tempPath;
      xCoordinate = getXcoordinate(tempPath,0);
      yCoordinate = getYcoordinate(tempPath,1);
      if(isPossible(xCoordinate,yCoordinate,playerPath[i])){
        playerPath[i].append(tempPath); //Adds the path given by user in the playerPath array

        choiceBoard[i][xCoordinate][yCoordinate] = to_string(move);// update the board with the user move
        }
      else{
        cout<<"Incorrect move Playe"<<i<<endl;
        goto retry;
      }

      answerFound = Gameover(playerPath[i],s1,s2);//Checks if answer is found using Gameover function
      
        if(answerFound){
          stopGame = true; //If answer was found Game has to be stopped
          winner = i;
          }
    }
    for(int boardNo = 0;boardNo<no;boardNo++){//
      for(int row = 7;row>=0;row--){
        cout<<row+1;
        for(int cell=0;cell<8;cell++){
          cout<<"  "<<board[boardNo][row][cell]<<" ";
        }
        cout<<endl;
        cout<<endl;
      }
      cout<<"   A  B  C  D  E  F  G  H "<<endl;
    }
    
    if(stopGame){
      break;
    }else{
      move++; //Give another turn
    }
  }
  return winner; //Stop the game
}


int main(){
    //no -> number of players, max 4 allowed!
    int no;
    reset();
    setBoard(); //Set the address on board cells
    cout<<"Enter no of Players: "<<endl;
    cin>>no;
    string s1,s2;
    cin>>s1>>s2;

    //int winner = setupGame(no,s1,s2); //Start the Game
    
    //cout<<"Player"<<winner<<"wins!!"<<endl;
  
    int steps = solvePath(s1,s2).second;
    cout<<steps<<endl;  
    printBoard(s1,steps);

    //for (int i = 0; i < no; i++)
    //{
        //reseting the visited and level board
        //reset();
        //Filling the addressBoard, assigning each cell its address, in string format
        //setBoard();
        //s1 -> Source
        //s2 -> Destination
        //string s1,s2;
        //cin>>s1>>s2;
        //Game(s1,s2);
        //int steps = solvePath(s1,s2);
        //cout<<steps<<endl;  
      
       // printBoard(s2,steps);
    //}
}


//1. Correct the Alphabetical order of the cpu path and print it 
//2. Concatinate userinput String in playerPath array
//3. Solve issue in board printing


//isValid                          Done
//setBoard                         Done
//reset                            Done
//Solve Path                       Done
//getXcoordinate,ycoordinate       Done
//PrintBoard                       Done
//isPossile                        Done
//SetupGame
//GameOver                         
//GetXcoordinateFinal              
