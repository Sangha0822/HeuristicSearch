#include <iostream>
#include <vector>
#include <algorithm>
#include "puzzle.h"
using namespace std;


void printGoalNode(const Node& goalNode) {
    cout << "Goal Depth: " << goalNode.depth << endl;
    for (int i = 0; i < 9; i++) 
    {
        cout << goalNode.state[i] << " ";
        if (i % 3 == 2)
        {
            cout << endl; 
        } 
    }
    cout << "-----------------" << endl;
}

int main()
{

    vector<int> initialState = {1,6,7,5,0,3,4,8,2}; 
    Problem p(initialState);
    p.initialUniformCost(); 
    p.initialHeursticQueue();
    p.initialManhattanQueue();

    Node node1 = p.uniformCost();
    printGoalNode(node1);

    Node node2 = p.heurstic();
    printGoalNode(node2);

    Node node3 = p.manhattan();
    printGoalNode(node3);
    

    return 0;
}