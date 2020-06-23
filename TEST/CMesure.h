#pragma once
#include "CArbre.h"

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
	int iTempsMesure;
	int iConsoMesure;

public:
	CMesure();
	~CMesure();

	void NouvelleMesure(CArbre *p_Arbre);
	int getTempsMesure(); 
	int getConsoMesure();
};