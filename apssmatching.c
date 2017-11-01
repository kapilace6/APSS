#include<stdio.h>
#include<algorithm>
#include<vector>
#include <unordered_map>
#include "kernel.cu"

vector<int> global_max_weight;
vector<int> max_weight;
vector<vector<int>> Matching;
int t=1;

void get_max_weight()
{
    for(int i=0;i<V.size();++i)
    {
        max_weight[i]=*max_element(V[i].begin(),V[i].end());
    }
}

int find_sum(int i)
{
    int sum=0;
    for(int j=0;j<n;++j)
        sum+=V[i][j];
    return sum;
}

int find_dot(int i,int j)
{
    int dot=0;
    for(int k=0;k<n;++k)
        dot+=V[i][k]*V[j][k]
    return dot;

}

void get_global_max_weight()
{
    for(int i = 0; i < N; ++i)
    {
        global_max_weight[I[i].first] = *max_element(I[i].second.begin(), I[i].second.end());
    }
}

void matching()
{
    get_global_max_weight();


    for(int x = 0; x < V.size(); ++x)         //Vector x in V
    {
        unordered_map<int, int> partScoreMap;
        for(int a = 0; a < V.size(); ++a)           //Can be Optimised
            partScoreMap[a] = 0;

        int remMaxScore = 1;
        int minSize = (t/max_weight[x]) * (t/max_weight[x]);
        for(int i = 0; i < N; ++i)
            remMaxScore = V[x][i] * global_max_weight[i];

        for(int i = N-1; i > -1; --i)
        {
            //Check if x is in this List
            if(V[x][I[i].first] == 0)
                continue;

            for(list<int>::iterator it = I[i].second.begin(); it != I[i].second.end(); ++it) // Iteratively remove (y,y[i]) from Ii
            {
               if(*it == x)
                    continue;

                if(count_if(V[*it].begin(), V[*it].end(), ssize) < minSize)
                    it = erase(it);
            }

            for(list<int>::iterator it = I[i].second.begin(); it != I[i].second.end(); ++it)
                if(partScoreMap[y] > 0 || remMaxScore >= t)
                    partScoreMap[y] += V[x][I[i].first] * V[*it][I[i].first];

            remMaxScore -= global_max_weight[I[i].first] * V[x][I[i].first];
        }

        for(i = 0;i < V.size(); ++i)
        {
            if(i == x || partScoreMap[i] == 0) continue;
            if(partScoreMap[i] + min(find_sum(i)*max_weight[x], find_sum(x)*max_weight[i]) >= t)
            {
                int s = partScoreMap[i] + find_dot(x,i);
                if(s >= t)
                {
                    vector<int> trip;
                    trip.push_back(x);
                    trip.push_back(i);
                    trip.push_back(s);

                    Matching.push_back(trip);
                }
            }
        }
    }
}

