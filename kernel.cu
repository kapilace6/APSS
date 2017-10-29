
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"

#include <stdio.h>
#include <algorithm>
#include <vector>
//#include <omp.h>
//#include <cuda.h>
using namespace std;
	
vector < vector <int> > V;
vector < pair<int, vector<int>> > I;
const int N = 10;

//Comparator Function for Bayardo Omega Permutation
bool bomega(vector<int> f, vector<int> l)
{ return (*max_element(f.begin(), f.end()) < *max_element(l.begin(), l.end())); }
void bayardo_omega()
{
	/* Sorting Vectors in V based on 
	   Maximum Value in each Vector */
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
	   in each Vector */
	sort(V.begin(), V.end(), somega);
}

//Comparator Function for Pi Permutation
bool bpi(pair<int, vector<int>> f, pair<int, vector<int>> l)
{ return (f.second.size() < l.second.size()); }
void bayardo_pi()
{
	/* Sort Inverted Index Map I based
	   on Dimension Density */
	sort(I.begin(), I.end(), bpi);
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

	vector<int> v[N];
	int i, j;
	for (i = 0; i < V.size(); ++i)
	{
		//#pragma omp parallel for shared(i,V,I)			//All the Dimensions can be checked for in Parallel
		for (j = 0; j < N; ++j)
			if (V[i][j] > 0)
				v[j].push_back(i);

		I.push_back(make_pair(j, v[j]));
	}

	bayardo_omega();
	//sarawagi_omega();

	bayardo_pi();
}