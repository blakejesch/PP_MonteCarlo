﻿// MonteCarlo.cpp : Defines the entry point for the console application.
//
#include <omp.h>
#include <iostream>
using namespace std;

int main()
{
	int thread_count = 4; //set number of threads to 4
	int number_of_tosses = 0;
	cout << "How many tosses will you throw? ";  //read in tosses
	cin >> number_of_tosses;
	long long int number_in_circle = 0;
	double x, y;
	double distance_squared;
#  pragma omp parallel for num_threads(thread_count) default(none) reduction(+ : number_in_circle) private(x, y, distance_squared)
	for (int toss = 0; toss < number_of_tosses; toss++) {
		//https://stackoverflow.com/questions/4310277/producing-random-float-from-negative-to-positive-range
		x = ((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1;
		y = ((float(rand()) / float(RAND_MAX)) * (1 - -1)) + -1;
		distance_squared = x * x + y * y;
		if (distance_squared <= 1) number_in_circle++;
	}
	double pi_estimate = 4 * number_in_circle / ((double)number_of_tosses); //gets p estimate
	cout << "Pi Estimate: " << pi_estimate << "\n";
	cout << "Number of hits: " << number_in_circle << "\n";
	cin.get();


    return 0;
}

