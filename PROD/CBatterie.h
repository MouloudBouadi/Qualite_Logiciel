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
 * SOURCE       : CBatterie.h
 * PRESENTATION : fichier entête de définition de la batterie
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

class CBatterie
{
private:
	int iNiveauBatterie;

public:
	CBatterie();
	CBatterie(int i_niveauBatterie);
	~CBatterie();

	int GetNiveauBatterie();

	void SetNiveauBatterie(int i_niveauBatterie);
};

