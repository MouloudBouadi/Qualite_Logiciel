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
	TempsMesure = 0; //secondes
	ConsoMesure = 0; //Watts
	
}

 /**************************************************************
 * METHODE : CMesure::NouvelleMesure()
 * PRESENTATION : Ajoute le temps de mesure et la consomation d'une mesure au totaux.
 *
 * **************************************************************/

void CMesure::NouvelleMesure(CArbre *p_Arbre)//donner l'arbre en paramètre'
{
	TempsMesure += 5;
	ConsoMesure += 30;
	p_Arbre->setStatut(1); //le statut passe à MESURE
    //ConsoMoteur += 14;
    //carte mère 12.5watt
	//appeler la fonction monArbre.setStatutArbre(MESURE)
}