# ESME-Concurrent-Computing
Contains programs using the MPI library.

Disclaimer :

Les codes forunis sont fait selon ma logique, il est donc vivement recommandé de vous les approprier en les refaisant à votre sauce; mes méthodes ne sont pas parfaites. Je vous demande de donner les liens vers ce GitHub ou de ne pas alterer les codes si vous les partagez.
Surtout, cherchez par vous même avant de copier les codes, vous trouverez tout un tas d'info sur le net. Parmi les sites que j'utilise :
https://stackoverflow.com/
http://www.cplusplus.com/
https://openclassrooms.com/

Conseils d'utilisation :

Chaque code est fonctionnel sur ma machine, avec la version de MPICH fournie par le professeur.

Pour la compilation, il faut soit :
- passer en ligne de commande (méthode détaillée plus bas.)
- configurer vorez IDE.

Pour compiler et executer un programme en mode CLI (Command Line Interface) avec MPICH et MinGW installé et configuré comme il faut (expliqué dans les fichiers fournis par le professeur) :

1) lancer la CMD en tant qu'administrateur.
2) Se placer dans le dossier contenant le fichier .c (exemple : cd C:\Users\NATHAN\Documents\MPI) Pour connaitre le chemin d'accès n'hésitez pas à effectuer un clic-droit -> propriétés.
3) Une fois dans le bon dossier entrez : gcc -I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -o test.exe test.c "C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x86\msmpi.lib" (Remplacez "test.c" et "test.exe" par les noms du fichier (exemple TP_ex3_simpson.c)
4) Si la compilation se déroule sans erreur : mpiexec -n 8 test.exe (Il faut bien entendu remplacer test.exe par le nom spécifié en 3. Le 8 peut être remplcé par une autre valeur (qui doit être un entier), celà correspond au nombre total de processus ici 8)


