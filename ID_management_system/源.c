

//小组成员:210421419林敏、210421216贾梁
//函数分工:sort()函数以及seek()函数是贾梁帮忙写的，其余都是我（林敏）写的
//部分函数参考及界面构造参考自http://t.csdn.cn/LG417



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
	char name[30];//姓名
	char ID[19];//定义身份证号,18位身份证号，最后第19个元素存放字符终止符
	char sex[3]; //性别
	char area[1000];//户籍所在地区
	int year;//出生日期
	int month;
	int day;
	char note[100];
	char test[10];
	struct time mark_time;
	
	
} person[N];//最大人数可更改

int  n = 0;//n代表当前录入的人数
int k=1;
int flag;
char path1[100];//读取的路径
char path2[100];//保存的路径

//函数声明

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


//本程序将实现输入ID后，读取相应信息，再实现居民信息的添加、删除、查找、排序、筛选、刷新和保存功能
int main()
{ 
	
	fetch_path();
	in_read(path1);
	printf("系统启动中......请稍等\n");
	printf("系统启动成功！\n");
	while (k)
		menu();
	
	system("pause");
	return 0;
}
//帮助函数
void help()
{
	printf("\n0.欢迎使用系统帮助！\n");
	printf("\n1.初次进入系统后,请先选择读取的文件路径和写入的文件路径,\n并先选择增加居民信息;\n");
	printf("\n2.按照菜单提示键入数字代号;\n");
	printf("\n3.操作居民信息后,切记保存;\n");
	printf("\n4.谢谢您的使用！\n");
	system("pause");
}
//菜单函数
void menu()
{
	
	int num;
	
	printf(" \n\n                    \n\n");
	printf("  ******************************************************\n\n");
	printf("  *             新冠疫情居民信息管理系统                  *\n \n");
	printf("  ******************************************************\n\n");
	printf("*********************系统功能菜单*************************       \n");
	printf("     ----------------------   ----------------------   \n");
	printf("     *********************************************     \n");
	printf("     * 0.系统帮助及说明  * * 1.增加居民信息   *     \n");
	printf("     *********************************************     \n");
	printf("     * 2.删除信息        * * 3. 清空居民信息  *     \n");
	printf("     *********************************************     \n");
	printf("     * 4.查询居民信息    * * 5.排序          *     \n");
	printf("     *********************************************     \n");
	printf("     * 6. 显示当前信息      * * 7.筛选出阳性     *     \n");
	printf("     ********************** **********************     \n");
	printf("     * 8.  保存操作    * * 9.退出系统      *     \n");
	printf("     ********************** **********************     \n");
	printf("     ----------------------   ----------------------   \n");
	printf("请选择菜单编号:");
	scanf("%d", &num);
	rewind(stdin);//刷新标准输入流
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
		printf("即将退出程序!\n");
		break;
	default:printf("请在0-8之间选择\n");
	}
}
//本函数将实现添加居民信息的功能
void insert()
{
	
	 
	int k;//判断
	int i=0,j,m=0;//m用于记录已录入的人数
	int flag; 
	
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
		printf("48小时核酸检测结果：");
		fgets(person[i].test, 9, stdin);
		person[i].test[strlen(person[i].test) - 1] = '\0';
		printf("是否继续添加信息,非0继续/0终止,当前已录入人数%d\n", m + 1);
		scanf("%d", &k);
		rewind(stdin);//刷新输入缓冲区
		i++; m++;
		if (k == 0)
		{
			n = i;//总人数更新
			break;
		}
	}
	
	
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
		
		printf("1.按身份证号查询2.按姓名查询3.退出本菜单\n");
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
void in_read(char path1[])
{
	printf("读取文件中......\n");
	FILE* fp1; int i=0;
	char s1[1024];//该数组用于读取文件中第一行的栏目
	if ((fp1 = fopen(path1, "a+")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	else
	{
		fgets(s1, 1024, fp1);//让文件位置指针指向下一行
		for (i = 0; feof(fp1) == 0; i++)
		{
			
			fscanf(fp1, "%s%s%d年%d月%d日%s%s%s%s", person[i].name, person[i].sex, &person[i].year, 
				&person[i].month, &person[i].day, person[i].area, person[i].ID, person[i].test, person[i].note);
			fscanf(fp1, "%d年%d月%d日(%s)%d时%d分%d秒\n",
				&person[i].mark_time.year, 
				&person[i].mark_time.month, 
				&person[i].mark_time.day, 
				&person[i].mark_time.wk_day, 
				&person[i].mark_time.h, 
				&person[i].mark_time.m, 
				&person[i].mark_time.s);//读取登记时间
		}
	}
	
	n = i;//读出已录入的人数
	fclose(fp1);
	printf("读取成功！\n");
}
//更新文件的内容
void save(char path2[])
{
	printf("保存中......请勿退出");
	FILE* fp1;
	
	int i;
	rewind(stdin);
	if ((fp1 = fopen(path2, "w+")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	else
	{
			fprintf(fp1, "姓名\t性别\t出生日期\t\t\t户籍所在地\t\t\t\t身份证号\t\t\t\t48小时核酸检测结果\t备注\t\t登记时间\n");
		for (i = 0; i <n ; i++)
		{
			fetch_time(&person[i]);
			fprintf(fp1, "%s\t%s\t%4d年%2d月%2d日\t\t%s\t\t%s\t\t%s\t\t\t\t%s", person[i].name, person[i].sex, 
				person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID,person[i].test, person[i].note);
			fprintf(fp1, "\t\t%d年%d月%d日(%s)%d时%d分%d秒\n",
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
	printf("保存成功！");

	system("pause");
}
//显示当前居民信息
void display()
{
	int i;
	
	printf( "姓名\t性别\t出生日期\t\t\t户籍所在地\t\t\t\t身份证号\t\t\t\t48小时核酸检测结果\t备注\t\t登记时间\n");
	for (i = 0; i < n; i++)
	{
		fetch_time(&person[i]);
		printf("%s\t%s\t%4d年%2d月%2d日\t\t%s\t\t%s\t\t%s\t\t\t\t%s", person[i].name, person[i].sex,
			person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].test, person[i].note);
		printf("\t\t%d年%d月%d日(%s)%d时%d分%d秒\n",
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
//清空文件内容，利用了文件打开方式中的"w"模式会清空文件的功能
void flush(char path2[])
{
	FILE* fp;
	

	
	if ((fp = fopen(path2, "w")) == NULL)
	{
		printf("打开失败\n");
	}
	else
	{
		printf("清空成功!\n");
		in_read(path1);//刷新内存
	}
	system("pause");
}
//按姓名排序
void sort() 
{
	int i, j,k;
	printf("排序方式:[1]按姓名升序[2]按姓名降序[3]按ID升序[4]按ID降序\n");
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
//获取路径
void fetch_path()
{
	printf("请输入要读取的文件的路径：\n");
	scanf("%s", path1);
	rewind(stdin);
	printf("请输入要写入的文件的路径:\n");
	scanf("%s", path2);
	rewind(stdin);
}
//大型交换现场（皮一下，诶嘿(〃'▽'〃) ）
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
//筛选出阳性的居民
void screen()
{
	int i;
	printf("姓名\t性别\t出生日期\t\t\t户籍所在地\t\t\t\t身份证号\t\t\t\t48小时核酸检测结果\t备注\t\t登记时间\n");
	for(i=0;i<n;i++)
		if (strcmp(person[i].test, "阳性") == 0)
		{

			fetch_time(&person[i]);
			printf("%s\t%s\t%4d年%2d月%2d日\t\t%s\t\t%s\t\t%s\t\t\t\t%s", person[i].name, person[i].sex,
				person[i].year, person[i].month, person[i].day, person[i].area, person[i].ID, person[i].test, person[i].note);
			printf("\t\t%d年%d月%d日(%s)%d时%d分%d秒\n",
				person[i].mark_time.year,
				person[i].mark_time.month,
				person[i].mark_time.day,
				person[i].mark_time.wk_day,
				person[i].mark_time.h,
				person[i].mark_time.m,
				person[i].mark_time.s);
		}

}
//获取当前系统时间存到结构体中
void fetch_time(struct people *person)
{
	time_t current = time(NULL);//time()函数获取当前日历时间存到结构体变量current中
	char* wday_name[] = { "日","一","二","三","四","五","六" };
	struct tm* timer = localtime(&current);//分解时间（系统时间）
	
	person->mark_time.year = timer->tm_year + 1900;
	person->mark_time.month = timer->tm_mon + 1;
	person->mark_time.day= timer->tm_mday;
	strcpy(person->mark_time.wk_day, wday_name[timer->tm_wday]);
	person->mark_time.h = timer->tm_hour;
	person->mark_time.m = timer->tm_min;
	person->mark_time.s = timer->tm_sec;

}