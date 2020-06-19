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
 * SOURCE       : CMesure.h
 * PRESENTATION : fichier entête de définition de l
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 19/06/2020
 * 
 ***************************************************************/ 

class CMesure
{

private:
	int TempsMesure;
	int ConsoMesure;

public:
	CMesure();
	~CMesure();

	void NouvelleMesure();
};

CMesure::CMesure()
{
	TempsMesure = 0; //secondes
	ConsoMesure = 0; //Watts
}
