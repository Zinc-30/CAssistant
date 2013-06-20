#include <stdio.h>
#include <math.h>
#include <string.h>
const M = 10000;
struct Hash
{
    int count;
    int hashTab[10];/*哈希表长度为10；存放10个整数来记录出现关键字的次数其中hashTab【0】-【9】分别为break,
    char,class,do,else,//for,if,int,void,while*/
    char file[1000];
} hash[2];
int fileProcessed(int x,char sourceData[]);
//将处理后的文件保存到字符数组里，该函数返回字符数组里字符的总个数
double possibality();
//根据两个哈希表和已有公式计算相似度
void Cumulating(int x,int location);
//增加特征字符数
void calcuNum(int x);
//计算特征字符数
int compare(char *s1, char *s2)
{
    //char s1[M],s2[M];
    int i,ans;
    //strcpy(s1,"abcde if");
    //strcpy(s2,"as");
    hash[0].count=fileProcessed(0,s1);
    hash[1].count=fileProcessed(1,s2);
    //printf("%s\n",hash[0].file);
    calcuNum(0);
    calcuNum(1);
    ans=possibality();
    //for (i=0;i<10;i++) printf("%d \n",hash[0].hashTab[i]);
    printf("%d\n",ans);
    return ans;
}
void Cumulating(int x,int location)
{
    hash[x].hashTab[location] ++;
}
int  fileProcessed(int x,char sourceData[])
{
    int i=0;
    while (sourceData[i])
    {
        if(sourceData[i] == '(' || sourceData[i] == ')' || sourceData[i] == '{' || sourceData[i] == '}' || sourceData[i] == '[' || sourceData[i] == ']' )
        {
            sourceData[i] = ' ';
        }
        if(sourceData[i] == ','|| sourceData[i] == '<' || sourceData[i] == '>')
        {
            sourceData[i] =' ';
        }
        i++;
    }
    i=0;
    int k=0;
    while (sourceData[i+k])
    {
        if (sourceData[i+k]==' ')
            while (sourceData[i+k+1]==' ')
            {
                k++;
            }
        hash[x].file[i]=sourceData[i+k];
        i++;
    }
    return i;
}
double possibality()
{
    int i;
    double sum = 0;
    double pos = 0;
    for(i = 0; i < 10; i ++)
    {
        sum = sum + (hash[0].hashTab[i] - hash[1].hashTab[i])*(hash[0].hashTab[i] - hash[1].hashTab[i]);
    }
    pos = sqrt(sum);
    return pos;
}
void calcuNum(int x)
{
    char data[M];
    int i = 0;
    int count;
    strcpy(data,hash[x].file);
    count=hash[x].count;
    // printf("%d\n",x);
    //printf("%s\n",hash[x].file);
    //printf("%d\n",count);
    while(i < count)
    {
        if(data[i] == 'i')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || i == 0)
            {
                i++;
                if(data[i] == 'f')
                {
                    i ++;
                    // printf("%d",i);printf("%c",data[i]);
                    if(data[i] == ' ' || data[i] == '\n'|| i==count )
                    {
                        Cumulating(x,6);
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n')
                        {
                            i ++;
                        }
                    }
                }
                else if(data[i] == 'n')
                {
                    i ++;
                    if(data[i] == 't')
                    {
                        i ++;
                        if(data[i] == ' ' || data[i] == '\n'|| i==count)
                        {
                            Cumulating(x,7);
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&&i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&&i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&&i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n' && i<count)
                {
                    i ++;
                }
            }
        }
        else if(data[i] == 'f')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'o')
                {
                    i ++;
                    if(data[i] == 'r')
                    {
                        i ++;
                        if(data[i] == ' ' || data[i] == '\n'&& i<count|| i==count)
                        {
                            Cumulating(x,5);
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        else if(data[i] == 'b')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'r')
                {
                    i ++;
                    if(data[i] == 'e')
                    {
                        i ++;
                        if(data[i] == 'a')
                        {
                            i ++;
                            if(data[i] == 'k')
                            {
                                i ++;
                                if(data[i] == ' ' || data[i] == '\n'|| i==count)
                                {
                                    Cumulating(x,0);
                                }
                                else
                                {
                                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                    {
                                        i ++;
                                    }
                                }
                            }
                            else
                            {
                                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                {
                                    i ++;
                                }
                            }
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        else if(data[i] == 'c')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'h')
                {
                    i ++;
                    if(data[i] == 'a')
                    {
                        i ++;
                        if(data[i] == 'r')
                        {
                            i ++;
                            if(data[i] == ' ' || data[i] == '\n'|| i==count)
                            {
                                Cumulating(x,1);
                            }
                            else
                            {
                                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                {
                                    i ++;
                                }
                            }
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else if(data[i] == 'l')
                {
                    i ++;
                    if(data[i] == 'a')
                    {
                        i ++;
                        if(data[i] == 's')
                        {
                            i ++;
                            if(data[i] == 's')
                            {
                                i ++;
                                if(data[i] == ' ' || data[i] == '\n'|| i==count)
                                {
                                    Cumulating(x,2);
                                }
                                else
                                {
                                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                    {
                                        i ++;
                                    }
                                }
                            }
                            else
                            {
                                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                {
                                    i ++;
                                }
                            }
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
                /*else
                {
                    while(data[i] != ' ' && data[i] != '\n')
                    {
                        i ++;
                    }
                }*/
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        else if(data[i] == 'd')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'o')
                {
                    i ++;
                    if(data[i] == ' ' || data[i] == '\n'|| i==count)
                    {
                        Cumulating(x,3);
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        if(data[i] == 'e')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'l')
                {
                    i ++;
                    if(data[i] == 's')
                    {
                        i ++;
                        if(data[i] == 'e')
                        {
                            i ++;
                            if(data[i] == ' ' || data[i] == '\n'|| i==count)
                            {
                                Cumulating(x,4);
                            }
                            else
                            {
                                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                {
                                    i ++;
                                }
                            }
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        else if(data[i] == 'v')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'o')
                {
                    i ++;
                    if(data[i] == 'i')
                    {
                        i ++;
                        if(data[i] == 'd')
                        {
                            i ++;
                            if(data[i] == ' ' || data[i] == '\n'|| i==count)
                            {
                                Cumulating(x,8);
                            }
                            else
                            {
                                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                {
                                    i ++;
                                }
                            }
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        if(data[i] == 'w')
        {
            if(data[i - 1] == ' ' || data[i - 1] == '\n' || data[i - 1] == 9 ||i == 0)
            {
                i++;
                if(data[i] == 'h')
                {
                    i ++;
                    if(data[i] == 'i')
                    {
                        i ++;
                        if(data[i] == 'l')
                        {
                            i ++;
                            if(data[i] == 'e')
                            {
                                i ++;
                                if(data[i] == ' ' || data[i] == '\n'|| i==count)
                                {
                                    Cumulating(x,9);
                                }
                                else
                                {
                                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                    {
                                        i ++;
                                    }
                                }
                            }
                            else
                            {
                                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                                {
                                    i ++;
                                }
                            }
                        }
                        else
                        {
                            while(data[i] != ' ' && data[i] != '\n'&& i<count)
                            {
                                i ++;
                            }
                        }
                    }
                    else
                    {
                        while(data[i] != ' ' && data[i] != '\n'&& i<count)
                        {
                            i ++;
                        }
                    }
                }
                else
                {
                    while(data[i] != ' ' && data[i] != '\n'&& i<count)
                    {
                        i ++;
                    }
                }
            }
            else
            {
                while(data[i] != ' ' && data[i] != '\n'&& i<count)
                {
                    i ++;
                }
            }
        }
        i ++;
    }
}
