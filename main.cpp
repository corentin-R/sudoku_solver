#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

void affichage();
void event(int *Pfin, int *Pecriture, int *Psouris_X, int *Psouris_Y,int *Pcase_valide);
void ecrire_fichier(int souris_X, int souris_Y);
void ecrire_grille(int x, int y, int valeur);
void resolution();
int lire_fichier(int souris_X, int souris_Y);


void grille_init(int grille[9][9][10]);
void grille_mofif(int grille[9][9][10], int ligne, int colonne, int valeur);
void grille_afficher(int grille[9][9][10], int num);
int verifLigne(int grille[9][9][10],int ligne, int colonne,int valAVerifier, int possibilite);
int verifColonne(int grille[9][9][10],int ligne, int colonne,int valAVerifier, int possibilite);
int verifGroupe(int grille[9][9][10],int ligne, int colonne,int valAVerifier, int possibilite);
int identiGroupe(int ligne, int colonne);
int resoudre(int grille[9][9][10]);

int main ( int argc, char** argv )
{
    remove("coordonées.txt");
    remove("coordgrille.txt");
    remove("solution.txt");
    affichage();
    return 0;
}

//gèestion de la SDL
void affichage()
{
    /********************************************************************************
    *
    *        initialisation
    *
    *******************************************************************************/

    //variables
    SDL_Surface *ecran = NULL, *fond = NULL, *valide = NULL;
    SDL_Rect coordfond, coordvalide;
    int fin = 0, ecriture = 0, souris_X = 0, souris_Y = 0, case_valide = 0, souris_X_precedent = 0, souris_Y_precedent = 0, i = 0, x = 0, y = 0, v = 0;
    int *Pfin = &fin, *Pecriture = &ecriture, *Psouris_X = &souris_X, *Psouris_Y = &souris_Y, *Pcase_valide = &case_valide;
    FILE *fichier = NULL;

    /* LANCEMENT SDL*/
    SDL_Init(SDL_INIT_VIDEO);

    /* TEST LANCEMENT SDL*/
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }

    /*CARACTERISTIGUE FENÊTRE*/
    ecran = SDL_SetVideoMode(432, 565, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("SUDOKU SOLVER", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_WM_SetIcon(SDL_LoadBMP("logo.bmp"), NULL);

    coordfond.x = 0;
    coordfond.y = 0;

    fond = SDL_LoadBMP("grille.bmp");
    SDL_BlitSurface(fond, NULL, ecran, &coordfond);

    SDL_Flip(ecran);

    event(Pfin,Pecriture,Psouris_X,Psouris_Y,Pcase_valide);

    ecrire_fichier(432,565);

    while((*Psouris_X < 117 || *Psouris_X > 317 || *Psouris_Y < 473 || *Psouris_Y > 522) && *Pfin == 0)
    {
        if(lire_fichier(*Psouris_X, *Psouris_Y) == 0 && (*Psouris_X != 0 && *Psouris_Y != 0))
        {
            coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
            coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
            valide = SDL_LoadBMP("ok.bmp");
            SDL_SetAlpha(valide, SDL_SRCALPHA, 190);
            SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
            SDL_Flip(ecran);
            *Pcase_valide = 1;
        }
        else
        {
            coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
            coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
            valide = SDL_LoadBMP("wrong.bmp");
            SDL_SetAlpha(valide, SDL_SRCALPHA, 190);
            SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
            SDL_Flip(ecran);
            *Pcase_valide = 0;
        }

        souris_X_precedent = *Psouris_X;
        souris_Y_precedent = *Psouris_Y;

        event(Pfin,Pecriture,Psouris_X,Psouris_Y,Pcase_valide);

        SDL_BlitSurface(fond, NULL, ecran, &coordfond);
        fichier = fopen("coordgrille.txt","r+");
        for(i = 0; i<100; i++)
        {
            fscanf(fichier,"%d %d %d", &x, &y, &v);
            switch(v)
            {
            case 1:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("1.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 2:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("2.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 3:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("3.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 4:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("4.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 5:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("5.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 6:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("6.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 7:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("7.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 8:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("8.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 9:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("9.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            }

        }
        fclose(fichier);
        SDL_Flip(ecran);

        if(*Pcase_valide == 1)
        {
            switch(*Pecriture)
            {
            case 1:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("1.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 2:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("2.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 3:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("3.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 4:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("4.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 5:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("5.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 6:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("6.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 7:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("7.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 8:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("8.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            case 9:
                coordvalide.x = *Psouris_X-(*Psouris_X%49)-2;
                coordvalide.y = *Psouris_Y-(*Psouris_Y%49)-2;
                valide = SDL_LoadBMP("9.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                SDL_Flip(ecran);
                ecrire_fichier(*Psouris_X, *Psouris_Y);
                ecrire_grille((*Psouris_X-(*Psouris_X%49))/49, (*Psouris_Y-(*Psouris_Y%49))/49, *Pecriture);
                break;
            }
            *Pecriture = 0;
        }

        if(*Pfin == 0 && souris_X_precedent == *Psouris_X && souris_Y_precedent == *Psouris_Y)
        {
            event(Pfin,Pecriture,Psouris_X,Psouris_Y,Pcase_valide);
        }

    }

    resolution();

    if(*Pfin == 0)
    {
        fond = SDL_LoadBMP("solution.bmp");
        SDL_BlitSurface(fond, NULL, ecran, &coordfond);
        fichier = fopen("solution.txt","r");
        for(i = 0; i<100; i++)
        {
            fscanf(fichier,"%d %d %d", &x, &y, &v);
            switch(v)
            {
            case 1:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("1.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 2:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("2.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 3:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("3.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 4:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("4.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 5:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("5.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 6:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("6.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 7:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("7.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 8:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("8.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            case 9:
                coordvalide.x = 49*x;
                coordvalide.y = 49*y;
                valide = SDL_LoadBMP("9.bmp");
                SDL_BlitSurface(valide, NULL, ecran, &coordvalide);
                break;
            }

        }
        fclose(fichier);
        SDL_Flip(ecran);

    }

    if(*Pfin == 0)
    {
        *Pcase_valide = 0;
        *Pecriture = 0;
        event(Pfin,Pecriture,Psouris_X,Psouris_Y,Pcase_valide);
    }

    SDL_FreeSurface(ecran);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(valide);

    SDL_Quit();
}

void event(int *Pfin, int *Pecriture, int *Psouris_X, int *Psouris_Y, int *Pcase_valide)
{
    int pause = 1;
    SDL_Event action;

    /*boucle évènement*/
    while(pause)//attente action
    {
        if(*Pcase_valide == 1)//si interesser par l'entre d'un chiffre
        {
            SDL_WaitEvent(&action);
            switch(action.type)
            {
            case SDL_QUIT:
                pause = 0;
                *Pfin = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                pause = 0;
                *Pfin = 0;
                *Psouris_X = action.motion.x;
                *Psouris_Y = action.motion.y;
                break;
            case SDL_KEYDOWN:
                switch (action.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    pause = 0;
                    *Pfin = 1;
                    break;
                case SDLK_SPACE:
                    pause = 0;
                    *Pfin = 0;
                    break;
                case SDLK_RETURN:
                    pause = 0;
                    *Pfin = 0;
                    break;
                case SDLK_1:
                    pause = 0;
                    *Pecriture = 1;
                    break;
                case SDLK_KP1:
                    pause = 0;
                    *Pecriture = 1;
                    break;
                case SDLK_2:
                    pause = 0;
                    *Pecriture = 2;
                    break;
                case SDLK_KP2:
                    pause = 0;
                    *Pecriture = 2;
                    break;
                case SDLK_3:
                    pause = 0;
                    *Pecriture = 3;
                    break;
                case SDLK_KP3:
                    pause = 0;
                    *Pecriture = 3;
                    break;
                case SDLK_4:
                    pause = 0;
                    *Pecriture = 4;
                    break;
                case SDLK_KP4:
                    pause = 0;
                    *Pecriture = 4;
                    break;
                case SDLK_5:
                    pause = 0;
                    *Pecriture = 5;
                    break;
                case SDLK_KP5:
                    pause = 0;
                    *Pecriture = 5;
                    break;
                case SDLK_6:
                    pause = 0;
                    *Pecriture = 6;
                    break;
                case SDLK_KP6:
                    pause = 0;
                    *Pecriture = 6;
                    break;
                case SDLK_7:
                    pause = 0;
                    *Pecriture = 7;
                    break;
                case SDLK_KP7:
                    pause = 0;
                    *Pecriture = 7;
                    break;
                case SDLK_8:
                    pause = 0;
                    *Pecriture = 8;
                    break;
                case SDLK_KP8:
                    pause = 0;
                    *Pecriture = 8;
                    break;
                case SDLK_9:
                    pause = 0;
                    *Pecriture = 9;
                    break;
                case SDLK_KP9:
                    pause = 0;
                    *Pecriture = 9;
                    break;
                }
                break;
            }
        }
        else
        {
            SDL_WaitEvent(&action);
            switch(action.type)
            {
            case SDL_QUIT:
                pause = 0;
                *Pfin = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                pause = 0;
                *Pfin = 0;
                *Psouris_X = action.motion.x;
                *Psouris_Y = action.motion.y;
                break;
            case SDL_KEYDOWN:
                switch (action.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    pause = 0;
                    *Pfin = 1;
                    break;
                case SDLK_SPACE:
                    pause = 0;
                    *Pfin = 0;
                    break;
                case SDLK_RETURN:
                    pause = 0;
                    *Pfin = 0;
                    break;
                }
                break;
            }
        }
    }
}

void ecrire_fichier(int souris_X, int souris_Y)
{
    FILE *fichier = NULL;

    fichier = fopen("coordonées.txt", "a+");
    fprintf(fichier, "%d %d\n",souris_X, souris_Y);

    fclose(fichier);

}
int lire_fichier(int souris_X, int souris_Y)
{
    FILE *fichier = NULL;
    int x = 0;
    int y = 0;
    int a = 0;
    int i = 0;

    fichier = fopen("coordonées.txt", "r");

    for(i = 0; i<100; i++)
    {
        fscanf(fichier, "%d %d",&x , &y);
        if(souris_X >= x-(x%49) && souris_X <= x-(x%49)+49 && souris_Y >= y-(y%49) && souris_Y <= y-(y%49)+49)
        {
            a = 1;
        }
    }
    fclose(fichier);

    return a;
}

void ecrire_grille(int x, int y, int valeur)
{
    FILE *fichier = NULL;

    fichier = fopen("coordgrille.txt", "a+");
    fprintf(fichier, "%d %d %d\n",x, y, valeur);

    fclose(fichier);
}
//-----partie algoritme-----------------------------------------------------------------------------------------

void resolution()
{

    int grille[9][9][10];
    int x = 0, y = 0, nombre = 0, k = 0, l = 0, i = 0;

    grille_init(grille);

    //grille_afficher(grille,0);
    FILE *fichier = NULL;

     fichier = fopen("coordgrille.txt", "r");

    for(i = 0; i<100; i++)
    {
        fscanf(fichier, "%d %d %d",&x, &y, &nombre);
        if(nombre != 0)
        {
            grille_mofif(grille,x,y,nombre);
        }
    }

    fclose(fichier);

    resoudre(grille);

    fichier = fopen("solution.txt", "w");


    for(k=0; k<9; k++)
    {
        for(l=0; l<9; l++)
        {
            fprintf(fichier, "%d %d %d\n",k, l, grille[k][l][0]);
        }
    }
    fclose(fichier);

//grille_afficher(grille,0);
// printf("groupe=%d\n", identiGroupe(0,0));
   // printf("après correction\n");
   // grille_afficher(grille,0);

}


void grille_init(int grille[9][9][10])
{
    int i=0, j=0, k=0;

    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            for(k=0; k<10; k++)
            {
                grille[i][j][k] = k;
            }
        }
    }
}

void grille_mofif(int grille[9][9][10], int ligne, int colonne, int valeur)
{
    //plus d'autres chiffres possibles et la première case est égale à la valeure de la case
    grille[ligne][colonne][0]=valeur;
    int i, j, k, l;
    for(k=1; k<10; k++)
    {
        grille[ligne][colonne][k]=0;
    }

    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            // printf("i=%d j=%d  k0=%d\n",i,j,grille[i][j][0] );
            if (grille[i][j][0] == 0)
            {
                //nbCasesVides++;
                for(l=1; l<10; l++)
                {
                    //si on trouve la veleur sur la ligne, la colone ou le groupe
                    if(verifGroupe(grille,i,j,l,0)!=0
                            || verifColonne(grille,i,j,l,0)!=0
                            || verifLigne(grille,i,j,l,0)!=0)
                    {
                        //la posibilité de cette valeure dans cette case devient égale à zéro
                        grille[i][j][l]=0;
                    }
                }
            }
        }
    }
}

/*void grille_afficher(int grille[9][9][10], int num)
{
    printf("affichage grille pour k=%d\n",num);
    int i,j;
    for(i=0; i<9; i++)
    {
        for(j=0; j<9; j++)
        {
            printf("%d", grille[i][j][num]);
        }
        printf("\n");
    }
    printf("\n");
}*/

//posiibilité =0 si on cherche des cases remplies, =1 si on fit la recherche pour de possiblités
int verifLigne(int grille[9][9][10],int ligne, int colonne,int valAVerifier, int possibilite)//1->meme valeure trouvée sur ligne
{
    int j;
    int memeVALsurLigne=0;//on suppose qu'il n'y a pas la même valeure sur la ligne
    for(j=0; j<9; j++)
    {
        if(possibilite==0)
        {
            if(grille[ligne][j][0]!=0 && j!=colonne)
            {
                if(grille[ligne][j][0]==valAVerifier)
                {
                    memeVALsurLigne++;
                }
            }
        }
        else if (possibilite==1)
        {
            if(grille[ligne][j][0]==0 && j!=colonne)
            {
                if(grille[ligne][j][valAVerifier]==valAVerifier)
                {
                    memeVALsurLigne++;
                }
            }
        }
    }
    return memeVALsurLigne;
}

int verifColonne(int grille[9][9][10],int ligne, int colonne,int valAVerifier, int possibilite)//1->meme valeure trouvée sur ligne
{
    int i;
    int memeVALsurColonne=0;//on suppose qu'il n'y a pas la même valeure sur la ligne
    for(i=0; i<9; i++)
    {
        if(possibilite==0)
        {
            if(grille[i][colonne][0]!=0 && i!=ligne)
            {
                if(grille[i][colonne][0]==valAVerifier)
                {
                    memeVALsurColonne++;
                }
            }
        }
        else if (possibilite==1)
        {
            if(grille[i][colonne][0]==0 && i!=ligne)
            {
                if(grille[i][colonne][valAVerifier]==valAVerifier)
                {
                    memeVALsurColonne++;
                }
            }
        }
    }
    return memeVALsurColonne;
}

int verifGroupe(int grille[9][9][10],int ligne, int colonne,int valAVerifier, int possibilite)//1->meme valeure trouvée sur ligne
{
    int i,j;
    int memeVALdansGroupe=0;//on suppose qu'il n'y a pas la même valeure sur la ligne
    int groupe=identiGroupe(ligne,colonne);
    int debutLigneGroupe;
    int debutColonneGroupe;
    switch (groupe)
    {
    case 1:
        debutLigneGroupe=0;
        debutColonneGroupe=0;
        break;
    case 2:
        debutLigneGroupe=0;
        debutColonneGroupe=3;
        break;
    case 3:
        debutLigneGroupe=0;
        debutColonneGroupe=6;
        break;
    case 4:
        debutLigneGroupe=3;
        debutColonneGroupe=0;
        break;
    case 5:
        debutLigneGroupe=3;
        debutColonneGroupe=3;
        break;
    case 6:
        debutLigneGroupe=3;
        debutColonneGroupe=6;
        break;
    case 7:
        debutLigneGroupe=6;
        debutColonneGroupe=0;
        break;
    case 8:
        debutLigneGroupe=6;
        debutColonneGroupe=3;
        break;
    case 9:
        debutLigneGroupe=6;
        debutColonneGroupe=6;
        break;
    default:
        printf("probleme fonction verifGroupe\n");
        break;

    }

    for(i=debutLigneGroupe; i<(debutLigneGroupe+3); i++)
    {
        for(j=debutColonneGroupe; j<(debutColonneGroupe+3); j++)
        {
            if(possibilite==0)
            {
                //si la case n'est pas vide et la case est différente de celle à vérifier
                if(grille[i][j][0]!=0 &&!(i==ligne && j==colonne))
                {
                    if(grille[i][j][0]==valAVerifier)
                    {
                        // printf("[%d %d] %d test verifGroup groupe=%d\n", i, j, valAVerifier, groupe);
                        memeVALdansGroupe++;
                    }
                }
            }
            else if (possibilite==1)
            {
                if(grille[i][j][0]==0 && !(i==ligne && j==colonne))
                {
                    if(grille[i][j][valAVerifier]==valAVerifier)
                    {
                        //printf("[%d %d] %d test verifGroup groupe=%d\n", i, j, valAVerifier, groupe);
                        memeVALdansGroupe++;
                    }
                }
            }
        }
    }
    return memeVALdansGroupe;
}

int identiGroupe(int ligne, int colonne)
{
    int groupe;

    if(ligne<3 && ligne>=0)
    {
        if(colonne<3)
        {
            groupe=1;
        }
        else if(colonne<6 && colonne>=3)
        {
            groupe=2;
        }
        else
        {
            groupe=3;
        }
    }

    else if(ligne<6  && ligne>=3)
    {
        if(colonne<3)
        {
            groupe=4;
        }
        else if(colonne<6 && colonne>=3)
        {
            groupe=5;
        }
        else
        {
            groupe=6;
        }
    }
    else if(ligne<9 && ligne>=6)
    {
        if(colonne<3)
        {
            groupe=7;
        }
        else if(colonne<6 && colonne>=3)
        {
            groupe=8;
        }
        else
        {
            groupe=9;
        }
    }
    return groupe;
}

int resoudre(int grille[9][9][10])
{
    int valRetour = 0;
    int nbCasesVides=0;
    int i,j,k;
    int tour =0;
    do
    {
        nbCasesVides=0;
        tour++;
        printf("tour=%d\n",tour );
       // grille_afficher(grille,0);
//        wait(1000);

        /* grille_afficher(grille,1);
         grille_afficher(grille,2);
         grille_afficher(grille,3);
         grille_afficher(grille,4);
         grille_afficher(grille,5);
         grille_afficher(grille,6);
         grille_afficher(grille,7);
         grille_afficher(grille,8);
         grille_afficher(grille,9);*/
        // printf("test resoudre\n");

        int nb0=0;
        int nb1=0;
        int nb2=0;
        int nb3=0;

        for(i=0; i<9; i++)
        {
            for(j=0; j<9; j++)
            {
                if(grille[i][j][0]==0)//si la case est vide
                {
                    nbCasesVides++;
                    for(k=1; k<10; k++)
                    {


                        if(grille[i][j][k]==k)//si le nb k est possible pour cette case
                        {
                            nb1 = verifLigne(grille,i,j,k,1);
                            nb2 = verifColonne(grille,i,j,k,1);
                            nb3 = verifGroupe(grille,i,j,k,1);

                            //si  il n'y pas  une autre possibilité pour cette valeur sur la ligne/colonne/groupe
                            if(nb1==0 || nb2==0 || nb3==0)
                            {
                               // printf("modif [%d %d] %d\n",i,j,k);
                                //grille_afficher(grille,k);
                                grille_mofif(grille,i,j,k);
                            }

                        }
                        /*if(grille[i][j][k]==0)
                        {
                            nb0++;//on compte le nb de posibilités nulles
                        }*/

                    }
                    //si il n'y a que des possibiltés nulles sauf pour une valeur (8=9-1)
                    if(nb0==8)
                    {
                        //on recherche la valeure pour laquelle il y a une possibilité
                        for(k=1; k<10; k++)
                        {
                            if(grille!=0)
                            {
                                // grille_mofif(grille,i,j,k);
                            }
                        }
                    }
                }

            }
        }
        /*grille_afficher(grille,1);
        grille_afficher(grille,2);
        grille_afficher(grille,3);
        grille_afficher(grille,4);
        grille_afficher(grille,5);
        grille_afficher(grille,6);
        grille_afficher(grille,7);
        grille_afficher(grille,8);
        grille_afficher(grille,9);*/
        if(nbCasesVides>(81-16))
        {
            valRetour = 1; //erreur pas assez de valeur pour résoudre
        }
        printf("nb cases vides = %d\n",nbCasesVides);
    }
    while(nbCasesVides!=0 && tour<70  && valRetour == 0 );
    if(tour>68)
    {
        valRetour = 1; //erreur: la fonction tourne dans le vide
    }
    return valRetour;
}


