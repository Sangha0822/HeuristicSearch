#include <iostream>
#include <vector>
#include <algorithm>
#include "puzzle.h"
using namespace std;



int main()
{

    vector<int> initialState = {1,6,7,5,0,3,4,8,2}; 
    Problem p(initialState);
    p.initialUniformCost(); 
    p.initialHeursticQueue();
    p.initialManhattanQueue();

    Node node1 = p.uniformCost(); //Uniform Cost

    Node node2 = p.heurstic(); //Missing Tile

    Node node3 = p.manhattan(); //Manhattan Distance


    return 0;
}