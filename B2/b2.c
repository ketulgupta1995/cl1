#include <iostream>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cmath>
#include <omp.h>

using namespace std ;


int adj[20][20], cost[20][20], n ;
int dp[20][1 << 20], npow ;

int TSP(int start, int subset_mask) {
	int temp, result = INT_MAX ;
	if (dp[start][subset_mask] != -1)
		return dp[start][subset_mask] ;
	for (int i = 0; i < n; i++) {
		int mask = (npow - 1) - (1 << i) ;
		int masked = subset_mask & mask ;
		if (masked != subset_mask) {
			temp = adj[start][i] + TSP(i, masked);
			if (temp < result)
				result = temp ;
		}
			
	}
	return dp[start][subset_mask] = result ;
}

int main() {
	cout << "Enter the size of square matrix : " << endl ;
	cin >> n ;
	npow = (int)pow(2, n) ;
	cout << "Enter the elements of the adjacency matrix : " << endl ;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> adj[i][j] ;
			cost[i][j] = adj[i][j] ;
		}

	// call TSP for all sources	
	#pragma omp for		
	for (int i = 0; i < n; i++) {
		memset(dp, -1, sizeof(dp)) ; // clearing out the table
		for (int i = 0; i < n; i++)
			dp[i][0] = adj[i][0] ;
		cout << "Starting from source " << i << " minimum path distance is : " << TSP(i, npow - 2) << endl ; 
		// 2nd arguments takes care of bitmask
	}

}
