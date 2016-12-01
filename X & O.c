#include<stdio.h>

int tabela[3][3]={ {-1,-2,-3},{-4,-5,-6},{-7,-8,-9} };
int i,j;

    //Declaratiile functiilor folosite
void afisare();
int completare();
int winner();
void computer();

int main()
{
    int linie,coloana,k;

	printf( "       X & 0 \n \n " );

	again:  // again este eticheta ce ajuta la reluarea jocului dupa ce acesta a luat sfarsit
	k=-1;

	//Daca jocul este reluat atunci matricea este reinitializata
    if( winner()==1 || winner()==0 || completare()==1 ){
        for( i=0;i<3;i++ ){
            for( j=0;j<3;j++ ){
                tabela[i][j]=k;
                k--;
            }
        }
    }

	printf("\n\n  Apasati o tasta pentru a incepe jocul.\n \n");
	getch(); // Functia getch citeste un caracter prin apasarea unei taste.Citirea se realizeaza fara ecou

    system ("cls"); // Sterge ecranul si este echivalenta cu functia clrscr()
    afisare();
    /*
        Se verifica daca jocul a luat sfarsit si anume daca:
    1.Matricea este completa,adica nu mai exista spatii libere.
        Acest lucru se efectueaza prin functia completare()
    2.Unul dintre jucatori a castigat.
        Acestu lucru se efectueaza prin functia winner()
    */
    while( completare()==0 && winner()<0 ){


        printf("\n Introduceti coordonatele lui X: \n");

        back: // Eticheta back ajuta la reintroducerea coordonatelor in cazul in care acestea sunt gresite
        printf("\n    Linia: ");
        scanf( "%d",&linie );

        printf( "    Coloana: " );
        scanf( "%d",&coloana );

    //Se verifica daca coordonatele introduse corespund unei pozitii din matrice
        if( linie<0 || linie>2 || coloana<0 || coloana>2 ){
            printf( "\n Ati introdus gresit coordonatele.Introduceti din nou! \n" );
            goto back; // instructunea de salt ne ajuta la reintroducerea coordonatelor de la eticheta back de mai sus
        }

    //Se verifica daca coordonatele introduse reprezinta o pozitie ocupata de unul dintre jucatori
        if( ( tabela[linie][coloana]==1 ) || ( tabela[linie][coloana]==0 ) ){
            printf( "\n Aceasta pozitie este ocupata.Introduceti din nou! \n" );
            goto back;
        }
    //Daca coordonatele introduse sunt bune atunci pozitia corespunzatoare va primi valuarea 1
        tabela[linie][coloana]=1;

    // Variabila k numara pozitiile libere din matrice
		k=0;
		for( i=0;i<3;i++ ){
			for( j=0;j<3;j++ ){
				if( tabela[i][j]<0 ){
					k++;
				}
			}
		}
    //Daca exista cel putin o pozitie libera si inca nu ati castigat se apeleaza functia computer()
		if( k>=1 ){
			if( winner()!=1 ){
			computer();
			}
		}
        system ("cls");
        afisare();

    }
    /*Se verifica daca exista un castigator si anume daca :
        - functia winner() returneaza 1 atunci ati castigat
        -functia winner() returneaza 0 atunci a castigat calculatorul
    */

    if( winner()==1 ){
        printf( "\n   Ai castigat! \n Felicitari! \n \n" );
        printf( "Pentru a juca din nou apasa tasta R. \n\n" );

        if( getch()=='r' ) // daca tasta apasata corespunde caracterului 'R' atunci jocul se reia cu ajutorul instructiunii de salt goto
            goto again;
    }

    if( winner()==0 ){
        printf( "\n   Ai pierdut! \n Continua sa joci si vei reusi! \n \n" );
        printf( "Pentru a juca din nou apasa tasta R \n \n" );

        if( getch()=='r' )
            goto again;
    }

		// Se verifica daca toate pozitiile matricei sunt ocupate ceea ce inseamna ca jocul s-a sfarsit la egalitate
    if( completare()==1 ){
        printf( "\n   Remiza! \n Ai jucat bine,dar nu este suficient. \n \n" );
        printf( "Pentru a juca din nou apasa tasta R " );

        if( getch()=='r' )
            goto again;
    }
}

/*
        Functia afisare() creaza tabelul necesar jocului.
    Initial toate elementele matricei sunt negative,fiind reprezentate prin spatiu.
    Se va afisa caracterul X pentru toate elementele matricei ce vor avea valuarea 1.
    Se va afisa caracterul O pentru toate elementele matricei ce vor avea valuarea 0.
*/
void afisare()
{
    printf("-------------\n");
    for( i=0;i<3;i++ ){
            printf("| ");
        for( j=0;j<3;j++ ){

            if( tabela[i][j]==1 ){
                printf("X");
                }
            else if( tabela[i][j]==0 ){
                printf("O");
            }
                else{
                    printf(" ");
                }
            printf(" | ");
        }
        printf("\n-------------\n");
    }
}

int completare()	//Returneaza 1 daca matricea este completa(contine numai valori de 0 si 1)sau 0 in caz contrar
{
    for( i=0;i<3;i++ ){
        for( j=0;j<3;j++ ){
            if( tabela[i][j]<0 ){
                return 0;
            }
        }
    }
    return 1;
}

int winner() // Returneaza 1 daca ati castigat,0 daca a castigat calculatorul si -1 daca inca nu exista un invingator
{
	int ok,var;

	/*Se verifica daca exista un castigator pe linii si anume daca se gaseste pe oricare dintre linii aceasi valuare
	atunci valuarea respectiva este returnata
    */
	for( i=0;i<3;i++ ){
		ok=1;
		for( j=0;j<3;j++ ){
			if( tabela[i][j]<0 ){
				ok=0; /* daca pozitia respectiva are valuare negativa inseamna ca este o pozitie libera pe acea linie si automat
					  nu exista un castigator
					*/
			}

			if( j==0 ){
				var=tabela[i][j]; //var retine prima pozitie a liniei fiind comparat ulterior cu celelalte valori aflate pe aceasi linie
			}

			if( tabela[i][j]!=var ){
				ok=0;	/*daca valorile pozitiilor liniei curente nu sunt egale cu valuarea lui var inseamna ca
						nu exista un castigator pe linia respectiva
					*/
			}
		}
		if( ok==1 ){
			return var;	//valuarea lui var este returnata numai in cazul in care aceasta se gaseste pe toate pozitiile liniei curente
		}
    }

	/*Se verifica daca exista un castigator pe coloane si anume daca se gaseste pe oricare dintre coloane aceasi valuare
	atunci valuarea respectiva este returnata
	*/
	for(i=0;i<3;i++){
		ok=1;
		for (j=0;j<3;j++){
			if(tabela[j][i]<0){
				ok=0; /* daca pozitia respectiva are valuare negativa inseamna ca este o pozitie libera pe acea coloana si automat
					  nu exista un castigator
					*/
			}

			if(j==0){
				var=tabela[j][i];	 //var retine prima pozitie a coloanei fiind comparat ulterior cu celelalte valori aflate pe coloana
			}

			if (tabela[j][i]!=var){
				ok=0; /*daca valorile pozitiilor coloanei curente nu sunt egale cu valuarea lui var inseamna ca nu exista un castigator
					  pe coloana respectiva
					*/
			}
		}
		if (ok==1){
			return var; //valuarea lui var este returnata numai in cazul in care aceasta se gaseste pe toate pozitiile coloanei curente
		}
	}

	/*Se verifica daca exista un castigator pe diagonala principala si anume daca se gaseste aceasi valuare pe toate pozitiile
	diagonalei principale atunci valuarea respectiva este returnata
	*/
	ok=1;
	for(i=0;i<3;i++){
		for (j=0;j<3;j++){
			if (i==j && tabela[i][j]<0){
				ok=0; /* daca pozitia respectiva are valuare negativa inseamna ca este o pozitie libera pe diagonala principala
					  si automat nu exista un castigator
					*/
			}

			if(i==j==0){
				var=tabela[i][j]; //var retine prima pozitie a diagonalei principale fiind comparat ulterior cu celelalte valori aflate pe aceasta
			}

			if (i==j && tabela[i][j]!=var){
				ok=0;   //daca valorile pozitiilor diagonalei principale nu sunt egale cu valuarea lui var inseamna ca nu exista un castigator

			}
		}
	}
	if (ok==1){
		return var; //valuarea lui var este returnata numai in cazul in care aceasta se gaseste pe toate pozitiile diagonalei principale
	}

	/*Se verifica daca exista un castigator pe diagonala secundara si anume daca se gaseste aceasi valuare pe toate pozitiile
	diagonalei secundare atunci valuarea respectiva este returnata
	*/
	ok=1;
	for( i=0;i<3;i++ ){
		for( j=0;j<3;j++ ){
			if( i+j==2 && tabela[i][j]<0 ){
				ok=0; /* daca pozitia respectiva are valuare negativa inseamna ca este o pozitie libera pe diagonala secundara
					  si automat nu exista un castigator
					*/
			}

			if( i+j==2 && i==0 && j==2  ){
				var=tabela[i][j]; //var retine prima pozitie a diagonalei secundare fiind comparat ulterior cu celelalte valori aflate pe aceasta
			}

			if( i+j==2 && tabela[i][j]!=var ){
				ok=0; //daca valorile pozitiilor diagonalei secundare nu sunt egale cu valuarea lui var inseamna ca nu exista un castigator
			}
		}
	}
	if( ok==1 ){
		return var; //valuarea lui var este returnata numai in cazul in care aceasta se gaseste pe toate pozitiile diagonalei secundare
	}

    return -1; //in cazul in care nu exista un castigator atunci se va returna -1
}

	//Computer() este functia ce realizeaza modul de "gandire" al calculatorului
void computer()
{
    int linie,coloana,ok,var,k;

	//Se parcurge matricea pe lini
    for( i=0;i<3;i++ ){
		k=0;
        for( j=0;j<3;j++ ){
            if( tabela[i][j]==0 ){ //k este echivalent cu numarul aparitiilor valorii 0 pe linia curenta
                k++;
				}
		}
	//daca valoarea 0 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber de pe linie pentru a castiga
		if( k==2 ){
            if( tabela[i][0]<0 ){
                linie=i;
                coloana=0;
                goto jump;	/*Daca pozitia este negativa,adica libera,atunci instructiunea de salt va trimite coordonatele pozitiei respective
						la sfarsitul functiei computer() unde va obtine valuarea 0
						*/
			}
            else if( tabela[i][1]<0 ){
                linie=i;
                coloana=1;
                goto jump;
            }
            else if( tabela[i][2]<0 ){
                linie=i;
                coloana=2;
                goto jump;
            }
		}
    }

	//Se parcurge matricea pe coloane
    for( i=0;i<3;i++ ){
        k=0;
        for( j=0;j<3;j++ ){
			 if( tabela[j][i]==0 ){
				   k++; //k este echivalent cu numarul aparitiilor valorii 0 pe coloana curenta
				}
        }
	//daca valoarea 0 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber de pe coloana pentru a castiga
        if( k==2 ){
            if( tabela[0][i]<0 ){
                linie=0;
                coloana=i;
                goto jump;
            }
            else if( tabela[1][i]<0 ){
                linie=1;
                coloana=i;
                goto jump;
            }
            else if( tabela[2][i]<0 ){
                linie=2;
                coloana=i;
                goto jump;
            }
        }
    }

	//Se parcurge diagonala principala a matricei
    k=0;
    for( i=0;i<3;i++ ){
        for( j=0;j<3;j++ ){
			if( i==j && tabela[i][j]==0 ){
                k++; //k este echivalent cu numarul aparitiilor valorii 0 pe diagonala principala
			}
			i++; // valuarea lui i creste pentru a parcurge mai repede diagonala
        }
    }
		/*daca valoarea 0 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber de pe diagonala principala
	pentru a castiga
    */
	if( k==2 ){
		 if( tabela[0][0]<0 ){
			linie=0;
			coloana=0;
			goto jump;
		 }
		 else if(tabela[1][1]<0){
			linie=1;
			coloana=1;
			goto jump;
		 }
		 else if( tabela[2][2]<0 ){
			 linie=2;
			coloana=2;
			goto jump;
		 }
     }

	//Se parcurge diagonala secundara a matricei
     k=0;
     for( i=0;i<3;i++ ){
        for( j=2;j>=0;j-- ){
            if( i+j==2 && tabela[i][j]==0 ){
				k++; //k este echivalent cu numarul aparitiilor valorii 0 pe diagonala secundara
			}
			i++; // valuarea lui i creste pentru a parcurge mai repede si mai eficient diagonala
		}
    }
	 /*daca valoarea 0 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber de pe diagonala secundara
	pentru a castiga
    */
    if( k==2 ){
		if( tabela[0][2]<0 ){
			linie=0;
			coloana=2;
			goto jump;
		}
		else if( tabela[1][1]<0 ){
					linie=1;
					coloana=1;
					goto jump;
				}
		else if( tabela[2][0]<0 ){
					linie=2;
					coloana=0;
					goto jump;
				}
    }

    for( i=0;i<3;i++ ){
		k=0;
        for( j=0;j<3;j++ ){
            if( tabela[i][j]==1 ){
                k++;  //k este echivalent cu numarul aparitiilor valorii 1 pe linia curenta
				}
		}
		/*daca valoarea 1 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber
	de pe linie pentru a va impiedica sa castigati
	*/
		if( k==2 ){
            if( tabela[i][0]<0 ){
                linie=i;
                coloana=0;
                goto jump;
            }
            else if( tabela[i][1]<0 ){
                linie=i;
                coloana=1;
                goto jump;
            }
            else if( tabela[i][2]<0 ){
                linie=i;
                coloana=2;
                goto jump;
            }
		}
    }

	//Se parcurge matricea pe coloane
    for( i=0;i<3;i++ ){
        k=0;
        for( j=0;j<3;j++ ){
			 if( tabela[j][i]==1 ){
				   k++; //k este echivalent cu numarul aparitiilor valorii 1 pe coloana curenta
				}
        }
		/*daca valoarea 1 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber
	de pe coloana pentru a va impiedica sa castigati
	*/
        if( k==2 ){
            if( tabela[0][i]<0 ){
                linie=0;
                coloana=i;
                goto jump;
            }
            else if( tabela[1][i]<0 ){
                linie=1;
                coloana=i;
                goto jump;
            }
            else if( tabela[2][i]<0 ){
                linie=2;
                coloana=i;
                goto jump;
            }
        }
    }

	//Se parcurge diagonala principala a matricei
    k=0;
    for( i=0;i<3;i++ ){
        for( j=0;j<3;j++ ){
			if( i==j && tabela[i][j]==1 ){
                k++;  //k este echivalent cu numarul aparitiilor valorii 1 pe diagonala principala
			}
			i++;
        }
    }
		/*daca valoarea 1 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber
	de pe diagonala pentru a va impiedica sa castigati
	*/
    if( k==2 ){
		 if( tabela[0][0]<0 ){
			linie=0;
			coloana=0;
			goto jump;
		 }
		 else if(tabela[1][1]<0){
			linie=1;
			coloana=1;
			goto jump;
		 }
		 else if( tabela[2][2]<0 ){
			 linie=2;
			coloana=2;
			goto jump;
		 }
     }

	//Se parcurge diagonala secundara a matricei
     k=0;
     for( i=0;i<3;i++ ){
        for( j=2;j>=0;j-- ){
            if( i+j==2 && tabela[i][j]==1 ){
				k++;
			}
			i++;
		}
    }
	 	/*daca valoarea 1 se gaseste de 2 ori si este randul calculatorului atunci acesta va puna O pe spatiul liber
	de pe diagonala pentru a va impiedica sa castigati
	*/
    if( k==2 ){
		if( tabela[0][2]<0 ){
			linie=0;
			coloana=2;
			goto jump;
		}
		else if( tabela[1][1]<0 ){
					linie=1;
					coloana=1;
					goto jump;
				}
		else if( tabela[2][0]<0 ){
					linie=2;
					coloana=0;
					goto jump;
				}
    }

	//Se parcurge matricea pe linii
    for( i=0;i<3;i++ ){
		ok=1;
        for( j=0;j<3;j++ ){
            if( tabela[i][j]==1 ){ /*daca pe linia curenta exista vreo valuare egala cu 1 atunci calculatorul nu va pune 0 pe linia respectiva
								   deoarece nu poate sa castige pe aceasta
								*/
				ok=0;
				}
		}
        if( ok==1 ){		//daca linia contine numai valori negative sau egale cu 0 atunci calculatorul va pune pe pozitia urmatoare valoarea 0
			if( tabela[i][0]<0 ){
				linie=i;
				coloana=0;
				goto jump;
			}
			else if( tabela[i][1]<0 ){
					linie=i;
					coloana=1;
					goto jump;
				}
			else if( tabela[i][2]<0 ){
					linie=i;
					coloana=2;
					goto jump;
				}
        }
	}

	//Se parcurge matricea pe coloane
    for( i=0;i<3;i++ ){
        ok=1;
        for( j=0;j<3;j++ ){
			 if( tabela[j][i]==1 ){ /*daca pe coloana curenta exista vreo valuare egala cu 1 atunci calculatorul nu va pune 0 pe coloana respectiva
								   deoarece nu poate sa castige pe aceasta
								*/
				   ok=0;
				}
        }
        if( ok==1 ){  //daca pe coloana se gasesc numai valori negative sau egale cu 0 atunci calculatorul va pune pe pozitia urmatoare valoarea 0
			if( tabela[0][i]<0 ){
				linie=0;
				coloana=i;
				goto jump;
			}
			else if( tabela[1][i]<0 ){
				linie=1;
				coloana=i;
				goto jump;
			}
			else if( tabela[2][i]<0 ){
				linie=2;
				coloana=i;
				goto jump;
			}
		}
	}

	//Se parcurge diagonala principala a matricei
    ok=1;
    for( i=0;i<3;i++ ){
        for( j=0;j<3;j++ ){
			if( i==j && tabela[i][j]==1 ){ /*daca pe diagonala principala exista vreo valuare egala cu 1 atunci calculatorul nu va pune 0
										 pe pozitiile ei deoarece nu poate sa castige pe aceasta
								*/
					ok=0;
			}
			i++;
        }
    }

     if( ok==1 ){   //daca pe diagonala se gasesc numai valori negative sau egale cu 0 atunci calculatorul va pune pe pozitia urmatoare valoarea 0
		 if( tabela[0][0]<0 ){
			linie=0;
			coloana=0;
			goto jump;
		 }
		 else if(tabela[1][1]<0){
			linie=1;
			coloana=1;
			goto jump;
		 }
		 else if( tabela[2][2]<0 ){
			 linie=2;
			coloana=2;
			goto jump;
		 }
     }

	 //Se parcurge diagonala secundata a matricei
     ok=1;
     for( i=0;i<3;i++ ){
        for( j=2;j>=0;j-- ){
            if( i+j==2 && tabela[i][j]==1 ){ /*daca pe diagonala secundara exista vreo valuare egala cu 1 atunci calculatorul nu va pune 0
										 pe pozitiile ei deoarece nu poate sa castige pe aceasta
								*/
				ok=0;
			}
			i++;
		}
    }

    if( ok==1 ){   //daca pe diagonala se gasesc numai valori negative sau egale cu 0 atunci calculatorul va pune pe pozitia urmatoare valoarea 0
		if( tabela[0][2]<0 ){
			linie=0;
			coloana=2;
			goto jump;
		}
		else if( tabela[1][1]<0 ){
					linie=1;
					coloana=1;
					goto jump;
				}
		else if( tabela[2][0]<0 ){
					linie=2;
					coloana=0;
					goto jump;
				}
    }

	//In cazul in care nu exista nicio posibilitate de a castiga calculatorul va marca prima pozitie libera(negativa) cu 0
    for( i=0;i<3;i++ ){
        for( j=0;j<3;j++ ){
            if( tabela[i][j]<0 ){
                linie=i;
                coloana=j;
                goto jump;
            }
        }
    }

    jump: //eticheta ce ajuta la transmiterea coordonatelor
    tabela[linie][coloana]=0;
}
