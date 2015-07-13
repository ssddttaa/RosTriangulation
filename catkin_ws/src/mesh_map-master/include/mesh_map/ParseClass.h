//
//  ParseClass.h
//  Tutorials
//
//  Created by Sadat Shaik on 6/16/15.
//
//

#ifndef __Tutorials__ParseClass__
#define __Tutorials__ParseClass__

#include <stdio.h>
#include <string>
#include <stdlib.h>

#include <vector>
using namespace std;

class ParseClass
{
    public:
        static void ParseEdgeFile(string nodeFile, vector<float> *nodeArray, int* numberOfVertices);
        static void ParseNodeFile(string nodeFile, vector<vector<float> > *nodeArray, int* numberOfVertices);
        static void ParseMeshFile(string meshFile, vector<int> *facetArray, int* numberOfFacets);
        static void ParseFaceFile(string faceFileName, vector<vector<float> > *nodeArray, int* numberOfVertices);
};

#endif /* defined(__Tutorials__ParseClass__) */
