#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
// Citations: Lecture Slide 2 & 3
// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
//https://www.geeksforgeeks.org/custom-comparator-in-priority_queue-in-cpp-stl/
//https://stackoverflow.com/questions/39759721/calculating-the-manhattan-distance-in-the-eight-puzzle



class Node
{
    public:
    vector<int> state;
    int depth;
    int emptyPos;
    int hn;

    Node()
    {
        depth = -1;
        emptyPos = -1;
        hn = 1000;
    }

    Node(const vector<int>& s)
    {
        depth = 0;

        for (int i = 0; i < s.size(); i++)
        {
            state.push_back(s[i]); 
        }
        findEmpty();
        missingTile();
    }

    Node& operator=(const Node& nody) 
{
    if (this != &nody)  
    {
        depth = nody.depth;
        emptyPos = nody.emptyPos;
        state = nody.state;
        hn = nody.hn;
    }
    return *this; 
}

    void missingTile()
    {
        int count = 0;
        vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        for(int i = 0; i < 9; i ++)
        {
            if(state[i] != goalState[i] && state[i] != 0)
            {
                count++;
            }
        }
        hn = count;
    }

    void manhattan()
    {
        int dis = 0;
        for(int i = 0; i < 9; i ++)
        {
            if(state[i] != 0)
            {
                int currRow = i/3;
                int currCol = i %3;

                int goalIndex = state[i] - 1;
                int goalRow = goalIndex / 3;
                int goalCol = goalIndex % 3;
                dis = dis + abs(currRow - goalRow) + abs(currCol - goalCol);
            }
        }
        hn = dis;
    }


    void findEmpty()
    {
        for (int i = 0; i < 9; i++)
        {
            if (state[i] == 0)
            {
                emptyPos = i;
                break;
            }
        }
    }

    bool moveRight()
    {
        if (emptyPos % 3 == 2)
        {
            return false;
        }

        return true;
    }

    bool moveLeft()
    {
        if (emptyPos % 3 == 0)
        {
            return false;
        }
        return true;
    }

    bool moveUp()
    {
        if (emptyPos < 3)
        {
            return false;
        }
        return true;
    }

    bool moveDown()
    {
        if (emptyPos > 5)
        {
            return false;
        }
        return true;
    }


};


class Compare {
    public:
       bool operator()(const Node& a, const Node& b) const {
           return (a.depth + a.hn) > (b.depth + b.hn);
       }
};


class Problem
{
    
    public:
    Node root;
    queue<Node> trackQ;
    queue<Node> tempQ;

    priority_queue<Node, vector<Node>, Compare> trackPrioQueue;
    priority_queue<Node, vector<Node>, Compare> tempPrioQueue;

    priority_queue<Node, vector<Node>, Compare> trackPrioManQueue;
    priority_queue<Node, vector<Node>, Compare> tempPrioManQueue;

    Problem() {};
    Problem(vector<int> &state)
    {
        root = Node(state);
    }


    Node uniformCost()
    {
        int expendedNode = 0;

        initialUniformCost();
        
        while(!tempQ.empty())
        {
            Node node = tempQ.front();
            tempQ.pop();
            expendedNode ++;
            
            if(isitGoal(node))
            {
                cout << "WE FOUND GOAL " << endl;
                cout << expendedNode << endl;
                return node;
            }

            
            
            if(node.moveRight())
            {
                Node tempnode = node;
                

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos + 1]);
                tempnode.emptyPos += 1;
            
                tempnode.depth ++;
                if(!checkExist(tempnode))
                {
                    tempQ.push(tempnode);
                    trackQ.push(tempnode);
                }
            }
            
            
            if(node.moveLeft())
            {
                Node tempnode = node;
                

                
                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos - 1]);
                tempnode.emptyPos -= 1;

                tempnode.depth ++;
                if(!checkExist(tempnode))
                {
                    tempQ.push(tempnode);
                    trackQ.push(tempnode);
                }
            }

            if(node.moveUp())
            {
                Node tempnode = node;
                

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos - 3]);
                tempnode.emptyPos -= 3;

                tempnode.depth ++;
                if(!checkExist(tempnode))
                {
                    tempQ.push(tempnode);
                    trackQ.push(tempnode);
                }
            }
            if(node.moveDown())
            {
                Node tempnode = node;
                

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos + 3]);
                tempnode.emptyPos += 3;
                tempnode.depth ++;

                if(!checkExist(tempnode))
                {
                    tempQ.push(tempnode);
                    trackQ.push(tempnode);
                }
            }
            
        }
        return Node();
        cout << expendedNode << endl;
    }

    Node heurstic()
    {
        int expendedNode = 0;

        initialHeursticQueue();

        while(!tempPrioQueue.empty())
        {
            
            Node node = tempPrioQueue.top();
            tempPrioQueue.pop();
            expendedNode ++;
            if(isitGoal(node))
            {
                cout << "WE FOUND GOAL " << endl;
                cout << expendedNode << endl;
                return node;

            }

            
            
            if(node.moveRight())
            {
                Node tempnode = node;
                tempnode.depth ++;

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos + 1]);
                tempnode.emptyPos += 1;
                tempnode.missingTile();  
                if(!checkHeursticExist(tempnode))
                {
                    tempPrioQueue.push(tempnode);
                    trackPrioQueue.push(tempnode);
                }
            }
            
            
            if(node.moveLeft())
            {
                Node tempnode = node;
                tempnode.depth ++;

                
                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos - 1]);
                tempnode.emptyPos -= 1;
                tempnode.missingTile(); 
                if(!checkHeursticExist(tempnode))
                {
                    tempPrioQueue.push(tempnode);
                    trackPrioQueue.push(tempnode);
                }
            }

            if(node.moveUp())
            {
                Node tempnode = node;
                tempnode.depth ++;

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos - 3]);
                tempnode.emptyPos -= 3;
                tempnode.missingTile();  
                if(!checkHeursticExist(tempnode))
                {
                    tempPrioQueue.push(tempnode);
                    trackPrioQueue.push(tempnode);
                }
            }
            if(node.moveDown())
            {
                Node tempnode = node;
                tempnode.depth ++;

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos + 3]);
                tempnode.emptyPos += 3;
                tempnode.missingTile();  
                if(!checkHeursticExist(tempnode))
                {
                    tempPrioQueue.push(tempnode);
                    trackPrioQueue.push(tempnode);
                }
            }

        }
        cout << expendedNode << endl;
        return Node();
        
    }

    Node manhattan()
    {
        int expendedNode = 0;

        initialManhattanQueue();

        while(!tempPrioManQueue.empty())
        {
            
            Node node = tempPrioManQueue.top();
            tempPrioManQueue.pop();
            expendedNode ++;
            if(isitGoal(node))
            {
                cout << "WE FOUND GOAL " << endl;
                cout << expendedNode << endl;
                return node;
            }

            
            
            if(node.moveRight())
            {
                Node tempnode = node;
                tempnode.depth ++;

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos + 1]);
                tempnode.emptyPos += 1;
                tempnode.manhattan();  
                if(!checkManhattanExist(tempnode))
                {
                    tempPrioManQueue.push(tempnode);
                    trackPrioManQueue.push(tempnode);
                }
            }
            
            
            if(node.moveLeft())
            {
                Node tempnode = node;
                tempnode.depth ++;

                
                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos - 1]);
                tempnode.emptyPos -= 1;
                tempnode.manhattan(); 
                if(!checkManhattanExist(tempnode))
                {
                    tempPrioManQueue.push(tempnode);
                    trackPrioManQueue.push(tempnode);
                }
            }

            if(node.moveUp())
            {
                Node tempnode = node;
                tempnode.depth ++;

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos - 3]);
                tempnode.emptyPos -= 3;
                tempnode.manhattan();  
                if(!checkManhattanExist(tempnode))
                {
                    tempPrioManQueue.push(tempnode);
                    trackPrioManQueue.push(tempnode);
                }
            }
            if(node.moveDown())
            {
                Node tempnode = node;
                tempnode.depth ++;

                swap(tempnode.state[tempnode.emptyPos], tempnode.state[tempnode.emptyPos + 3]);
                tempnode.emptyPos += 3;
                tempnode.manhattan();  
                if(!checkManhattanExist(tempnode))
                {
                    tempPrioManQueue.push(tempnode);
                    trackPrioManQueue.push(tempnode);
                }
            }

        }
        cout << expendedNode << endl;
        return Node();
        
    }

    void initialUniformCost()
    {
        trackQ.push(root);
        tempQ.push(root);
    };
    
    void initialHeursticQueue()
    {
       trackPrioQueue.push(root);
       tempPrioQueue.push(root);
    }

    void initialManhattanQueue()
    {
        root.manhattan();
        trackPrioManQueue.push(root);
        tempPrioManQueue.push(root);
    }

    bool checkExist(Node node)
    {
        queue<Node> tempQueue = trackQ;

        while(!tempQueue.empty())
        {
            if(tempQueue.front().state == node.state)
            {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }
    
    bool checkHeursticExist(Node node)
    {
        priority_queue<Node,vector<Node>, Compare> tempQueue = trackPrioQueue;

        while(!tempQueue.empty())
        {
            if(tempQueue.top().state == node.state)
            {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }

    bool checkManhattanExist(Node node)
    {
        priority_queue<Node,vector<Node>, Compare> tempQueue = trackPrioManQueue;

        while(!tempQueue.empty())
        {
            if(tempQueue.top().state == node.state)
            {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }
    

    bool isitGoal(Node x)
    {
        vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        for(int i = 0; i < x.state.size(); i ++)
        {
            if(x.state[i] != goalState[i])
            {
                return false;
            }
        }
        return true;
    }

};


#endif