#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <winbgim.h>
#include<windows.h>
#include<mmsystem.h>
#include "Functii.cpp"
#include <cstring>



using namespace std;
void transformaScor(char s[],int scor)
{
    strcpy(s,"Ai eliminat ");
    char u[3],z[3];
    u[0]=scor%10+'0';
    scor=scor/10;
    if(scor!=0)
    {
        u[1]=u[0];
        u[0]=scor%10+'0';
    }
    strcat(s,u);
    s[strlen(s)]=NULL;
    strcat(s," de piese!");

}
void joaca(int width,int height)
{
    int x,y;
    int ok=1;
    char s[256];
    cleardevice();
    int statusJoaca=mutarePiesa(width,height);
    cleardevice();
    int masura_scris=width/140;
    if(statusJoaca==1)
    {
        settextstyle(3,0,masura_scris);
        settextjustify(1,1);
        outtextxy(getmaxx()/2,height*4/10,"AI CASTIGAT!");
        outtextxy(getmaxx()/2,height*5/10,"apasa AICI pentru meniu");
        transformaScor(s,scor);
        outtextxy(getmaxx()/2,height*6/10,s);
    }
    else
    {
        if(statusJoaca==0)
        {
            settextstyle(3,0,masura_scris);
            settextjustify(1,1);
            outtextxy(getmaxx()/2,height*4/10,"AI PIERDUT...");
            outtextxy(getmaxx()/2,height*5/10,"apasa AICI pentru meniu");
            transformaScor(s,scor);
            outtextxy(getmaxx()/2,height*6/10,s);
        }
        else
        {
            if (statusJoaca==2)
            {
                goto terminatJoaca;
            }

        }
    }

    while(ok==1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            ok=0;
        }
    }
    if(x>=getmaxx()/2-20 && x<=getmaxx()/2+20 && y>=height*5/10-10&&y<=height*5/10)
    {

    }
terminatJoaca:
    ;
}


void optiuni(int &width,int &height)
{
    int ok=1,iesit=0;
    do
    {
        int i=2,j;
        int numar=4;
        int masura_scris=width/140;
        int latura=width/numar;
        int sus=(getmaxy()-width)/2;
        int stanga=(getmaxx()-height)/2;
        setbkcolor(temaCulori.fundal);
        clearviewport();
        setcolor(temaCulori.general);
        for (int j=1; j<=numar-1; j++)
        {
            rectangle(stanga+latura*(i-2),sus+latura*(j-0.25),stanga+latura*i,sus+latura*(j+0.25));
        }

        rectangle(stanga+latura*(i-2),sus+latura*(4-0.25),stanga+latura*(i+2),sus+latura*(4+0.25));

        setfillstyle(SOLID_FILL,WHITE);
        fillellipse(stanga+latura*3.5,sus+latura*2,25, 25);
        setfillstyle(SOLID_FILL,MAGENTA);
        fillellipse(stanga+latura*3.5,sus+latura*3,25, 25);


        settextstyle(3,0,masura_scris);
        settextjustify(1,1);
        outtextxy(stanga+latura*3.5,sus+latura*1,"THEMES:");
        outtextxy(stanga+latura*(i-1),sus+latura*1,"MARE");
        outtextxy(stanga+latura*(i-1),sus+latura*2,"MEDIU");
        outtextxy(stanga+latura*(i-1),sus+latura*3,"MIC");
        outtextxy(stanga+latura*i,sus+latura*4,"INAPOI");

        int ok=1,x,y,marime;
        while(ok==1)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                ok=0;
            }
        }
        if(x>=stanga && x<=stanga+latura*2 && y>=sus+latura*0.75&&y<=sus+latura*1.25)
        {
            height=600;
            width=600;
            closegraph();
            initwindow(200+width,100+height);
        }
        else
        {
            if (x>=stanga && x<=stanga+latura*2 && y>=sus+latura*1.75&&y<=sus+latura*2.25)
            {
                height=500;
                width=500;
                closegraph();
                initwindow(200+width,100+height);
            }
            else
            {
                if (x>=stanga && x<=stanga+latura*2 && y>=sus+latura*2.75&&y<=sus+latura*3.25)
                {
                    height=400;
                    width=400;
                    closegraph();
                    initwindow(200+width,100+height);
                }
                else
                {
                    if (x>=stanga && x<=stanga+latura*4 && y>=sus+latura*3.75&&y<=sus+latura*4.25)
                        iesit=1;
                    else
                    {
                        if (x>=stanga+latura*3.5-25 && x<=stanga+latura*3.5+25 && y>=sus+latura*2-25&&y<=sus+latura*2+25)
                        {
                            if(temaCulori.general!=BLUE)
                            {
                                PlaySound((LPCSTR)"muzica1.wav", NULL, SND_ASYNC|SND_LOOP);
                            }
                            tema1(temaCulori);

                        }
                        else
                        {
                            if (x>=stanga+latura*3.5-25 && x<=stanga+latura*3.5+25 && y>=sus+latura*3-25&&y<=sus+latura*3+25)
                            {
                                if(temaCulori.general!=WHITE)
                                {
                                    PlaySound((LPCSTR)"muzica2.wav", NULL, SND_ASYNC|SND_LOOP);
                                }

                                tema2(temaCulori);

                            }
                        }
                    }
                }
            }
        }

    }
    while(iesit==0);
}



void meniu(int width, int height)
{
    int ok=1;
    int iesit=0;
    initwindow(200+width,100+height);
    int i=2,j;
    int numar=4;
    do
    {
        int latura=width/numar;
        int masura_scris=width/140;
        int sus=(getmaxy()-width)/2;
        int stanga=(getmaxx()-height)/2;

        setbkcolor(temaCulori.fundal);
        clearviewport();
        setcolor(temaCulori.general);
        if(temaCulori.general==BLUE)
        {
            readimagefile("BLUE.jpg", getmaxx()/2-100, sus-90, getmaxx()/2+100,sus+110);
        }
        else
        {
            readimagefile("BLACK.jpg", getmaxx()/2-100, sus-90, getmaxx()/2+100,sus+110);
        }


        for (int j=1; j<=numar; j++)
        {
            rectangle(stanga+latura*(i-2),sus+latura*(j-0.25),stanga+latura*(i+2),sus+latura*(j+0.25));
        }



        settextstyle(3,0,masura_scris);
        settextjustify(1,1);
        outtextxy(getmaxx()/2,sus+latura*1,"PLAY");
        outtextxy(getmaxx()/2,sus+latura*2,"INTRODUCERE");
        outtextxy(getmaxx()/2,sus+latura*3,"OPTIUNI");
        outtextxy(getmaxx()/2,sus+latura*4,"EXIT");



        int x,y,marime,ok=1;
        while(ok==1)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                ok=0;
            }
        }

        if(x>=stanga && x<=stanga+latura*4 && y>=sus+latura*0.75&&y<=sus+latura*1.25)
        {
            joaca(width,height);
        }
        else
        {
            if (x>=stanga && x<=stanga+latura*4 && y>=sus+latura*1.75&&y<=sus+latura*2.25)
            {
                generare(tablou);
                desenInstructiuni1(tablou,width, height);

            }
            else
            {
                if (x>=stanga && x<=stanga+latura*4 && y>=sus+latura*2.75&&y<=sus+latura*3.25)
                {
                    optiuni(width,height);
                    cleardevice();
                }
                else
                {
                    if (x>=stanga && x<=stanga+latura*4 && y>=sus+latura*3.75&&y<=sus+latura*4.25)
                    {
                        iesit=1;
                    }
                }
            }
        }

    }
    while(iesit==0);
}




int main()
{
    PlaySound((LPCSTR)"muzica1.wav", NULL, SND_ASYNC|SND_LOOP);
    tema1(temaCulori);
    meniu(400,400);
    closegraph();
    return 0;

}

