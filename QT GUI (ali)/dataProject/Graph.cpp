#include "Graph.h"
using namespace std;
Graph::Graph(){}

Graph::Graph(int numVertices,vector<User*>& users) : adjList(numVertices+1) {
    this->users=users;
}


void Graph::addEdge(User* u, User* v) {
    // Assuming that the User class has an 'id' attribute
    int userId = stoi(u->id);
    int followerId =stoi(v->id);

    // Adding the edge to the adjacency list
    adjList[userId].push_back(v);
}

void Graph::printAdjacencyList()  {
    for (int i = 1; i < adjList.size(); ++i) {
        cout << "User ID " << i << " -> ";
        for (const User* user : adjList[i]) {
            cout << user->id << " ";
        }
        cout << endl;
    }
}

void Graph::buildGraph(){

    // Adding edges based on followers
    for (int i = 0; i < users.size(); ++i) {
        User* currentUser = users[i];
        for (int j = 0; j < currentUser->followers.size(); ++j) {
            User* follower = getUserById(currentUser->followers[j]->id);
            this->addEdge(currentUser, follower);
        }
    }
}

User* Graph::getUserById(const string &userid)
{
    for(User *user:users){
        if(user->id == userid)
            return user;
    }
    return nullptr;
}

User* Graph::findMostInfluentialUser() {
    User* mostInfluentialUser = nullptr;
    int maxFollowers = 0;

    for (int i = 1; i < adjList.size(); ++i) {
        int followersCount = adjList[i].size();
        if (followersCount > maxFollowers) {
            mostInfluentialUser = getUserById(to_string(i));
            maxFollowers = followersCount;
        }
    }
    return mostInfluentialUser;
}


User* Graph::findMostActiveUser()
{
	vector<int> activity(adjList.size(), 0);
	for (int i = 0; i < adjList.size(); i++)
	{
		for (const User* follower : adjList[i])
        {
            int loc =stoi(follower->id);
            activity[loc]++;
        }
	}
    int max = activity[0];
    int max_loc = 0;

    for (int i = 1; i < activity.size(); i++)
    {
        if (activity[i] > max)
        {
            max = activity[i];
            max_loc = i;
        }
    }
    return getUserById(to_string(max_loc));
}


vector<User*> Graph::findMutualFollowers(const string& ID1, const string& ID2)
{
    User* user1 = getUserById(ID1);
    User* user2 = getUserById(ID2);
    vector<User*> mutual_followers;
    // Find mutual followers
    for (User* follower1 : adjList[stoi(user1->id)])
    {
        for (User* follower2 : adjList[stoi(user2->id)])
        {
            if (follower1->id == follower2->id)
            {
                mutual_followers.push_back(follower1);
            }
        }
    }
    return mutual_followers;
}


vector<User*> Graph::suggest_followers(const string&id)
{
    vector<bool> v(this->users.size()+1,false);
    User* user=getUserById(id);
    vector<User*> followers=adjList[stoi(user->id)];
    vector<User*> suggested_followers;

    v[stoi(id)]=true;
    for(User* follower:followers)
    {
       User* u=getUserById(follower->id);
       vector<User *> followers_of_followers=adjList[stoi(u->id)];
       for(User* f:followers_of_followers){
           if(!v[stoi(f->id)]){
            suggested_followers.push_back(f);
             v[stoi(f->id)]=true;
           }
       }
    }
	return suggested_followers;
}

string Graph:: get_mostInfluentialUser()
{
  User *user=findMostInfluentialUser();
  return "Most Influential User is : " + user->name + " ID: " + user->id;
}


string Graph:: get_mostActiveUser()
{
  User *user=findMostActiveUser();
  return "Most Active User is : " + user->name + " ID: " + user->id;
}

string Graph:: get_suggestedFollowers(const string& ID)
{
  vector<User*> users=suggest_followers(ID);
  string s;
  for(User* user:users)
  {
      s+="Suggested Follower: " + user->name + " ID : " + user->id +'\n';
  }
  if(s.empty())
    return "NO Suggested Followers";
  else
      return s;
}
string Graph:: get_mutualFollowers(const string& ID1,const string& ID2)
{
  vector<User*> users=findMutualFollowers(ID1,ID2);
  string s;
  for(User* user:users)
  {
      s+="Mutual Follower: " + user->name + " ID : " + user->id +'\n';
  }
  if(s.empty())
    return "NO Mutual Followers";
  else
      return s;
}


