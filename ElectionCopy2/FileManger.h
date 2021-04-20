#pragma once
#include<windows.h>
#include <fstream>
#include <iostream>
#include<string>
#include"DynamicArr.h"
#define _CRT_SECURE_NO_WARNINGS
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#define MAX_SIZE 100
#define NOT_FOUND -1

using namespace std;

enum Numbers {
	Zero = 0,
	One = 1,
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Eleven = 11,
	Twelve = 12
};
enum ElectionType {
	Simple = 1,
	Regular = 2,
	UNION=3,
	SHARE=4
};

enum Months {
	January=1,
	February= 2,
	March =3 ,
	April = 4, 
	May = 5, 
	June = 6, 
	July = 7 ,
	August = 8 ,
	September = 9 ,
	October = 10 ,
	November = 11,
	December = 12 
};



/*********main functions************/

void homePage();

void printHomeChoise();

//this function send the user to start new election
void newElection();

//this function get the file path and loads election
void loadElection();

//this function	print the election type options
void chooseRound();

void checkDate(int day, int month, int year);

template <class T>
int findMaxInArr(T arr, int size) {
	int maxInd = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] > arr[maxInd]) {
			maxInd = i;
		}
	}
	return maxInd;
}