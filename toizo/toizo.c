#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

struct node {
	int x;
	int y;
};

struct agent {
	struct node begin;
	struct node end;
};

int size_x, size_y, number_of_agents;
struct agent* agents;
char** graph;
struct node adds[5];
char** solution;
int counter = 0;

char findPath(int agent, struct node currentPoint) {
	if(currentPoint.x == agents[agent].end.x
			&& currentPoint.y == agents[agent].end.y) {
		if(agent == 0)
			return 1;

		int nextAgent = agent - 1;
		graph[agents[nextAgent].end.y][agents[nextAgent].end.x] = 1;

		if(findPath(nextAgent, agents[nextAgent].begin))
			return 1;
		
		graph[agents[nextAgent].end.y][agents[nextAgent].end.x] = 0;
	} else {
		struct node newPoint;
		int dir;
		for(dir = 1; dir < 5; ++dir) {
			newPoint.x = currentPoint.x + adds[dir].x;
			newPoint.y = currentPoint.y + adds[dir].y;
			
			if(newPoint.x < 0 
					|| newPoint.x >= size_x 
					|| newPoint.y < 0 
					|| newPoint.y >= size_y)
				continue;

			if(!graph[newPoint.y][newPoint.x])
				continue;

			graph[newPoint.y][newPoint.x] = 0;
			solution[currentPoint.y][currentPoint.x] = dir;
			++counter;

			if(findPath(agent, newPoint))
				return 1;

			graph[newPoint.y][newPoint.x] = 1;
			solution[currentPoint.y][currentPoint.x] = 0;
			--counter;
		}
	}

	return 0;
}

int main(int argc, char** argv) {
	scanf("%d %d", &size_x, &size_y);
	scanf("%d", &number_of_agents);

	agents = malloc(number_of_agents * sizeof(struct agent));

	int i, j;
	solution = malloc(size_y * sizeof(char*));
	for(i = 0; i < size_y; ++i) {
		solution[i] = malloc(size_x * sizeof(char));
		memset(solution[i], 0, size_x * sizeof(char));
	}

	graph = malloc(size_y * sizeof(char*));
	for(i = 0; i < size_y; ++i) {
		graph[i] = malloc(size_x * sizeof(char));
		memset(graph[i], 1, size_x * sizeof(char));
	}

	adds[1].x = -1;
	adds[1].y = 0;
	adds[2].x = 1;
	adds[2].y = 0;
	adds[3].x = 0;
	adds[3].y = -1;
	adds[4].x = 0;
	adds[4].y = 1;


	int tmp_begin_x, tmp_begin_y, tmp_end_x, tmp_end_y;
	for(i = 0; i < number_of_agents; ++i) {
		scanf("%d %d %d %d",
				&tmp_begin_x,
				&tmp_begin_y,
				&tmp_end_x,
				&tmp_end_y);
		agents[i].begin.x = tmp_begin_x - 1;
		agents[i].begin.y = tmp_begin_y - 1;
		agents[i].end.x = tmp_end_x - 1;
		agents[i].end.y = tmp_end_y - 1;

		graph[agents[i].begin.y][agents[i].begin.x] = 0;	
		graph[agents[i].end.y][agents[i].end.x] = 0;	
	}

	int lastAgent = number_of_agents - 1;
	graph[agents[lastAgent].end.y][agents[lastAgent].end.x] = 1;

	char solutionFound = findPath(lastAgent, 
			agents[lastAgent].begin);
	
	if(solutionFound) {
		printf("%d\n", counter);
		for(i = 0; i < size_y; ++i)
			for(j = 0; j < size_x; ++j)
				if(solution[i][j])
					printf("%d %d %d %d\n", j + 1, i + 1, 
							adds[(int)solution[i][j]].x, adds[(int)solution[i][j]].y);
	}

	for(i = 0; i < size_y; ++i) {
		free(solution[i]);
		free(graph[i]);
	}
	free(solution);
	free(graph);
	free(agents);

	return 0;
}
