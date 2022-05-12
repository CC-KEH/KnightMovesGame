#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
const int INF = 1e9+10;

//
int visited[8][8];          //This Matrix stores whether the block is visited or not, assigns 0 or 1 value
int level[8][8];            //This Matrix stores the minimum paths from src to ith row-jth col in int format
string addressBoard[8][8] = {""};  //This Matrix stores the path from src to the ith row-jth col in String format
string board[8][8] = {" "}; //Initialise all blocks as empty

int getXcoordinate(string s){
    //Returns the X coordinate by converting character to integer
    return s[0] - 'a';
}
int getYcoordinate(string s){
    //Returns the Y coordinate by converting character to integer
    return s[1] - '1';
}
string getXcoordinateFinal(string path){
  string newPath;
  switch(stoi(path)){
    case 0:
      newPath = "a"; 
    case 1:
      newPath = "b"; 
    case 2:
      newPath = "c"; 
    case 3:
      newPath = "d"; 
    case 4:
      newPath = "e"; 
    case 5:
      newPath = "f"; 
    case 6:
      newPath = "g"; 
    case 7:
      newPath = "h";
    default:
      cout<<"Error in Coordinates X final Conversion"<<endl;
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

int solvePath(string knightPosition, string targetPosition){
    int sourceX = getXcoordinate(knightPosition);
    int sourceY = getYcoordinate(knightPosition);
    int destX = getXcoordinate(targetPosition);
    int destY = getYcoordinate(targetPosition);
    
    
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
  return level[destX][destY];
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
  int destX = getXcoordinate(targetPosition);
  int destY = getYcoordinate(targetPosition);
  
  string path = addressBoard[destX][destY];

  cout<<path<<endl;

  int step=0;
  for(int i = path.size()-1;i>=0;i-=2){
        //X-Coordinate, convert integer-String to integer
        int y = path[i-1] - '0';
        int x = path[i] - '0';    
        board[x][y] = to_string(step);
        step++;
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

void Game(string s1,string s2){
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
}else{
    cout<<"Oopsie Wrong Answer"<<endl;
    
    cout<<"1. Retry  2. Watch Answer"<<endl;
    cin>>no;
    if(no == 1){
        factor/=1.5;
        goto retry;
    }else{
        printBoard(s2,cpuAnswer);
    }
}
  /*
    if(player1_Path != player2_Path){
    //Only 1 of them is correct no need to compare their time
    if(cpuAnswer==player1_Path){
      cout<<"Player 1 wins the game! "<<endl;
      cout<<"Player 1 Score: "<<score_1<<endl;
      cout<<"Player 2 Score: 0"<<endl;
      
    }else if(cpuAnswer==player2_Path){
      cout<<"Player 2 wins the game! "<<endl;
      cout<<"Player 2 Score: "<<score_2<<endl;
      cout<<"Player 1 Score: 0"<<endl;
      }
    else{
      cout<<"Wrong answer from both sides"<<endl;
      cout<<"1. Retry  2. Watch Answer"<<endl;
      cin>>no;
      if(no == 1){
        factor/=1.5;
        goto retry;
    }else{
        printBoard(s2,cpuAnswer);
    }
    }
  }
  else{
    if(cpuAnswer==player1_Path){
      comparetime(player1,player2);
      if(time.player1<time.player2){
        cout<<"Player 1 wins the game by answering in less time"<<endl;
        cout<<"Player 1 Score: "<<score_1<<endl;
      }else{
        cout<<"Player 2 wins the game by answering in less time"<<endl;
        cout<<"Player 2 Score: "<<score_2<<endl;
      }
    }
  }
  */
}


int main(){
    //no -> number of testcases
    int no;
    cin>>no;
    for (int i = 0; i < no; i++)
    {
        //reseting the visited and level board
        reset();
        //Filling the addressBoard, assigning each cell its address, in string format
        setBoard();
        //s1 -> Source
        //s2 -> Destination
        string s1,s2;
        cin>>s1>>s2;
        //Game(s1,s2);
        int steps = solvePath(s1,s2);
        cout<<steps<<endl;  
      
        printBoard(s2,steps);
    }
}

//1. Check X and Y value after conversion
//2. Check Steps Value by printing each
//3. Check Board by printing it completely
//4. Add The print move (Alphabetical order) Below the board
//5. Add Game Function
