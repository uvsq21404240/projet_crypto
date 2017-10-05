#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void puissance_modulaire(mpz_t r ,mpz_t a, mpz_t h, mpz_t n)// on calcule avec cette fonction a^(p-1) mod p , si >0 c est que les deux nombre a pour pgcd(1) donc il sont premier entre eux
{
	mpz_set_ui(r , 1);
	mpz_t mod;
	mpz_init(mod);
	if(mpz_cmp_ui(h,0) == 0) // cas ou la puissance est egale a 0
		{mpz_set_ui(r,1);}
	if(mpz_cmp_ui(a,0) == 0) // cas ou la base est egale a 0
		{mpz_set_ui(r,0);}
	while (mpz_cmp_ui(h,0) > 0)
		{
			mpz_mod_ui(mod,h,2);

			if(mpz_cmp_ui(mod,0)==0) //si il est paire
				{
					mpz_div_ui(h,h,2);  
				}
			else
				{	
					mpz_mul(r,r,a);
					mpz_mod(r,r,n);
					mpz_sub_ui(h,h,1);
					mpz_div_ui(h,h,2);					
				}
		mpz_mul(a,a,a);
		mpz_mod(a,a,n);

		}
}
/*
 * Cette fonction renvoie 0 si n est composé et 1 s'il est probablement premier. On effectue le test de Fermat k fois.
 */


int Fermat(mpz_t n, int k){
	
	mpz_t n_save;
	int i;
	mpz_t a;
	gmp_randstate_t state;
	mpz_t r, h, h2;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned)time(NULL));
	mpz_init(a);
	mpz_init(r);
	mpz_init(h);
	mpz_init(n_save);	
	mpz_sub_ui(h,n,1);
	mpz_init_set(h2, h);
	
	for(i = 0; i < k; i++){
		do{
			mpz_urandomm (a,state,n);
		}while(mpz_cmp_si (a, 0 ) == 0);								//choix de a aléatoire avec 0 < a < n
		
		puissance_modulaire(r, a, h, n);
		mpz_set(h, h2);
		if(mpz_cmp_si (r, 1))
			{
				return 0;
			}
		}
	return 1;
	mpz_clear(n_save);
}
/*
 * Renvoie la décomposition n-1 = 2^s * t
 * n doit etre impair
 */
void decomposer( mpz_t s , mpz_t t , mpz_t n)
{
	mpz_set_ui(s,0);
	mpz_t tpmp ; mpz_t mod; mpz_t cmt;
	mpz_init(tpmp);mpz_init(mod);mpz_init(cmt);
	mpz_sub_ui(tpmp,n,1);// tpmp = n - 1
	mpz_mod_ui(mod,tpmp,2);
	while(mpz_cmp_ui(mod,0)==0)
		{
			mpz_div_ui(tpmp,tpmp,2);
			mpz_add_ui(cmt,cmt,1);
			mpz_mod_ui(mod,tpmp,2);
		}
	mpz_set(t,tpmp);
	mpz_set(s,cmt);
	mpz_clear(tpmp);
	mpz_clear(cmt);
	mpz_clear(mod);
}
/*
 * Cette fonction est équivalente à la boucle pour donnée dans le sujet du devoir.
 * Elle retourne 1 si n est composé et que a est un témoin de Miller et 0 si n est probablement premier pour la valeur de a donnée en argument
 */

int Temoin_de_Miller(mpz_t a, mpz_t n){
	mpz_t s, d, x, n_1;
	mpz_init(s); mpz_init(d); mpz_init(x);
	mpz_sub_ui(n_1, n, 1);
	decomposer(s, d, n);
	puissance_modulaire(x, a, d, n);
	
	if(mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_1) == 0){					//si x = 1 ou x = n-1
		return 0;
	}
	
	while(mpz_cmp_ui(s, 1) > 0){										//tq s > 1
		mpz_mul(x, x, x);
		mpz_mod(x, x, n);
		if(mpz_cmp(x, n_1) == 0)										//si x = n-1
			return 0;
		mpz_sub_ui(s, s, 1);
	}
	mpz_clear(x);mpz_clear(n_1);
	return 1;
}

/*
 * Cette fonction renvoie 0 si n est composé et 1 s'il est probablement premier. On effectue le test de Miller- Rabin k fois.
 */
 
int Miller_Rabin(mpz_t n, int k){
	mpz_t pair;
	mpz_init(pair);
	mpz_mod_ui(pair, n, 2);
	if(mpz_cmp_si (n, 2 ) < 0)			
		return 1;
		
	if(mpz_cmp_si (pair, 0 ) == 0)										//on ne veut tester que des nombres impairs
		return 0;
						
	int i;
	mpz_t a;
	mpz_t n_1;
	mpz_init(a);
	mpz_init(n_1);														//n_1 = n-1
	mpz_sub_ui(n_1, n, 1);
	
	gmp_randstate_t state;
	gmp_randinit_default (state);
	gmp_randseed_ui(state,(unsigned)time(NULL));
	
	for(i = 0; i < k; i++){
		do{
			mpz_urandomm (a,state,n_1);
		}while((mpz_cmp_si (a, 0 ) == 0) || (mpz_cmp_si (a, 1 ) == 0));	//on choisit a aléatoire avec 1 < a < n-1
		if(Temoin_de_Miller(a, n))
			return 0;
	}
	mpz_clear(pair);
	return 1;
}

int main(){
	mpz_t a, h, n, r, h2, t , s, s1 , puis, j;
	mpz_init(n);mpz_init(h);mpz_init(a);mpz_init(r);mpz_init(h2);mpz_init(s);mpz_init(t);mpz_init(s1);mpz_init(puis);mpz_init(j);
	mpz_add_ui(puis,puis,2);
	mpz_set_ui(j,1);
	int i;
	do{
		printf("Quelle est la valeur (supérieure à 2) à tester ? \n");
		gmp_scanf ("%Zd", n);
	}while(mpz_cmp_ui(n, 2) < 0);					
	do{
		printf("Quel est le nombre d'itérations ? \n");
		scanf("%d", &i);
	}while(i < 1);
	if(Fermat(n, i))
		printf("D'après le test de Fermat le nombre est probablement premier \n");
	else
		printf("D'après le test de Fermat le nombre est composé \n");
	if(Miller_Rabin(n, i))
		printf("D'après le test de Miller Rabin le nombre est probablement premier \n");
	else
		printf("D'après le test de Miller Rabin le nombre est composé \n");
	mpz_clear(a);mpz_clear(h);mpz_clear(n);mpz_clear(r);mpz_clear(h2);mpz_clear(s);mpz_clear(t);mpz_clear(s1);mpz_clear(puis);mpz_clear(j);
}
