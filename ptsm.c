#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <string.h>

#define MAX_C 12
#define MAX_INT 2147483647

int x = 0, t = 0;
int m[MAX_C][MAX_C] = {};

int min_path_length = MAX_INT;
int min_route[MAX_C] = {};

void visit(int prev, int cur, int num_visited, int visited_cities[], int cur_route[], int cur_path_length)
{
	// updates path
	cur_path_length += m[prev][cur];
	cur_route[num_visited] = cur;
	visited_cities[cur] = 1;
	num_visited++;

	// printf("%d %d %d %d\n", prev, cur, num_visited, cur_path_length);

	int i;
	// if reach end of path
	if (num_visited == x)
	{
		if (cur_path_length < min_path_length)
		{
			min_path_length = cur_path_length;
			for (i = 0 ; i < x ; i++)
			{
				min_route[i] = cur_route[i];
			}
		}
		return;
	}

	for (i = 1 ; i < x ; i++)
	{
		if (visited_cities[i] == 0)
		{
			visit(cur, i, num_visited, visited_cities, cur_route, cur_path_length);
			visited_cities[i] = 0;
			cur_route[num_visited] = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	x = atoi(argv[1]);
	t = atoi(argv[2]);

	FILE* fptr;
	char filename[100];
    strcat(filename, argv[3]);

	fptr = fopen(filename, "r");
	if (!fptr)
	{
		printf("Failed to open file %s\n", filename);
		exit(1);
	}

	int i, j;
	for (i = 0 ; i < x ; i++)
	{
		for (j = 0 ; j < x ; j++)
		{
			fscanf(fptr,"%d ",&m[i][j]);
		}
	}
	fclose(fptr);

	int num_visited = 1, visited_cities[MAX_C] = {}, cur_route[MAX_C] = {}, cur_path_length = 0;
	visited_cities[0] = 1;
	cur_route[0] = 0;

	#pragma omp parallel for
	for (i = 1 ; i < x ; i++)
	{
		visit(0, i, num_visited, visited_cities, cur_route, cur_path_length);
		visited_cities[i] = 0;
		cur_route[num_visited] = 0;
	}
	
	printf("Best path: %d", min_route[0]);
	for (i = 1 ; i < x ; i++)
	{
		printf(" %d", min_route[i]);
	}
	printf("\n");

	printf("Distance: %d\n", min_path_length);

	return 0;
}