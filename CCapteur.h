#pragma once

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n� TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CCapteur.h
 * PRESENTATION : fichier ent�te de d�finition du cpateur de signaux balise
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

class CCapteur
{
private:
	int iEtatCapteur;

public:
	int GetEtatCapteur();
	void SetEtatCapteur(int);
	CCapteur();
    CCapteur(int _iEtatCapteur);
	~CCapteur();
};



