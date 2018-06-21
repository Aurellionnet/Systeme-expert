#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

typedef struct Films
{
	char nom[20];
	char genre[20];
	int date;
	char origine[20];
	char realisateur[20];
	char acteur[20];
	int id;
	struct Films *suiv;
} FILMS;

typedef struct Liste_films
{
	char nom[20];
	FILMS *Info_films;
	struct Liste_films *suiv;
}INFO_F;

FILMS * CreerBR();
FILMS* InsererBR(FILMS* Liste, FILMS* E);
void AfficherBR(FILMS *Liste);
INFO_F *Rechercher_filmBR(FILMS *Liste, char mot[30], int nbre);
void Afficher_recherche_filmBR(FILMS * Liste, FILMS * filmRech);
void Modifier_nomBR(FILMS *Liste, FILMS *filmRech);
void Modifier_genreBR(FILMS *Liste, FILMS *filmRech);
void Modifier_dateBR(FILMS *Liste, FILMS *filmRech);
void Modifier_origineBR(FILMS *Liste, FILMS *filmRech);
void Modifier_acteurBR(FILMS *Liste, FILMS *filmRech);
void Modifier_realisateurBR(FILMS *Liste, FILMS *filmRech);
void SauvegarderBR(FILMS * Liste);
FILMS* lireFicCreerBR(void);
void desallocBR(FILMS *Liste);
FILMS* SupprimerBR(FILMS*Liste, char *Lequel);

FILMS * CreerBR()
{	
	FILMS *E;
	E=(FILMS*)malloc(sizeof(FILMS));
  	if (E == NULL)
  	{
  		printf("Erreur d'allocation memoire\n");
  	}
  	else
  	{
	printf("Nom: \n"); 
  	scanf("%s", E->nom); 
  	printf("Genre: \n"); 
  	scanf("%s", E->genre); 
  	printf("Date: \n"); 
  	scanf("%d",&E->date); 
  	printf("Origine: \n"); 
  	scanf("%s",E->origine);
  	printf("Acteur principal: \n"); 
  	scanf("%s",E->acteur);
  	printf("Realisateur: \n"); 
  	scanf("%s",E->realisateur);
  	E->suiv = NULL;		
  	
    }
	return E;
}


FILMS* InsererBR(FILMS* Liste, FILMS* E)
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

	if(strcmp (E->nom, Liste->nom) <  0)  // Cas nouveau < premier maillon pas de else car return
	{
		E->suiv = Liste;
		return E;
	}

Liste->suiv = InsererBR(Liste->suiv, E);						// Insertion dans le reste de la liste
return Liste;
}



void AfficherBR(FILMS *Liste)
{
	int i=0;
	if(Liste == NULL)
		return;
	
	printf("\nNom: %s\n", Liste->nom);
	printf("Genre: %s\n", Liste->genre);
	printf("Date: %d\n", Liste->date);
	printf("Origine: %s\n", Liste->origine);
	printf("Acteur principal: %s\n", Liste->acteur);
	printf("Realisateur: %s\n", Liste->realisateur);
	AfficherBR(Liste->suiv);
} 

INFO_F *Rechercher_filmBR(FILMS *Liste, char mot[30], int nbre)
{
int icmp=0;
int i;
	if (Liste==NULL)
	{ 
	printf("\nMot non trouvé\n"); return NULL; 
	}
	for (i=0; i>nbre; i++)
{

icmp = strcmp(mot,Liste->nom);
	if (icmp==0)
	{ 
	printf("\nMot trouve\n");
	return Liste;
	}
}
	if (icmp!=0)
	{
		return Rechercher_filmBR(Liste->suiv, mot, nbre);
	}
				
return Liste;	
}

void Afficher_recherche_filmBR(FILMS * Liste, FILMS * filmRech)
{
	printf("Film rechercher : %s\n",filmRech);	
	printf("Voici ses informations : \n");
	printf("\nNom: %s", filmRech->nom);
	printf("\nGenre: %s", filmRech->genre);
	printf("\nDate: %d\n", filmRech->date);
}

void Modifier_nomBR(FILMS *Liste, FILMS *filmRech)
{
	char modif_nom[30];

		printf("Nom du nouveau nom: ");
		scanf("%s", modif_nom);
		strcpy(filmRech->nom, modif_nom);
		printf("\nNom modifier !\n");
}

void Modifier_genreBR(FILMS *Liste, FILMS *filmRech)
{
	char modif_genre[30];

		printf("Nom du nouveau genre: ");
		scanf("%s", modif_genre);
		strcpy(filmRech->genre, modif_genre);
		printf("\nGenre modifier !\n");
}

void Modifier_dateBR(FILMS *Liste, FILMS *filmRech)
{
	int modif_date;

		printf("Nouvelle date: ");
		scanf("%d",&modif_date);
		filmRech->date = modif_date;
		printf("\nDate modifier !\n");		
}

void Modifier_origineBR(FILMS *Liste, FILMS *filmRech)
{
	char modif_ori[20];

		printf("Nouvelle origine: ");
		scanf("%s",modif_ori);
		strcpy(filmRech->origine, modif_ori);
		printf("\nOrigine modifier !\n");		
}

void Modifier_acteurBR(FILMS *Liste, FILMS *filmRech)
{
	char modif_act[20];

		printf("Nouvel acteur: ");
		scanf("%s",modif_act);
		strcpy(filmRech->acteur, modif_act);
		printf("\nActeur modifier !\n");		
}

void Modifier_realisateurBR(FILMS *Liste, FILMS *filmRech)
{
	char modif_real[20];

		printf("Nouveau realisateur: ");
		scanf("%s",modif_real);
		strcpy(filmRech->realisateur, modif_real);
		printf("\nRealisateur modifier !\n");		
}

void SauvegarderBR(FILMS * Liste)
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
			if (fwrite(Liste, sizeof(FILMS), 1, fic) != 1)
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



FILMS* lireFicCreerBR(void)
{
	int lecture=0;
	FILE * fic = NULL;
	fic=fopen("base_regles.txt", "r");
	do
	{
	 lecture=fgetc(fic);
	 printf("%c",lecture);
	} while(lecture !=EOF);
	fclose(fic);
	}
	


void desallocBR(FILMS *Liste)
{
	if (Liste != NULL)
	{
		desallocBR(Liste->suiv);
		free(Liste);
	}
}

FILMS* SupprimerBR(FILMS*Liste, char *Lequel)
{ 
	FILMS * Remove;
	
	if (Liste == NULL)
	{
		printf("\nLe nom n'est pas dans la liste");
		return Liste;
	}
	
	if (strcmp(Lequel,Liste->nom == 0))
	{
		Remove = Liste;
		Liste = Liste->suiv;
		free(Remove);
		return Liste;
	}
	else
	{
		Liste->suiv= SupprimerBR(Liste->suiv,Lequel);
		return Liste;
	}
}


int main(void)
{
	FILMS *Liste=NULL;
	FILMS *E=NULL;
	FILMS *T;
	FILMS *S;
	INFO_F *film;
	INFO_F *Liste1=NULL;
	INFO_F * E1;
	FILMS *filmRech;
	int save;
	char mot[30];
	char infoModif;
	char Lequel[30];
	
	int choix, nbre, i;

	while(1)
	{
		printf("MENU BASE DE REGLES: \n");
		printf("0- Quitter: \n");
		printf("1 - Afficher \n");
		printf("2- Creer \n");
		printf("3- Rechercher \n");
		printf("4- Modifier \n");
		printf("5- Sauvegarder \n");
		printf("6- Charger \n");
		printf("7- Supprimer un film\n");
		printf("8- Tout supprimer\n");
		scanf("%d",&choix);
		switch(choix)
		{
	
			case 0: return 0;
			
			case 1: AfficherBR(Liste);
					break;
			

			case 2: printf("combien voulez vous rajouter de films ? \n");
					scanf("%d",&nbre);
					for(i=0;i<nbre;i++)
					{
					printf("\n Film n°%d: \n",i+1);
					E=CreerBR();
					Liste=InsererBR(Liste,E);
					}
					break;
			
			case 3:	printf("Quel film voulez-vous rechercher les informations ?");
					scanf("%s", mot);
					filmRech = Rechercher_filmBR(Liste, mot, nbre);
					Afficher_recherche_filmBR(Liste, filmRech);	
					break;
			
			case 4:	printf("\nQuel film voulez-vous modifier?\n");
					scanf("%s",mot);
					
					filmRech = Rechercher_filmBR(Liste, mot, nbre);
					Afficher_recherche_filmBR(Liste, filmRech);
			
					printf("\nQuel informations du film voulez vous modifier ?\n G pour genre\n N pour nom\n D pour date \n O pour origine \nA pour acteur\n R pour realisateur\n");
					scanf("%s",&infoModif);
						
						switch(infoModif)
						{
							case 'N': Modifier_nomBR(Liste, filmRech); break;
										
							case 'G': Modifier_genreBR(Liste, filmRech); break;
										
							case 'D': Modifier_dateBR(Liste, filmRech); break;
							
							case 'O': Modifier_origineBR(Liste, filmRech); break;
							
							case 'A': Modifier_acteurBR(Liste, filmRech); break;
							
							case 'R': Modifier_realisateurBR(Liste, filmRech); break;
							
							default : printf("Mauvais choix\n"); 	
						} 
					break;
					
			case 5: SauvegarderBR(Liste);break;
			
			case 6: lireFicCreerBR();break;
			
			case 7: printf("Quel film voulez vous supprimer ?\n");
					scanf("%s",Lequel);
					SupprimerBR(Liste, Lequel); break;
					
			case 8: desallocBR(Liste);break;
			
			default : printf("Mauvais choix\n"); 
		}
	}
}
