#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int floor_start, floor_end;
int max_floor = 21;
typedef enum {
    empty,//空闲
    up,//上升
    down//下降
} ElevatorState;
struct elevatorstatus
{
	int now_floor;//当前电梯所在层数
    ElevatorState state;
    int sever_floor;//可服务楼层，1为双层，-1为单层，0为全部楼层
}elevator[5];


void First_elevator()
{
    for (int i = 1; i <= 4; i++)
    {
        elevator[i].now_floor = 0;
        elevator[i].state = empty;
        if (i == 2)
            elevator[i].sever_floor = -1;
        else if (i == 3)
            elevator[i].sever_floor = 1;
        else
            elevator[i].sever_floor = 0;
    }
}
void clearscreen()
{
    system("cls");
}

void display(int id) 
{
    for (int i = max_floor - 1; i >= 0; i--) {
            printf("+-------------------------+-------------------------+-------------------------+-------------------------+\n");
            if (elevator[1].now_floor == i)
            {
                    printf("|         %2d       电梯1  ", i);
            }
            else
            {
                if (id == 1 && floor_start == i)
                    printf("|         %2d      开始楼层",i);
                else
                    printf("|         %2d              ", i);
            }
            if (elevator[2].now_floor == i)
            {
                printf("|         %2d       电梯2  ", i);
            }
            else
            {
                if (id == 2 && floor_start == i)
                    printf("|         %2d      开始楼层",i);
                else
                    printf("|         %2d              ", i);
            }
            if (elevator[3].now_floor == i)
            {
                printf("|         %2d       电梯3  ", i);
            }
            else
            {
                if (id == 3 && floor_start == i)
                    printf("|         %2d      开始楼层",i);
                else
                    printf("|         %2d              ", i);
            }
            if (elevator[4].now_floor == i)
            {
                printf("|         %2d       电梯4  |\n", i);
            }
            else
            {
                if (id == 4 && floor_start == i)
                    printf("|         %2d       开始楼层\n",i);
                else
                    printf("|         %2d              |\n", i);
            }
    }
            printf("+-------------------------+-------------------------+-------------------------+-------------------------+\n");
            Sleep(800);
}

int elevatorruning(int floor_start, int floor_end)
{
    int i,id,sub,subb=100,sub_1;
    enum system;
    elevator[0].now_floor = floor_start;
    sub = floor_start - floor_end;
    if (sub > 0)
        elevator[0].state = down;
    else
        elevator[0].state = up;
    sub = abs(sub);
    if (floor_start % 2 == 0 && floor_end % 2 == 0)
        elevator[0].sever_floor = 1;
    if (floor_start % 2 != 0 && floor_end % 2 != 0)
        elevator[0].sever_floor = -1;
    if (floor_start % 2 == 0 && floor_end % 2 != 0 || floor_start % 2 != 0 && floor_end % 2 == 0)
        elevator[0].sever_floor = 0;

    for (i = 1; i <= 4; i++)
    {
        if(elevator[0].sever_floor == 1)//双层
            if (i == 1 || i == 3 || i == 4)
            {
                sub_1 = abs(elevator[0].now_floor - elevator[i].now_floor);
                if (sub_1 < subb)
                {
                    subb = sub_1;
                    if (floor_end <= 10&&floor_start<=10)
                    {
                        id = i;
                    }
                    else
                        id = 4;
                }
            }
        if (elevator[0].sever_floor == -1)//单层
            if (i == 1 || i == 2 || i == 4)
            {
                sub_1 = abs(elevator[0].now_floor - elevator[i].now_floor);
                if (sub_1 < subb)
                {
                    subb = sub_1;
                    if (floor_end <= 10 && floor_start <= 10)
                    {
                        id = i;
                    }
                    else
                        id = 4;
                }
            }
        if (elevator[0].sever_floor == 0)//混层
            if (i == 1 || i == 4)
            {
                sub_1 = abs(elevator[0].now_floor - elevator[i].now_floor);
                if (sub_1 < subb)
                {
                    subb = sub_1;
                    if (floor_end <= 10 && floor_start <= 10)
                    {
                        id = i;
                    }
                    else
                        id = 4;
                }
            }
    }
    //printf("所做电梯编号：%d\n", id);
    for (i = 0; i < subb; i++)
    {
        //printf("\t当前电梯所在楼层：%d\n", elevator[id].now_floor);
        if (floor_start > elevator[id].now_floor)//电梯上升
        {
            elevator[id].now_floor++;
            elevator[id].state = up;
            display(id);
            clearscreen();
        }
        if (floor_start < elevator[id].now_floor)//电梯下降
        {
            elevator[id].now_floor--;
            elevator[id].state = down;
            display(id);
            clearscreen();
        }
    }
    //printf("\t当前电梯所在楼层：%d\n", elevator[id].now_floor);
    for (i = 0; i < sub; i++)
    {
        //printf("\t\t当前电梯所在楼层：%d\n", elevator[id].now_floor);
        if (elevator[0].state == down)
        {
            elevator[id].now_floor--;
            elevator[id].state = down;
            display(id);
            clearscreen();
        }
        if (elevator[0].state == up)
        {
            elevator[id].now_floor++;
            elevator[id].state = up;
            display(id);
            clearscreen();
        }

    }
    elevator[id].state = empty;
    display(id);
    //printf("\t\t当前电梯所在楼层：%d\n", elevator[id].now_floor);
    printf("电梯%d已到达%d层\n", id, elevator[id].now_floor);
    return id;
}

int main()
{
    First_elevator();//初始化电梯
    while (1)
    {
        printf("所在楼层：");
        scanf_s("%d", &floor_start);
        printf("前往楼层：");
        scanf_s("%d", &floor_end);
        int a=elevatorruning(floor_start, floor_end);
    }
}
