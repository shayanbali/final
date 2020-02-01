#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
int a_tool,b_tool;
struct random//baraye sakht mokhtasate random
{
    int i;
    int j;
};
struct khune// zakhire etelaat map
{
        int jens; //energy = 1, mitosis = 2, forbidden = 3, normal = 4
        int energy;
        int vaziat;
};
struct khune map[1000][1000];//jadvali ke rush kar mikonim
char visual_map[1000][1000];//jadvali ke be karbar namayesh dade mishe
struct selool//baraye linked list selool ha
{
    int energy;
    char name[5];
    struct selool *next;
    int x;
    int y;
};

struct selool*list_x=NULL;//linked list player 1
struct selool*list_y=NULL;// linked list player 2

struct selool *new_khune(int energy, char name[])
{
    struct selool *new_node=(struct selool *)malloc(sizeof(struct selool));
    new_node->energy=energy;
    strcpy((new_node->name),name);
    new_node->next=NULL;
    return new_node;
};

void add_end(struct selool *list,int energy, char name[])
{
    struct selool *curr=list;
    for ( ; curr->next!=NULL; curr=curr->next);
    curr->next=new_khune(energy,name);
}

int tool,num_x,num_y;
void move(int i,int j,struct selool *list)//tabe jabejayi selool ha
{
    int n,temp;
    printf("[1] North\n[2] South\n[3] North east\n[4] North west\n[5] South east\n[6] South west\n");
    scanf("%d",&n);
    struct selool *curr=list;
    switch (n)
    {
        case 1:
            if (i!=0)
            {
                if (map[i-1][j].vaziat==0 && map[i-1][j].jens!=3)
                {
                    temp=map[i][j].vaziat;
                    map[i][j].vaziat=0;
                    map[i-1][j].vaziat=temp;
                    curr=list;
                    while (curr!=NULL)
                    {
                        if ((curr)->x==i && (curr)->y==j)
                        {
                            (curr)->x--;
                            break;
                        }
                        (curr)=(curr)->next;
                    }
                }
            }else printf("YOU CAN'T\n");
            break;
        case 2:
            if (i!=tool-1)
            {
                if (map[i+1][j].vaziat==0 && map[i+1][j].jens!=3)
                {
                    temp=map[i][j].vaziat;
                    map[i][j].vaziat=0;
                    map[i+1][j].vaziat=temp;
                    curr=list;
                    while (curr!=NULL)
                    {
                        if ((curr)->x==i && (curr)->y==j)
                        {
                            (curr)->x++;
                            break;
                        }
                        (curr)=(curr)->next;
                    }
                }
                else printf("YOU CAN'T\n");
            }else printf("YOU CAN'T\n");
            break;
        case 3:
            if (j==tool-1 ||(j%2==0 && i==0))
                printf("YOU CAN'T\n");
            else
            {
                if (j%2==0)
                {
                       if (map[i-1][j+1].vaziat==0 && map[i-1][j+1].jens!=3)
                        {
                            temp=map[i][j].vaziat;
                            map[i][j].vaziat=0;
                            map[i-1][j+1].vaziat=temp;
                            curr=list;
                            while (curr!=NULL)
                            {
                                if ((curr)->x==i && (curr)->y==j)
                                {
                                    (curr)->x--;
                                    (curr)->y++;
                                    break;
                                }
                                (curr)=(curr)->next;
                            }
                        }
                        else printf("YOU CAN'T\n");
                }
                else
                {
                    if (map[i][j+1].vaziat==0 && map[i][j+1].jens!=3)
                    {
                        temp=map[i][j].vaziat;
                        map[i][j].vaziat=0;
                        map[i][j+1].vaziat=temp;
                        curr=list;
                        while (curr!=NULL)
                        {
                            if ((curr)->x==i && (curr)->y==j)
                            {
                                (curr)->y++;
                                break;
                            }
                            (curr)=(curr)->next;
                        }
                    }else printf("YOU CAN'T");
                }
            }
            break;
        case 4:
            if (j==0 ||(j%2==0 && i==0))
                printf("YOU CAN'T\n");
            else
            {
                if (j%2==0)
                {
                       if (map[i-1][j-1].vaziat==0 && map[i-1][j-1].jens!=3)
                        {
                            temp=map[i][j].vaziat;
                            map[i][j].vaziat=0;
                            map[i-1][j-1].vaziat=temp;
                            curr=list;
                            while (curr!=NULL)
                            {
                                if ((curr)->x==i && (curr)->y==j)
                                {
                                    (curr)->x--;
                                    (curr)->y--;
                                    break;
                                }
                                (curr)=(curr)->next;
                            }
                        }
                        else printf("YOU CAN'T\n");
                }
                else
                {
                    if (map[i][j-1].vaziat==0 && map[i][j-1].jens!=3)
                    {
                        temp=map[i][j].vaziat;
                        map[i][j].vaziat=0;
                        map[i][j-1].vaziat=temp;
                        curr=list;
                        while (curr!=NULL)
                        {
                            if ((curr)->x==i && (curr)->y==j)
                            {
                                (curr)->y--;
                                break;
                            }
                            (curr)=(curr)->next;
                        }
                    }else printf("YOU CAN'T\n");
                }
            }
            break;
        case 5:
            if (j==tool-1 ||(j%2==1 && i==tool-1))
                printf("YOU CAN'T\n");
            else
            {
                if (j%2==0)
                {
                       if (map[i][j+1].vaziat==0 && map[i][j+1].jens!=3)
                        {
                            temp=map[i][j].vaziat;
                            map[i][j].vaziat=0;
                            map[i][j+1].vaziat=temp;
                            curr=list;
                            while (curr!=NULL)
                            {
                                if ((curr)->x==i && (curr)->y==j)
                                {
                                    (curr)->y++;
                                    break;
                                }
                                (curr)=(curr)->next;
                            }
                        }
                        else printf("YOU CAN'T\n");
                }
                else
                {
                    if (map[i+1][j+1].vaziat==0 && map[i+1][j+1].jens!=3)
                    {
                        temp=map[i][j].vaziat;
                        map[i][j].vaziat=0;
                        map[i+1][j+1].vaziat=temp;
                        curr=list;
                        while (curr!=NULL)
                        {
                            if ((curr)->x==i && (curr)->y==j)
                            {
                                (curr)->y++;
                                (curr)->x++;
                                break;
                            }
                            (curr)=(curr)->next;
                        }
                    }else printf("YOU CAN'T\n");
                }
            }
            break;
        case 6:
            if (j==0 ||(j%2==1 && i==tool-1))
                printf("YOU CAN'T\n");
            else
            {
                if (j%2==0)
                {
                       if (map[i][j-1].vaziat==0 && map[i][j-1].jens!=3)
                        {
                            temp=map[i][j].vaziat;
                            map[i][j].vaziat=0;
                            map[i][j-1].vaziat=temp;
                            curr=list;
                            while (curr!=NULL)
                            {
                                if ((curr)->x==i && (curr)->y==j)
                                {
                                    (curr)->y--;
                                    break;
                                }
                                (curr)=(curr)->next;
                            }
                        }
                        else printf("YOU CAN'T\n");
                }
                else
                {
                    if (map[i+1][j-1].vaziat==0 && map[i+1][j-1].jens!=3)
                    {
                        temp=map[i][j].vaziat;
                        map[i][j].vaziat=0;
                        map[i+1][j-1].vaziat=temp;
                        curr=list;
                        while (curr!=NULL)
                        {
                            if ((curr)->x==i && (curr)->y==j)
                            {
                                (curr)->y--;
                                (curr)->x++;
                                break;
                            }
                            (curr)=(curr)->next;
                        }
                    }else printf("YOU CAN'T\n");
                }
            }
            break;
    }
}

struct random rand_set()//sakht mokhtasate random
{
    int i,j;
    struct random loc;
    srand(time(NULL));
    while (1)
    {
        i=rand()%tool;
        j=rand()%tool;
        if (map[i][j].vaziat==0 && map[i][j].jens!=3)
        {
            loc.i=i;
            loc.j=j;
            return loc;
        }
    }
};
void boost_energy(int i,int j,struct selool*list)
{
    struct selool *curr = list;
    while (1)
    {
        if (curr -> x == i && curr -> y == j)
        {
            break;
        }
        curr = curr -> next;
    }
    if (map[i][j].energy == 0 || curr -> energy == 100)
    {
        printf("YOU CAN'T\n");
        return;
    }
    int cnt = 0;
    while (cnt <= 15)
    {
        cnt++;
        if (map[i][j].energy - cnt < 0 || curr -> energy + cnt > 100)
            break;
    }
    cnt--;
    curr -> energy += cnt;
    map[i][j].energy -= cnt;
}

int split_cell (int i, int j, struct selool *list)
{
    if (map[i][j].jens != 2)
    {
        printf("YOU CAN'T\n");
        return 0;
    }
    struct selool *curr = list;
    while (curr!=NULL)
    {
        if (curr -> x == i && curr -> y == j)
            break;
        curr = curr -> next;
    }
    if (curr -> energy < 80)
    {
        printf("YOU CAN'T\n");
        return;
    }
    struct selool* curr2=list;
    for(;curr2->next!=NULL;curr2=curr2->next);
    int n,temp;
    char name[5];
    printf("[1] North\n[2] South\n[3] Northeast\n[4]\nNorthwest[5] Southeast\n[6]Southwest\n");
    scanf("%d",&n);
    switch (n)
    {
        case 1:
            if (i!=0)
            {
                if (map[i-1][j].vaziat==0 && map[i-1][j].jens!=3)
                {
                    map[i-1][j].vaziat=map[i][j].vaziat;
                    printf("please give me a name\n");
                    scanf("%s",name);
                    add_end(list,40,name);
                    curr2=curr2->next;
                    curr2->x=i-1;
                    curr2->y=j;
                    curr->energy=40;
                    return 1;
                }
            }else {printf("YOU CAN'T\n"); return 0;}
            break;
        case 2:
            if (i!=tool-1)
            {
                if (map[i+1][j].vaziat==0 && map[i+1][j].jens!=3)
                {
                    map[i+1][j].vaziat=map[i][j].vaziat;
                    printf("please give me a name\n");
                    scanf("%s",name);
                    add_end(list,40,name);
                    curr2=curr2->next;
                    curr2->x=i+1;
                    curr2->y=j;
                    curr->energy=40;
                    return 1;
                }
            }else {printf("YOU CAN'T\n"); return 0;}
            break;
        case 3:
            if (j==tool-1 ||(j%2==0 && i==0))
                {printf("YOU CAN'T\n"); return 0;}
            else
            {
                if (j%2==0)
                {
                       if (map[i-1][j+1].vaziat==0 && map[i-1][j+1].jens!=3)
                        {
                            map[i-1][j+1].vaziat=map[i][j].vaziat;
                            printf("please give me a name\n");
                            scanf("%s",name);
                            add_end(list,40,name);
                            curr2=curr2->next;
                            curr2->x=i-1;
                            curr2->y=j+1;
                            curr->energy=40;
                            return 1;
                        }
                        else {printf("YOU CAN'T\n"); return 0;}
                }
                else
                {
                    if (map[i][j+1].vaziat==0 && map[i][j+1].jens!=3)
                    {
                        map[i][j+1].vaziat=map[i][j].vaziat;
                        printf("please give me a name\n");
                        scanf("%s",name);
                        add_end(list,40,name);
                        curr2=curr2->next;
                        curr2->x=i;
                        curr2->y=j+1;
                        curr->energy=40;
                        return 1;
                    }else {printf("YOU CAN'T\n"); return 0;}
                }
            }
            break;
        case 4:
            if (j==0 ||(j%2==0 && i==0))
                {printf("YOU CAN'T\n"); return 0;}
            else
            {
                if (j%2==0)
                {
                       if (map[i-1][j-1].vaziat==0 && map[i-1][j-1].jens!=3)
                        {
                            map[i-1][j-1].vaziat=map[i][j].vaziat;
                            printf("please give me a name\n");
                            scanf("%s",name);
                            add_end(list,40,name);
                            curr2=curr2->next;
                            curr2->x=i-1;
                            curr2->y=j-1;
                            curr->energy=40;
                            return 1;
                        }
                        else {printf("YOU CAN'T\n"); return 0;}
                }
                else
                {
                    if (map[i][j-1].vaziat==0 && map[i][j-1].jens!=3)
                    {
                        map[i][j-1].vaziat=map[i][j].vaziat;
                        printf("please give me a name\n");
                        scanf("%s",name);
                        add_end(list,40,name);
                        curr2=curr2->next;
                        curr2->x=i;
                        curr2->y=j-1;
                        curr->energy=40;
                        return 1;
                    }else {printf("YOU CAN'T\n"); return 0;}
                }
            }
            break;
        case 5:
            if (j==tool-1 ||(j%2==1 && i==tool-1))
                {printf("YOU CAN'T\n"); return 0;}
            else
            {
                if (j%2==0)
                {
                       if (map[i][j+1].vaziat==0 && map[i][j+1].jens!=3)
                        {
                            map[i][j+1].vaziat=map[i][j].vaziat;
                            printf("please give me a name\n");
                            scanf("%s",name);
                            add_end(list,40,name);
                            curr2=curr2->next;
                            curr2->x=i;
                            curr2->y=j+1;
                            curr->energy=40;
                            return 1;
                        }
                        else {printf("YOU CAN'T\n"); return 0;}
                }
                else
                {
                    if (map[i+1][j+1].vaziat==0 && map[i+1][j+1].jens!=3)
                    {
                        map[i+1][j+1].vaziat=map[i][j].vaziat;
                        printf("please give me a name\n");
                        scanf("%s",name);
                        add_end(list,40,name);
                        curr2=curr2->next;
                        curr2->x=i+1;
                        curr2->y=j+1;
                        curr->energy=40;
                        return 1;
                    }else {printf("YOU CAN'T\n"); return 0;}
                }
            }
            break;
        case 6:
            if (j==0 ||(j%2==0 && i==0))
                {printf("YOU CAN'T\n"); return 0;}
            else
            {
                if (j%2==0)
                {
                       if (map[i][j-1].vaziat==0 && map[i][j-1].jens!=3)
                        {
                            map[i][j-1].vaziat=map[i][j].vaziat;
                            printf("please give me a name\n");
                            scanf("%s",name);
                            add_end(list,40,name);
                            curr2=curr2->next;
                            curr2->x=i;
                            curr2->y=j-1;
                            curr->energy=40;
                            return 1;
                        }
                        else {printf("YOU CAN'T\n"); return 0;}
                }
                else
                {
                    if (map[i+1][j-1].vaziat==0 && map[i+1][j-1].jens!=3)
                    {
                        map[i+1][j-1].vaziat=map[i][j].vaziat;
                        printf("please give me a name\n");
                        scanf("%s",name);
                        add_end(list,40,name);
                        curr2=curr2->next;
                        curr2->x=i+1;
                        curr2->y=j-1;
                        curr->energy=40;
                        return 1;
                    }else {printf("YOU CAN'T\n"); return 0;}
                }
            }
            break;
    }


}
void print_map(int tool)
{
    int i,j,m,n,p,q;
    m=0;
    n=0;
    q=0;
    p=1;
    char a='a'-1;
    visual_map[1][1]=' ';
    for (i=1;i<=tool*2+2;i++)
    {
        for (j=1;j<=4*tool+1;j++)
        {
            if ((j-1)%4>0)visual_map[i][j]='_';
            if (i==1) visual_map[i][j]='_';
            if (i==tool*2+2) visual_map[i][j]='_';
            if (j%4==1&& i>1){
                if((j/4)%2==0)
                {
                    if (i%2==0) visual_map[i][j]='/'; else visual_map[i][j]='\\';
                }else
                {
                     if (i%2==0) visual_map[i][j]='\\'; else visual_map[i][j]='/';
                }
            }
            if (j%8==2 && i%2==0 && i!=tool*2+2) {

                    if (map[m][n].vaziat==0)visual_map[i][j]=' ';
                    else if (map[m][n].vaziat==1)visual_map[i][j]='x';
                        else visual_map[i][j]='y';
                    //n=n+2;
            }
            if (j%8==3 && i%2==0 && i!=tool*2+2) visual_map[i][j]='-';
            if (j%8==4 && i%2==0 && i!=tool*2+2){
                    if (map[m][n].jens==1)visual_map[i][j]='E';
                    else if (map[m][n].jens==2)visual_map[i][j]='M';
                        else if (map[m][n].jens==3) visual_map[i][j]='F';
                        else visual_map[i][j]='N';
                    n=n+2;
            }
            if (j%8==6 && i%2==1 && i>1) {
                    if (map[q][p].vaziat==0)visual_map[i][j]=' ';
                    else if (map[q][p].vaziat==1)visual_map[i][j]='x';
                        else visual_map[i][j]='y';
                    //p=p+2;
            }
            if (j%8==7 && i%2==1 && i>1) visual_map[i][j]='-';
            if (j%8==0 && i%2==1 && i>1) {
                if (map[q][p].jens==1)visual_map[i][j]='E';
                    else if (map[q][p].jens==2)visual_map[i][j]='M';
                        else if (map[q][p].jens==3) visual_map[i][j]='F';
                        else visual_map[i][j]='N';
                p=p+2;
            }
            if (tool%2==1 ){
                if (n>(tool-1)){
                    m++;
                    n=0;
                }
                if (p>tool-1){
                    q++;
                    p=1;
                }
            }else
            {
                if (n>(tool-1)){
                    m++;
                    n=0;
                }
                if (p>tool-1){
                    q++;
                    p=1;
                }
            }
            printf("%c",visual_map[i][j]);

        }
        printf("\n");
    }
}
void print_node(struct selool*list)// namayesh moshakhasate selool ha
{
    struct selool*curr=list;
    while (curr!=NULL)
    {   printf("%s",curr->name);
        printf("(%d,%d)",curr->x,curr->y);
        printf(" energy:%d\n",curr->energy);
        curr=curr->next;
    }


}

