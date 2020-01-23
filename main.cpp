#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"
using namespace std;


static int elevations[MAX_ROWS][MAX_COLS];
static Pixel image[MAX_ROWS][MAX_COLS];

int main()
{
	int max;
	int min;
	int rows;
	int cols;
	int greenLine;
	int shortDist;
	Pixel color;
	Pixel greenColor;
	string filename;
	int distance;

	cin >> rows;
	if (!cin)
	{
		cout << "Error: Problem reading in rows and columns.";
	   	exit(1);
	}
	cin >> cols;
	if (!cin)
	{
	   	cout << "Error: Problem reading in rows and columns.";
	   	exit(1);
	}
	if (rows < 1 || cols < 1 || rows > MAX_ROWS || cols > MAX_COLS)
	{
		cout << "Error: Problem reading in rows and columns.";
		exit(1);
	}
	cin >> filename;

	ifstream nfs;
	ofstream outData;

	nfs.open(filename);
	if (!nfs)
	{
		 cout << "Error: Unable to open file<" << filename << ">." << endl;
		 exit(1);
	}

	loadData(elevations, rows, cols, nfs);
	nfs.close();

	findMaxMin(elevations, rows, cols, max, min);

	loadGreyscale(image, elevations,rows, cols, max, min);



	color.red = 252;
	color.green = 25;
	color.blue = 63;

	for(int i=0; i<rows; i++)
	{
		distance = colorPath(elevations, image, rows, cols, color, i);

		if (i==0)
		{
			shortDist = distance;
			greenLine = i;

		}

		else
		{
			if (distance < shortDist)
			{
				shortDist = distance;
				greenLine = i;
			}
		}
	}


	greenColor.red = 31;
	greenColor.green = 253;
	greenColor.blue = 13;

	distance = colorPath(elevations, image, rows, cols, greenColor, greenLine);

	outData.open(filename + ".ppm");

	outputImage(image, rows, cols, outData);

	outData.close();
}
