#pragma once

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CMoteur.h
 * PRESENTATION : fichier entête de définition du moteur
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

class CMoteur
{


//Conso moyenne 14,0 Watts
//Vitesse de déplacement 0,42m/s
//Pente maximale 10%

private:
	double dCouple;
	int iNum;
;

	//temps de parcours
	//nombre de mesure
	//consommation du moteur
	
public:
	CMoteur();
	~CMoteur();

	
};

CMoteur::CMoteur()
{

}
