#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000

struct people
{
	char name[30];//姓名
	char ID[19];//定义身份证号,18位身份证号，最后第19个元素存放字符终止符
	char sex[3]; //性别
	char area[1000];//户籍所在地区
	int year;//出生日期
	int month;
	int day;
	char note[100];
} person[N];
int  n = 0;//n代表当前录入的人数
int flag;
void trans_ID();
void help();
void seek();
void in_read();
void insert();
void del();
void display();
void save();
void menu();
void in_write();
//本程序将实现输入ID后，读取相应信息，再实现居民信息的添加、删除、查找、排序、筛选、刷新和保存功能
int main()
{ 
	
	
	
	
	
	
	
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
//本函数将实现添加居民信息的功能
void insert()
{
	
	 
	int k;//判断
	int i=0,j,m=0;//m用于记录已录入的人数
	int flag; 
	in_read();
	i = n;
	while (1)
	{
		printf("请输入十八位身份证号：");
		flag = 1;//确保能顺利进入循环
		while (flag)
		{
			flag = 0;//考虑了只有一组数据的情况
			fgets(person[i].ID, 19, stdin);
			rewind(stdin);//刷新输入缓冲区
			for (j = 0; j < i; j++)
			{
				if (strcmp(person[i].ID, person[j].ID) == 0)
				{
					printf("输入ID重复请重新输入\n");
					flag = 1;//确保了能在while循环中重新输入ID
					break;
				}

			}
		}
		trans_ID(&person[i]);
		printf("请输入姓名:");

		fgets(person[i].name, 30, stdin);
		person[i].name[strlen(person[i].name) - 1] = '\0';//防止换行

		printf("请输入需要备注的信息：");

		fgets(person[i].note, 100, stdin);
		person[i].note[strlen(person[i].note) - 1] = '\0';

		printf("是否继续添加居民信息,非0继续/0终止,当前已录入人数%d\n", m + 1);
		scanf("%d", &k);
		rewind(stdin);//刷新输入缓冲区
		i++; m++;
		if (k == 0)
		{
			n = i;//总人数更新
			break;
		}
	}
	in_write();
	
}
//将已知身份证号转换为具体信息
void trans_ID(struct people *person)
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
//本函数将根据身份证号删除居民的信息。由于对已有文件的内容进行删除操作有些困难，本函数采用读取文件到结构体数组后，再进行删除操作，最后对文件内容更新的方法
void del()
{
	
	char ID[19]; int i, j, flag = 0,k;//flag记录是否删除成功
	in_read();
	while (1)
	{
		printf("请输入要删除的居民的身份证号：");
		fgets(ID, 19,stdin);//输入待删除居民信息的身份证号
		rewind(stdin);//刷新输入缓冲区
		for (i = 0; i < n; i++)
		{
			if (strcmp(ID, person[i].ID) == 0)
			{
				flag = 1;
				for (j = i; j < n - 1; j++)//将所删除居民之后居民往前移动一位
					person[i] = person[i + 1];
			}
		}
		if (flag == 1)
		{
			printf("删除成功\n");
			n--;//录入总人数减一
			in_write();
		}
		else
		{
			printf("删除失败\n");
		}
		printf("是否继续？[0]No/[>1]Yes\n");
		scanf("%d", &k);
		rewind(stdin);
		if (!k)
			break;
	}
	
}
/*查找*/
void seek()
{
	int i, item, flag;
	char name[30], ID[19];

	
	while (1)
	{
		printf("------------------\n");
		printf("-----1.按身份证号查询-----\n");
		printf("-----2.按姓名查询-----\n");
		printf("-----3.退出本菜单-----\n");
		printf("------------------\n");
		printf("请选择子菜单编号:");
		scanf("%d", &item);
		rewind(stdin);
		flag = 0;
		switch (item)
		{
		case 1:
			printf("请输入要查询的人员的身份证号:\n");
			fgets(ID, 19,stdin);
			for (i = 0; i<n; i++)
				if (strcmp(ID, person[i].ID) == 0)
				{
					flag = 1;
					printf("人员姓名\t身份证号\t性别\t所在地区\t出生日期\n");
					printf("--------------------------------------------------------------------\n");
					printf("%s\t%s\t%s\t%s\t%d年%d月%d日\n", person[i].name, person[i].ID, person[i].sex, person[i].area, person[i].year, person[i].month, person[i].day);
				}
			if (0 == flag)
				printf("该ID不存在！\n"); break;
		case 2:
			printf("请输入要查询的居民的姓名:\n");
			fgets(name, 30,stdin);
			name[strlen(name) - 1] = '\0';//去掉换行符
			for (i = 0; i<n; i++)
				if (strcmp(person[i].name, name) == 0)
				{
					flag = 1;
					printf("人员姓名\t身份证号\t性别\t所在地区\t出生日期\n");
					printf("--------------------------------------------------------------------\n");
					printf("%s\t%s\t%s\t%s\t%d年%d月%d日\n", person[i].name, person[i].ID, person[i].sex, person[i].area, person[i].year, person[i].month, person[i].day);
				}
			if (0 == flag)
				printf("该人员不存在！\n"); break;
		case 3:return;
		default:printf("请在1-3之间选择\n");
		}
		printf("是否继续?[0]否/[1]是");
		int k;
		scanf("%d", &k);
		rewind(stdin);//刷新输入缓冲区
		if (!k)
			break;
	}
}
//将文件中的信息逐行读取到结构体数组中
void in_read()
{
	FILE* fp1; int i=0;
	char s1[1024];//该数组用于读取文件中第一行的栏目
	if ((fp1 = fopen("F:\\register_ID.txt", "a+")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	else
	{
		fgets(s1, 1024, fp1);//让文件位置指针指向下一行
		for(i=0;feof(fp1)==0;i++)
			fscanf(fp1,"%s\t\t\t%s\t\t\t%d年%d月%d日\t\t\t%s\t\t\t%s\t\t\t%s\n", person[i].name, person[i].sex, &person[i].year, &person[i].month, &person[i].day, person[i].area, person[i].ID, person[i].note);//读取信息
	}
	
	n = i;//读出已录入的人数
	fclose(fp1);
}
//更新文件的内容
void in_write()
{
	FILE* fp1;
	int i;
	if ((fp1 = fopen("F:\\register_ID.txt", "w+")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	else
	{
		getc(fp1);
		if (feof(fp1) == 1)
		{
			fseek(fp1, -1, SEEK_CUR);
			fprintf(fp1, "姓名\t\t\t性别\t\t\t出生日期\t\t\t\t户籍所在地\t\t\t\t\t身份证号\t\t\t\t\t备注\n");
		}
		else
			fseek(fp1, -1, SEEK_CUR);
		for (i = 0; i <n ; i++)
		{
			fprintf(fp1, "%s\t\t\t%s\t\t\t%d年%d月%d日\t\t\t%s\t\t\t%s\t\t\t%s\n", person[i].name, person[i].sex, person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].note);
		}
	}
	fclose(fp1);
}
//显示当前学生信息
