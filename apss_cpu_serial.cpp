#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <list>
#include <unordered_map>
//#include "kernel.cpp"
using namespace std;

typedef pair<int, list<int>> pili;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

vector < vector <int> > V;
vector < pair<int, list<int>> > I;
const int N = 200;

vector<int> global_max_weight(200,0);
vector<int> max_weight(100, 0);
vector<vector<int>> Matching;
int t = 12;

/*
//Comparator Function for Bayardo Omega Permutation
bool bomega(vector<int> f, vector<int> l)
{ return (*max_element(f.begin(), f.end()) < *max_element(l.begin(), l.end())); }
void bayardo_omega()
{
/* Sorting Vectors in V based on
Maximum Value in each Vector
sort(V.begin(), V.end(), bomega);
}

bool ssize(int f)
{ return (f > 0); }
bool somega(vector<int> f, vector<int> l)
{ return (count_if(f.begin(), f.end(), ssize) < count_if(l.begin, l.end, ssize)); }
void sarawagi_omega()
{
/* Sorting Vectors in V based on
Number of Non-Zero components
in each Vector
sort(V.begin(), V.end(), somega);
}



//Comparator Function for Pi Permutation
bool bpi(pair<int, vector<int>> f, pair<int, vector<int>> l)
{ return (f.second.size() < l.second.size()); }
void bayardo_pi()
{
/* Sort Inverted Index Map I based
on Dimension Density
sort(I.begin(), I.end(), bpi);
}

int partition_bpi(int p, int r)
{
int t = p + (rand() % (r - p + 1));
pili temp = I[r];
I[r] = I[t];
I[t] = temp;

int i = p;
for (int j = p; j < r; ++j)
if (I[j].second.size() <= I[r].second.size())
{
temp = I[i];
I[i] = I[j];
I[j] = temp;

++i;
}

temp = I[i];
I[i] = I[r];
I[r] = temp;

return i;
}

void quick_sort_bpi(int p, int r)
{
if (p >= r)
return;

int q = partition_bpi(p, r);
quick_sort_bpi(p, q - 1);
quick_sort_bpi(q + 1, r);
}*/

int partition_bpi(int p, int r)
{
	int t = p + (rand() % (r - p + 1));
	pili temp(I[r]);
	swap(I[r], I[t]);
	swap(I[t], temp);

	int i = p;
	for (int j = p; j < r; ++j)
		if (I[j].second.size() >= I[r].second.size())
		{
			swap(temp, I[i]);
			swap(I[i], I[j]);
			swap(I[j], temp);

			++i;
		}

	swap(temp, I[i]);
	swap(I[i], I[r]);
	swap(I[r], temp);

	return i;
}
void quick_sort_bpi(int p, int r)
{
	if (p >= r)
		return;

	int q = partition_bpi(p, r);
	quick_sort_bpi(p, q - 1);
	quick_sort_bpi(q + 1, r);
}

bool ssize(int f)
{
	return (f > 0);
}
int partition_sarawagi_omega(int p, int r)
{
	int t = p + (rand() % (r - p + 1));
	vi temp(V[r]);
	swap(V[r], V[t]);
	swap(V[t], temp);
	int i = p;
	for (int j = p; j < r; ++j)
		if (count_if(V[j].begin(), V[j].end(), ssize) <= count_if(V[r].begin(), V[r].end(), ssize))
		{
			swap(temp, V[i]);
			swap(V[i], V[j]);
			swap(V[j], temp);

			++i;
		}

	swap(temp, V[i]);
	swap(V[i], V[r]);
	swap(V[r], temp);

	return i;
}
void quick_sort_sarawagi_omega(int p, int r)
{
	if (p >= r)
		return;

	int q = partition_sarawagi_omega(p, r);
	quick_sort_sarawagi_omega(p, q - 1);
	quick_sort_sarawagi_omega(q + 1, r);
}

int partition_bomega(int p, int r)
{
	int t = p + (rand() % (r - p + 1));
	vi temp(V[r]);
	swap(V[r], V[t]);
	swap(V[t], temp);
	int i = p;
	for (int j = p; j < r; ++j)
		if (max_weight[j] <= max_weight[r])
		{
			swap(temp, V[i]);
			swap(V[i], V[j]);
			swap(V[j], temp);

			++i;
		}

	swap(temp, V[i]);
	swap(V[i], V[r]);
	swap(V[r], temp);

	return i;
}
void quick_sort_bomega(int p, int r)
{
	if (p >= r)
		return;

	int q = partition_bomega(p, r);
	quick_sort_bomega(p, q - 1);
	quick_sort_bomega(q + 1, r);
}

void preprocess()
{
	/* Assume a list of Vectors : V[]
	in an N-Dimensional Space, we
	build an Inverted Index Map I,
	which contains N pair of
	elements, where the first element
	is the dimension, and the second
	is a vector which contain indices
	of the vectors that have a
	projection in that dimension. */

	list<int> v[N];
	int x, j;
	for (x = 0; x < V.size(); ++x)
	{
		//#pragma omp parallel for shared(x,V,I)			//All the Dimensions can be checked for in Parallel
		for (j = 0; j < N; ++j)
			if (V[x][j] > 0)
				v[j].push_back(x);
	}

	for (j = 0; j < N; ++j)
		I.push_back(make_pair(j, v[j]));

	quick_sort_bomega(0, 99);
	//quick_sort_sarawagi_omega(0, 99);

	quick_sort_bpi(0, 199);
}


/*vector < vector <int> > V;
vector < pair<int, list<int>> > I;
const int N = 200;
*/

//We need to know the exact numbr of Vectors andd Dimensions beforehand

void get_max_weight()
{
    for(int p=0;p<100;++p)
    {
		max_weight[p] = *max_element(V[p].begin(),V[p].end());
    }
}

int find_sum(int i)
{
    int sum=0;
    for(int j=0;j<N;++j)
        sum+=V[i][j];
    return sum;
}

int find_dot(int i,int j)
{
    int dot=0;
	for (int k = 0; k < N; ++k)
		dot += V[i][k] * V[j][k];
    return dot;

}

void get_global_max_weight()
{
    for(int i = 0; i < N; ++i)
    {
		if (I[i].second.size() == 0)
			break;

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
		
        int remMaxScore = 0;
        int minSize = (t/max_weight[x]) * (t/max_weight[x]);
        for(int i = 0; i < N; ++i)
            remMaxScore += V[x][i] * global_max_weight[i];

        for(int i = N-1; i > -1; --i)
        {
            //Check if x is in this List
            if(V[x][I[i].first] == 0)
                continue;

			bool er = false;
            for(list<int>::iterator it = I[i].second.begin(); it != I[i].second.end(); ) // Iteratively remove (y,y[i]) from Ii
            {
				if (*it == x)
				{
					++it;
					continue;
				}

				er = false;
				if (count_if(V[*it].begin(), V[*it].end(), ssize) < minSize)
				{
					it = I[i].second.erase(it);
					er = true;
				}

				if (!er) ++it;
            }

            for(list<int>::iterator it = I[i].second.begin(); it != I[i].second.end(); ++it)
                if(partScoreMap[i] > 0 || remMaxScore >= t)
                    partScoreMap[i] += V[x][I[i].first] * V[*it][I[i].first];

            remMaxScore -= global_max_weight[I[i].first] * V[x][I[i].first];
        }

        for(int i = 0; i < V.size(); ++i)
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

void readFunc()
{
	vector<int> col;
	ifstream file("fffff.txt");
	if (file.is_open()) {
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 200; ++j) {
				int s;
				file >> s;
				col.push_back(s);
			}
			V.push_back(col);
			col.clear();
		}
	}
}

int main()
{
	readFunc();
	get_max_weight();

	preprocess();
	matching();

	for (vvi::iterator it = Matching.begin(); it != Matching.end(); ++it)
		cout << (*it)[0] << " . " << (*it)[1] << " = " << (*it)[2] << endl;

	cout << "\n\n Number of Matching Pairs : " << Matching.size() << endl;

	/*for (int j = 0; j < N; ++j)
	{
		for (list<int>::iterator it = I[j].second.begin(); it != I[j].second.end(); ++it)
			cout << (*it) << ' ';

		cout << " " << j << endl;
	}*/
	system("pause");
}