#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

typedef struct Faits
{
	char Faits[20];
	struct Faits *suiv;
} Faits;

typedef struct Liste_faits
{
	char faits[20];
	Faits *Info_faits;
	struct Liste_faits *suiv;
}NINFO_F;

Faits * CreerBF();
Faits* InsererBF(Faits* Liste, Faits* E);
void AfficherBF(Faits *Liste);
NINFO_F *Rechercher_fait(Faits *Liste, char mot[30]);
void Afficher_recherche_fait(Faits * Liste, Faits * faitRech);
void Modifier_nomBF(Faits *Liste, Faits *faitRech);
void SauvegarderBF(Faits * Liste);
Faits* lireFicCreerBF(void);
void desallocBF(Faits *Liste);


Faits * CreerBF()
{	
	Faits *E;
	E=(Faits*)malloc(sizeof(Faits));
  	if (E == NULL)
  	{
  		printf("Erreur d'allocation memoire\n");
  	}
  	else
  	{
	printf("Fait: \n"); 
  	scanf("%s", E->Faits);  
  	E->suiv = NULL;		
    }
	return E;
}


Faits* InsererBF(Faits* Liste, Faits* E)
{
	if(E == NULL) // Cas liste vide
	{
		printf("Rien a inserer \n");
		return Liste;
	}
	if (Liste == NULL)
	{
		return E;
	}

	if(strcmp (E->Faits, Liste->Faits) <  0)  // Cas nouveau < premier maillon pas de else car return
	{
		E->suiv = Liste;
		return E;
	}

Liste->suiv = InsererBF(Liste->suiv, E);						// Insertion dans le reste de la liste
return Liste;
}




void AfficherBF(Faits *Liste)
{
	int i=0;
	if(Liste == NULL)
		return;
	
	printf("\nFait: %s\n", Liste->Faits);
	AfficherBF(Liste->suiv);
} 

NINFO_F *Rechercher_fait(Faits *Liste, char mot[30])
{
	NINFO_F * cpt;


	if (Liste == NULL)
	{ 
	printf("\nMot non trouvé\n"); return NULL; 
	}
	
	for(cpt == Liste ; cpt != NULL ; cpt == cpt->suiv)
	{
		if(strcmp(mot, cpt->faits) == 0)
			return cpt;
	
	}
		

	return NULL;

}

void Afficher_recherche_fait(Faits * Liste, Faits * faitRech)
{
	printf("Fait rechercher : %s\n",faitRech);	
	printf("Voici le resultat : \n");
	printf("\nFait: %s", faitRech->Faits);
}

void Modifier_nomBF(Faits *Liste, Faits *faitRech)
{
	char modif_nom[30];

		printf("Nom du nouveau fait: ");
		scanf("%s", modif_nom);
		strcpy(faitRech->Faits, modif_nom);
		printf("\nFait modifier !\n");
}

void SauvegarderBF(Faits * Liste)
{
	FILE *fic = NULL;
	char sNomFic[30];
	printf("\n *************************SAUVEGARDE *************************");
	printf("\nDonnez le nom du fichier a creer (attention son contenu sera effacer): ");
	scanf(" %s", sNomFic);
	
	if ((fic = fopen(sNomFic, "a")) == NULL)
		printf("\nErreur d'ouverture de fichier - Abandon");
	else
	{ 
		while(Liste != NULL)
		{
			if (fwrite(Liste, sizeof(Faits), 1, fic) != 1)
			{ 
				printf("\nErreur d'ecriture dans le fichier - Abandon");
				Liste = NULL;
			}
			else
				Liste = Liste->suiv;
		}
		if ((fic != NULL) && (fclose(fic) != 0))
			printf("\nProbleme de fermeture de fichier");
	}
} 



Faits* lireFicCreerBF(void)
{
	int lecture=0;
	FILE * fic = NULL;
	fic=fopen("base_faits.txt", "r");
	do
	{
	 lecture=fgetc(fic);
	 printf("%c",lecture);
	} while(lecture !=EOF);
	fclose(fic);
}
	


void desallocBF(Faits *Liste)
{
	if (Liste != NULL)
	{
		desallocBF(Liste->suiv);
		free(Liste);
	}
}

int main(void)
{
	Faits *Liste=NULL;
	Faits *E=NULL;
	NINFO_F *film;
	Faits *faitRech;
	int save;
	char mot[30];
	char infoModif;
	char Lequel[30];
	
	int choix, nbre, i;

	while(1)
	{
		printf("MENU BASE DE FAITS: \n");
		printf("0- Quitter: \n");
		printf("1 - Afficher \n");
		printf("2- Creer \n");
		printf("3- Rechercher \n");
		printf("4- Modifier \n");
		printf("5- Sauvegarder \n");
		printf("6- Charger \n");
		printf("7- Tout supprimer\n");
		scanf("%d",&choix);
		switch(choix)
		{
	
			case 0: return 0;
			
			case 1: AfficherBF(Liste);
					break;
			

			case 2: printf("combien voulez vous rajouter de faits ? \n");
					scanf("%d",&nbre);
					for(i=0;i<nbre;i++)
					{
					printf("\n Fait n°%d: \n",i+1);
					E=CreerBF();
					Liste=InsererBF(Liste,E);
					}
					break;
			
			case 3:	printf("\nQuel fait voulez-vous modifier?\n");
					scanf("%s",mot);
					faitRech = Rechercher_fait(Liste, mot);
					Afficher_recherche_fait(Liste, faitRech);
					Modifier_nomBF(Liste, faitRech); break;
										
			case 4: SauvegarderBF(Liste);break;
			
			case 5: lireFicCreerBF();break;
					
			case 6: desallocBF(Liste);break;
			
			default : printf("Mauvais choix\n"); 
		}
	}
}
