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

 /**************************************************************
 * METHODE : CMesure::NouvelleMesure()
 * PRESENTATION : Ajoute le temps de mesure et la consomation d'une mesure au totaux.
 *
 * **************************************************************/

void CMesure::NouvelleMesure()
{
	TempsMesure += 5;
	ConsoMesure += 30;
}