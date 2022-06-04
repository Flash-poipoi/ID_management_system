#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000

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
void flush();
void path_edit();

//������ʵ������ID�󣬶�ȡ��Ӧ��Ϣ����ʵ�־�����Ϣ����ӡ�ɾ�������ҡ�����ɸѡ��ˢ�ºͱ��湦��
int main()
{ 
	
	path_edit();
	sort();
	save(path2);
	system("pause");
	return 0;
}
void help()
{
	printf("\n0.��ӭʹ��ϵͳ������\n");
	printf("\n1.���ν���ϵͳ��,����ѡ�����Ӿ�����Ϣ;\n");
	printf("\n2.���ղ˵���ʾ�������ִ���;\n");
	printf("\n3.���Ӿ�����Ϣ��,�мǱ���;\n");
	printf("\n4.лл����ʹ�ã�\n");
}
void menu()
{
	int num;
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                ������Ϣ����ϵͳ                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************ϵͳ���ܲ˵�*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.ϵͳ������˵��  * *  1.��վ�����Ϣ   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.��ѯ������Ϣ    * *  3.���Ӿ�����Ϣ *     ");
	printf("     *********************************************     \n");
	printf("     * 4.��IDɾ����Ϣ    * *  5.��ʾ��ǰ��Ϣ *     \n");
	printf("     *********************************************     \n");
	printf("     * 6.�������    * *  *     \n");
	printf("     ********************** **********************     \n");
	printf("     * 8.�˳�ϵͳ        *                            \n");
	printf("     **********************                            \n");
	printf("     ----------------------   ----------------------                           \n");
	printf("��ѡ��˵����:");
	scanf("%d", &num);
	switch (num)
	{
	case 0:help(); break;
	case 1:flush(); break;
	case 2:seek(); break;
	case 3:insert(); break;
	case 4:del(); break;
	case 5:display(); break;
	case 6:; break;
	case 7:save(path2); break;
	case 8:
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
	in_read(path1);
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

		printf("�Ƿ������Ӿ�����Ϣ,��0����/0��ֹ,��ǰ��¼������%d\n", m + 1);
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
	in_read(path1);
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
		printf("------------------\n");
		printf("-----1.�����֤�Ų�ѯ-----\n");
		printf("-----2.��������ѯ-----\n");
		printf("-----3.�˳����˵�-----\n");
		printf("------------------\n");
		printf("��ѡ���Ӳ˵����:");
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
		for(i=0;feof(fp1)==0;i++)
			fscanf(fp1,"%s\t\t\t%s\t\t\t%d��%d��%d��\t\t\t%s\t\t\t%s\t\t\t%s\n", person[i].name, person[i].sex, &person[i].year, &person[i].month, &person[i].day, person[i].area, person[i].ID, person[i].note);//��ȡ��Ϣ
	}
	
	n = i;//������¼�������
	fclose(fp1);
}
//�����ļ�������
void save(char path2[])
{
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
			fprintf(fp1, "����\t�Ա�\t��������\t\t\t�������ڵ�\t\t\t���֤��\t\t\t��ע\n");
		for (i = 0; i <n ; i++)
		{
			fprintf(fp1, "%3s\t%1s\t%4d��%2d��%2d��\t\t%10s\t\t%18s\t\t%s\n", person[i].name, person[i].sex, person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].note);
		}
	}
	fclose(fp1);
}
//��ʾ��ǰ������Ϣ
void display()
{
	int i;
	in_read(path1);
	printf("����\t�Ա�\t��������\t\t�������ڵ�\t\t\t���֤��\t\t\t��ע\n");
	for (i = 0; i < n; i++)
		printf("%3s\t%1s\t%4d��%2d��%2d��\t\t%10s\t\t%18s\t\t%s\n", person[i].name, person[i].sex, person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].note);
	

}
//����ļ����ݣ��������ļ��򿪷�ʽ�е�"w"ģʽ������ļ��Ĺ���
void flush()
{
	FILE* fp;
	char path[100];
	printf("������Ҫ��յ��ļ���·��\n");
	scanf("%s", path);
	rewind(stdin);
	if ((fp = fopen(path, "w")) == NULL)
	{
		printf("��ʧ��\n");
	}
	else
	{
		printf("��ճɹ�!\n");
	}
}
//����
void sort()
{
	
	struct people temp;
	int i, k, j;
	for (i = 0; i < n - 1; i++) 
	{
		for (j = i+1; j < n; j++) 
		{
			if (strcmp(person[i].name, person[j].name) > 0) 
			{
				temp = person[i];
				person[i] = person[j];
				person[j] = temp;
			}
		}
	}
	
}
void path_edit()
{
	printf("������Ҫ��ȡ���ļ���·����\n");
	scanf("%s", path1);
	rewind(stdin);
	printf("������Ҫд����ļ���·��:\n");
	scanf("%s", path2);
	rewind(stdin);
}