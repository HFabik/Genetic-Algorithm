// Include everything necessary here 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"
# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif


void printArray(double *arr, int size)
{
    for(int i = 0; i < size-1; i++)
    {
        printf("%lf, ", arr[i]);
    }
    printf("%lf", arr[size-1]);
}


int main(int argc, char *argv[])
{   
    // ###################################################################################
    // YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code
    if (argc != 6)
    {
        printf("ERROR: correct format is 5 input numbers: <POPULATION SIZE> <MAX GENERATIONS> <crossover rate> <mutate rate> <stop criteria>\n");
        return 1;
    }

    // YOUR CODE: Assign all inputs given by the user argv[i] like:
    // POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);

    // ###################################################################################
    /* YOUR CODE: You must change this part based on the lower and upper bounds
    1. based on what function is going to be minimized (let's say Levy)
    2. given bound in https://www.sfu.ca/~ssurjano/optimization.html for each function.*/ 

    // the number of variables (d)
    int NUM_VARIABLES = 10;
    // the lower bounds of variables (x_1, x_2, ..., x_d) where d=NUM_VARIABLES
    double Lbound[] = {-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5};
    // the upper bounds of variable
    double Ubound[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    /*For example: in Levy function x_i ∈ [-10, 10], for all i = 1, …, d. This means:
    lower bound = -10 for all x_i
    upper bound = +10 for all x_i
    if d =10 (or NUM_VARIABLES = 10) then:*/
    //double Lbound[] = {-5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0, -5.0};
    //double Ubound[] = {+5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0, +5.0};

    /*Another example: in Griewank() if NUM_VARIABLES = 7, then:*/
    //double Lbound[] = {-600.0, -600.0, -600.0, -600.0, -600.0, -600.0, -600.0, -600.0, -600.0, -600.0};
    //double Ubound[] = {+600.0, +600.0, +600.0, +600.0, +600.0, +600.0, +600.0, 600.0, 600.0, 600.0};

    // ###################################################################################

    // YOUR CODE: Here make all the initial print outs
    printf("Genetic Algorithm is initiated.\n------------------------------------------------\n");
    printf("The number of variables: %d\n", NUM_VARIABLES);
    printf("Lower bounds: [");
    printArray(Lbound, sizeof(Lbound)/sizeof(Lbound[0]));
    printf("]\nUpper bounds: [");
    printArray(Ubound, sizeof(Ubound)/sizeof(Ubound[0]));
    printf("]\nPopulation Size: %d\n", POPULATION_SIZE);
    printf("Max Generations: %d\n", MAX_GENERATIONS);
    printf("Crossover Rate: %0.6lf\n", crossover_rate);
    printf("Mutation Rate: %0.6lf\n", mutate_rate);
    printf("Stopping criteria: %0.16lf\n\n", stop_criteria);

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // <YOUR CODE: Declare all the arrays you need here>
    double population[POPULATION_SIZE][NUM_VARIABLES];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];
    double fitness[POPULATION_SIZE];
    double best_solution[NUM_VARIABLES]; //*best_solution = malloc(NUM_VARIABLES*sizeof(double));
    double best_eval = 1e9;


    // <YOUR CODE: Call generate_population function to initialize the "population"> like:
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);

    // iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met
    for (int generation = 0; generation < MAX_GENERATIONS; generation++)
    {
        // <YOUR CODE: Compute the fitness values using objective function for
        // each row in "population" (each set of variables)> like:
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);

        // <YOUR CODE: Here implement the logic of finding best solution with minimum fitness value
        // and the stopping criteria>
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            if (fitness[i] < best_eval)
            {
                best_eval = fitness[i];
                memcpy(best_solution, population[i], sizeof(double) * NUM_VARIABLES);
                if (best_eval < stop_criteria) 
                {
                    goto end;
                }
            }
        }


        // <YOUR CODE: Here call the crossover function>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);

        // <YOUR CODE: Here call the mutation function>
        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);

        // Now you have the new population, and it goes to the beginning of loop to re-compute all again
    }
    
    end:
    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Results\n------------------------------------------------\n");
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // <Your CODE: Here print out the best solution and objective function value for the best solution like the format>
    printf("Best solution found: (");
    printArray(best_solution, sizeof(best_solution)/sizeof(best_solution[0])); //NUM_VARIABLES*sizeof(double));
    printf(")\nBest fitness: %0.16lf\n", best_eval);
    

    return 0;
}
