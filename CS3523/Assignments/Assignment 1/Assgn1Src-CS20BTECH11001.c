#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define MAX_LINE_LENGTH 10000

bool useFileReading = false;

typedef struct parameters
{
    unsigned p, r, index;
} parameters;

typedef struct point
{
    int x, y;
} point;

point points[100000];
point sourcePoint;

point nearestPoints[16];
double minDistances[16];

void findNearest(void *params)
{
    // printf("%d %d\n", ((parameters *)params)->p, ((parameters *)params)->r);
    unsigned p = ((parameters *)params)->p;
    unsigned r = ((parameters *)params)->r;
    unsigned index = ((parameters *)params)->index;

    if (p == r)
    {
        return;
    }
    for (int i = p; i <= r; i++)
    {
        double distance = sqrt(pow(points[i].x - sourcePoint.x, 2) + pow(points[i].y - sourcePoint.y, 2));
        if (distance < minDistances[index])
        {
            minDistances[index] = distance;
            nearestPoints[index].x = points[i].x;
            nearestPoints[index].y = points[i].y;
        }
    }
}

void randomizePoints(point points[], unsigned numberOfPoints)
{
    for (unsigned i = 0; i < numberOfPoints; i++)
    {
        points[i].x = (rand() % 2 == 0) ? rand() % (numberOfPoints) : -(rand() % (numberOfPoints));
        points[i].y = (rand() % 2 == 0) ? rand() % (numberOfPoints) : -(rand() % (numberOfPoints));
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    unsigned numberOfPoints;
    unsigned N;

    if (useFileReading)
    {
        FILE *fp = fopen("input.txt", "r");
        if (fp == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        else
        {
            fscanf(fp, "%u", &N);

            fseek(fp, 1, SEEK_CUR); // Sets the file position to the current position plus offset(1 here).
            char line[MAX_LINE_LENGTH];
            fgets(line, MAX_LINE_LENGTH, fp);
            sscanf(line, "(%d,%d)", &sourcePoint.x, &sourcePoint.y);
            fscanf(fp, "%u", &numberOfPoints);
            fseek(fp, 1, SEEK_CUR);
            fgets(line, MAX_LINE_LENGTH, fp);
            for (int i = 0; i < numberOfPoints; i++)
            {
                sscanf(line, "(%d,%d)%s", &points[i].x, &points[i].y, line);
            }
        }
    }
    else
    {
        numberOfPoints = atoi(argv[1]);
        N = atoi(argv[2]);
        randomizePoints(points, numberOfPoints);
        sourcePoint.x = (rand() % 2 == 0) ? rand() % (numberOfPoints) : -(rand() % (numberOfPoints));
        sourcePoint.y = (rand() % 2 == 0) ? rand() % (numberOfPoints) : -(rand() % (numberOfPoints));
    }

    for (int i = 0; i < N; i++)
    {
        minDistances[i] = DBL_MAX;
    }

    clock_t t;
    t = clock();

    pthread_t tids[N];
    parameters *params[N];

    // Running function on subarrays
    // start and end contain the indices of the array such that points[start] - points[end] is the subarray
    unsigned start = 0;
    unsigned end = ceil((double)numberOfPoints / N) - 1;
    for (unsigned i = 0; i < N; i++)
    {
        params[i] = malloc(sizeof(parameters));
        params[i]->p = start;
        params[i]->r = end;
        params[i]->index = i;

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, &findNearest, params[i]);

        start = start + ceil((double)numberOfPoints / N);
        end = end + ceil((double)numberOfPoints / N);
        // For the last case where end index is greater than numerOfArrayElements
        end = (end > numberOfPoints - 1) ? numberOfPoints - 1 : end;
    }

    // Joining all the threads
    for (int i = 0; i < N; i++)
    {
        pthread_join(tids[i], NULL);
        free(params[i]);
    }

    point nearestPoint;
    double minDistance = DBL_MAX;

    // Getting the closest point from the nearestPoints subarrays
    unsigned mid = ceil((double)numberOfPoints / N) - 1;
    end = mid + ceil((double)numberOfPoints / N);
    end = (end > numberOfPoints - 1) ? numberOfPoints - 1 : end;
    for (int i = 0; i < N; i++)
    {
        if (minDistances[i] < minDistance)
        {
            minDistance = minDistances[i];
            nearestPoint.x = nearestPoints[i].x;
            nearestPoint.y = nearestPoints[i].y;
        }
        mid = end;
        end = end + ceil((double)numberOfPoints / N);
        end = (end > numberOfPoints - 1) ? numberOfPoints - 1 : end;
    }

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    if (useFileReading)
    {
        printf("Time taken for TSP of %u elements with %u threads: %lf milliseconds\n", numberOfPoints, N, time_taken * 1000);
        printf("(%d,%d)\n", nearestPoint.x, nearestPoint.y);
    }
    else
        printf("%lf", time_taken * 1000);
    return 0;
}

// gcc -w -lm -pthread Assgn1Src-CS20BTECH11001.c -o exec1 && ./exec1