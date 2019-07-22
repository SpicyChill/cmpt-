
//
//  king-moves.cpp
//  Assignment5
//
//  Created by Yao Zhou on 2019/3/28.
//  Copyright © 2019 Yao Zhou. All rights reserved.
//
#include "mapio.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#define DEBUG false

using namespace std;

//Desc: Create a bfsqueue to store coordinates.
queue < pair<unsigned, unsigned> > bfsqueue;

//Desc: Create a 2 d array position_keeper to store the previous coordinates of current one.
vector<vector<pair<unsigned,unsigned> >> position_keeper;

//Desc: Push the space point into queue if it value of distmap is -1.
//Pre: All the coordinates be pushed into queue have to first satisfy is not "#".
//Post: Distmap is keeping update and the end point's value in distmap is the distance it go from start point and position_keeper store the path of start to end.
void bfs( vector<vector <int> >& distmap , ChessMap& map , int index1 , int index2 , int first , int second , pair<unsigned, unsigned>& temp ){
    if( distmap[index1][index2] == -1 ){
        position_keeper[index1][index2].first = first;
        position_keeper[index1][index2].second = second;
        distmap[index1][index2] = distmap[first][second] + 1;
        bfsqueue.push(temp);
    }
}

//Desc: Using recursion to print out the path from start point to the end point.
void trace_back( pair<unsigned, unsigned> coordinate,ChessMap& map ){
       pair<unsigned,unsigned> temp = position_keeper[coordinate.first][coordinate.second];
       if( map[temp.first][temp.second] == 'k' )
            return;
        trace_back( temp , map );
        cout << temp.first << ", " << temp.second << endl;

}
int main () {
    //     input routine supplied in "mapio.h"
    //.   - access characters in the mapgrid using grid[row][col], 
    //      where 0 <= row, col < n

    ChessMap map;

    cin >> map;
    unsigned n = map.dim();
    cout << map;

    //Desc: Creat a distmap to record the distance from start point to end point.
    vector<vector <int> > distmap(n,vector<int>(n));

    //Desc: Initialize position_keeper 2d array.
    position_keeper=vector<vector<pair<unsigned,unsigned> >>(n,vector<pair<unsigned,unsigned>>(n));

    pair<unsigned, unsigned> start, end;
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            distmap[i][j]=-1;
            if (map[i][j] == 'k') { 
                distmap[i][j]=0;
                start = pair<unsigned, unsigned>({i,j}); 
                }
            if(map[i][j]=='o')
                 end = pair<unsigned, unsigned>({i,j});
        }
        // if (DEBUG) cout << '[' << map[i] << ']' << endl;
    }
    if (DEBUG) cout << "The starting position is: " << start.first << ", " << start.second << endl;

    
    bfsqueue.push(start);

    //Desc: Pop the top element in bfsqueue to determine it surrounding element if satisfied push condition.
    //Pro: bfsqueue is not empty.
    while( !bfsqueue.empty() ){
         pair <unsigned,unsigned> p = bfsqueue.front();
         bfsqueue.pop();
         for( int i=-1;i<=1;i++ ){
             for( int j=-1;j<=1;j++ ){
                if( i == 0&&j == 0 ){ continue; }
                int index1 = p.first + i;
                int index2 = p.second + j;
                if( index1 > n-1 || index2 > n-1 || index1 < 0 || index2 < 0 ){ continue; }
                if( map[index1][index2] == '#'){continue; }
                pair<unsigned, unsigned> temp( index1 , index2 );
                bfs( distmap , map , index1 , index2 , p.first , p.second , temp );
             }
         }

    }


    if( distmap[end.first][end.second] == -1 )
           cout << "Impossible" << endl;
    else {   
           trace_back( end , map ); 
           cout << end.first << ", " << end.second << endl;
    }  
    return 0;
}

