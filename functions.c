// Your CODE: Include everything necessary here 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "functions.h"


double generate_random(double min, double max)
{
    // Your CODE: implement a function to return a value between min and max
    //srand((unsigned int) time(NULL));
    double randomNum = ((float) rand()/(float) (RAND_MAX))*(max - min) + min;
    return randomNum;
}

int generate_int(int min, int max)
{
    // Your CODE: implement the function to return a random integer value
    int randInt = rand() % (max - min + 1) + min;
    return randInt;
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES])
{
    // Your CODE: randomly initialize for all values in "population[i][j]""
    srand(time(NULL));
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for(int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = generate_int(Lbound[j], Ubound[j]);
        }
    }
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    /* Your CODE: compute "fitness[i]" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
    for(int i  = 0; i < POPULATION_SIZE; i++)
    {
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);
    }
}

void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Your CODE: Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/
    double total = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        total += 1/(1e-6+fitness[i]);
    }
    double fitness_probs[POPULATION_SIZE];
    double runningTotal = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        runningTotal += (1/(1e-6+fitness[i])) / total;
        fitness_probs[i] = runningTotal;
    }


    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        double r = generate_random(0, 1);
        for(int j = 0; j < POPULATION_SIZE; j++)
        {
            if (r < fitness_probs[j])
            {
                memcpy(new_population[i], population[j], NUM_VARIABLES * sizeof(double));
                break;
            }
        }
    }

    int numParents = 0;
    int parents[NUM_VARIABLES];
    for (int k = 0; k < POPULATION_SIZE; k++)
    {
        double r = generate_random(0, 1);
        if (r < crossover_rate)
        { 
            parents[numParents] = k;
            numParents++;
        }
    }
    
    if (numParents == 0 || numParents == 1) {return;}


    double temp[NUM_VARIABLES];
    memcpy(temp, new_population[parents[0]], NUM_VARIABLES * sizeof(double));

    for(int i = 0; i < numParents-1; i++)
    {
        int crossPos = generate_int(1, NUM_VARIABLES-1);
        int index = parents[i];   
        int next = parents[i+1];
        for(int j = crossPos; j < NUM_VARIABLES; j++)
        {
            new_population[index][j] = new_population[next][j];
        }
    }
    int index = numParents-1;
    int crossPos = generate_int(1, NUM_VARIABLES-1);
    for(int j = crossPos; j < NUM_VARIABLES; j++)
    {
        new_population[parents[index]][j] = temp[j];
    }
}


void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    /*Your CODE: Implement the logic of mutation on "new_population" and then copy everything into "population"*/
    int total_gen = NUM_VARIABLES * POPULATION_SIZE;
    int num_muts = mutate_rate * total_gen;
    for (int i = 0; i < num_muts; i++)
    {
        int r = generate_int(0, total_gen-1);
        int row = r / NUM_VARIABLES; 
        int col = r % NUM_VARIABLES;
        new_population[row][col] = generate_random(Lbound[col], Ubound[col]);
    }
    memcpy(population, new_population, sizeof(double) * POPULATION_SIZE * NUM_VARIABLES);
}
