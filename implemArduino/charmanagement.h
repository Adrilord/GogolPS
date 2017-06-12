#ifndef CHARMANAGEMENT
#define CHARMANAGEMENT

//Ecriture de src dans dst de begin à begin+sizeSrc
void strupdate(char* dest, unsigned int begin, char* src, unsigned int sizeSrc);

//Transforme un entier en chaîne de caractères
void int2TabChar(char* dest, unsigned int sizeDest, unsigned int src);

//Transforme un entier long en chaîne de caractères
void long2TabChar(char* dest, unsigned int sizeDest, unsigned long src);

//Transforme un nombre flottant en chaîne de caractères avec un choix de
//précision pour la partie entière et pour la partie décimale
void float2TabChar(char* dest, unsigned int sizeInt, unsigned int sizeDec, float src);

#endif
