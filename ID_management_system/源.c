

//С���Ա:210421419������210421216����
//�����ֹ�:sort()�����Լ�seek()�����Ǽ�����æд�ģ����඼���ң�������д��
//���ֺ����ο������湹��ο���http://t.csdn.cn/LG417



#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 100000
struct time
{
	int year;
	int month;
	int day;
	char wk_day[4];
	int h;
	int m;
	int s;

};
struct people
{
	char name[30];//����
	char ID[19];//�������֤��,18λ���֤�ţ�����19��Ԫ�ش���ַ���ֹ��
	char sex[3]; //�Ա�
	char area[1000];//�������ڵ���
	int year;//��������
	int month;
	int day;
	char note[100];
	char test[10];
	struct time mark_time;
	
	
} person[N];//��������ɸ���

int  n = 0;//n����ǰ¼�������
int k=1;
int flag;
char path1[100];//��ȡ��·��
char path2[100];//�����·��

//��������

void trans_ID(struct people* person);
void help();
void seek();
void in_read(char path1[]);
void save(char path2[]);
void insert();
void del();
void display();
void menu();
void sort();
void flush(char path2[]);
void fetch_path();
void screen();
void huge_swap(struct people* a, struct people* b);
void fetch_time(struct people* person);


//������ʵ������ID�󣬶�ȡ��Ӧ��Ϣ����ʵ�־�����Ϣ����ӡ�ɾ�������ҡ�����ɸѡ��ˢ�ºͱ��湦��
int main()
{ 
	
	fetch_path();
	in_read(path1);
	printf("ϵͳ������......���Ե�\n");
	printf("ϵͳ�����ɹ���\n");
	while (k)
		menu();
	
	system("pause");
	return 0;
}
//��������
void help()
{
	printf("\n0.��ӭʹ��ϵͳ������\n");
	printf("\n1.���ν���ϵͳ��,����ѡ���ȡ���ļ�·����д����ļ�·��,\n����ѡ�����Ӿ�����Ϣ;\n");
	printf("\n2.���ղ˵���ʾ�������ִ���;\n");
	printf("\n3.����������Ϣ��,�мǱ���;\n");
	printf("\n4.лл����ʹ�ã�\n");
	system("pause");
}
//�˵�����
void menu()
{
	
	int num;
	
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *             �¹����������Ϣ����ϵͳ                  *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************ϵͳ���ܲ˵�*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.ϵͳ������˵��  * * 1.���Ӿ�����Ϣ   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.ɾ����Ϣ        * * 3. ��վ�����Ϣ  *     \n");
	printf("     *********************************************     \n");
	printf("     * 4.��ѯ������Ϣ    * * 5.����          *     \n");
	printf("     *********************************************     \n");
	printf("     * 6. ��ʾ��ǰ��Ϣ      * * 7.ɸѡ������     *     \n");
	printf("     ********************** **********************     \n");
	printf("     * 8.  �������    * * 9.�˳�ϵͳ      *     \n");
	printf("     ********************** **********************     \n");
	printf("     ----------------------   ----------------------   \n");
	printf("��ѡ��˵����:");
	scanf("%d", &num);
	rewind(stdin);//ˢ�±�׼������
	switch (num)
	{
	case 0:help(); break;
	case 1:insert(); break;
	case 2:del(); break;
	case 3:flush(path2); break;
	case 4:seek(); break;
	case 5:sort(); break;
	case 6:display(); break;
	case 7:screen(); break;
	case 8:save(path2); break;
	case 9:
		k = 0;
		printf("�����˳�����!\n");
		break;
	default:printf("����0-8֮��ѡ��\n");
	}
}
//��������ʵ����Ӿ�����Ϣ�Ĺ���
void insert()
{
	
	 
	int k;//�ж�
	int i=0,j,m=0;//m���ڼ�¼��¼�������
	int flag; 
	
	i = n;
	while (1)
	{
		printf("������ʮ��λ���֤�ţ�");
		flag = 1;//ȷ����˳������ѭ��
		while (flag)
		{
			flag = 0;//������ֻ��һ�����ݵ����
			fgets(person[i].ID, 19, stdin);
			rewind(stdin);//ˢ�����뻺����
			for (j = 0; j < i; j++)
			{
				if (strcmp(person[i].ID, person[j].ID) == 0)
				{
					printf("����ID�ظ�����������\n");
					flag = 1;//ȷ��������whileѭ������������ID
					break;
				}

			}
		}
		trans_ID(&person[i]);
		printf("����������:");

		fgets(person[i].name, 30, stdin);
		person[i].name[strlen(person[i].name) - 1] = '\0';//��ֹ����

		printf("��������Ҫ��ע����Ϣ��");

		fgets(person[i].note, 100, stdin);
		person[i].note[strlen(person[i].note) - 1] = '\0';
		printf("48Сʱ����������");
		fgets(person[i].test, 9, stdin);
		person[i].test[strlen(person[i].test) - 1] = '\0';
		printf("�Ƿ���������Ϣ,��0����/0��ֹ,��ǰ��¼������%d\n", m + 1);
		scanf("%d", &k);
		rewind(stdin);//ˢ�����뻺����
		i++; m++;
		if (k == 0)
		{
			n = i;//����������
			break;
		}
	}
	
	
}
//����֪���֤��ת��Ϊ������Ϣ
void trans_ID(struct people *person)
{
	FILE* fp;
	int i;
	char code_area[100] = { 0 };//�����������
	int ymd[8]; 
	int year=0, month=0, day=0;
	
	if ((fp = fopen("ID_area.txt", "r")) == NULL)//�ļ���Ҫ��GBK����
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	else
	{
		while ((strncmp(person->ID, code_area, 6) != 0))//�Ƚ����֤��ǰ��λ���ļ��еĵ�������
		{


			if (!feof(fp))//ִ�е��ļ�ĩβ
			{
				fgets(code_area, 100, fp);//��ȡ�ļ��е�һ��
				code_area[strlen(code_area) - 1] = '\0';//ȥ����ĩ�Ļ��з�
				strcpy(person->area, code_area + 6);//�����ҵ��Ķ�Ӧ����ĵ����浽area�ַ�������

			}
			else
			{
				strcpy(person->area, "�����ڣ�������ѳ���");
				break;
			}
		}
		for (i = 6; i <= 13; i++)//ȡ����������
		{
			ymd[i - 6] = person->ID[i]-'0';
		}
		for (i = 0; i < 4; i++)
			year = year * 10 + ymd[i];//����һ�ֽ���ת���ķ�����t=t*Ȩֵ+λֵ
		for (i = 0; i < 2; i++)
			month = month * 10 + ymd[i + 4];
		for (i = 0; i < 2; i++)
			day = day * 10 + ymd[i + 6];
		person->year = year;
		person->month = month;
		person->day = day;
		if (person->ID[16] % 2)//�Ա��ж�
			strcpy(person->sex, "��");
		else
			strcpy(person->sex, "Ů");
		
	}
	fclose(fp);
}
//���������������֤��ɾ���������Ϣ�����ڶ������ļ������ݽ���ɾ��������Щ���ѣ����������ö�ȡ�ļ����ṹ��������ٽ���ɾ�������������ļ����ݸ��µķ���
void del()
{
	
	char ID[19]; int i, j, flag = 0,k;//flag��¼�Ƿ�ɾ���ɹ�
	
	while (1)
	{
		printf("������Ҫɾ���ľ�������֤�ţ�");
		fgets(ID, 19,stdin);//�����ɾ��������Ϣ�����֤��
		rewind(stdin);//ˢ�����뻺����
		for (i = 0; i < n; i++)
		{
			if (strcmp(ID, person[i].ID) == 0)
			{
				flag = 1;
				for (j = i; j < n - 1; j++)//����ɾ������֮�������ǰ�ƶ�һλ
					person[i] = person[i + 1];
			}
		}
		if (flag == 1)
		{
			printf("ɾ���ɹ�\n");
			n--;//¼����������һ
			
		}
		else
		{
			printf("ɾ��ʧ��\n");
		}
		printf("�Ƿ������[0]No/[>1]Yes\n");
		scanf("%d", &k);
		rewind(stdin);
		if (!k)
			break;
	}
	
}
/*����*/
void seek()
{
	int i, item, flag;
	char name[30], ID[19];

	
	while (1)
	{
		
		printf("1.�����֤�Ų�ѯ2.��������ѯ3.�˳����˵�\n");
		scanf("%d", &item);
		rewind(stdin);
		flag = 0;
		switch (item)
		{
		case 1:
			printf("������Ҫ��ѯ����Ա�����֤��:\n");
			fgets(ID, 19,stdin);
			for (i = 0; i<n; i++)
				if (strcmp(ID, person[i].ID) == 0)
				{
					flag = 1;
					printf("��Ա����\t���֤��\t�Ա�\t���ڵ���\t��������\n");
					printf("--------------------------------------------------------------------\n");
					printf("%s\t%s\t%s\t%s\t%d��%d��%d��\n", person[i].name, person[i].ID, person[i].sex, person[i].area, person[i].year, person[i].month, person[i].day);
				}
			if (0 == flag)
				printf("��ID�����ڣ�\n"); break;
		case 2:
			printf("������Ҫ��ѯ�ľ��������:\n");
			fgets(name, 30,stdin);
			name[strlen(name) - 1] = '\0';//ȥ�����з�
			for (i = 0; i<n; i++)
				if (strcmp(person[i].name, name) == 0)
				{
					flag = 1;
					printf("��Ա����\t���֤��\t�Ա�\t���ڵ���\t��������\n");
					printf("--------------------------------------------------------------------\n");
					printf("%s\t%s\t%s\t%s\t%d��%d��%d��\n", person[i].name, person[i].ID, person[i].sex, person[i].area, person[i].year, person[i].month, person[i].day);
				}
			if (0 == flag)
				printf("����Ա�����ڣ�\n"); break;
		case 3:return;
		default:printf("����1-3֮��ѡ��\n");
		}
		printf("�Ƿ����?[0]��/[1]��");
		int k;
		scanf("%d", &k);
		rewind(stdin);//ˢ�����뻺����
		if (!k)
			break;
	}
}
//���ļ��е���Ϣ���ж�ȡ���ṹ��������
void in_read(char path1[])
{
	printf("��ȡ�ļ���......\n");
	FILE* fp1; int i=0;
	char s1[1024];//���������ڶ�ȡ�ļ��е�һ�е���Ŀ
	if ((fp1 = fopen(path1, "a+")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	else
	{
		fgets(s1, 1024, fp1);//���ļ�λ��ָ��ָ����һ��
		for (i = 0; feof(fp1) == 0; i++)
		{
			
			fscanf(fp1, "%s%s%d��%d��%d��%s%s%s%s", person[i].name, person[i].sex, &person[i].year, 
				&person[i].month, &person[i].day, person[i].area, person[i].ID, person[i].test, person[i].note);
			fscanf(fp1, "%d��%d��%d��(%s)%dʱ%d��%d��\n",
				&person[i].mark_time.year, 
				&person[i].mark_time.month, 
				&person[i].mark_time.day, 
				&person[i].mark_time.wk_day, 
				&person[i].mark_time.h, 
				&person[i].mark_time.m, 
				&person[i].mark_time.s);//��ȡ�Ǽ�ʱ��
		}
	}
	
	n = i;//������¼�������
	fclose(fp1);
	printf("��ȡ�ɹ���\n");
}
//�����ļ�������
void save(char path2[])
{
	printf("������......�����˳�");
	FILE* fp1;
	
	int i;
	rewind(stdin);
	if ((fp1 = fopen(path2, "w+")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	else
	{
			fprintf(fp1, "����\t�Ա�\t��������\t\t\t�������ڵ�\t\t\t\t���֤��\t\t\t\t48Сʱ��������\t��ע\t\t�Ǽ�ʱ��\n");
		for (i = 0; i <n ; i++)
		{
			fetch_time(&person[i]);
			fprintf(fp1, "%s\t%s\t%4d��%2d��%2d��\t\t%s\t\t%s\t\t%s\t\t\t\t%s", person[i].name, person[i].sex, 
				person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID,person[i].test, person[i].note);
			fprintf(fp1, "\t\t%d��%d��%d��(%s)%dʱ%d��%d��\n",
				person[i].mark_time.year,
				person[i].mark_time.month,
				person[i].mark_time.day,
				person[i].mark_time.wk_day,
				person[i].mark_time.h,
				person[i].mark_time.m,
				person[i].mark_time.s);
		}
	}
	fclose(fp1);
	printf("����ɹ���");

	system("pause");
}
//��ʾ��ǰ������Ϣ
void display()
{
	int i;
	
	printf( "����\t�Ա�\t��������\t\t\t�������ڵ�\t\t\t\t���֤��\t\t\t\t48Сʱ��������\t��ע\t\t�Ǽ�ʱ��\n");
	for (i = 0; i < n; i++)
	{
		fetch_time(&person[i]);
		printf("%s\t%s\t%4d��%2d��%2d��\t\t%s\t\t%s\t\t%s\t\t\t\t%s", person[i].name, person[i].sex,
			person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].test, person[i].note);
		printf("\t\t%d��%d��%d��(%s)%dʱ%d��%d��\n",
			person[i].mark_time.year,
			person[i].mark_time.month,
			person[i].mark_time.day,
			person[i].mark_time.wk_day,
			person[i].mark_time.h,
			person[i].mark_time.m,
			person[i].mark_time.s);
	}
	system("pause");
}
//����ļ����ݣ��������ļ��򿪷�ʽ�е�"w"ģʽ������ļ��Ĺ���
void flush(char path2[])
{
	FILE* fp;
	

	
	if ((fp = fopen(path2, "w")) == NULL)
	{
		printf("��ʧ��\n");
	}
	else
	{
		printf("��ճɹ�!\n");
		in_read(path1);//ˢ���ڴ�
	}
	system("pause");
}
//����������
void sort() 
{
	int i, j,k;
	printf("����ʽ:[1]����������[2]����������[3]��ID����[4]��ID����\n");
		scanf("%d", &k);
		switch (k)
		{

			case 1:	for (i = 0; i < n - 1; i++)
					{
						for (j = i + 1; j < n; j++)
						{
							if (strcmp(person[i].name, person[j].name) > 0)
							{
								huge_swap(&person[i], &person[j]);
							}
						}
					}break;
			case 2: for (i = 0; i < n - 1; i++)
			{
				for (j = i + 1; j < n; j++)
				{
					if (strcmp(person[i].name, person[j].name) <0)
					{
						huge_swap(&person[i], &person[j]);
					}
				}
			}break;
			case 3: for (i = 0; i < n - 1; i++)
			{
				for (j = i + 1; j < n; j++)
				{
					if (strcmp(person[i].ID, person[j].ID) > 0)
					{
						huge_swap(&person[i], &person[j]);
					}
				}
			}break;
			case 4: for (i = 0; i < n - 1; i++)
			{
				for (j = i + 1; j < n; j++)
				{
					if (strcmp(person[i].name, person[j].name) < 0)
					{
						huge_swap(&person[i], &person[j]);
					}
				}
			}break;
			default: break;
		}
}
//��ȡ·��
void fetch_path()
{
	printf("������Ҫ��ȡ���ļ���·����\n");
	scanf("%s", path1);
	rewind(stdin);
	printf("������Ҫд����ļ���·��:\n");
	scanf("%s", path2);
	rewind(stdin);
}
//���ͽ����ֳ���Ƥһ�£�����(��'��'��) ��
void huge_swap(struct people *a,struct people *b)
{
	struct people temp;
	strcpy(temp.name, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp.name);

	strcpy(temp.ID, a->ID);
	strcpy(a->ID, b->ID);
	strcpy(b->ID, temp.ID);

	strcpy(temp.sex, a->sex);
	strcpy(a->sex, b->sex);
	strcpy(b->sex, temp.sex);

	strcpy(temp.area, a->area);
	strcpy(a->area, b->area);
	strcpy(b->area, temp.area);

	temp.year = a->year;
	a->year = b->year;
	b->year = temp.year;

	temp.month = a->month;
	a->month = b->month;
	b->month = temp.month;

	temp.day = a->day;
	a->day = b->day;
	b->day = temp.day;

	strcpy(temp.test, a->test);
	strcpy(a->test, b->test);
	strcpy(b->test, temp.test);

	strcpy(temp.note, a->note);
	strcpy(a->note, b->note);
	strcpy(b->note, temp.note);

}
//ɸѡ�����Եľ���
void screen()
{
	int i;
	printf("����\t�Ա�\t��������\t\t\t�������ڵ�\t\t\t\t���֤��\t\t\t\t48Сʱ��������\t��ע\t\t�Ǽ�ʱ��\n");
	for(i=0;i<n;i++)
		if (strcmp(person[i].test, "����") == 0)
		{

			fetch_time(&person[i]);
			printf("%s\t%s\t%4d��%2d��%2d��\t\t%s\t\t%s\t\t%s\t\t\t\t%s", person[i].name, person[i].sex,
				person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].test, person[i].note);
			printf("\t\t%d��%d��%d��(%s)%dʱ%d��%d��\n",
				person[i].mark_time.year,
				person[i].mark_time.month,
				person[i].mark_time.day,
				person[i].mark_time.wk_day,
				person[i].mark_time.h,
				person[i].mark_time.m,
				person[i].mark_time.s);
		}

}
//��ȡ��ǰϵͳʱ��浽�ṹ����
void fetch_time(struct people *person)
{
	time_t current = time(NULL);//time()������ȡ��ǰ����ʱ��浽�ṹ�����current��
	char* wday_name[] = { "��","һ","��","��","��","��","��" };
	struct tm* timer = localtime(&current);//�ֽ�ʱ�䣨ϵͳʱ�䣩
	
	person->mark_time.year = timer->tm_year + 1900;
	person->mark_time.month = timer->tm_mon + 1;
	person->mark_time.day= timer->tm_mday;
	strcpy(person->mark_time.wk_day, wday_name[timer->tm_wday]);
	person->mark_time.h = timer->tm_hour;
	person->mark_time.m = timer->tm_min;
	person->mark_time.s = timer->tm_sec;

}