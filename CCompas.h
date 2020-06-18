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
 * SOURCE       : CCompas.h
 * PRESENTATION : fichier entête de définition du compas
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

class CCompas
{
private:
	int iCoordX;
	int iCoordY;

public:
	CCompas();
    CCompas(int,int);
	~CCompas();

	int GetCompasX();
    int GetCompasY();

	void SetCompasX(int _iCoordX);
	void SetCompasY(int _iCoordY);
	
};

CCompas::CCompas()
{
	iCoordX = 0;
	iCoordY = 0;
}

