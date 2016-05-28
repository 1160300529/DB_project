#ifndef __LCC__
#define __LCC__
#endif

#include <stdio.h>
#include<stdlib.h>
#include <mysql.h>
#include<string>
#include<iostream>

using namespace std;

#define maxsize 1024

int login=0;
string Global_friendEmail;    //��Ӻ��ѣ�������ӣ���ȫ�ֱ���
string Global_deleteRemark; //ɾ�����ѣ�����ɾ��
string Global_logID;          //ɾ����־��ɾ����Ӧ�����ۡ�����
//��ʼ����
void showHome();
//��¼ע��
void LoginOrRegist();
string Regist();
string LoginIn();
//��ҳ
int HomeView();
//������Ϣ
int PerfectDate();
//���ƻ�����Ϣ
int PerfectPersonInfo();
string UpdatePersonInfo(string userIDstr);
string PerfectEmail(string userIDstr);
//���Ƹ��˾���
int PerfectExperience();
string PerfectEduExperience(string userIDstr);
string ChangeEduExperience(string userIDstr);
string PerfectWorkExperience(string userIDstr);
string ChangeWorkExperience(string userIDstr);
//�������  ���� �޸� ɾ��
int HandleGroup();
string CreateGroup(string userIDstr);
string ChangeGroup(string userIDstr);
string DeleteGroup(string userIDstr);
string ShowFriendInGroup(string userIDstr);
//������ӵ�������
string AddFriendToGroup(string userIDstr);
//���ѹ���
int ManageGdFriend();
string SearchFriend();
string AddNewFriend(string userIDstr);
string AddNewFriendMutual(string userIDstr);
string DeleteFriend(string userIDstr);
string DeleteFriendMutual(string userIDstr);
//��Ϣ����
int ManageNews();
string ShowNews(string userIDstr);
string SendNews(string userIDstr);
//��־����
int ManageLog();
string ShowLog(string userIDstr);
string PublicLog(string userIDstr);
string ChangeLog(string userIDstr);
string DeleteLog(string userIDstr);
string DeleteReplyOfLog(string userIDstr);//��־ɾ����ɾ����Ӧ�Ļظ�
string DeleteShareOfLog(string userIDstr); //��־ɾ����ɾ����Ӧ�ķ���
//�����־�ظ�
int ManageReplyAndSharelog();
string AddComment(string userIDstr);
string ShowComment(string userIDstr);
//������־
string AddSharelog(string userIDstr);
string showSharLog(string userIDstr);

int main(int argc, char **argv)
{
    MYSQL mysql_conn; /* Connection handle */
    //
    showHome();
    LoginOrRegist();
    string userIDstr;
    string userEmail;
    MYSQL_RES *mysql_result;
    MYSQL_ROW mysql_row;
    if (mysql_init(&mysql_conn) != NULL)
    {
        if (mysql_real_connect(
                    &mysql_conn, "localhost", "root",
                    "mjy123456", "networking", MYSQL_PORT,
                    NULL, 0) != NULL)
            {
                if(login == 0)
                    {
                        system("cls");
                        const char *myquery = Regist().c_str();
                        mysql_query(&mysql_conn,"set names gbk");
                        mysql_query(&mysql_conn,myquery);

                        const char *myquery0 = LoginIn().c_str();
                        mysql_query(&mysql_conn,myquery0);
                        mysql_result = mysql_store_result(&mysql_conn);
                        //***********//�жϲ���*****
                        if(mysql_result!=0)
                            login = 1;   //��¼�ɹ�
                        else login = 0;
                        int num_row = mysql_num_rows(mysql_result);
                        //int num_col = mysql_num_fields(mysql_result);
                        int f1;
                        for(f1=0; f1<num_row; f1++)
                        {
                            mysql_row = mysql_fetch_row(mysql_result);
                            userIDstr = mysql_row[0];
                            userEmail = mysql_row[1];
                            printf("\n");
                        }
                    }
                else
                    {
                        const char *myquery0 = LoginIn().c_str();
                        mysql_query(&mysql_conn,myquery0);
                        mysql_result = mysql_store_result(&mysql_conn);
                        if(mysql_result!=0)
                            login = 1;   //��¼�ɹ�
                        else login =0 ;
                        int num_row = mysql_num_rows(mysql_result);
                        int f1;
                        for(f1=0; f1<num_row; f1++)
                        {
                            mysql_row = mysql_fetch_row(mysql_result);
                            userIDstr = mysql_row[0];
                            userEmail = mysql_row[1];
                            printf("\n");
                        }

                    }
                if(login==1)  //�ѵ�¼
                {

                        system("cls");
                        while(int homenum = HomeView())
                       {
                           switch (homenum)
                           {
                           case 1://���Ƹ�����Ϣ
                               {
                                   int datanum = PerfectDate();
                                   if(datanum == 1)  //���ƻ�����Ϣ
                                   {
                                       int personnum = PerfectPersonInfo();
                                       if(personnum == 1)  //������Ϣ�޸�
                                       {
                                           system("cls");
                                           const char *person_query = UpdatePersonInfo(userIDstr).c_str();
                                           mysql_query(&mysql_conn,person_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t�޸ĳɹ�"<<endl;
                                         }
                                       else if(personnum == 2) //��Ӹ�������
                                       {
                                           const char *email_query = PerfectEmail(userIDstr).c_str();
                                           mysql_query(&mysql_conn,email_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                       }
                                       else

                                            system("cls");
                                            break;
                                   }
                                   else if(datanum == 2)  //���Ƹ��˾���
                                   {
                                       int expnum = PerfectExperience();
                                       if(expnum == 1)  //���ƽ�������
                                       {
                                           system("cls");
                                           const char * edu_query = PerfectEduExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,edu_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                       }
                                       else if(expnum == 2) //�޸Ľ�������
                                       {
                                           system("cls");
                                           const char * changedu_query = ChangeEduExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,changedu_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t�޸ĳɹ�"<<endl;
                                       }
                                       else if(expnum == 3)  //���ƹ�������
                                       {
                                           system("cls");
                                           const char * work_query = PerfectWorkExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,work_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                       }
                                       else if(expnum == 4) //�޸Ĺ�������
                                       {
                                           system("cls");
                                           const char * changework_query = ChangeWorkExperience(userIDstr).c_str();
                                           mysql_query(&mysql_conn,changework_query);
                                           mysql_result = mysql_store_result(&mysql_conn);
                                           if(mysql_result!=0) cout<<"\t�޸ĳɹ�"<<endl;
                                       }
                                       else
                                       {
                                           system("cls");
                                           break;
                                       }
                                                                                                               }
                                   else
                                    {
                                         system("cls");
                                         break;
                                    }
                                     break;

                               }
                           case 2://Ⱥ�����
                               {
                                   int groupnum = HandleGroup();
                                   if(groupnum == 1)//����Ⱥ��
                                   {
                                       system("cls");
                                       const char *creategroup_query = CreateGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,creategroup_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                   }
                                   else if(groupnum == 2) //�޸�Ⱥ��
                                   {
                                       system("cls");
                                       const char * changeGroup_query = ChangeGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,changeGroup_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       if(mysql_result!=0) cout<<"\t�޸ĳɹ�"<<endl;
                                   }
                                   else if(groupnum == 3)
                                   {
                                       system("cls");
                                       const char * delete_group_query = DeleteGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,delete_group_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       if(mysql_result!=0) cout<<"\tɾ���ɹ�"<<endl;
                                   }
                                   else if(groupnum == 4)
                                   {
                                       system("cls");
                                       const char * showFriendIngroup_query = ShowFriendInGroup(userIDstr).c_str();
                                       mysql_query(&mysql_conn,showFriendIngroup_query);
                                       mysql_result = mysql_store_result(&mysql_conn);
                                       int num_row = mysql_num_rows(mysql_result);
                                       cout<<endl;
                                       for(int i=0;i<num_row;i++)
                                       {
                                           mysql_row = mysql_fetch_row(mysql_result);
                                           if(i==0) printf("\t����:%s\n\n",mysql_row[0]);
                                           printf("\t��ע��%s\n",mysql_row[1]);
                                           printf("\t����:%s\n",mysql_row[2]);
                                           printf("\t����:%s\n",mysql_row[3]);

                                       }
                                       if(mysql_result!=0) cout<<"\t"<<endl;
                                   }
                                   else
                                     {
                                         system("cls");
                                         break;
                                     }
                                 break;
                               }
                           case 3://���ѹ���
                               {
                                   int friendnum = ManageGdFriend();
                                   if(friendnum == 1) //���Һ���
                                   {
                                        system("cls");
                                        const char *search_query = SearchFriend().c_str();
                                        mysql_query(&mysql_conn,search_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        int num_row = mysql_num_rows(mysql_result);
                                        int f1;
                                        printf("\n\t************************���ҽ��***********************\t\n");
                                        printf("\n");
                                        for(f1=0; f1<num_row; f1++)
                                        {
                                            mysql_row = mysql_fetch_row(mysql_result);
                                            printf("\t������%s\n",mysql_row[0]);
                                            printf("\t����: %s\n",mysql_row[1]);
                                            printf("\t�Ա�%s\n",mysql_row[2]);
                                            printf("\t���գ�%s\n",mysql_row[3]);
                                            printf("\tסַ��%s\n\n\n",mysql_row[4]);
                                        }
                                   }
                                   else if(friendnum == 2) //��Ӻ���
                                   {
                                    system("cls");//��ӵ����������б�
                                    const char* addFriend_query = AddNewFriend(userIDstr).c_str();
                                    mysql_query(&mysql_conn,addFriend_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                    //��ӵ��Է��б�
                                    const char* addFriendmutual_query = AddNewFriendMutual(userIDstr).c_str();
                                    mysql_query(&mysql_conn,addFriendmutual_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                   }
                                   else if(friendnum == 3) //ɾ������
                                   {
                                    system("cls");
                                    const char* deleteFriend_query = DeleteFriend(userIDstr).c_str();
                                    //cout<<deleteFriend_query<<endl;
                                    //const char* deleteFriendmutual_query = DeleteFriendMutual(userIDstr).c_str();
                                    //cout<<deleteFriendmutual_query<<endl;
                                    mysql_query(&mysql_conn,deleteFriend_query);
                                    //mysql_query(&mysql_conn,deleteFriendmutual_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\tɾ���ɹ�"<<endl;
                                   }
                                   else if(friendnum == 4)
                                   {
                                    system("cls");
                                    const char* addFriendToGroup_query = AddFriendToGroup(userIDstr).c_str();
                                    mysql_query(&mysql_conn,addFriendToGroup_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                   }
                                   else
                                   {
                                      system("cls");
                                      break;
                                   }
                                    break;
                               }
                           case 4://��Ϣ����
                            {
                                int newsnum = ManageNews();
                                if(newsnum == 1) //�鿴��Ϣ
                                {
                                    system("cls");
                                    const char* showNews_query = ShowNews(userIDstr).c_str();
                                    mysql_query(&mysql_conn,showNews_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    int num_row = mysql_num_rows(mysql_result);
                                    int f1;
                                    for(f1=0;f1<num_row;f1++)
                                    {
                                        mysql_row = mysql_fetch_row(mysql_result);
                                        printf("\t������ID��%s\n",mysql_row[3]);
                                        printf("\t������ID��%s\n",mysql_row[2]);
                                        printf("\t����ʱ��: %s\n",mysql_row[1]);
                                        printf("\t��Ϣ����:%s\n\n\n",mysql_row[0]);
                                    }


                                }
                                else if(newsnum == 2) //������Ϣ
                                {
                                    system("cls");
                                    const char* sendNews_query = SendNews(userIDstr).c_str();
                                    mysql_query(&mysql_conn,sendNews_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                }
                                else
                                    {
                                    system("cls");
                                     break;
                                     }
                                    break;

                            }
                           default: //��־����
                            {
                                int lognum= ManageLog();
                                if(lognum == 1)
                                    {
                                    system("cls");
                                    const char* showlog_query = ShowLog(userIDstr).c_str();
                                    mysql_query(&mysql_conn,showlog_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    int num_row = mysql_num_rows(mysql_result);
                                    int f1;
                                    for(f1=0;f1<num_row;f1++)
                                    {
                                        mysql_row = mysql_fetch_row(mysql_result);
                                        printf("\t��־ID��%s\n",mysql_row[0]);
                                        printf("\t���ݣ�%s\n",mysql_row[1]);
                                        printf("\t����ʱ��: %s\n",mysql_row[2]);
                                        printf("\t�ɻظ�:%s\n",mysql_row[3]);
                                        printf("\t�ɹ���:%s\n",mysql_row[4]);
                                        printf("\n\n");
                                    }

                                    //���ۼ�������־
                                    int num = ManageReplyAndSharelog();
                                    if(num == 1)  //������־
                                    {
                                        const char* add_comment_log_query = AddComment(userIDstr).c_str();
                                        mysql_query(&mysql_conn,add_comment_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                    }
                                    else if(num == 2) //�鿴����
                                    {
                                        system("cls");
                                        const char* show_comment_log_query = ShowComment(userIDstr).c_str();
                                        mysql_query(&mysql_conn,show_comment_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        int num_row = mysql_num_rows(mysql_result);
                                        int f1;
                                        for(f1=0;f1<num_row;f1++)
                                        {
                                            mysql_row = mysql_fetch_row(mysql_result);
                                            if(f1 == 0) printf("\t��־���ݣ�%s\n\n",mysql_row[0]);
                                            printf("\t�ظ�ʱ�䣺%s\n",mysql_row[1]);
                                            printf("\t�ظ�����: %s\n",mysql_row[2]);

                                        }
                                    }
                                    else if(num == 3) //������־
                                    {
                                        const char* add_share_log_query = AddSharelog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,add_share_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                    }
                                    else if(num == 4)  //�鿴����
                                    {
                                        system("cls");
                                       const char* show_share_log_query = showSharLog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,show_share_log_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                         int num_row = mysql_num_rows(mysql_result);
                                        int f1;
                                        for(f1=0;f1<num_row;f1++)
                                        {
                                            mysql_row = mysql_fetch_row(mysql_result);
                                            printf("\t��־���ݣ�%s\n",mysql_row[0]);
                                            printf("\t�޸�ʱ�䣺%s\n",mysql_row[1]);
                                            printf("\t����ʱ��: %s\n",mysql_row[2]);
                                            printf("\t��������: %s\n",mysql_row[3]);
                                            printf("\n\n");
                                        }
                                    }
                                    else
                                        break;
                                    }
                                else if(lognum == 2) //������־
                                    {
                                    system("cls");
                                    const char* sendLog_query = PublicLog(userIDstr).c_str();
                                    mysql_query(&mysql_conn,sendLog_query);
                                    mysql_result = mysql_store_result(&mysql_conn);
                                    if(mysql_result!=0) cout<<"\t��ӳɹ�"<<endl;
                                    }
                                else if(lognum == 3)
                                    {
                                        const char* changeLog_query = ChangeLog(userIDstr).c_str();
                                        //cout<<changeLog_query<<endl;
                                        mysql_query(&mysql_conn,changeLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        if(mysql_result!=0) cout<<"\t�޸ĳɹ�"<<endl;
                                    }
                                else if(lognum == 4)
                                    {
                                        string mysql_Query = DeleteLog(userIDstr);
                                        const char* deleteReplyOfLog_query = DeleteReplyOfLog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,deleteReplyOfLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        const char* deleteShareOfLog_query = DeleteShareOfLog(userIDstr).c_str();
                                        mysql_query(&mysql_conn,deleteShareOfLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);

                                        const  static char* deleteLog_query = mysql_Query.c_str();
                                        //cout<<deleteLog_query<<endl;
                                        mysql_query(&mysql_conn,deleteLog_query);
                                        mysql_result = mysql_store_result(&mysql_conn);
                                        if(mysql_result!=0) cout<<"\t right delete!"<<endl;
                                    }
                               else
                                    {
                                        system("cls");
                                        break;
                                    }
                                }

                           }
                       }
                }
            }
        else
            printf("Connection fails.\n");
    }
    else
    {
        printf("Initialization fails.\n");
        return -1;
    }

    mysql_close(&mysql_conn);
    return 0;
}

void  showHome()
{
    printf("\t*****************************************\t\n\n");
    printf("\t*\t��ӭ�����罻����ƽ̨\t\t*\n\n");
    printf("\t*****************************************\t\n");
    printf("\n\n\n");
}

void LoginOrRegist()
{
    printf("\t*****************************************\t\n");
    printf("\t����1 -> ��¼ \t\t ����0 -> ע��\t\n");
    cout<<"\t����(1/0)��";
    scanf("\t%d",&login);
     printf("\n\n\n");
}

string Regist()
{
     printf("\t*******************ע��******************\t\n");
     string query;
     string mainEmail,password,name,address,birthday,sex;
     printf("\t��дע������:");
     cin>>mainEmail;
     mainEmail = mainEmail+"','";
     printf("\t�������룺");
     cin>>password;
     password = password+"','";
     printf("\t�������ݿ�ѡ��Ϊ�գ�Ϊ������-1��\n");
     printf("\t����������");
     cin>>name;
     if(name == "-1")
        {
            name = "NULL";
            name = name+",";
       }
     else{
         name = name+"',";
     }
     printf("\t�����Ա�������1��Ů����0����");
     cin>>sex;
     if(sex == "-1")
        {
            sex = "1,'";//Ĭ��Ϊ��
        }
    else{
        sex = sex +",'";
    }
     printf("\t�����ַ��");
     cin>>address;
     if(address == "-1")
     {
         address = "NULL";
         address = address+"')";
     }
     else{
        address = address+"');";
     }
     printf("\t�����������(����2001.1.1)��");
     cin>>birthday;
     if(birthday == "-1")
        {
            birthday = "NULL";
            birthday = birthday + ",'";
        }
     else{
        birthday = birthday+"','";
     }
     query = "Insert into BasicInformation(mainEmail,password,name,sex,\
        birthday,address) values('";
    query = query +mainEmail+password+name+sex+birthday+address;
     printf("\n\n\n");
    return query;
}

string LoginIn()
{
     system("cls");
     printf("\t*******************��¼******************\t\n");
     string query,mainEmail,password;
     printf("\t����ע�����䣺");
     cin>>mainEmail;
     printf("\t�������룺");
     cin>>password;
     query = "Select userID,mainEmail from BasicInformation where mainEmail = '" + mainEmail + \
            "' and password ='" + password +"';";
     printf("\n\n\n");
     return query;
}

int HomeView()
{
     //system("cls");
     int num;
     printf("\n\t***************************��ҳ**************************\t\n");
     printf("\t1 ���Ƹ�����Ϣ  2 Ⱥ�����  3 ���ѹ���  4 ��Ϣ����  5 ��־����\n");
     printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}
//**********************************************************
int PerfectDate()
{
    int num;
    printf("\n\t**********************���Ƹ�����Ϣ*********************\t\n");
    printf("\t1 ���ƻ�����Ϣ\t 2 ���Ƹ��˾���\t 3 ������ҳ\n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>3))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

int PerfectPersonInfo()
{
    int num;
    printf("\n\t**********************���ƻ�����Ϣ*********************\t\n");
    printf("\t1 ���ƻ�����Ϣ\t 2 ��Ӹ�������\t 3 ������ҳ\n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>3))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

string UpdatePersonInfo(string userIDstr)
{
    printf("\n\t***********************�޸���Ϣ**********************\t\n");
     string query,password,name,sex,address,birthday;
     query = "update BasicInformation SET password = '";
     printf("\t���������룺");
     cin>>password;
     query = query + password +"',name = '";
     printf("\t����������");
     cin>>name;
     query = query + name +"',sex =";
     printf("\t�����Ա�������1��Ů����0����");
     cin>>sex;
     query = query + sex + ",address = '";
     printf("\t�����ַ��");
     cin>>address;
     query = query + address +"',birthday = '";
     printf("\t�����������(����2001.1.1)��");
     cin>>birthday;
     query = query + birthday +"' where UserID = " + userIDstr +";";
     printf("\n\n\n");
    return query;
}

string PerfectEmail(string userIDstr)
{
    printf("\n\t***********************�������**********************\t\n");
    string email,query;
    printf("\t�������䣺");
    cin>>email;
    query = "Insert into useremail values("+userIDstr+",'"+email+"');";
     printf("\n\n\n");
    return query;
}

int PerfectExperience()
{
    int num;
    printf("\n\t**********************���Ƹ��˾���*********************\t\n");
    printf("\t1 ��ӽ�������  2 �޸Ľ�������  3 ��ӹ�������  4 �޸Ĺ������� 5 ������ҳ\n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
      printf("\n\n\n");
     return num;
}

string PerfectEduExperience(string userIDstr)
{
    printf("\n\t**********************���ƽ�������*********************\t\n");
    printf("\t�������ݿ�ѡ��Ϊ�գ�Ϊ������-1��\n");
    string edulevel,BeginTime,EndTime,UnivName,degree,query;
    query = "Insert into EduExperience values("+userIDstr+",'";
    printf("\t��������ȼ���");
    cin>>edulevel;
    query = query + edulevel +"','";
    printf("\t���뿪ʼʱ�䣨��2001.1.1����");
    cin>>BeginTime;
    query = query + BeginTime + "','";
    printf("\t�������ʱ�䣨��2001.1.1����");
    cin>>EndTime;
    query = query + EndTime + "','";
     printf("\t����ѧУ���ƣ�");
    cin>>UnivName;
    query = query + UnivName + "','";
     printf("\t����ѧλ��");
    cin>>degree;
    query = query + degree + "');";
     printf("\n\n\n");
    return query;

}

string ChangeEduExperience(string userIDstr)
{
    printf("\n\t**********************�޸Ľ�������*********************\t\n");
    printf("\t�������ݿ�ѡ��Ϊ�գ�Ϊ������-1��\n");
    string edulevel,BeginTime,EndTime,UnivName,degree,query;
    query = "Update  EduExperience set edulevel = '";
    printf("\t��������ȼ���");
    cin>>edulevel;
    query = query + edulevel +"',BeginTime = '";
    printf("\t���뿪ʼʱ�䣨��2001.1.1����");
    cin>>BeginTime;
    query = query + BeginTime + "',EndTime = '";
    printf("\t�������ʱ�䣨��2001.1.1����");
    cin>>EndTime;
    query = query + EndTime + "',UnivName = '";
     printf("\t����ѧУ���ƣ�");
    cin>>UnivName;
    query = query + UnivName + "',degree = '";
     printf("\t����ѧλ��");
    cin>>degree;
    query = query + degree + "' where UserID ="+userIDstr+";";
     printf("\n\n\n");
    return query;
}

string PerfectWorkExperience(string userIDstr)
{
    printf("\n\t**********************���ƹ�������*********************\t\n");
    printf("\t�������ݿ�ѡ��Ϊ�գ�Ϊ������-1��\n");
    string query,workCompany,position,BeginTime,EndTime;
    query = "Insert into workexperience values("+userIDstr + ",'";
    printf("\t���빤����λ��");
    cin>>workCompany;
    query = query + workCompany +"','";
    printf("\t����ְλ��");
    cin>>position;
    query = query + position +"','";
    printf("\t���뿪ʼʱ�䣺");
    cin>>BeginTime;
    query = query + BeginTime +"','";
    printf("\t�������ʱ�䣺");
    cin>>EndTime;
    query = query + EndTime +"');";
     printf("\n\n\n");
    return query;
}

string ChangeWorkExperience(string userIDstr)
{
    printf("\n\t**********************�޸Ĺ�������*********************\t\n");
    printf("\t�������ݿ�ѡ��Ϊ�գ�Ϊ������-1��\n");
    string query,workCompany,position,BeginTime,EndTime;
    query = "update workexperience set workCompany = '";
    printf("\t���빤����λ��");
    cin>>workCompany;
    query = query + workCompany +"',position = '";
    printf("\t����ְλ��");
    cin>>position;
    query = query + position +"',BeginTime ='";
    printf("\t���뿪ʼʱ�䣺");
    cin>>BeginTime;
    query = query + BeginTime +"',EndTime='";
    printf("\t�������ʱ�䣺");
    cin>>EndTime;
    query = query + EndTime +"' where UserID = "+userIDstr+";";
     printf("\n\n\n");
    return query;
}
//************************************************************
int HandleGroup()
{
    int num;
    printf("\n\t************************Ⱥ�����***********************\t\n");
    printf("\t 1 ����Ⱥ��  2 �޸�Ⱥ��  3 ɾ��Ⱥ��  4 �鿴Ⱥ���ں��� 5 ������ҳ\n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

string CreateGroup(string userIDstr)
{
     printf("\n\t************************��������***********************\t\n");
     string query,GroupName;
     query = "Insert into FriendGroup(UserID,GroupName) values(" + userIDstr + ",'";
     printf("\t����������ƣ�");
     cin>>GroupName;
     query = query + GroupName +"');";
     printf("\n\n\n");
     return query;
}

string ChangeGroup(string userIDstr)
{
    printf("\n\t************************�޸ķ���***********************\t\n");
    string query,Oldname,NewName;
    query = "Update FriendGroup set GroupName = '";
    printf("\t����ԭ��������:");
    cin>>Oldname;
    printf("\t�������µ�����:");
    cin>>NewName;
    query = query + NewName +"' where UserID = " +userIDstr +" and GroupName = '"+Oldname+"';";
     printf("\n\n\n");
    return query;
}

string DeleteGroup(string userIDstr)
{
    printf("\n\t************************ɾ������***********************\t\n");
    string query,GroupName;
    printf("\t����Ҫɾ���������ƣ�");
    cin>>GroupName;
    query = "Delete from FriendGroup where UserID = "+userIDstr+" and GroupName = '"+GroupName+"';";
     printf("\n\n\n");
    return query;
}
string ShowFriendInGroup(string userIDstr)
{
    printf("\n\t************************���ں���***********************\t\n");
    string query,groupName;
    printf("\t����鿴���ѷ���:");
    cin>>groupName;
    query = "select groupname,remark,name,mainEmail from GoodFriend,BasicInformation where GoodFriend.UserID = " + userIDstr +" and groupname = '"+groupName+"' and GoodFriend.FriendID = BasicInformation.UserID;";
    return query;
}
//*****************************************************************

int ManageGdFriend()
{
   int num;
    printf("\n\t************************���ѹ���***********************\t\n");
    printf("\t 1 ���Һ���  2 ��Ӻ���  3 ɾ������  4 ������Ӻ���  5 ������ҳ\n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
      printf("\n\n\n");
     return num;
}

string SearchFriend()
{
     printf("\n\t************************���Ѳ���***********************\t\n");
     string query,FriendEmail;
     query = "Select name,mainEmail,sex,birthday,address from BasicInformation where mainEmail = '";
     printf("\t�����������:");
     cin>>FriendEmail;
     query = query +FriendEmail+"';";
      printf("\n\n\n");
     return query;
}

string AddNewFriend(string userIDstr)
{
    printf("\n\t************************��Ӻ���***********************\t\n");
    string query,FriendEmail,remark;
    query = "Insert into GoodFriend(UserID,FriendID,remark) values("+userIDstr+",(select userID from BasicInformation where mainEmail = '";
    printf("\t�����������:");
    cin>>FriendEmail;
    Global_friendEmail = FriendEmail;  //����ȫ�ֱ��������ڻ������
    query = query +FriendEmail +"'),'";
    printf("\t���뱸ע��");
    cin>>remark;
    query = query +remark + "');";
     printf("\n\n\n");
    return query;
}
//�Է������б�����Ӻ���
string AddNewFriendMutual(string userIDstr)
{
    string query,FriendEmail,remark;
    query = "Insert into GoodFriend(UserID,FriendID) values((select userID from BasicInformation where mainEmail = '" + Global_friendEmail+"')," + userIDstr + ");";
    return query;
}
string DeleteFriend(string userIDstr)
{
    printf("\n\t************************ɾ������***********************\t\n");
    string query,friendRemark;
    printf("\t������ѱ�ע:");
    cin>>friendRemark;
    Global_deleteRemark = friendRemark;
    query = "Delete from GoodFriend where UserID = " + userIDstr +" and remark = '"+friendRemark+"';";
     printf("\n\n\n");
    return query;
}
//�Է������б���ɾ��
string DeleteFriendMutual(string userIDstr)
{
    string query;
    query = "delete from goodfriend where FriendID = "+userIDstr + " and UserID in (select friendID from goodfriend where remark = '" + Global_deleteRemark + "');";
    return query;
}
string AddFriendToGroup(string userIDstr)
{
    printf("\n\t************************��Ӻ���������***********************\t\n");
    string query,friendRemark,GroupName;
    printf("\t������ѱ�ע��");
    cin>>friendRemark;
    printf("\t�����������:");
    cin>>GroupName;
    query = "Update goodfriend set groupName = '"+GroupName+"' where UserID = " +userIDstr +" and remark = '"+friendRemark+"';";
    return query;
}
//*****************************************************************
int ManageNews()
{
    int num;
    printf("\n\t************************��Ϣ����***********************\t\n");
    printf("\t 1 �鿴��Ϣ \t 2������Ϣ \t 3 ������ҳ\n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
     cin>>num;
     while((num<1)||(num>3))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
      return num;
}

string ShowNews(string userIDstr)
{
    printf("\n\t************************�鿴��Ϣ***********************\t\n");
    string query;
    query = "select * from News where SendpersonID = " + userIDstr +" or RecvpersonID = " +userIDstr+";";
     printf("\n\n\n");
     return query;
}

string SendNews(string userIDstr)
{
    printf("\n\t************************������Ϣ***********************\t\n");
    string query,RecvPerson,NewsContent;
    query = "Insert into News values('";
    printf("\t�������������:");
    cin>>RecvPerson;
    printf("\t���뷢�����ݣ�");
    cin>>NewsContent;
   // char * newContent = new char[maxsize];
    //gets(NewsContent);
    //NewsContent = newContent;
    query = query + NewsContent +"',CURTime()," + userIDstr+",";
    query = query+ "(select UserID from BasicInformation where mainEmail ='"+RecvPerson+"'));";
     printf("\n\n\n");
     return query;
}

//*****************************************************************
int ManageLog()
{
    system("cls");
    int num;
    printf("\n\t************************��־����***********************\t\n");
    printf("\t 1 �鿴��־  2������־  3 �޸���־  4 ɾ����־ 5 ������ҳ \n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
    cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}

string ShowLog(string userIDstr)
{
     printf("\n\t************************�鿴��־***********************\t\n");
     string query;
     query = "Select LogID,LogContent,ChangeTime,CanReply,CanPublic from Log where UserID = "+userIDstr+";";
      printf("\n\n\n");
      return query;
}

string PublicLog(string userIDstr)
{
    printf("\n\t************************������־***********************\t\n");
    string query,LogContent,CanReply,CanPublic,ChangeTime;
    query = "Insert into Log(UserID,LogContent,ChangeTime,CanReply,CanPublic) values(" + userIDstr + ",'";
    printf("\t������־���ݣ�");
    cin>>LogContent;
    query = query +LogContent+"',CURTime(),";
    printf("\t�Ƿ�ɻظ�����1/��0����");
    cin>>CanReply;
     query = query +CanReply+",";
    printf("\t�Ƿ񹫿�����1/��0����");
    cin>>CanPublic;
     query = query +CanPublic+");";
    printf("\n\n\n");
     return query;
}

string ChangeLog(string userIDstr)
{
    printf("\n\t************************�޸���־***********************\t\n");
    string query,logID,LogContent,ChangeTime,CanReply,CanPublic;
    query = "update Log set LogContent = '";
    printf("\t�����޸���־��ID��");
    cin>>logID;
    printf("\t������־���ݣ�");
    cin>>LogContent;
    query = query + LogContent+"',ChangeTime = CURTime(),CanPublic=";
    printf("\t�Ƿ񹫿�����1/��0����");
    cin>>CanPublic;
    query = query +CanPublic + ",CanReply = ";
    printf("\t�Ƿ�ɻظ�����1/��0����");
    cin>>CanReply;
    query = query + CanReply +" where UserID = "+userIDstr+" and LogID = "+logID +";";
     printf("\n\n\n");
    return query;

}

string DeleteLog(string userIDstr)
{
    printf("\n\t*******************ɾ����־******************\t\n");
    string query,logID;
    printf("\t����Ҫɾ����־��ID��");
    cin>>logID;
    Global_logID = logID;//����ȫ�ֱ�����ɾ����־��Ӧ�Ļظ�
    query = "Delete from Log where UserID = "+userIDstr+" and logID = "+ logID + ";";
     printf("\n\n\n");
     return query;
}

string DeleteReplyOfLog(string userIDstr)
{
    string query;
    query = "delete from Reply where logID = " + Global_logID +" and ReplytopersonID = "+ userIDstr +";";
    return query;
}
string DeleteShareOfLog(string userIDstr)
{
    string query;
    query = "delete from share where logID = " +Global_logID +" and UserID = "+ userIDstr +";";
    return query;
}
//***********************************************************
int ManageReplyAndSharelog()
{
     int num;
    printf("\n\t************************��־���������***********************\t\n");
    printf("\t 1 ������־ 2 �鿴���� 3 ������־ 4 �鿴������־  5 ������ҳ \n");
    printf("\t�����Ӧ��Ž����Ӧ����ҳ��:");
    cin>>num;
     while((num<1)||(num>5))
     {
         printf("\t�������������������룺");
         cin>>num;
     }
     printf("\n\n\n");
     return num;
}
//�������
string AddComment(string userIDstr)
{
    printf("\n\t************************������־***********************\t\n");
    string query,replycontent,logID,replyToEmail;
    printf("\t���뱻�ظ������䣺");
    cin>>replyToEmail;
    printf("\t����ظ���־ID��");
    cin>>logID;
    printf("\t����ظ����ݣ�");
    cin>>replycontent;
    query = "insert into Reply(ReplytopersonID,BeRepliedID,LogID,replytime,replyContent) values("+userIDstr+",(select UserID from basicInformation where mainEmail = '" + replyToEmail+"'),"+logID+",CURTime(),'"+replycontent+"');";
    return query;
}

string ShowComment(string userIDstr)
{
     printf("\n\t************************�鿴����***********************\t\n");
     string query,logID;
     printf("\t����鿴���۵���־��ID��");
     cin>>logID;
     query = "select LogContent,Replytime,ReplyContent from Log,Reply where Reply.LogID = log.LogID and reply.LogID = "+ logID+";";
     return query;
}


string AddSharelog(string userIDstr)
{
    printf("\n\t************************������־***********************\t\n");
    string query,logID,CommentContent;
    printf("\t���������־��ID��");
    cin>>logID;
    printf("\t�����������:");
    cin>>CommentContent;
    query = "insert into share(UserID,ShareTime,commentTime,commentContent,logID) values("+userIDstr+",CURTime(),CURTime(),'"+CommentContent+ "',"+logID+ ");";
    return query;
}
string showSharLog(string userIDstr)
{
    printf("\n\t************************�鿴����***********************\t\n");
    string query;
    query = "select logContent,ChangeTime,ShareTime,CommentContent from share,log where share.logID = Log.logID and share.UserID = " + userIDstr +";";
    return query;
}





