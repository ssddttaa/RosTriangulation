//
//  BufferActions.cpp
//  Tutorials
//
//  Created by Sadat Shaik on 6/15/15.
//
//

#include "mesh_map/BufferActions.h"


void BufferActions::addObjectToBuffer(float *vertexesToAdd, float *colorsToAdd, int numberOfVertices, vector<float> *vertex_buffer_pointer, vector<float> *color_buffer_pointer)
{
    for(int i = 0;i<numberOfVertices;i++)
    {
        vertex_buffer_pointer->push_back(vertexesToAdd[i]);
        color_buffer_pointer->push_back(colorsToAdd[i]);
    }
}

void BufferActions::addVec3ToBuffer(int * arrayOfVec3, vector<float> *buffer_pointer, vector<vector<float> > * allVec3s, int numberOfVectorsToAdd)
{
    for(int i = 0;i<numberOfVectorsToAdd;i++)
    {
        int whichPointToAdd = arrayOfVec3[i];
        vector<float> tempVec(allVec3s->at(whichPointToAdd));
        buffer_pointer->push_back(tempVec[0]);
        buffer_pointer->push_back(tempVec[1]);
        buffer_pointer->push_back(tempVec[2]);
    }
}
