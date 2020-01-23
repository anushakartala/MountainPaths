#include <iostream>
#include <fstream>
#include <cmath>
#include "functions.h"
using namespace std;

void findMaxMin(const int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, int& max, int& min) {
	min = elevations[0][0];
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			if (elevations[i][j] < min)
				min = elevations[i][j];
		}
	}

	max = elevations[0][0];
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
			{
				if (elevations[i][j] > max)
					max = elevations[i][j];
			}
	}
}



void loadData(int elevations[MAX_ROWS][MAX_COLS], int rows, int cols, istream& inData)
{
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			if (inData.eof())
		    {
				cout << "Error: End of file reached prior to getting all the required data.";
		    	exit(1);
		    }
		   	inData >> elevations[i][j];

		    if (inData.fail())
		    {
		    	cout << "Error: Read a non-integer value." << endl;
		    	exit(1);
		    }
		    if (inData.bad())
		    {
		    	cout << "Error: Problem reading the file." << endl;
		    	exit(1);
		    }
		}

	}
	int endData = 0;
	inData >> endData;
	if (!inData.fail())
	{
		if (!inData.bad())
	    {
			cout << "Error: Too many data points.";
	        exit(1);
	    }
	}
}



int scaleValue(int value, int max, int min)
{
	double maxValue;
	double minValue;
	double doubleValue;
	maxValue = max;
	minValue = min;
	doubleValue = value;
    return round(((doubleValue - minValue) / (maxValue - minValue)) * 255);
}



void loadGreyscale(Pixel image[MAX_ROWS][MAX_COLS], const int elevations[MAX_ROWS][MAX_COLS], 
                    int rows, int cols, int max, int min)
{
	double shadeGrey;
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			image[i][j].red = scaleValue(elevations[i][j], max, min);
			image[i][j].blue = scaleValue(elevations[i][j], max, min);
			image[i][j].green = scaleValue(elevations[i][j], max, min);
		}
	}
}



void outputImage(const Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, ostream& outData)
{
	outData << "P3" << endl;
	outData << cols << " " << rows << endl;
	outData << "255" << endl;
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			outData << image[i][j].red << " ";
			outData << image[i][j].green << " ";
			outData << image[i][j].blue << " ";
		}
	}
}

int colorPath(const int elevations[MAX_ROWS][MAX_COLS], Pixel image[MAX_ROWS][MAX_COLS], int rows, int cols, Pixel color, int start_row)
{
	image[start_row][0].red = color.red;
	image[start_row][0].blue = color.blue;
	image[start_row][0].green = color.green;

	int minDist;
	int distance;
	int finalRow;
	distance = 0;

	for (int i=0; i<cols-1; i++)
	{

		minDist = abs(elevations[start_row][i] - elevations[start_row][i+1]);
		finalRow = start_row;
		if(start_row<rows-1)
		{
			if(abs(elevations[start_row + 1][i+1] - elevations[start_row][i]) < minDist)
			{
				minDist = abs(elevations[start_row][i] - elevations[start_row+1][i+1]);
				finalRow = start_row + 1;
			}
		}
		if(start_row>0)
		{
			if(abs(elevations[start_row - 1][i+1] - elevations[start_row][i]) < minDist)
			{
				minDist = abs(elevations[start_row][i] - elevations[start_row-1][i+1]);
				finalRow = start_row - 1;

			}
		}

		image[finalRow][i+1].red = color.red;
		image[finalRow][i+1].blue = color.blue;
		image[finalRow][i+1].green = color.green;
		start_row=finalRow;
		distance = distance + minDist;

	}
	return distance;
}
