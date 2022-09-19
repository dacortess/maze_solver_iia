#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <math.h>
#include "Utils.h"

using namespace std;

class Compare{
    pair<int, int> _target;
public:
    Compare(pair<int, int> target){
        _target = target;
    }
    bool operator() (const Node a, const Node b){
        float aDistance = sqrt( pow(_target.second - a.position.second, 2) + pow(a.position.first - _target.first, 2));
        float bDistance = sqrt( pow(_target.second - b.position.second, 2) + pow(b.position.first - _target.first, 2));

        return aDistance > bDistance;
    }
};

typedef priority_queue<Node, vector<Node>, Compare> Heap;

Node AStar(vector<vector<char>>& map, vector<pair<int, int>>& traverse, Node start, Node end, bool& failure){
    if (IsFinish(map, start.position, end.position)){
        failure = false;
        return start;
    }

    Heap frontier(Compare(end.position));
    frontier.push(start);
    set<pair<int, int>> reached;
    reached.insert(start.position);
    while (!frontier.empty()){
        Node current = frontier.top();
        frontier.pop();
        traverse.push_back(current.position);
        if(IsFinish(map, current.position, end.position)){
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
    Node start(0,1);
    Node end(map.size() - 1, map.size() - 2);
    bool failure;
    vector<pair<int,int>> traverse;
    Node fin = AStar(map, traverse, start, end, failure);
    if(!failure){
        WriteSolutionPath(fin.path, "AStar_path");
        WriteTraverse(traverse, "AStar_traverse");
    }else{
        cout << "FAILED" << '\n';
    }
    return 0;
}