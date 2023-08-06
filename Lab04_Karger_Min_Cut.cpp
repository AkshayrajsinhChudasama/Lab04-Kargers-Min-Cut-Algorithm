
#include <iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;


int find(int x,vector<int>& parent){
    if(x == parent[x]){
        return parent[x];
    }else{
        parent[x] = find(parent[x],parent);
        return parent[x];
    }
}

void do_union(int x,int y,vector<int>& parent){
    int u = find(x,parent);
    int v = find(y,parent);
    if(u!=v){
        parent[u] = v;
    }
}
vector<vector<int>> count_edges(vector<vector<int>>& graph){
    vector<vector<int>>edge;
    int n = graph.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if(graph[i][j] == 1){
                edge.push_back({i,j});
            }
        }
    }
    return edge;
}

int find_kargers_min_cut(vector<vector<int>>& graph){
    vector<vector<int>>edge = count_edges(graph);
    int no_of_edges = edge.size();
    int no_of_verteices = graph.size();
    int res = INT_MAX;
    int k = 100*no_of_verteices*no_of_verteices;
    int itr_no = 0;
    while(k--){
        itr_no++;
        // cout<<"Iteration no : "<<itr_no<<endl;
        vector<int>parent(no_of_edges);
        for (int i = 0; i < no_of_edges; i++) {
            parent[i] = i;
        }
        int n = no_of_edges;
        int m = no_of_verteices;
        int min_on_this_iteration=0;
        while(m > 2){
            int ind = rand()%no_of_edges;
            int u = edge[ind][0];
            int v = edge[ind][1];
            if(find(u,parent) != find(v,parent)){
                
                do_union(u,v,parent);
                m--;
            }
        }
        for (int i = 0; i < no_of_edges; i++) {
            int u = edge[i][0];
            int v = edge[i][1];
            if(find(u,parent) != find(v,parent)){
                min_on_this_iteration++;
            }
        }
        
        res = min(res,min_on_this_iteration);
    }
    return res;
}


int main()
{
    srand(time(0));
    vector<vector<int>>graph =
    {
        {0,1,1,1},
        {1,0,0,1},
        {1,0,0,1},
        {1,1,1,0}
    };
    vector<vector<int>>graph2 =
    {
        {0,1,0,0,1},
        {1,0,1,1,1},
        {0,1,0,1,0},
        {0,1,1,0,1},
        {1,1,0,1,0}
    };
    vector<vector<int>>graph3 =
    {
        {0,1,1,1},
        {1,0,1,0},
        {1,1,0,0},
        {1,0,0,0}
    };
    vector<vector<int>>graph4 =
    {
    //   0 1 2 3 4 5
        {0,1,0,0,1,1},
        {1,0,1,1,0,0},
        {0,1,0,1,0,0},
        {0,1,1,0,1,0},
        {1,0,0,1,0,1},
        {1,0,0,0,1,0}
    };

    cout<<find_kargers_min_cut(graph)<<endl;//for this answer should be 2
    cout<<find_kargers_min_cut(graph2)<<endl;//for this answer should be 2
    cout<<find_kargers_min_cut(graph3)<<endl;//for this answer should be 1
    cout<<find_kargers_min_cut(graph4)<<endl;//for this answer should be 2
    return 0;
}
