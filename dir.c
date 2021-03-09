#include "dir.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int BM_search(char* str1, char* str2)// алгоритм Бойера - Мура поиска слова в строке
{
    int res;
    int T [256];
    int lenstr1= strlen(str1);
    int lenstr2= strlen(str2);
    for (int i = 0; i < 256; i++)
    {
        T[i]=lenstr1;
    }
    for (int i = 0; i < lenstr1 - 1; i++)
    {
        T[str1[i]]=lenstr1 - 1 - i;
    }


    int j,i;
    i = j = lenstr1 - 1;
     while (i<lenstr2 && j >= 0)
     {
        int k = i;
        j = lenstr1 - 1;

        while (j>=0)
        {
            if (str2[k] == str1[j]) 
            {
                j--; k--;
            }
            //если символы не равны то делаем сдвиг согласно таблице
            else
            {
                i = i + T[str2[i]];
                j = lenstr1- 1;
                break;
            }
        }
    }
    /*возврат позиции
    если не найдено	-1
    если найдено		i + 1 - len of P*/
    
    return (j >= 0) ? -1 : i + 1 - lenstr1;
}
    


int main()
{
    int N = 1000;
    char arr[N];
    char* key = (char*)calloc(1,sizeof(char));
    strcpy(key,"i love motemotika");
    DIR *direct=opendir("/home/whitenigga/univer/forlab");
    if(direct==NULL)
    {
        printf("havn't files");
        return -1;
    }
    struct dirent *entry;
    while(entry = readdir(direct))
    {
        FILE *file;
        file = fopen(entry->d_name, "r");
        if (file == NULL)
        {
            printf("end.\n");
            exit(1);
        }
        while (fscanf(file,"%s",arr) != EOF)
        {
            // printf("%s",arr);
            // char* tdm = strtok(key, " ,.:;");//Выделение первой части строки
            // while(tdm != NULL)//выделение последующих частей
            // {
            //     char *istr = strstr(arr,tdm);//поиск слова в строке текстового файла
            //     if(istr != NULL)
            //     {
            //         printf("%s\n", istr);
            //         printf("%s\n",entry->d_name );
            //     } 
            //     tdm = strtok(NULL," ,.:;"); //выделение очередной части строки  
            // }
            // char* event1 = (char*)calloc(1,sizeof(char));
            // char* event2 = (char*)calloc(1,sizeof(char));
            // int j = 0;
            // for(int i = 0; i < strlen(key); i++)
            // {

            //     if((key[i] != ' ')||(key[i] != '.')||(key[i] != ','))
            //     {
            //         event1[j] = key[i];
            //         j++;
            //     }
            //     else
            //     {
            //         // for (int k = 0; k < strlen(arr); i++)
            //         // {
            //         //     int l = 0;
            //         //     if((arr[k] != ' ')||(arr[k] != '.')||(arr[k] != ','))
            //         //     {
            //         //         event2[l] = arr[k];
            //         //         l++;
            //         //     }
            //         //     else
            //         //     {
            //         //         if(strcmp(event1,event2)==0)
            //         //         {
            //         //             printf("%s\n", event1);
            //         //         }
            //         //         event1 = NULL;
            //         //     }
                        
            //         // }
            //         // event1 = NULL; 
            //         printf("%s\n",event1);
            //         printf("%s\n",arr);
            //         if(strcmp(event1,arr)==0)
            //         {
            //             printf("%s\n", event1);
            //         }
            //         event1 = NULL;
            //         j = 0;
            //     }


            // }
            // free(event1);
            // free(event2);
            int el = BM_search(arr, key);
            
            if(el!=-1)
            {
                printf("this is word:%s , path :/home/whitenigga/univer/forlab/%s\n",arr,entry->d_name);
            }
        }
        fclose(file);

    }
    closedir(direct);
    
    
    return 0;

}
