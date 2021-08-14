/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 2 Group 10
 * Dunn Header File
************************************************/

#ifndef dunn_h
#define dunn_h

#include <list>

#include "point.h"
#include "cluster.h"

using namespace std;

class Dunn {
  private:
    static int kvals[3];
    static double dunns[3];
  public:
    static double dunn(const list<Cluster>& clusters, int type);
    static void printAnalysis();
};

#endif
