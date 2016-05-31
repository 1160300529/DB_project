
#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"
#include<time.h>
#define MAX 1000
int Random(int low,int high);                            //���������
void storeData(unsigned int * blk,Buffer *buf);          //�洢����
void loadData(unsigned int * blk,Buffer *buf);            //��ȡ����

void SelectRelationship(unsigned int * blk,Buffer *buf);   //ѡ���ϵ

void MappingRelationship(unsigned int * blk,Buffer *buf);  //ͶӰ��ϵ
unsigned int Merge(unsigned int left,int ln,unsigned int right,int rn,Buffer *buf);
unsigned int Exsort(unsigned int saddr,int n,Buffer *buf);

void ConnectRelationship(unsigned int * blk,Buffer *buf);   //���ӹ�ϵ
void Nst_Loop_Join(unsigned int * blk,Buffer *buf);
void Sort_Merge_Join(unsigned int * blk,Buffer *buf);
void Hash_Join(unsigned int *blk, Buffer *buf);

void CollectionRelationship(unsigned int * blk,Buffer *buf);  //���ϲ���


int main()
{
    srand((unsigned)time(NULL));
    Buffer buf; /* A buffer */
    //unsigned char *blk; /* A pointer to a block */
    unsigned int *blk;
    int i = 0;
    int sel;
    /* Initialize the buffer */
    if (!initBuffer(520, 64, &buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    storeData(blk, &buf);
    //loadData(blk,&buf);
    while(1)
    {
        printf("\t***** 1 ѡ��\t2 ͶӰ\t3 ����\t 4 ���ϲ��� *****\n\n ");
        scanf("%d",&sel);
        switch (sel)
        {
        case 1:  //ѡ���ϵ
            {
                SelectRelationship(blk,&buf);
                continue;
            }
        case 2: //ͶӰ��ϵ
            {
                MappingRelationship(blk,&buf);
                continue;
            }
        case 3:  //���ӹ�ϵ
            {
                ConnectRelationship(blk,&buf);
               continue;
            }
        case 4: //���ϲ���
            {
                CollectionRelationship(blk,&buf);
               continue;
            }
        default:
            {
                printf("\tѡ����Ŵ�����������!\n\n");
                continue;
            }
        }
    }
    printf("\n");
    printf("# of IO's is %d\n", buf.numIO); /* Check the number of IO's */
    system("pause");
    return 0;
}
/** \brief  ���������
 *  Random
 * \param int low
 * \param  int high
 * \return  int
 *
 */
int Random(int low,int high)  //���������
{
    return rand()%(high-low)+low+1;
}
/** \brief  �洢����
 *     storeData
 * \param unsigned int *blk
 * \param  Buffer * buf
 * \return void
 *
 */
void storeData(unsigned int * blk,Buffer *buf) //�洢����
{
    unsigned int a,b,c,d;
    int Ri,Rj,Si,Sj;
    for(Ri=0;Ri<16;Ri++)
    {
        blk = getNewBlockInBuffer(buf);
        for(Rj=0;Rj<7;Rj++)
        {
            a = Random(1,40);
            b = Random(1,1000);
            *(blk+2*Rj) = a;
            *(blk+2*Rj+1) = b;
        }
        *(blk+2*Rj+1)=Ri+1; //����һ��ĵ�ַ
        if(Ri == 15)
        {
            *(blk+2*Rj+1)=0;
        }
        //printf("R %d,%d\n",*blk,*(blk+1));
        if (writeBlockToDisk(blk, Ri, buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        freeBlockInBuffer(blk,buf);
    }
    for(Si=0;Si<32;Si++)
    {
        blk = getNewBlockInBuffer(buf);
        for(Sj=0;Sj<7;Sj++)
        {
            c= Random(20,60);
            d = Random(1,1000);
            *(blk+2*Sj)=c;
            *(blk+2*Sj+1)=d;
        }
        *(blk+2*Sj+1) = Si+21; //����һ���Ŀ��
        if(Si==31)
        {
            *(blk+2*Sj+1) = 0;
        }
        //printf("S %d,%d\n",*blk,*(blk+1));
        if (writeBlockToDisk(blk, Si+20, buf) != 0)
        {
            perror("Writing Block Failed!\n");
            return -1;
        }
        freeBlockInBuffer(blk,buf);
    }
}
/** \brief ��ȡ����
 *   loadData
 * \param  unsigned int * blk
 * \param  Buffer * buf
 * \return void
 *
 */
void loadData(unsigned int * blk,Buffer *buf)
{
    unsigned int a,b,c,d;
    int ri,rj,si,sj;
    for(ri=0;ri<16;ri++)
    {
        if((blk = readBlockFromDisk(ri,buf))==NULL)
        {
            perror("Reading Block Failed!\n");
            return;
        }
        for(rj=0;rj<7;rj++)
        {
            a = *(blk+2*rj);
            b = *(blk+2*rj+1);
            printf("R = %d,%d\n",a,b);
        }
        freeBlockInBuffer(blk,buf);
    }
    for(si=0;si<32;si++)
    {
      if((blk = readBlockFromDisk(si+20,buf))==NULL)
        {
            perror("Reading Block Failed!\n");
            return;
        }
     for(sj=0;sj<7;sj++)
     {
         c = *(blk+2*sj);
         d = *(blk+2*sj+1);
         printf("S = %d,%d\n",c,d);
     }
     freeBlockInBuffer(blk,buf);
    }
}
/** \brief ѡ���ϵ
 * �������� ��Ԫ���� �����㷨
 * �����Ŵ���
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void SelectRelationship(unsigned int * blk,Buffer *buf)
{
 printf("\t1 ��������   2 ��Ԫ����   3 �����㷨   -1 ����\n");
 int sel=0;
 int i,j,a,b,c,d;
 int line_count=60;  //60 ��ʼ�洢
 unsigned int *disk_blk;
 while(sel!=-1)
 {
     scanf("%d",&sel);
     switch (sel)
     {
     case 1: //��������
         {
             for(i=0;i<16;i++)  //��R
             {
                 blk = readBlockFromDisk(i,buf);
                 for(j=0;j<7;j++)
                 {
                     if(*(blk+2*j)==40)
                     {
                         a = 40;
                         b = *(blk+2*j+1);
                         printf("a = %d, b = %d\n",a,b);
                         disk_blk = getNewBlockInBuffer(buf);
                         *disk_blk = a;
                         *(disk_blk+1)=b;
                         writeBlockToDisk(disk_blk,line_count,buf);
                         line_count++;
                     }
                 }
                 freeBlockInBuffer(blk,buf);
             }
             line_count+=10;   //�м���10��blk������ R.A=40 ��S.C=60��Ԫ��
             for(i=0;i<32;i++)
             {
                 blk = readBlockFromDisk(i+20,buf);
                 for(j=0;j<7;j++)
                 {
                     if(*(blk+2*j)==60)
                     {
                         c = 60;
                         d = *(blk+2*j+1);
                         printf("c = %d, d = %d\n",c,d);
                          disk_blk = getNewBlockInBuffer(buf);
                         *disk_blk = c;
                         *(disk_blk+1)=d;
                         writeBlockToDisk(disk_blk,line_count,buf);
                         line_count++;
                     }
                 }
                 freeBlockInBuffer(blk,buf);
             }
             printf("\n");
             break;
         }
     case 2: //��Ԫ����
         {
             break;
         }
     case 3: //�����㷨
         {
             break;
         }
     default:
         {
              break;
         }
     }
 }

}

unsigned int Merge(unsigned int left,int ln,unsigned int right,int rn,Buffer *buf)
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
            blk1=(int *)readBlockFromDisk(left+l,buf);
        if(r==rn)
             *blk2=MAX;//�ұ߽���
        else
            blk2=(int *)readBlockFromDisk(right+r,buf);
        if(*blk1<*blk2)
        {
            writeBlockToDisk(blk1,tmpaddr+offset,buf);
            l++;//���ָ�����
            offset++;//д��ĵ�ַ����ƶ�
        }
        else
        {
            writeBlockToDisk(blk2,tmpaddr+offset,buf);
            r++;
            offset++;
        }
        freeBlockInBuffer(blk1,buf);
        freeBlockInBuffer(blk2,buf);
    }
    for(i=0;i<offset;i++)//д��ԭ����λ��
    {
        blk1=(int*)readBlockFromDisk(tmpaddr+i,buf);
        writeBlockToDisk(blk1,left+i,buf);
        freeBlockInBuffer(blk1,buf);
    }
    return left;
}

unsigned int Exsort(unsigned int saddr,int n,Buffer *buf)
{
    unsigned int left,right;
    if(n==1)   ///complete sorting
        return saddr;
    left=Exsort(saddr,n/2,buf);
    right=Exsort(saddr+n/2,n-n/2,buf);
    return Merge(left,n/2,right,n-n/2,buf);
}
/** \brief ͶӰ��ϵ
 * ʵ�ֹ�ϵͶӰ�����洢�ڴ�����
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void MappingRelationship(unsigned int * blk,Buffer *buf)  //��R.AͶӰ
{
 printf("\t ͶӰ��ϵ   \n");
 int ri,rj,a,basic=200,num=0,counta=0,count=0;
 unsigned int *disk_blk,tmp;
 printf("\t����ǰ R.A :\n");
 for(ri=0;ri<16;ri++)
    {
        if((blk = readBlockFromDisk(ri,buf))==NULL)
        {
            perror("Reading Block Failed!\n");
            return;
        }
        for(rj=0;rj<7;rj++)
        {
            a = *(blk+2*rj);
            printf("%d ",a);
            disk_blk = getNewBlockInBuffer(buf);
            *disk_blk = a;
            writeBlockToDisk(disk_blk,basic+num,buf); //200-311.blk
            num++;
            freeBlockInBuffer(disk_blk,buf);
        }
        freeBlockInBuffer(blk,buf);
    }
    printf("\n");
    printf("\t����� R.A:\n");
    basic = Exsort(basic,num,buf);
    //printf("%d\n",basic);
    for(ri=0;ri<num;ri++)
    {
        blk = readBlockFromDisk(basic+ri,buf);
        printf("%d ",*blk);
        freeBlockInBuffer(blk,buf);
    }
    printf("\n\tȥ�غ� R.A :\n");
    blk=(int*)readBlockFromDisk(basic,buf);
    disk_blk = getNewBlockInBuffer(buf); //������� 350-�� R.A
    tmp=*blk;
    *(disk_blk+count) = tmp;
    //writeBlockToDisk(disk_blk,basic+150+counta,buf);
    printf("%d ",tmp);
    for(ri=1; ri<num; ri++)
    {
        while(*blk==tmp)
        {
            freeBlockInBuffer(blk,buf);
            ri++;
            if(ri<num)
                blk=(int*)readBlockFromDisk(basic+ri,buf);
            else
            {
                goto END;
            }
        }
        //disk_blk = getNewBlockInBuffer(buf); //������� 350-390��
        tmp=*blk;
        count++;
        *(disk_blk+count) = tmp;
        if(ri==num-1)
            {
                 writeBlockToDisk(disk_blk,basic+150+counta,buf);
                 freeBlockInBuffer(disk_blk,buf);
            }
        else
        {
            if(count == 15)
            {
                 *(disk_blk+count+1) = basic+150+counta+1; //����һ�����
                 writeBlockToDisk(disk_blk,basic+150+counta,buf);
                 freeBlockInBuffer(disk_blk,buf);
                 count = -1;
                 counta++;
            }
        }
        printf("%d ",tmp);
        freeBlockInBuffer(blk,buf);
    }
END:    printf("\n\n");
}
/** \brief Nst_Loop_Join
 *
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */

void Nst_Loop_Join(unsigned int * blk,Buffer *buf)
{
 int ri,rj,si,sj,num=1000,blk_count=0;
 int a,b,c,d;
 unsigned int *desk_blk,*wr_blk;
 for(ri=0;ri<16;ri++)
 {
     blk = readBlockFromDisk(ri,buf);  //R ÿ��block
     for(rj=0;rj<7;rj++)
     {
         a = *(blk+2*rj);
         for(si=0;si<32;si++)
         {
             desk_blk = readBlockFromDisk(si+20,buf);//s ÿ��block
             for(sj=0;sj<7;sj++)
             {
                 c = *(desk_blk+2*sj);
                 if(a == c)
                 {
                     b = *(blk+2*rj+1);
                     d = *(desk_blk+2*sj+1);
                     printf("(%d,%d) (%d,%d) \n",a,b,c,d);
                     if(blk_count==0)
                      {
                        wr_blk = getNewBlockInBuffer(buf);
                      }
                     *(wr_blk+blk_count)=a;
                     *(wr_blk+blk_count+1)=b;
                     *(wr_blk+blk_count+2)=d;
                     blk_count+=3;
                     if(ri==15&&si==31)   //��������һ���飨��������Ҳ���д洢
                     {
                          writeBlockToDisk(wr_blk,num,buf);
                           freeBlockInBuffer(wr_blk,buf);
                     }
                     else
                     {
                            if(blk_count == 15)   //������������
                         {
                             *(wr_blk+blk_count) = num+1;  //����ĸ��ֽ� �洢��һ��Ŀ��
                             writeBlockToDisk(wr_blk,num,buf);
                             num++;
                             freeBlockInBuffer(wr_blk,buf);
                             blk_count=0;
                         }
                     }
                  }

             }
             freeBlockInBuffer(desk_blk,buf);
         }
     }
     freeBlockInBuffer(blk,buf);
 }
}

void Sort_Merge_Join(unsigned int * blk,Buffer *buf)
{

}

void Hash_Join(unsigned int *blk, Buffer *buf)
{

}
/** \brief ���ӹ�ϵ
 * Nst_Loop_Join�㷨 Sort_Merge_Join�㷨 Hash_Join�㷨
 *�����Ŵ���
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void ConnectRelationship(unsigned int * blk,Buffer *buf)
{
    printf("\t1 Nst_Loop_Join \t2 Sort_Merge_Join \t3 Hash_Join \t��������\n");
    int sel=0;
    while(sel!=-1)
    {
        scanf("%d",&sel);
        switch (sel)
        {
        case 1: //Nst_Loop_Join�㷨
            {
                Nst_Loop_Join(blk,buf);
                continue;
            }
        case 2: //Sort_Merge_Join�㷨
            {
                continue;
            }
        case 3: //Hash_Join�㷨
            {
                continue;
            }
        default:
            break;
        }
    }
}

/** \brief ���ϲ���
 * ����������
 * \param unsigned int * blk
 * \param Buffer *buf
 * \return void
 *
 */
void CollectionRelationship(unsigned int * blk,Buffer *buf)
{
    printf("\t 1 �� \t 2 �� \t 3 �� \t ��������\n");
    int sel=0;
    while(sel!=-1)
    {
        scanf("%d",&sel);
        switch (sel)
        {
        case 1: //��
            {
                continue;
            }
        case 2: //��
            {
                continue;
            }
        case 3://��
            {
                continue;
            }
        default:
            break;
        }
    }
}








