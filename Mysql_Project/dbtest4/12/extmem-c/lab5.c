#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include "extmem.h"

#define MAX 1000

unsigned int *blk;
Buffer buf;

int random(int low,int high)
{
    int i=0;
    i=rand()%(high-low+1)+low;
    return i;
}

void select()
{
    int i,j;
    //int temp=0;
    printf("A\tB\n");
    for(i=0;i<16;i++)
    {
        blk=(int*)readBlockFromDisk(i,&buf);//�������
        for(j=0;j<7;j++)
        {
            if(*(blk+2*j)==40)
                printf("%d\t%d\n",(int)*(blk+2*j),(int)*(blk+2*j+1));
        }
        //temp=*(blk+2*j+1);
        //printf("%d ",temp);
        freeBlockInBuffer(blk,&buf);
        blk=NULL;
    }
    printf("C\tD\n");
    for(i=0; i<32; i++)
    {
        blk=(int*)readBlockFromDisk(i+16,&buf);
        for(j=0; j<7; j++)
        {
            if(*(blk+2*j)==60)
                printf("%d\t%d\n",(int)*(blk+2*j),(int)*(blk+2*j+1));
        }
        freeBlockInBuffer(blk,&buf);
    }
    return;
}

unsigned int Merge(unsigned int left,int ln,unsigned int right,int rn)
{
    int l=0,r=0;//����
    int offset=0,i;
    unsigned int tmpaddr=left+500;//�������ĵ�ַ
    unsigned int *blk1,*blk2;
    while(l<ln||r<rn)
    {
        if(l==ln)//��߽���
            *blk1=MAX;
        else
            blk1=(int *)readBlockFromDisk(left+l,&buf);
        if(r==rn)
             *blk2=MAX;//�ұ߽���
        else
            blk2=(int *)readBlockFromDisk(right+r,&buf);
        if(*blk1<*blk2)
        {
            writeBlockToDisk(blk1,tmpaddr+offset,&buf);
            l++;//���ָ�����
            offset++;//д��ĵ�ַ����ƶ�
        }
        else
        {
            writeBlockToDisk(blk2,tmpaddr+offset,&buf);
            r++;
            offset++;
        }
        freeBlockInBuffer(blk1,&buf);
        freeBlockInBuffer(blk2,&buf);
    }
    for(i=0;i<offset;i++)//д��ԭ����λ��
    {
        blk1=(int*)readBlockFromDisk(tmpaddr+i,&buf);
        writeBlockToDisk(blk1,left+i,&buf);
        freeBlockInBuffer(blk1,&buf);
    }
    return left;
}

unsigned int Exsort(unsigned int saddr,int n)
{
    unsigned int left,right;
    if(n==1)   ///complete sorting
        return saddr;
    left=Exsort(saddr,n/2);
    right=Exsort(saddr+n/2,n-n/2);
    return Merge(left,n/2,right,n-n/2);
}

void projection()
{
    unsigned int i,j,tmp;
    unsigned int newadd=1000,offset=0;
    unsigned int *blk,*disk_blk=NULL;
    printf("\n����ǰ��\n");
    for(i=0;i<16;i++)
    {
        blk=(int*)readBlockFromDisk(i,&buf);
        for(j=0;j<7;j++)
        {
            disk_blk=getNewBlockInBuffer(&buf);//����һ���¿�
            *disk_blk=*(blk+2*j);
            printf("%d ",*disk_blk);
            writeBlockToDisk(disk_blk,newadd+offset,&buf);
            offset++;
            freeBlockInBuffer(disk_blk,&buf);
        }
        freeBlockInBuffer(blk,&buf);
    }
    printf("\n�����\n");
    newadd=Exsort(newadd,offset);//1000,112,return 1000
    for(i=0;i<offset;i++)
    {
        blk=(int*)readBlockFromDisk(newadd+i,&buf);
        printf("%d ",*blk);
        freeBlockInBuffer(blk,&buf);
    }
    printf("\nȥ�غ�\n");
    blk=(int*)readBlockFromDisk(newadd,&buf);
    tmp=*blk;
    printf("%d ",tmp);
    for(i=1; i<offset; i++)
    {
        while(*blk==tmp)
        {
            freeBlockInBuffer(blk,&buf);
            i++;
            if(i<offset)
                blk=(int*)readBlockFromDisk(newadd+i,&buf);
            else
            {
                goto END;
            }
        }
        tmp=*blk;
        printf("%d ",tmp);
        freeBlockInBuffer(blk,&buf);
    }
END:    printf("\n");
}

int NLJ()
{
    unsigned int i,j,m,n,count=0,k=0;
    unsigned int newadd=1000;
    unsigned int * rblk,*sblk,*result_blk;
    result_blk=NULL;
    for(i=0; i<16; i++)
    {
        rblk=(int*)readBlockFromDisk(i,&buf);
        for(j=0; j<7; j++)
        {
            for(m=16; m<48; m++)
            {
                sblk=(int*)readBlockFromDisk(m,&buf);
                for(n=0; n<7; n++)
                {
                    if(*(rblk+2*j)==*(sblk+2*n))   ///R.A=S.C
                    {
                        k++;
                        if(result_blk==NULL)
                        {
                            result_blk=getNewBlockInBuffer(&buf);
                            count=0;
                        }
                        *(result_blk+count)=*(rblk+2*j);
                        *(result_blk+count+1)=*(rblk+2*j+1);
                        *(result_blk+count+2)=*(sblk+2*n+1);
                        count=count+3;
                        if(count==15)   ///result_blk full
                        {
                            *(result_blk+count)=newadd+1;
                            writeBlockToDisk(result_blk,newadd,&buf);
                            newadd++;
                            freeBlockInBuffer(result_blk,&buf);
                            result_blk=NULL;//�ÿ�
                        }
                    }
                }
                freeBlockInBuffer(sblk,&buf);
            }
        }
        freeBlockInBuffer(rblk,&buf);
    }
    if(result_blk!=NULL)
    {
        *(result_blk+15)=0;
        writeBlockToDisk(result_blk,newadd,&buf);
        newadd++;
        freeBlockInBuffer(result_blk,&buf);
    }
    for(i=1000; i<newadd; i++)
    {
        result_blk=(int*)readBlockFromDisk(i,&buf);
        for(j=0; j<15; j=j+3)
        {
            printf("%d %d %d\n",*(result_blk+j),*(result_blk+j+1),*(result_blk+j+2));
        }
        freeBlockInBuffer(result_blk,&buf);
    }
    printf("k=%d",k);
}

int main()
{
    int ch;
    unsigned int i,j;
    unsigned int A,B;
    srand((unsigned)time(NULL));
    if (!initBuffer(520,64,&buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    ///����д�����
    for(i=0;i<16;i++)//��ϵR
    {
        blk = getNewBlockInBuffer(&buf);//������������һ����
        for(j=0;j<7;j++)
        {
            A=random(1,40);
            *(blk+2*j)=A;
            B=random(1,1000);
            *(blk+2*j+1)=B;
        }
        *(blk+2*j+1)=i+1;//��һ����ĵ�ַ
        if(i==15)
        {
            *(blk+2*j+1)=0;//��ĩβ����־
        }
        if (writeBlockToDisk(blk,i,&buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        freeBlockInBuffer(blk,&buf);
    }
    for(i=0;i<32;i++)//��ϵS
    {
        blk = getNewBlockInBuffer(&buf);
        for(j=0; j<7; j++)
        {
            A=random(20,60);
            *(blk+2*j)=A;
            B=random(1,1000);
            *(blk+2*j+1)=B;
        }
        *(blk+2*j+1)=i+17;
        if(i==31)
            *(blk+2*j+1)=0;
        if (writeBlockToDisk(blk,i+16,&buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        freeBlockInBuffer(blk,&buf);
    }
    printf("1.ѡ���ϵ\n2.ͶӰ\n3.NLJ\n");
    scanf("%d",&ch);
    switch(ch)
    {
    case 1:
        select();
        break;
    case 2:
        projection();
        break;
    case 3:
        NLJ();
        break;
    }
    return 0;
}
