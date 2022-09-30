/**
 * To compile in Windows use g++ -o DFS DFS.cpp -lpsapi
 * To compile in Linux use g++ -o DFS DFS.cpp
 */
#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include "Utils.h"

using namespace std;

Node DFS(vector<vector<char>>& map, vector<pair<int, int>>& traverse, Node start, Node end, bool& failure){
    if (IsFinish(map, start.position, end.position)){
        failure = false;
        return start;
    }

    stack<Node> frontier;
    frontier.push(start);
    set<pair<int, int>> reached;
    reached.insert(start.position);
    while (!frontier.empty()){
        Node current = frontier.top();
        frontier.pop();
        traverse.push_back(current.position);
        if (IsFinish(map, current.position, end.position)){
            failure = false;
            return current;
        }
        vector<Node> childs = Expand(map, current);
        for(int i = 0; i < childs.size(); i++){
            pair<int, int> position = childs[i].position;
            if (!reached.count(position)){
                reached.insert(position);
                frontier.push(childs[i]);
            }
        }
    }

    failure = true;
    return start;
}

int main(int argc, char **argv) {
    vector<vector<char>> map = GetMap(argv[1]);
    Node start(0, FindCellIndex(map[0]));
    Node end(map.size() - 1, FindCellIndex(map[map.size() - 1]));
    bool failure;
    vector<pair<int,int>> traverse;
    auto startTime = std::chrono::system_clock::now();
    Node fin = DFS(map, traverse, start, end, failure);
    auto endTime = std::chrono::system_clock::now();
    double totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() / 1000.0;
    if(!failure){
        WriteSolutionPath(fin.path, "DFS_path");
        WriteTraverse(traverse, "DFS_traverse");
        WriteMemoryAndTime(totalTime, "DFS_stats");
    }else{
        cout << "FAILED" << '\n';
    }
    return 0;
}
