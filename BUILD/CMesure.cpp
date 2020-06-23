#include "CMesure.h"

/**************************************************************
 *
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615
 * Reproduction et diffusion interdites.
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 *
 * SOUS-SYSTEME : ROBIOT SIMU
 *
 * SOURCE       : CCompas.cpp
 * PRESENTATION : fichier source de définition du compas. Géolocalisation du robiot
 *
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1
 * DATE         : 19/06/2020
 *
 ***************************************************************/

CMesure::CMesure()
{
	iTempsMesure = 0; //secondes
	iConsoMesure = 0; //Watts
	
}

 /**************************************************************
 * METHODE : CMesure::NouvelleMesure()
 * PRESENTATION : Ajoute le temps de mesure et la consomation d'une mesure au totaux.
 *
 * **************************************************************/

void CMesure::NouvelleMesure(CArbre *p_Arbre)//donner l'arbre en paramètre'
{
	iTempsMesure += 5;
	iConsoMesure += 30;
	p_Arbre->setStatut(1);
}

/**************************************************************
* METHODE : CMesure::getTempsMesure()
* PRESENTATION : donnne le temps cumulé des mesures
*
* **************************************************************/

int CMesure::getTempsMesure()
{
	return iTempsMesure;
}

/**************************************************************
* METHODE : CMesure::getConsoMesure()
* PRESENTATION : donnne la conso cumulée des mesures
*
* **************************************************************/

int CMesure::getConsoMesure()
{
	return iConsoMesure;
}

/**************************************************************
* METHODE : CMesure::~CMesure()
* PRESENTATION : Destructeur de CMesure
*
* **************************************************************/

CMesure::~CMesure()
{

}