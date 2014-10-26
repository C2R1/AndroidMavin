// -------------------KinectmaindroiteOK--------------
//Fonction de départ, gère les coordonnées
//

#include "stdafx.h"
#include <iostream>//bibliothèque pour le flux d'image (inutile ici)
#include <Windows.h>
#include <NuiApi.h>// bibliothèque nécessaire pour la kinect

using namespace std;
int main()
{
   NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);// initialisation du capteur de données relatives au squelette
   NUI_SKELETON_FRAME ourframe;						// crée la frame "ourframe"
   while (1)
   {
     NuiSkeletonGetNextFrame(0, &ourframe); // place les données reçues dans "ourframe"
     for (int i = 0; i < 6; i++)			// 6 pour le nombre pour le nombre de type de données a acquérir
     {
       if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED) //  pendant les 6 états de la structure skeletondata on utilise eTrackingState et on verifie si il est egal à NUI_SKELETON_TRACKED(=1)
         {
		  cout << "Hauteur main droite: " ; // affiche main droite
          cout << ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y << endl;// dans les 6 états de la structure skeletondata on utilise skeleton position et plus precisement la main droite
		  cout << "Largeur main droite: " ; // affiche main droite
          cout << ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x << endl;// dans les 6 états de la structure skeletondata on utilise skeleton position et plus precisement la main gauche
	     }
     }
     system("cls");// fermeture de la fenêtre
   }
  NuiShutdown();//arrêt de la kinect
	return 0;
}

