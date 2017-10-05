Dm de cryptographie, test de primalité Milleur-Rabin , Fermat.

Pour compiler : make
Pour executer : ./dm_elkael_momenzadeh

Fonctions 

-la fonction puissance modulaire calcule une puissance modulaire avec une complexité de log(n), elle renvoie la valeur r qui est la valeur de retour, elle utilise 4 variables de typs mpz_t, la 1er pour stocker la valeur, le second la base, la troisième la puissance, le dernier le modulo.
-la fonction décomposer permet de décomposer un nombre impair par puissance de 2 * le reste, la fonction prend 3 arguments mpz_ts la 1er stockée s, le second stock t et le dernier et la valeur du modulo ou du nombre à tester.
-la fonction Fermat appelle la fonction puissance modulaire . Cette fonction fait varier la base afin de prouver que le nombre n n'est pas divisible.
-la fonction Miller-Rabin appellel la fonction puissance modulaire et la fonction décomposer, elle permet de vérifier si un nombre et compose ou non.


Projet fait à 2 , Thomas Momenzadeh , Maxime Elkael