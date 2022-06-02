#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000

struct people
{
	char name[30];//姓名
	char ID[20];//定义身份证号,18位身份证号，最后第19个元素存放字符终止符
	char sex[3]; //性别
	char area[1000];//所在地区，
	int year;//出生日期
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

int main()//本程序将实现输入ID后，读取相应信息，再实现居民信息的添加、删除、查找、排序、筛选、刷新和保存功能
{ 
	

	insert();
	system("pause");
	return 0;
}
void help()
{
	printf("\n0.欢迎使用系统帮助！\n");
	printf("\n1.初次进入系统后,请先选择增加居民信息;\n");
	printf("\n2.按照菜单提示键入数字代号;\n");
	printf("\n3.增加居民信息后,切记保存;\n");
	printf("\n4.谢谢您的使用！\n");
}
/*void menu()
{
	int num;
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *                居民信息管理系统                    *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************系统功能菜单*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.系统帮助及说明  * *  1.刷新居民信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.查询居民信息    * *   *     \n");
	printf("     *********************************************     \n");
	printf("     * 4.增加居民信息    * *  5.按ID删除信息 *     \n");
	printf("     *********************************************     \n");
	printf("     * 6.显示当前信息    * *  7.保存当前居民信息*     \n");
	printf("     ********************** **********************     \n");
	printf("     * 8.退出系统        *                            \n");
	printf("     **********************                            \n");
	printf("     ----------------------   ----------------------                           \n");
	printf("请选择菜单编号:");
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
		printf("即将退出程序!\n");
		break;
	default:printf("请在0-8之间选择\n");
	}
}*/
void insert()//本函数将实现添加居民信息的功能
{
	FILE* fp1;
	int k;
	char note[100]="无"; //用于备注，初始化为无信息
	int i=0;//用于记录已录入的人数
	if ((fp1 = fopen("F:\\register_ID.txt", "w")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	else
	{
		fprintf(fp1, "姓名\t\t\t性别\t\t\t出生日期\t\t\t\t户籍所在地\t\t\t\t\t身份证号\t\t\t\t\t备注\n");
		while (1)
		{
			
			trans_ID(fp1, &person[i]); 
			printf("请输入姓名:");
			
			fgets(person[i].name,30,stdin);	
			person[i].name[strlen(person[i].name) - 1] = '\0';
			
			printf("请输入需要备注的信息：");
			
			fgets(person[i].note, 100, stdin);
			person[i].note[strlen(person[i].note) - 1] = '\0';
			fprintf(fp1,"%s\t\t\t%s\t\t\t%d年%d月%d日\t\t\t%s\t\t\t%s\t\t\t%s\n", person[i].name, person[i].sex, person[i].year,person[i].month,person[i].day,person[i].area,person[i].ID,person[i].note);
			
			printf("是否继续添加居民信息,非0继续/0终止,当前已录入人数%d\n",i+1);
			scanf("%d", &k);
			rewind(stdin);//刷新输入缓冲区
			
				if (k == 0)
				{
					break;
					fclose(fp1);
				}
				i++;
		}
	}
	
	
}
void trans_ID(FILE *fp1,struct people *person)//将已知身份证号转换为具体信息
{
	FILE* fp;
	int i;
	char code_area[100] = { 0 };//定义地区编码
	int ymd[8]; 
	int year=0, month=0, day=0;
	
	if ((fp = fopen("ID_area.txt", "r")) == NULL)//文件需要用GBK编码
	{
		printf("打开文件失败\n");
		exit(0);
	}
	else
	{
		
		printf("请输入十八位身份证号：(请不要输入多余数字)");
		
			fgets(person->ID,19,stdin);
			rewind(stdin);//刷新输入缓冲区
		
		
		while ((strncmp(person->ID, code_area, 6) != 0))//比较身份证号前六位和文件中的地区编码
		{


			if (!feof(fp))//执行到文件末尾
			{
				fgets(code_area, 100, fp);//读取文件中的一行
				code_area[strlen(code_area) - 1] = '\0';//去除行末的换行符
				strcpy(person->area, code_area + 6);//将查找到的对应编码的地区存到area字符数组中

			}
			else
			{
				strcpy(person->area, "不存在，或地区已撤销");
				break;
			}
		}
		for (i = 6; i <= 13; i++)//取出出生日期
		{
			ymd[i - 6] = person->ID[i]-'0';
		}
		for (i = 0; i < 4; i++)
			year = year * 10 + ymd[i];//这是一种进制转换的方法：t=t*权值+位值
		for (i = 0; i < 2; i++)
			month = month * 10 + ymd[i + 4];
		for (i = 0; i < 2; i++)
			day = day * 10 + ymd[i + 6];
		person->year = year;
		person->month = month;
		person->day = day;
		if (person->ID[16] % 2)//性别判断
			strcpy(person->sex, "男");
		else
			strcpy(person->sex, "女");
		
	}
	fclose(fp);
}