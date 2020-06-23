/**************************************************************
* CLASSE : CDijsktra
* PRESENTATION : Function that determines the shorter path from a Source A to a point B.
*
* METHODES PUBLIQUES :
* <Methode1> : <description rapide de la methode 1>
* <Methode2> : <description rapide de la methode 2>
* <Methode3> : <description rapide de la methode 3>
* <Methode4> : <description rapide de la methode 4>
*
* OBSERVATIONS :
**************************************************************/

#pragma once
#define V 9 //Nombre d'arbre à contrôler, choisi arbitrairement ici
class CDijsktra
{
private:
public:
CDijsktra();
~CDijsktra();
int	minDistance(int dist[], bool sptSet[]);
void dijkstra(int graph[V][V], int src);
void printSolution(int dist[]);


};

