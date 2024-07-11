/*
 * File: ambulance_dispatch.cpp
 * Version: 1.0
 * ---------------------------------------------------------------
 * This file implements the problem about how to dispatch ambulance
 * in a city with some requires. First, it should be the fastest
 * way. Second, when more than one center are the fastest, the 
 * ambulances should also be more. Third, when still cannot find
 * the unique way, the streets that should be go through also need
 * be taken into consideration.
 */

#include <stdio.h>
#define MAX 32767

/*
 * Global array: map, hos, car
 * -----------------------------
 * These arrays are used to record the information about the city.
 * map is used to record two places that can be connected by a
 * street. hos is used to record the paths and costs when we set
 * from one ambulance dispatch center to all the other places in 
 * the city. And car is used to record the number of cars in each 
 * ambulance dispatch center.
 */
 
static int map[2000][2000],hos[50][2000],car[20];

/*
 * Global variable: ns, na, m, k
 * --------------------------------
 * ns is used to record the number of the pick-up spots. na is used
 * to record the number of the ambulance dispatch centers. m is used
 * to record the number of streets connecting the spots and the centers.
 * k is used to record the number of emergency calls.
 */ 
 
static int ns,na,m,k;

/*
 * Function: out
 * Usage: out(center, spot);
 * --------------------------
 * This function give the shortest path from one pick-up spot to one
 * ambulance dispatch center and print all the nodes in the path from 
 * the ambulance dispatch center to the spot with its cost.
 */

void out(int center, int spot)
{
	static int re_path[2000];
	int i,j = 0;
	re_path[0] = spot;
	
	// stop until find the ambulance dispatch center
	while(hos[center][spot]!=0){
		re_path[++j] = hos[center+1][spot];
		spot = re_path[j];
	}
	car[center/3+1]--; // minus one car for it has been dispatched
	
	// output all the nodes in the way and its total cost
	printf("A-%d",center/3+1);
	for (i=j-1;i>=0;i--){
		printf(" %d",re_path[i]-10);
	}
	printf("\n");
	printf("%d\n",hos[center][re_path[0]]);
}

int main()
{
	int i,j,t;
	scanf("%d %d",&ns,&na);
	for (i=1;i<=na;i++) scanf("%d",&car[i]);
	scanf("%d",&m);
	
	/*
	 * Use a matrix to record all the connections in the city between
	 * ambulance dispatch centers and pick-up spots. For those have
	 * connections, the value would be turned from zero to the cost
	 * from the place to another.
	 * The beginning 10 rows are used to record the ambulance dispatch
	 * center so they are record in map[1-10][] and map[][1-10]. And the
	 * following are used to record the pick-up spots.
	 */
	for (i=0;i<m;i++){
		char dot1[10],dot2[10];
		int d1,d2,cost;
		scanf("%s %s %d",dot1,dot2,&cost);
		if (dot1[0]=='A') d1 = dot1[2]-'0';
		else d1 = dot1[0]-'0'+10;
		if (dot2[0]=='A') d2 = dot2[2]-'0';
		else d2 = dot2[0]-'0'+10;
		map[d1][d2] = map[d2][d1] = cost;
	}
	
	/*
	 * Use a two-dimension array to record cost, path and known information
	 * to do the Dijkstra's Algorithms. So first initialize them. The first
	 * line is infinity except the source and used to record the costs from
	 * the source to this place, while the second and the third lines are 
	 * all zero and used to record the precursor and whether it has been 
	 * visited seperately.
	 */
	for (i=0;i<3*na;i+=3){
		for (j=1;j<=10+ns;j++) {
			hos[i][j] = MAX;
			if (j==i/3+1) hos[i][j] = 0;
		}
	}
	
	for (i=0;i<3*na;i+=3){ // for each ambulance dispatch center, do one step
		int v;
		for (t=0;t<ns+na;t++){ // go through all the places in the city
			int min,x;
			min = MAX;
			// find smallest unknown distance vertex
			for (x=1;x<=10+ns;x++){
				if (hos[i+2][x]==0&&min>hos[i][x]){
					min = hos[i][x];
					v = x;
				}
			}
			hos[i+2][v] = 1; // tell that this vertex has been visited
			
			// find the smallest costs of each node
			for (j=1;j<=10+ns;j++){ // each node adjacent to v
				if (map[v][j]!=0){
					if (hos[i+2][j]==0){
						if (hos[i][v]+map[v][j] < hos[i][j]){
							hos[i][j] = hos[i][v]+map[v][j];
							hos[i+1][j] = v;
						}
					}
				}
			}	
		}
	}
	
	scanf("%d",&k);
	for (i=1;i<=k;i++){ // for each emergency call, do one step
		int spot,min,count=0,index,samecar=0,indexcar,temp,minstreet,indexstreet;
		static int flag[11],flagcar[11],street[11];
		scanf("%d",&spot);
		min = MAX;
		// find the smallest costs from each ambulance dispatch center to the spot
		for (j=0;j<3*na;j+=3){
			if (min>hos[j][10+spot]&&car[j/3+1]!=0) min = hos[j][10+spot];
		}
		// examine whether more than one centers can arrive the spot with this cost
		for (j=0;j<3*na;j+=3){
			if (min==hos[j][10+spot]&&car[j/3+1]!=0){
				count++;
				flag[j/3+1] = 1;
				index = j/3+1;
			}
		}
		
		// case1: no center has ambulance to give a hand
		if (count==0) printf("All Busy\n");
		// case2: only one center can give the smallest cost
		else if (count==1) out(3*index-3,10+spot);
		// case3: more than one centers can give the smallest cost
		else {
			// find the maximum number of available cars in each smallest-costed center
			for (j=1;j<=na;j++){
				if (flag[j]==1&&car[j]>car[index]) index = j;
			}
			// examine whether more than one centers have the maximum number of cars
			for (j=1;j<=na;j++){
				if (flag[j]==1&&car[j]==car[index]){
					samecar++;
					flagcar[j] = 1;
					indexcar = j;
				}
			}
			// case3-1: no center has ambulance to give a hand
			if (samecar==0) printf("All Busy\n");
			// case3-2: only one center can give the maximum number of cars
			else if (samecar==1) out(3*indexcar-3,10+spot);
			// case3-3: more than one centers can give the maximum number of cars
			else{
				// find the strees in the path from one center to one spot
				for (j=1;j<=na;j++){
					if (flagcar[j]==1){
						temp = 10+spot;
					    while(hos[3*j-3+1][temp]!=0){
						    street[j]++;
						    temp = hos[3*j-2][temp];
					    }
					}
				}
				minstreet = na+ns;
				// find the minimum number of streets in the path and output it
				for (j=1;j<=na;j++){
					if (flagcar[j]==1&&minstreet>street[j]){
						minstreet = street[j];
						indexstreet = j;
					}
				}
				out(3*indexstreet-3,10+spot);
			}
		}
	}
	return 0;
}
