#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include.h"

//char src[1000];

int define(char *src)
{
    char thechange[100][2][30];
    char tobechange[100],change[100];
    int countchange,f,i,k,j,l,m,n;
    int flag;
    int count,t,tt;
    count=strlen(src);
    countchange=0;
    t=tt=0;
    k=0;

    //strcpy(src,"#include\n#define x 1\nxx xx x");
    //printf("%s",src);
    count=strlen(src);
    // for (i=0;i<3;i++) src[i]=' ';
    // printf("%s",src);
    // //printf("%d\n",strstr(src,"#")-src);
    // scanf("%d",&count);


    while ((strstr(src,"#"))!=0)
        {
            t=strstr(src,"#")-src;
            i=1;
            while (src[t+i]==' ') i++;
            removechar(src,t+1,i-1);

            if ((strstr(src,"#define"))!=0) {
                 tt=strstr(src,"#define")-src;
                 k=strstr(src,"#define")-src+7;

                 while (src[k]==' '&& k<count)
                  {
                     k++;
                  }
                j=0;

                 while (src[k]!=' '&& src[k]!='\n'&& k<count)
                 {
                      tobechange[j++]=src[k++];
                 }
                 tobechange[j]=0;
                 flag=1;
                 while (src[k]==' '&& k<count)
                        {
                            k++;
                        }
                 j=0;
                 while (/*src[k]!=' '&& */src[k]!='\n' && k<count)
                        {
                           change[j++]=src[k++];
                        }
                 change[j]=0;
                 for (m=0; m<countchange; m++) if (strcmp(thechange[m][0],tobechange)==0)
                     {
                         flag=0;
                         break;
                     }
               // printf("change 1:%s   2:%s",tobechange,change);
                 if (flag){
                     strcpy(thechange[countchange][0],tobechange);
                     strcpy(thechange[countchange][1],change);
                     countchange++;
                 }
                 //printf("//%d%c---%d%c\n",tt,src[tt],k,src[k]);
                 removechar(src,tt,k-tt+1);
                 //printf("//%d%c---%d%c\n",tt,src[t],k+1,src[k+1]);
                 //printf("%s",src);
            }else{
                i=1;
                while (src[t+i]!='\n') i++;
               // printf("%d%c---%d%c",t,src[t],i+t,src[t+i]);
                removechar(src,t,i+1);
               // printf("%s",src);
            }
        }
    for (j=0;j<countchange;j++)
    while ((strstr(src,thechange[j][0]))!=0)
    {
            //printf("change: 1:%s   2:%s\n",thechange[j][0],thechange[j][1]);
            strcpy(src,replace(src,thechange[j][0],thechange[j][1]));
    }

    //printf("%s",src);
    //scanf("%d",&count);
    return 0;
}
