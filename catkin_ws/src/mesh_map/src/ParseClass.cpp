//
//  ParseClass.cpp
//  Tutorials
//
//  Created by Sadat Shaik on 6/16/15.
//
//

#include "mesh_map/ParseClass.h"

#include <stdio.h>
#include <string>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void ParseClass::ParseEdgeFile(string fileName, vector<float> *nodeArray, int* numberOfVertices)
{
    ifstream fileHandle;
    fileHandle.open(fileName.c_str());
    string currentLine = "";
    bool pastHeader = false;
    while(getline(fileHandle, currentLine))
    {
        istringstream iss(currentLine);
        if(!pastHeader)
        {
            iss>>*numberOfVertices;
            pastHeader = true;
        }
        else
        {
            
            float nextNumber;
            iss>>nextNumber; //Throw away first value, which is the id of hte current point.
            
            iss>>nextNumber; //Keep the second number, as that is x coordinate
            nodeArray->push_back(nextNumber);
            
            iss>>nextNumber; //Keep the third number, as that is y coordinate
            nodeArray->push_back(nextNumber);
            
            iss>>nextNumber; //Keep the fourth number, as that is z coordinate
            nodeArray->push_back(nextNumber);
            
            //Since tetrahedra have four vertices, you also have to get the fifth value to get all vertices.
            
            iss>>nextNumber; //Keep the fifth number, as that is z coordinate
            nodeArray->push_back(nextNumber);
        }
    }
}

void ParseClass::ParseNodeFile(string fileName, vector<vector<float> > *nodeArray, int* numberOfVertices)
{
    ifstream fileHandle;
    fileHandle.open(fileName.c_str());
    string currentLine = "";
    bool pastHeader = false;
    while(getline(fileHandle, currentLine))
    {
        istringstream iss(currentLine);
        if(!pastHeader)
        {
            iss>>*numberOfVertices;
            pastHeader = true;
        }
        else
        {
            
            float nextNumber, xCoordinate = 0.0, yCoordinate = 0.0, zCoordinate = 0.0;
            iss>>nextNumber; //Throw away first value, which is the id of hte current point.
            
            iss>>xCoordinate;
            iss>>yCoordinate;
            iss>>zCoordinate;
            
            vector<float> coordinate;
            coordinate.push_back(xCoordinate);
            coordinate.push_back(yCoordinate);
            coordinate.push_back(zCoordinate);
            
            nodeArray->push_back(coordinate);
        }
    }
}


void ParseClass::ParseMeshFile(string meshFile, vector<int> *facetArray, int* numberOfFacets)
{
    ifstream fileHandle;
    fileHandle.open(meshFile.c_str());
    string currentLine = "";
    bool pastHeader = false;
    getline(fileHandle, currentLine);
    while(getline(fileHandle, currentLine))
    {
        istringstream iss(currentLine);
        if(!pastHeader)
        {
            iss>>*numberOfFacets;
            pastHeader = true;
        }
        else
        {
            
            float nextNumber;
            vector<float> tempFacet;
            iss>>nextNumber; //Throw away first value, which is the id of hte current point.
            
            iss>>nextNumber; //Keep the second number, as that is x coordinate
            
            tempFacet.push_back(nextNumber);
            
            iss>>nextNumber; //Keep the third number, as that is y coordinate
            tempFacet.push_back(nextNumber);
            
            iss>>nextNumber; //Keep the fourth number, as that is z coordinate
            tempFacet.push_back(nextNumber);
        }
    }
}


void ParseClass::ParseFaceFile(string faceFileName, vector<vector<float> > *nodeArray, int* numberOfVertices)
{
    ifstream fileHandle;
    fileHandle.open(faceFileName.c_str());
    string currentLine = "";
    while(getline(fileHandle, currentLine))
    {
        istringstream iss(currentLine);
        float nextNumber;
        
        vector<float> tempVec;
        iss>>nextNumber; //Keep the second number, as that is x coordinate
        
        tempVec.push_back(nextNumber);
        
        iss>>nextNumber; //Keep the third number, as that is y coordinate
        tempVec.push_back(nextNumber);
        
        iss>>nextNumber; //Keep the fourth number, as that is z coordinate
        tempVec.push_back(nextNumber);
        
        nodeArray->push_back(tempVec);
    }
}
