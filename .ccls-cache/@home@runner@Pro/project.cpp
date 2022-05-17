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

bool isPossible(int xCoordinate,int yCoordinate,string path){
  int prevYmove = getYcoordinate(path,path.length()-1); //Gives the last move y axis information
  int prevXmove = getXcoordinate(path,path.length()-2); //Gives the last move x axis information
  
  if(xCoordinate>=0 && xCoordinate<8 && yCoordinate>=0 && yCoordinate<8){//Checks validity of X & Y coordinate
  if((prevXmove+2==xCoordinate) && (prevYmove+1==yCoordinate||prevYmove-1==yCoordinate) || ((prevXmove-1==xCoordinate) && (prevYmove+2==yCoordinate || prevYmove-2==yCoordinate)) || ((prevXmove+1==xCoordinate) && (prevYmove+2==yCoordinate ||prevYmove-2==yCoordinate)) ||((prevXmove-2==xCoordinate) && (prevYmove-1==yCoordinate || prevYmove+1==yCoordinate))){
          return true;
   }
  }
  return false;
  }
  

bool Gameover(string playerPath,string s1,string s2){

string path = solvePath(s1,s2).first;
string newPath = "";

for(int i = 0;i<path.length();i+=2){
    newPath += getcoordinatesFinal(path[i],true);
    newPath += getcoordinatesFinal(path[i+1],false);    
  }
  
cout<<"\n"<<newPath<<endl;
if(playerPath==newPath){
    return true;
}
else if(playerPath[playerPath.length()-1] == s2[1] && playerPath[playerPath.length()-2] == s2[0]){

    return true;
} 
else{
    return false;
  }
}

string setupGame(int no,string s1,string s2){
  string choiceBoard[4][8][8];
  int scoreArr[4] = {0};
  int factor = 2;
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

        //here yCoordinate represents Row & xCoordinate represents column
        choiceBoard[i][yCoordinate][xCoordinate] = to_string(move);// update the board with the user move

        for(int row = 7;row>=0;row--){
          cout<<row+1;
          for(int cell=0;cell<8;cell++){
          cout<<"  "<<choiceBoard[i][row][cell]<<" ";
        }
        cout<<endl;
        cout<<endl;
      }
        
      cout<<"   A  B  C  D  E  F  G  H "<<endl;    
        }
      else{
        cout<<"ILLEGAL MOVE PLAYER "<<i<<endl;
        goto retry;
      }

      answerFound = Gameover(playerPath[i],s1,s2);//Checks if answer is found using Gameover function
      
        if(answerFound){
          stopGame = true; //If answer was found Game has to be stopped
          for(int path = 0;path<no;path++){  
            if(playerPath[i].length()<playerPath[path].length()){
            winner = i;
            }else{
              winner = path;
            }
          }
          }
    }
    //print here
    
    if(stopGame){
      break;
    }else{
      move++; //Give another turn
    }
  }
  string answer = to_string(winner) + to_string(playerPath[winner].length()/2);
  return answer; //Stop the game
}
string printRandomString(int n){
    char alphabet[3] = { 'f', 'g','h'};
 
    string res = "";
    for (int i = 0; i < n; i++){
        res = res + alphabet[rand() % 3];
      }
    string num = to_string(1 + (rand() % ( 8 - 1 + 1 )));
    return res+num;
}

int main(){
    //no -> number of players, max 4 allowed!
    
    int no;
    reset();
    setBoard(); //Set the address on board cells
    cout<<"Enter no of Players: "<<endl;
    cin>>no;
    string s1,s2;
    srand(time(NULL)); //makes use of the computer's internal clock to control the choice of the seed. Since time is continually changing, the seed is forever changing. Remember, if the seed number remains the same, the sequence of numbers will be repeated for each run of the program.
    s2 = printRandomString(1);
    s1 = "a1";
    cout<<"You Start from: "<<s1<<endl;
    cout<<"Reach "<<s2<<" in minimum moves & be quick!"<<endl;
    string returnedAnswer = setupGame(no,s1,s2); //Start the Game and return the winner
    
    char winner = returnedAnswer[0];
    string steps =  returnedAnswer.substr(1);//return the steps taken by winner
    int minSteps = solvePath(s1,s2).second;
    cout<<"PLAYER "<<winner<<" WINS THE GAME WITH "<<steps<<" STEPS"<<endl;

    cout<<"Shortest Path to reach: "<<s2<<"is given below."<<endl;
    printBoard(s1,minSteps);
    
}





/*
1. Score: 
   retry://If the move given by player is wrong they will retry to give their move
      
      //auto start = high_resolution_clock::now();
      
      cin>>tempPath;
     
      
      //auto stop = high_resolution_clock::now();  

      //auto duration = duration_cast<seconds>(stop - start);

      //int time = (int)duration.count(); 
      
      //int score = 100/time;
          
      //scoreArr[i] += score;
      
      //cout<<"\n"<<scoreArr[i]<<endl;

      //cout<<"\n"<<score<<endl;

      //Storing player Score in the array

  CALCULATE THE SCORE IN THE END using array

  if other players dont reach the target arrScore[i] = 0;

  //Print Score
  cout<<"Player Name     ||    Score"<<endl;
  for(int i=0;i<4;i++){
    cout<<"PLAYER "<<i<<"\t ||   "scoreArr[i]<<endl;
  }

  Try adding KNP algorithm for giving score. Time based score is not working properly
*/