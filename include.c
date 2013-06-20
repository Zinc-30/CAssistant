#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FLAG "include"
#define MAXLENTH 204800

char *replace(char *src, char *sub, char *dst);
void removechar(char src[],int x,int l); //removechar l chars(begin at the x th 'char') from "src"
void getfile(char *word);
//void getfile0(char *word);
char* get_path(char *word);
void complete_file(char *cpath, char *path1, char *src);
int label(char src[],int x,int l);
char included[100][20];
int includedcount;
char src1[MAXLENTH];//the code of the include

int include(char *cpath, char *path, char *src)
{
    int n;
    int i;
    char path1[100];//the location of the file
    //char *cpath="C:\\Users\\xin\\Desktop\\test\\1\\";//the location of the codeedit
    //char *path="C:\\Users\\xin\\Desktop\\test\\file.txt";// the location of the c-project
    //char src[1000];//the code of the c
    
    n=strlen(path);
    while (path[n]!='\\') n--;
    for (i=0;i<n;i++) path1[i]=path[i];

    includedcount=0;
    //getfile0(path);
    complete_file(cpath,path1,src);
    //printf("%s",src);
    //scanf("%d",&n);

    return 0;
}

void complete_file(char *cpath, char *path1, char *src)
{
    char pathname[100];
    char filename[100];
    char labeltxt[100];
    char includetxt[MAXLENTH];
    int t,k,tt,i,j,count,q;
    char s[100];
    int flag,fx;
    
    
    int m=0;fx=1;
    while ((strstr(src,"#"))!=0&&fx)
        {
            t=strstr(src,"#")-src;
            i=1;count=strlen(src);
            while (src[t+i]==' ') i++;
            removechar(src,t+1,i-1);
            fx=0;
            if ((strstr(src,"#include"))!=0) {
                 fx=1;
				 tt=strstr(src,"#include")-src;
                 k=tt+8;

                while (src[k]==' '&& k<count)
                  {
                     k++;
                  }
                j=0;
                while (src[k]!=' '&& src[k]!='\n'&& k<count)
                 {
                      filename[j++]=src[k++];
                 }
                 filename[j-1]=0;
                 q=label(src,tt,k-tt+1);
                 for(i=0;i<k-tt+1;i++) labeltxt[i]='X';
                 labeltxt[k-tt+1]=0;
                 if (filename[0]=='"'){
                    removechar(filename,0,1);
                    strcpy(s,path1);
                    strcat(s,filename);
                    strcpy(pathname,s);
                 }  else
                 if (filename[0]=='<') {
                    removechar(filename,0,1);
                    strcpy(s,cpath);
                    //printf("%s",s); 
                    strcat(s,filename);
                    strcpy(pathname,s);
                 }
            
        flag=1;
        for (i=0;i<includedcount;i++)
            if (strcmp(filename,included[i])==0){ flag=0;break; }
        //printf("%s",src);
        if (flag){
                includedcount++;
                getfile(pathname);
                strcpy(included[includedcount],filename);
                strcpy(includetxt,src1);
                strcpy(src,replace(src,labeltxt,includetxt));
        
		}
		}
    }
}



void getfile(char *filename)
{
    FILE *fin;
    char c;
    fin = fopen(filename, "r");
    int i,count;
    i=0;
    while ((c=fgetc(fin)) != -1)
    {
        if (c!='\r') {src1[i] = c;i++;}
       // printf("%c",src[i-1]);
    }
    src1[i]=0;
    fclose(fin);

}

// void getfile0(char *filename)
// {
//     FILE *fin;
//     char c;
//     fin = fopen(filename, "r");
//     int i,count;
//     i=0;
//     while ((c=fgetc(fin)) != -1)
//     {
//         if (c!='\r') {src[i] = c;i++;}
//        // printf("%c",src[i-1]);
//     }
//     src[i]=0;
//     fclose(fin);

// }



int label(char *src,int x,int l)
{
    int i;
    for (i=0;i<l;i++) {
        src[x+i]='X';
    }
    return i;
}

void getPath(char *path)
{
    int i;
    for(i = strlen(path); i>=0 && path[i] != '\\'; i--);
    path[++i] = '\0';
}

char *replace(char *src, char *sub, char *dst)
{
    int pos = 0;
    int offset = 0;
    int srcLen, subLen, dstLen;
    int i;
    char *pRet = "";
    //printf("%s\n",src);
    //printf("%s\n",sub);
    //printf("%s\n",dst);
    srcLen = strlen(src);
    subLen = strlen(sub);
    dstLen = strlen(dst);
    pRet = (char *)malloc(srcLen + dstLen - subLen + 1);//(¨ªa2?¨º?¡¤???????)
    if (NULL != pRet)
    {
        if ((strstr(src,sub))==0) { printf("%s","did not find"); return 0;}
        pos = strstr(src, sub) - src;
        memcpy(pRet, src, pos);
        offset += pos;
        memcpy(pRet + offset, dst, dstLen);
        offset += dstLen;
        memcpy(pRet + offset, src + pos + subLen, srcLen - pos - subLen);
        offset += srcLen - pos - subLen;
        *(pRet + offset) = '\0';
    }
    return pRet;

}


void removechar(char *src,int x,int l) //removechar l chars(begin at the x th 'char') from "src"
{
    int i,subLen=strlen(src);
    for (i=x;i+l<=subLen;i++) src[i]=src[i+l];
}
