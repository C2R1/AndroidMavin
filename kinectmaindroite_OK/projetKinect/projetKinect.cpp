// -------------------KinectmaindroiteOK--------------
//Fonction de d�part, g�re les coordonn�es
//

#include "stdafx.h"
#include <iostream>//biblioth�que pour le flux d'image (inutile ici)
#include <Windows.h>
#include <NuiApi.h>// biblioth�que n�cessaire pour la kinect

using namespace std;
int main()
{
   NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);// initialisation du capteur de donn�es relatives au squelette
   NUI_SKELETON_FRAME ourframe;						// cr�e la frame "ourframe"
   while (1)
   {
     NuiSkeletonGetNextFrame(0, &ourframe); // place les donn�es re�ues dans "ourframe"
     for (int i = 0; i < 6; i++)			// 6 pour le nombre pour le nombre de type de donn�es a acqu�rir
     {
       if (ourframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED) //  pendant les 6 �tats de la structure skeletondata on utilise eTrackingState et on verifie si il est egal � NUI_SKELETON_TRACKED(=1)
         {
		  cout << "Hauteur main droite: " ; // affiche main droite
          cout << ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y << endl;// dans les 6 �tats de la structure skeletondata on utilise skeleton position et plus precisement la main droite
		  cout << "Largeur main droite: " ; // affiche main droite
          cout << ourframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x << endl;// dans les 6 �tats de la structure skeletondata on utilise skeleton position et plus precisement la main gauche
	     }
     }
     system("cls");// fermeture de la fen�tre
   }
  NuiShutdown();//arr�t de la kinect
	return 0;
}

