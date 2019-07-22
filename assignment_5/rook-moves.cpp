
#include "mapio.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#define DEBUG true

using namespace std;
queue < pair<unsigned, unsigned> > bfsqueue;
vector<vector<pair<unsigned,unsigned> >> position_keeper;
vector< vector<string> > direction_keep;
void bfs(vector<vector <int> >& distmap, ChessMap& map,int index1,int index2, int first,int second,pair<unsigned, unsigned>& temp){
      
    if((distmap[index1][index2]==-1)&&(direction_keep[index1][index2]==direction_keep[first][second])){
        distmap[index1][index2]=distmap[first][second];
        position_keeper[index1][index2].first=first;
        position_keeper[index1][index2].second=second;
        cout<<"the coordinate"<<index1<<" , "<<index2<<" keeping "<< position_keeper[index1][index2].first<<" , "<<position_keeper[index1][index2].second<<endl;
        cout<<"push"<<temp.first<<","<<temp.second<<"in to queue"<<endl;
        
        cout<<distmap[index1][index2]<<endl;
        bfsqueue.push(temp);
    }
    else if((distmap[index1][index2]==-1)&&(direction_keep[index1][index2]!=direction_keep[first][second])){
             distmap[index1][index2]=distmap[first][second]+1;
             position_keeper[index1][index2].first=first;
             position_keeper[index1][index2].second=second;
              bfsqueue.push(temp);
    }
    else if(distmap[index1][index2]>distmap[first][second]+1){
        if(direction_keep[index1][index2]==direction_keep[first][second])
         distmap[index1][index2]=distmap[first][second];
        if(direction_keep[index1][index2]!=direction_keep[first][second])
            distmap[index1][index2]=distmap[first][second]+1;
         position_keeper[index1][index2].first=first;
         position_keeper[index1][index2].second=second;
         bfsqueue.push(temp);
             
    }
}
void trace_back(pair<unsigned, unsigned> coordinate,ChessMap& map){
       pair<unsigned,unsigned> temp=position_keeper[coordinate.first][coordinate.second];
       cout<<"the previous coordinate is "<<temp.first<<" , "<<temp.second<<endl;
       if(map[temp.first][temp.second]=='r')
            return;
        trace_back(temp,map);
        cout<< temp.first<<", "<<temp.second<<endl;

}
int main () {
    //     input routine supplied in "mapio.h"
    //.   - access characters in the mapgrid using grid[row][col], 
    //      where 0 <= row, col < n

    ChessMap map;

    cin >> map;
    unsigned n = map.dim();
    cout << map;
    vector<vector <int> > distmap(n,vector<int>(n));
    position_keeper=vector<vector<pair<unsigned,unsigned> >>(n,vector<pair<unsigned,unsigned>>(n));
    direction_keep=vector<vector<string>>(n,vector<string>(n));


    pair<unsigned, unsigned> start, end;
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            distmap[i][j]=-1;
            direction_keep[i][j]="no direction";
            if (map[i][j] == 'r') { 
                distmap[i][j]=0;
                direction_keep[i][j]="rook";
                start = pair<unsigned, unsigned>({i,j}); 
                }
            if(map[i][j]=='o')
                 end = pair<unsigned, unsigned>({i,j});
        }
        // if (DEBUG) cout << '[' << map[i] << ']' << endl;
    }
    if (DEBUG) cout << "The starting position is: " << start.first << ", " << start.second << endl;

    
    bfsqueue.push(start);
    while(!bfsqueue.empty()){
         pair <unsigned,unsigned> p = bfsqueue.front();
         cout<<"the element be pop from queue is"<<p.first<<","<<p.second<<endl;
         bfsqueue.pop();
         for(int i=-1;i<=1;i++){
             for(int j=-1;j<=1;j++){
                if((i==0&&(j==1||j==-1))||(j==0&&(i==1||i==-1))){
                      int index1=p.first+i;
                      int index2=p.second+j;
                      if(index1>n-1||index2>n-1||index1<0||index2<0){ continue; }
                      if(map[index1][index2]=='#'){continue; }
                      pair<unsigned, unsigned> temp(index1,index2);
                      if(i==0&&j==-1){ direction_keep[index1][index2]="left"; }
                      if(i==0&&j==1){ direction_keep[index1][index2]="right";}
                      if(i==1&&j==0){ direction_keep[index1][index2]="down";}
                      if(i==-1&&j==0){ direction_keep[index1][index2]="up";}
                      bfs(distmap,map,index1, index2,p.first,p.second,temp);
                    }
                
                }
            }

        }


    if(distmap[end.first][end.second]==-1)
           cout<<"Impossible"<<endl;
    else {   
           trace_back(end,map); 
           cout<<end.first<<", "<<end.second<<endl;
    }  
    return 0;
}
