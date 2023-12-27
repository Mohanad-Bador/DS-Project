#include<iostream>
#include<vector>
#include "Functions.h"
#include "XMLParser.h"
#include "User.h"
#include "Graph.h"
using namespace std;
//Graph graph;

int main()
{
    XMLParser parser;
    vector<User*> users =parser.parseXML("sample.xml");
    for(int i=0;i<users.size();i++)
    {
        users[i]->printUser();
    }

    Graph userGraph(users.size(),users);

    userGraph.buildGraph();

    userGraph.printAdjacencyList();

    userGraph.findMostInfluentialUser();

    userGraph.findMostActiveUser();

    userGraph.findMutualFollowers("2","3");

    userGraph.suggest_followers("2");

    for(int i=0;i<users.size();i++)
    {
        users[i]->postSearchByWord("solar");
    }

  return 0;
}