#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000

struct people
{
	char name[30];//����
	char ID[20];//�������֤��,18λ���֤�ţ�����19��Ԫ�ش���ַ���ֹ��
	char sex[3]; //�Ա�
	char area[1000];//���ڵ�����
	int year;//��������
	int month;
	int day;
	char note[100];
} person[N];
int k = 1;
void trans_ID();
void help();
void seek();

void insert();
void del();
void display();
void save();
void menu();

int main()//������ʵ������ID�󣬶�ȡ��Ӧ��Ϣ����ʵ�־�����Ϣ����ӡ�ɾ�������ҡ�����ɸѡ��ˢ�ºͱ��湦��
{ 
	

	insert();
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
/*void menu()
{
	int num;
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                ������Ϣ����ϵͳ                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************ϵͳ���ܲ˵�*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.ϵͳ������˵��  * *  1.ˢ�¾�����Ϣ   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.��ѯ������Ϣ    * *   *     \n");
	printf("     *********************************************     \n");
	printf("     * 4.���Ӿ�����Ϣ    * *  5.��IDɾ����Ϣ *     \n");
	printf("     *********************************************     \n");
	printf("     * 6.��ʾ��ǰ��Ϣ    * *  7.���浱ǰ������Ϣ*     \n");
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
	case 3:; break;
	case 4:insert(); break;
	case 5:del(); break;
	case 6:display(); break;
	case 7:save(); break;
	case 8:
		k = 0;
		printf("�����˳�����!\n");
		break;
	default:printf("����0-8֮��ѡ��\n");
	}
}*/
void insert()//��������ʵ����Ӿ�����Ϣ�Ĺ���
{
	FILE* fp1;
	int k;
	char note[100]="��"; //���ڱ�ע����ʼ��Ϊ����Ϣ
	int i=0;//���ڼ�¼��¼�������
	if ((fp1 = fopen("F:\\register_ID.txt", "w")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	else
	{
		fprintf(fp1, "����\t\t\t�Ա�\t\t\t��������\t\t\t\t�������ڵ�\t\t\t\t\t���֤��\t\t\t\t\t��ע\n");
		while (1)
		{
			
			trans_ID(fp1, &person[i]); 
			printf("����������:");
			
			fgets(person[i].name,30,stdin);	
			person[i].name[strlen(person[i].name) - 1] = '\0';
			
			printf("��������Ҫ��ע����Ϣ��");
			
			fgets(person[i].note, 100, stdin);
			person[i].note[strlen(person[i].note) - 1] = '\0';
			fprintf(fp1,"%s\t\t\t%s\t\t\t%d��%d��%d��\t\t\t%s\t\t\t%s\t\t\t%s\n", person[i].name, person[i].sex, person[i].year,person[i].month,person[i].day,person[i].area,person[i].ID,person[i].note);
			
			printf("�Ƿ������Ӿ�����Ϣ,��0����/0��ֹ,��ǰ��¼������%d\n",i+1);
			scanf("%d", &k);
			rewind(stdin);//ˢ�����뻺����
			
				if (k == 0)
				{
					break;
					fclose(fp1);
				}
				i++;
		}
	}
	
	
}
void trans_ID(FILE *fp1,struct people *person)//����֪���֤��ת��Ϊ������Ϣ
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
		
		printf("������ʮ��λ���֤�ţ�(�벻Ҫ�����������)");
		
			fgets(person->ID,19,stdin);
			rewind(stdin);//ˢ�����뻺����
		
		
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