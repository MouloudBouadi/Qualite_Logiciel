#pragma once
#include <iostream>

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CArbre.h
 * PRESENTATION : fichier entête de définition d'arbres
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/

class CArbre
{
private:
	int iArbreX;
	int iArbreY;
	int iStatut;

	
public:
	enum statusArbre {
		NONMESURE, MESURE
	};

	CArbre();
	CArbre(int _iArbreX, int _iArbreY, int _iStatut);

	void setStatus(int _iStatut);

	int getArbreX();
	int getArbreY();

	~CArbre();

};

