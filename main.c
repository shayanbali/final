#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "tabe.h"


int main()
{
    struct selool *curr;
    struct random rnd_loc;
    char name[5];
    unsigned char car;
    int i,j,n,n2,count,mod,halat,q;
    //sizeof(unsigned char)
    FILE *fp,*fp_save,*fp_x,*fp_y;
    scanf("%s",name);
    fp=fopen(name,"rb");
    fread(&tool,sizeof(int),1,fp);
    printf("%d\n",tool);
    for(i=0;i<tool;i++)//khandane naqshe
    {
        for (j=0;j<tool;j++)
        {
            fread(&car,sizeof(unsigned char),1,fp);
            if (car=='1')map[i][j].jens=1; else
                if (car=='2') map[i][j].jens=2; else
                if (car=='3') map[i][j].jens=3; else
                map[i][j].jens=4;
        }
    }

    for (i=0;i<tool;i++)
    {
        for (j=0;j<tool;j++)
        {
            map[i][j].vaziat=0;
            if (map[i][j].jens!=1) map[i][j].energy=0;
            else map[i][j].energy=100;
        }
    }
    while (1)//shoru bazi while ke bazi tush anjam mishe
    {
    printf("[1]Load\n[2]New single player game\n[3]New Multiplayer game\n[4]Exit\n");
    scanf("%d",&n);
    switch (n)
    {
        case 1:{
            //load section
            fp_save=fopen("save_info.bin","rb");
            fp_x=fopen("x_info.bin","rb");
            fp_y=fopen("y_info.bin","rb");
            for (i=0;i<tool;i++)
            {
                for (j=0;j<tool;j++)
                {
                    fread(&map[i][j].energy,sizeof(int),1,fp_save);
                }
            }
            fread(&halat,sizeof(int),1,fp_x);
            switch (halat)//tayin 2nafare 1nafare budan
            {
                case 0://single player load
                    fread(&num_x,sizeof(int),1,fp_x);
                    list_x=new_khune(0,"s");
                    fread(&list_x->energy,sizeof(int),1,fp_x);
                    fread(&list_x->x,sizeof(int),1,fp_x);
                    fread(&list_x->y,sizeof(int),1,fp_x);
                    map[list_x->x][list_x->y].vaziat=1;
                    fread(list_x->name,sizeof(char),5,fp_x);
                    for(curr=list_x;curr->next!=NULL;curr=curr->next);
                    for (i=1;i<num_x;i++)
                    {

                        add_end(list_x,0,"s");
                        curr=curr->next;
                        fread(&curr->energy,sizeof(int),1,fp_x);
                        fread(&curr->x,sizeof(int),1,fp_x);
                        fread(&curr->y,sizeof(int),1,fp_x);
                        map[curr->x][curr->y].vaziat=1;
                        fread(curr->name,sizeof(char),5,fp_x);
                    }
                    while (1)
                    {
                        print_map(tool);
                        printf("please enter the name of your cell\n");
                        print_node(list_x);
                        scanf("%s",name);
                        curr=list_x;
                        while (curr->next!=NULL)
                        {
                            if (strcmp(curr->name,name)==0) break;
                            curr=curr->next;
                        }
                        printf("[1] Move \n[2] Split a cell \n[3] Boost energy\n[4] Save \n[5] Exit\n");
                        scanf("%d",&n2);
                        switch (n2)
                        {
                            case 1:
                                move(curr->x,curr->y,list_x);
                                break;
                            case 2:
                                q=split_cell(curr->x,curr->y,list_x);
                                if (q==1) num_x++;
                                break;
                            case 3:
                                boost_energy(curr->x,curr->y,list_x);
                                break;
                            case 4://save
                                fp_x=fopen("x_info.bin","wb");
                                fp_save=fopen("save_info.bin","wb");
                                i=0;
                                fwrite(&i,sizeof(int),1,fp_x);
                                fwrite(&num_x,sizeof(int),1,fp_x);
                                curr=list_x;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_x);
                                    fwrite(&curr->x,sizeof(int),1,fp_x);
                                    fwrite(&curr->y,sizeof(int),1,fp_x);
                                    fwrite(&curr->name,sizeof(char),5,fp_x);
                                    curr=curr->next;
                                }

                                for (i=0;i<tool;i++)
                                {
                                    for (j=0;j<tool;j++)
                                    {
                                        fwrite(&map[i][j].energy,sizeof(int),1,fp_save);
                                    }
                                }
                                fclose(fp_save);
                                fclose(fp_x);
                                break;
                            case 5:
                                return 0;
                                break;
                        }

                    }
                    case 1://multiplayer load
                        fread(&num_x,sizeof(int),1,fp_x);
                        list_x=new_khune(0,"s");
                        fread(&list_x->energy,sizeof(int),1,fp_x);
                        fread(&list_x->x,sizeof(int),1,fp_x);
                        fread(&list_x->y,sizeof(int),1,fp_x);
                        fread(list_x->name,sizeof(char),5,fp_x);
                        map[list_x->x][list_x->y].vaziat=1;
                        for(curr=list_x;curr->next!=NULL;curr=curr->next);
                        for (i=1;i<num_x;i++)
                        {
                            add_end(list_x,0,"s");
                            curr=curr->next;
                            fread(&curr->energy,sizeof(int),1,fp_x);
                            fread(&curr->x,sizeof(int),1,fp_x);
                            fread(&curr->y,sizeof(int),1,fp_x);
                            fread(curr->name,sizeof(char),5,fp_x);
                            map[curr->x][curr->y].vaziat=1;
                        }
                        fread(&num_y,sizeof(int),1,fp_y);
                        list_y=new_khune(0,"s");
                        fread(&list_y->energy,sizeof(int),1,fp_y);
                        fread(&list_y->x,sizeof(int),1,fp_y);
                        fread(&list_y->y,sizeof(int),1,fp_y);
                        fread(list_y->name,sizeof(char),5,fp_y);
                        map[list_y->x][list_y->y].vaziat=1;
                        for(curr=list_y;curr->next!=NULL;curr=curr->next);
                        for (i=1;i<num_y;i++)
                        {

                        add_end(list_y,0,"s");
                        curr=curr->next;
                        fread(&curr->energy,sizeof(int),1,fp_y);
                        fread(&curr->x,sizeof(int),1,fp_y);
                        fread(&curr->y,sizeof(int),1,fp_y);
                        fread(curr->name,sizeof(char),5,fp_y);
                        map[curr->x][curr->y].vaziat=2;
                    }
                    count=0;//shomarande nobat
                while (1)
                {
                    count++;
                    mod=count%2;
                    switch (mod)
                    {
                        case 1:
                            print_map(tool);
                            printf("please enter the name of your cell player 1\n");
                            print_node(list_x);
                            scanf("%s",name);
                            curr=list_x;
                            while (curr->next!=NULL)
                            {
                                if (strcmp(curr->name,name)==0) break;
                                curr=curr->next;
                            }
                            printf("[1] Move \n[2] Split a cell \n[3] Boost energy\n[4] Save \n[5] Exit\n");
                            scanf("%d",&n2);
                            switch (n2)
                            {
                                case 1:
                                    move(curr->x,curr->y,list_x);
                                    break;
                                case 2:
                                    q=split_cell(curr->x,curr->y,list_x);
                                    if (q==1) num_x++;
                                    break;
                                case 3:
                                    boost_energy(curr->x,curr->y,list_x);
                                    break;
                                case 4:
                                    //save;
                                    fp_x=fopen("x_info.bin","wb");
                                fp_y=fopen("y_info.bin","wb");
                                fp_save=fopen("save_info.bin","wb");
                                i=1;
                                fwrite(&i,sizeof(int),1,fp_x);
                                fwrite(&num_x,sizeof(int),1,fp_x);
                                curr=list_x;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_x);
                                    fwrite(&curr->x,sizeof(int),1,fp_x);
                                    fwrite(&curr->y,sizeof(int),1,fp_x);
                                    fwrite(&curr->name,sizeof(char),5,fp_x);
                                    curr=curr->next;
                                }
                                fwrite(&num_y,sizeof(int),1,fp_y);
                                curr=list_y;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_y);
                                    fwrite(&curr->x,sizeof(int),1,fp_y);
                                    fwrite(&curr->y,sizeof(int),1,fp_y);
                                    fwrite(&curr->name,sizeof(char),5,fp_y);
                                    curr=curr->next;
                                }
                                for (i=0;i<tool;i++)
                                {
                                    for (j=0;j<tool;j++)
                                    {
                                        fwrite(&map[i][j].energy,sizeof(int),1,fp_save);\
                                    }
                                }
                                fclose(fp_save);
                                fclose(fp_x);
                                fclose(fp_y);

                                    break;
                                case 5:
                                    return 0;
                                    break;

                                }
                                break;
                        case 0:
                            print_map(tool);
                            printf("please enter the name of your cell player 2\n");
                            print_node(list_y);
                            scanf("%s",name);
                            curr=list_y;
                            while (curr!=NULL)
                            {
                                if (strcmp(curr->name,name)==0) break;
                                curr=curr->next;
                            }
                            printf("[1] Move \n[2] Split a cell \n[3] Boost energy\n[4] Save \n[5] Exit\n");
                            scanf("%d",&n2);
                            switch (n2)
                            {
                                case 1:
                                    move(curr->x,curr->y,list_y);
                                    break;
                                case 2:
                                    q=split_cell(curr->x,curr->y,list_y);
                                    if (q>0) num_y++;
                                    break;
                                case 3:
                                    boost_energy(curr->x,curr->y,list_y);
                                    break;
                                case 4:
                                    //save;
                                     {
                                    fp_x=fopen("x_info.bin","wb");
                                    fp_y=fopen("y_info.bin","wb");
                                    fp_save=fopen("save_info.bin","wb");
                                    i=1;
                                    fwrite(&i,sizeof(int),1,fp_x);
                                    fwrite(&num_x,sizeof(int),1,fp_x);
                                    curr=list_x;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_x);
                                    fwrite(&curr->x,sizeof(int),1,fp_x);
                                    fwrite(&curr->y,sizeof(int),1,fp_x);
                                    fwrite(&curr->name,sizeof(char),5,fp_x);
                                    curr=curr->next;
                                }
                                fwrite(&num_y,sizeof(int),1,fp_y);
                                curr=list_y;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_y);
                                    fwrite(&curr->x,sizeof(int),1,fp_y);
                                    fwrite(&curr->y,sizeof(int),1,fp_y);
                                    fwrite(&curr->name,sizeof(char),5,fp_y);
                                    curr=curr->next;
                                }
                                for (i=0;i<tool;i++)
                                {
                                    for (j=0;j<tool;j++)
                                    {
                                        fwrite(&map[i][j].energy,sizeof(int),1,fp_save);\
                                    }
                                }
                                fclose(fp_save);
                                fclose(fp_x);
                                fclose(fp_y);
                                    break;
                                     }
                                case 5:
                                    return 0;
                                    break;

                            }
                            break;
                    }
                    if (n2==5) break;
                }

                }


                break;
        }
        case 2:{//single
            printf("please enter number of your blocks player1\n");
            scanf("%d",&num_x);
            printf("please give me your blocks's names\n");
            scanf("%s",name);
            list_x=new_khune(0,name);
            list_x->energy=0;
            rnd_loc=rand_set();
            list_x->x=rnd_loc.i;
            list_x->y=rnd_loc.j;
            map[rnd_loc.i][rnd_loc.j].vaziat=1;
            for(curr=list_x;curr->next!=NULL;curr=curr->next);
            for (i=1;i<num_x;i++)
            {
                scanf("%s",name);
                add_end(list_x,0,name);
                for(curr=list_x;curr->next!=NULL;curr=curr->next);
                rnd_loc=rand_set();
                curr->x=rnd_loc.i;
                curr->y=rnd_loc.j;
                map[rnd_loc.i][rnd_loc.j].vaziat=1;

            }
            //printf("\n%d %d\n",list_x->x,list_x->y);
            while (1)
            {
                print_map(tool);
                for(curr=list_x;curr->next!=NULL;curr=curr->next);
                curr->next=NULL;
                printf("\nplease enter the name of your cell\n");
                print_node(list_x);
                scanf("%s",name);
                for(curr=list_x;curr!=NULL;curr=curr->next){
                    if (strcmp(curr->name,name)==0) break;
                }
                //printf("\n%d\n",curr->x);
                //printf("\n%d\n",curr->y);

                printf("[1] Move \n[2] Split a cell \n[3] Boost energy\n[4] Save \n[5] Exit\n");
                scanf("%d",&n2);
                switch (n2)
                {
                    case 1:
                        move(curr->x,curr->y,list_x);
                        break;
                    case 2:
                        q=split_cell(curr->x,curr->y,list_x);
                        if (q==1) num_x++;
                        break;
                    case 3:
                        boost_energy(curr->x,curr->y,list_x);
                        break;
                    case 4:
                        //save;
                                fp_x=fopen("x_info.bin","wb");
                                fp_save=fopen("save_info.bin","wb");
                                i=0;
                                printf("aa\n");
                                fwrite(&i,sizeof(int),1,fp_x);
                                fwrite(&num_x,sizeof(int),1,fp_x);
                                curr=list_x;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_x);
                                    fwrite(&curr->x,sizeof(int),1,fp_x);
                                    fwrite(&curr->y,sizeof(int),1,fp_x);
                                    fwrite(&curr->name,sizeof(char),5,fp_x);
                                    curr=curr->next;
                                }
                                printf("aa\n");

                                for (i=0;i<tool;i++)
                                {
                                    for (j=0;j<tool;j++)
                                    {
                                        fwrite(&map[i][j].energy,sizeof(int),1,fp_save);
                                    }
                                }
                                fclose(fp_save);
                                fclose(fp_x);

                        break;
                    case 5:
                        return 0;
                        break;
                }
                if (n2==5){
                        system("cls");
                        break;

                }
            }

            break;

        }
        case 3:{//multi
            printf("please enter number of your blocks player1\n");
            scanf("%d",&num_x);
            printf("please give me the names of blocks\n");
            scanf("%s",name);
            list_x=new_khune(0,name);
            list_x->energy=0;
            rnd_loc=rand_set();
            list_x->x=rnd_loc.i;
            list_x->y=rnd_loc.j;
            map[rnd_loc.i][rnd_loc.j].vaziat=1;
            for(curr=list_x;curr->next!=NULL;curr=curr->next);
            for (i=1;i<num_x;i++)
            {
                scanf("%s",name);
                add_end(list_x,0,name);
                curr=curr->next;
                rnd_loc=rand_set();
                curr->x=rnd_loc.i;
                curr->y=rnd_loc.j;
                map[rnd_loc.i][rnd_loc.j].vaziat=1;
            }
            printf("please enter number of your blocks player2\n");
            scanf("%d",&num_y);
            printf("please give me the names of blocks\n");
            scanf("%s",name);
            list_y=new_khune(0,name);
            list_y->energy=0;
            rnd_loc=rand_set();
            list_y->x=rnd_loc.i;
            list_y->y=rnd_loc.j;
            map[rnd_loc.i][rnd_loc.j].vaziat=2;
            for(curr=list_y;curr->next!=NULL;curr=curr->next);
            for (i=1;i<num_y;i++)
            {
                scanf("%s",name);
                add_end(list_y,0,name);
                curr=curr->next;
                rnd_loc=rand_set();
                curr->x=rnd_loc.i;
                curr->y=rnd_loc.j;
                map[rnd_loc.i][rnd_loc.j].vaziat=2;
            }
            count=0;
            while (1)
            {
               count++;
               mod=count%2;
               print_map(tool);
               switch (mod)
               {
                    case 1:
                        printf("please enter the name of your cell player 1\n");
                        print_node(list_x);
                        scanf("%s",name);
                        curr=list_x;
                        while (curr!=NULL)
                        {
                            if (strcmp(curr->name,name)==0) break;
                            curr=curr->next;
                        }
                        printf("[1] Move \n[2] Split a cell \n[3] Boost energy\n[4] Save \n[5] Exit\n");
                        scanf("%d",&n2);
                        switch (n2)
                        {
                            case 1:
                                move(curr->x,curr->y,list_x);
                                break;
                            case 2:
                                q=split_cell(curr->x,curr->y,list_x);
                                if (q==1) num_x++;
                                break;
                            case 3:
                                boost_energy(curr->x,curr->y,list_x);
                                break;
                            case 4:
                                {
                                //save;
                                fp_x=fopen("x_info.bin","wb");
                                fp_y=fopen("y_info.bin","wb");
                                fp_save=fopen("save_info.bin","wb");
                                i=1;
                                fwrite(&i,sizeof(int),1,fp_x);
                                fwrite(&num_x,sizeof(int),1,fp_x);
                                curr=list_x;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_x);
                                    fwrite(&curr->x,sizeof(int),1,fp_x);
                                    fwrite(&curr->y,sizeof(int),1,fp_x);
                                    fwrite(&curr->name,sizeof(char),5,fp_x);
                                    curr=curr->next;
                                }
                                fwrite(&num_y,sizeof(int),1,fp_y);
                                curr=list_y;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_y);
                                    fwrite(&curr->x,sizeof(int),1,fp_y);
                                    fwrite(&curr->y,sizeof(int),1,fp_y);
                                    fwrite(&curr->name,sizeof(char),5,fp_y);
                                    curr=curr->next;
                                }
                                for (i=0;i<tool;i++)
                                {
                                    for (j=0;j<tool;j++)
                                    {
                                        fwrite(&map[i][j].energy,sizeof(int),1,fp_save);\
                                    }
                                }
                                fclose(fp_save);
                                fclose(fp_x);
                                fclose(fp_y);
                                break;
                                }
                            case 5:
                                return 0;
                                break;

                        }
                        break;
                    case 0:
                        printf("please enter the name of your cell player 2\n");
                        print_node(list_y);
                        scanf("%s",name);
                        curr=list_y;
                        while (curr!=NULL)
                        {
                            if (strcmp(curr->name,name)==0) break;
                            curr=curr->next;
                        }
                        printf("[1] Move \n[2] Split a cell \n[3] Boost energy\n[4] Save \n[5] Exit\n");
                        scanf("%d",&n2);
                        switch (n2)
                        {
                            case 1:
                                move(curr->x,curr->y,list_y);
                                break;
                            case 2:
                                q=split_cell(curr->x,curr->y,list_y);
                                if (q>0) num_y++;
                                break;
                            case 3:
                                boost_energy(curr->x,curr->y,list_y);
                                break;
                            case 4:
                                {
                                //save;
                                fp_x=fopen("x_info.bin","wb");
                                fp_y=fopen("y_info.bin","wb");
                                fp_save=fopen("save_info.bin","wb");
                                i=1;
                                fwrite(&i,sizeof(int),1,fp_x);
                                fwrite(&num_x,sizeof(int),1,fp_x);
                                curr=list_x;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_x);
                                    fwrite(&curr->x,sizeof(int),1,fp_x);
                                    fwrite(&curr->y,sizeof(int),1,fp_x);
                                    fwrite(&curr->name,sizeof(char),5,fp_x);
                                    curr=curr->next;
                                }
                                fwrite(&num_y,sizeof(int),1,fp_y);
                                curr=list_y;
                                while (curr!=NULL)
                                {
                                    fwrite(&curr->energy,sizeof(int),1,fp_y);
                                    fwrite(&curr->x,sizeof(int),1,fp_y);
                                    fwrite(&curr->y,sizeof(int),1,fp_y);
                                    fwrite(&curr->name,sizeof(char),5,fp_y);
                                    curr=curr->next;
                                }
                                for (i=0;i<tool;i++)
                                {
                                    for (j=0;j<tool;j++)
                                    {
                                        fwrite(&map[i][j].energy,sizeof(int),1,fp_save);
                                    }
                                }
                                fclose(fp_save);
                                fclose(fp_x);
                                fclose(fp_y);
                                break;
                                }
                            case 5:
                                return 0;
                                break;

                        }
                        break;
                }
                if (n2==5){
                 system("cls");
                 break;
                }
            }
        }
        case 4:
            exit(0);
    }
    }


    return 0;
}
