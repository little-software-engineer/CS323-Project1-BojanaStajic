//Projektni zadatak iz predmeta CS323 na temu konzolne aplikacije "80s Retro Video Club" koja sluzi za iznajmljivanje filmova iz video kluba.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include<time.h>
#define BUFFER_SIZE 50


int pretraziFilm();
int filmPodaci();
void iznajmiFilm();

struct film {
    int id;
    char naziv[20];
    int godina;
    char opis[40];
    char glumci[40];
    
  
};



int main()
{
    const char* messages[] = { //niz koji cuva stringove koji su citati iz filmova a nasumicno se pojavljuju kao pozdravna poruka svaki put kada se aplikacija pokrene
        "Who's that girl?",
        "E.T. phone home.",
        "Nobody puts Baby in a corner",
        "Say hello to my little friend!",
        "Yippee-Ki-Yay"
    };
     
    srand(time(0));


        printf("%s\n", messages[rand() % 5]);
    
        printf("Pritisnite bilo koje dugme za pokretanje...\n");  //Pocetak menija sa korisnickim unosima
        getch();

        while (1) {
            printf("\n\n80s Video Club");
            printf("\n\n 1. Pretrazi film\n");
            printf(" 2. Prikaz svih filmova\n");
            printf(" 3. Iznajmi film\n");
            printf(" 4. Izadji\n");
            printf("\n");

            int odabir;

            scanf_s(" %d", &odabir);

            switch (odabir) {
            case 1:
                pretraziFilm();
                printf("\n  Pritisni bilo koje dugme za izlaz.......\n");
                getch();
                break;
            case 2:
                filmPodaci();
                break;
            case 3:
                iznajmiFilm();
                break;
            case 4:

                printf("\n Hvala na poverenju. Video Club phones home!\n\n");
                return 0;

            default:
                printf("\nInvalid option");
                getch();
            }

        }

       

        
      
       

}


void iznajmiFilm() { //metoda trazi input od korisnika i kreira jedinstveni tekstualni fajl koji cuva podatke o njegovoj transakciji, odnosno iznajmljivanju

    char ponovi;
    time_t t;   
    time(&t);

    do {

        printf("\nCreating iznajmljivanje.txt...\n");
        FILE* fp = fopen("iznajmljivanje.txt", "w");
        if (fp == NULL) {
            printf("Error: iznajmljivanje.txt nije kreiran.\n");
            fclose(fp);
            return;
        }
      
        int filmId; //korisnik ovo vidi u ponudi koji je broj u pitanju
        char ime[20];
        char prezime[20];
        char datumVracanja[20] = "14/7/2023";

        srand(time(0));
        double  cena = (rand() %
            (900 - 400 + 1)) + 400;




        printf("\n\nUnesite id filma: ");
        scanf("%d", &filmId);
        printf("\nUnesite Vase ime: ");
        scanf(" %s", &ime);
        printf("\nUnesite Vase prezime: ");
        scanf("%s", &prezime);
        printf("\nDatum i vreme iznajmljivanja: %s", ctime(&t));
        printf("Datum vracanja: %s\n", datumVracanja);
        printf("Ukupna cena: %f dinara\n", cena);




        fprintf(fp, "Film id: %d\nIme: %s\nPrezime: %s\nDatum iznajmljivanja: %s\nDatum vracanja: %s\nUkupna cena: %f dinara\n", filmId, ime, prezime, ctime(&t), datumVracanja, cena);

        fclose(fp);
        printf("Uneto uspesno!\n");

        printf("Da li zelite napraviti jos jednu porudzbinu?(d/n) : ");
        scanf("%s", &ponovi);
        if (ponovi == 'n') {
            printf("\n Hvala na poverenju. Video Club phones home!\n\n");
            exit(0);
        }
    } while (ponovi == 'd' || ponovi == 'D');
      


    
}

        int filmPodaci() { //metoda za citanje podataka o filmovima iz fajlova i prikazivanja istih korisniku u konzoli

            FILE* textfile;
            char* text;
            long    numbytes;

            textfile = fopen("filmovi.txt", "r");
            if (textfile == NULL)
                return 1;

            fseek(textfile, 0L, SEEK_END);
            numbytes = ftell(textfile);
            fseek(textfile, 0L, SEEK_SET);

            text = (char*)calloc(numbytes, sizeof(char));
            if (text == NULL)
                return 1;

            fread(text, sizeof(char), numbytes, textfile);
            fclose(textfile);

            printf(text);

        }

        int pretraziFilm() { //metoda pretrazuje ponudu na osnovu unetog stringa korisnika te mu vraca sta se nalazi u katalogu a da se poklapa sa njegovom pretragom (naziv filma, glumci, ...)
            char nametoSearch[BUFFER_SIZE];
            char names[BUFFER_SIZE];
            
            FILE* fPtr;
            if (fPtr = fopen("filmovi.txt", "r"))
            {
                //podeseno na 0 ali indikuje da li je rezultat pronadjen, a u tom slucaju je 1
                int fountRecord = 0;
                printf("Pronadjeni rezultati : ");
                //koristimo fgets jer je pretraga mozda sa razmacima kada je u pitanju naziv filma ili ime i prezime glumca
                fgets(nametoSearch, BUFFER_SIZE, stdin);
             
                nametoSearch[strlen(nametoSearch) - 1] = '\0';

                while (fgets(names, BUFFER_SIZE, fPtr))
                {
                    // strstr vraca startnu adresu podstringa u slucaju ako postoji
                    if (strstr(names, nametoSearch))
                    {
                        printf("%s\n", names);
                        fountRecord = 1;
                    }
                }
                if (!fountRecord)
                    printf("%s nije pronadjeno\n", nametoSearch);

                fclose(fPtr);
            }
            else
            {
                printf("Fajl ne moze da se otvori!\n");
            }
            return 0;

        }
