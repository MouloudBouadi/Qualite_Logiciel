#pragma once
#include <string> 
using namespace std ;

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
 * DATE         : 19/06/2020
 * 
 ***************************************************************/ 
class CMoteur
{
private:
	int iEtatMoteurGauche; //14W 0.42m/s
	int iEtatMoteurDroite; //14W 0.42m/s

	
public:
	CMoteur();
	~CMoteur();
	int GetEtatMoteur(string IDmoteur);
	void SetEtatMoteur(int _iEtatMoteurGauche, int _iEtatMoteurDroit);
    void Avancer();
    void Reculer();
    void Gauche();
    void Droite();
};
