#include <iostream>
#include <winbgim.h>
#include <cstdlib>
#include <conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<stack>


using namespace std;
struct mutare
{
    int x1;
    int y1;
    int x2;
    int y2;
};
struct theme
{
    int piesa;
    int select;
    int general;
    int fundal;
    int sageata;
};
theme temaCulori;
int tablou[8][8];
int scor=0;
stack <mutare> history;
void tema1(theme &temaCulori)
{
    temaCulori.fundal=CYAN;
    temaCulori.general=BLUE;
    temaCulori.piesa=WHITE;
    temaCulori.select=LIGHTRED;
    temaCulori.sageata=BLACK;
}
void tema2 (theme &temaCulori)
{
    temaCulori.fundal=BLACK;
    temaCulori.general=WHITE;
    temaCulori.piesa=MAGENTA;
    temaCulori.select=GREEN;
    temaCulori.sageata=BROWN;
}
bool meniuInJoc(int width, int height, int x, int y)
{
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    int latura=width/7;
    if(x>=stanga+latura*5.2 && x<=stanga+latura*7.3 && y>=sus+latura*5.8&&y<=sus+latura*6.5)
    {
        return true;
    }
    return false;

}
bool undoInJoc(int width, int height, int x, int y)
{
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    int latura=width/7;
    if(x>=stanga-latura*0.2 && x<=stanga+latura*1.7 && y>=sus+latura*5.8&&y<=sus+latura*6.5)
    {
        return true;
    }
    return false;
}
bool mutareValida(int x1, int y1, int x2, int y2)
{
    if(tablou[x2][y2]==0)
    {
        if((x1==x2 && (y1+2==y2|| y1-2==y2))||(y1==y2 && (x1+2==x2|| x1-2==x2)))
        {
            if(tablou[(x1+x2)/2][(y1+y2)/2]==1)
            {
                return true;
            }

        }
    }
    return false;
}
bool inInterior(int x, int y, int x1, int y1, int x2, int y2)
{
    return x1<=x && x<=x2 && y1<=y && y<=y2;
}

bool ocupat(int x, int y,int tablou[8][8])
{
    if(tablou[x][y]==1)
    {
        return true;
    }
    return false;
}
bool afara(int x,int y)
{
    if((x<=2||x>=6)&&(y<=2||y>=6))
    {
        return true;
    }
    return false;
}
void stergePiesa(int linia, int coloana, int width, int height)
{
    int x1,y1,x2,y2,xmijloc,ymijloc;
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    int latura=width/7;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    setcolor(temaCulori.general);
    rectangle(x1,y1,x2,y2);
    setcolor(temaCulori.fundal);
    setfillstyle(SOLID_FILL,temaCulori.fundal);
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
}
void deseneazaPiesa(int linia, int coloana,int culoare,int width, int height)
{
    int x1,y1,x2,y2,xmijloc,ymijloc;
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    int latura=width/7;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    setcolor(temaCulori.general);
    rectangle(x1,y1,x2,y2);
    setcolor(temaCulori.fundal);
    setfillstyle(SOLID_FILL,temaCulori.fundal);
    bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
    setcolor(temaCulori.general);
    setfillstyle(SOLID_FILL,culoare);
    fillellipse(xmijloc,ymijloc,18,18);
}
bool posibil_stanga(int x, int y,int tablou[8][8])
{
    if(y>=3&&ocupat(x,y-1,tablou)&&!ocupat(x,y-2,tablou)&&!afara(x,y-1)&&!afara(x,y-2))
    {
        return true;
    }
    return false;
}


bool posibil_jos(int x, int y,int tablou[8][8])
{
    if(x<=5&&ocupat(x+1,y,tablou)&&!ocupat(x+2,y,tablou)&&!afara(x+1,y)&&!afara(x+2,y))
    {
        return true;
    }
    return false;
}

bool posibil_dreapta(int x, int y,int tablou[8][8])
{
    if(y<=5&&ocupat(x,y+1,tablou)&&!ocupat(x,y+2,tablou)&&!afara(x,y+1)&&!afara(x,y+2))
    {
        return true;
    }
    return false;
}

bool posibil_sus(int x, int y,int tablou[8][8])
{
    if(x>=3&&ocupat(x-1,y,tablou)&&!ocupat(x-2,y,tablou)&&!afara(x-1,y)&&!afara(x-2,y))
    {
        return true;
    }
    return false;
}

bool posibil(int x,int y,int tablou[8][8])
{
    if(ocupat(x,y,tablou))
    {
        if(posibil_stanga(x,y,tablou))
        {
            return true;
        }
        if(posibil_sus(x,y,tablou))
        {
            return true;
        }
        if(posibil_dreapta(x,y,tablou))
        {
            return true;
        }
        if(posibil_jos(x,y,tablou))
        {
            return true;
        }
    }
    return false;
}
bool terminat(int tablou[8][8])
{
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=7; j++)
        {
            if(!afara(i,j)&&posibil(i,j,tablou))
            {
                return false;
            }
        }
    }
    return true;
}
bool castigat(int tablou[8][8])
{
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=7; j++)
        {
            if(!afara(i,j)&&tablou[i][j]==1&&!(i==3&&j==3))
            {
                return false;
            }
        }

    }
    return true;
}

void generare(int tablou[8][8])
{
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=7; j++)
        {
            if(!afara(i,j))
            {
                tablou[i][j]=1;
            }
            else
            {
                tablou[i][j]=-1;
            }
        }

    }
    tablou[4][4]=0;
}


void desen(int tablou[8][8],int height,int width)
{
    int i,j;
    int latura=width/7;
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    setbkcolor(temaCulori.fundal);
    clearviewport();
    setcolor(temaCulori.general);
    setfillstyle(SOLID_FILL,temaCulori.piesa);
    for (int i=1; i<=7; i++)
    {
        for (int j=1; j<=7; j++)
        {
            if(!afara(i,j))
            {
                rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
            }
            if(tablou[i][j]==1)
            {
                fillellipse(stanga+latura*(i-0.5),sus+latura*(j-0.5),18,18);
            }

            rectangle(stanga-latura*0.2,sus+latura*5.8,stanga+latura*1.7,sus+latura*6.5);
            rectangle(stanga+latura*5.2,sus+latura*5.8,stanga+latura*7.3,sus+latura*6.5);
            settextjustify(1,1);
            outtextxy(stanga+latura*0.75,sus+latura*6.15,"UNDO");
            outtextxy(stanga+latura*6.25,sus+latura*6.15,"MENIU");

        }

    }
}
void afisare(int tablou[8][8])
{
    for(int i=1; i<=7; i++)
    {
        for(int j=1; j<=7; j++)
        {

            if(!afara(i,j))
            {

                cout<<tablou[i][j];
            }
            else
            {
                cout<<" ";
            }
        }
        cout<<endl;
    }
}
int mutarePiesa(int width,int height)
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    scor=0;
    bool mutareCorecta;
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    int latura=width/7;
    mutare ultimaMutare;
    ultimaMutare.x1=-1;
    ultimaMutare.x2=-1;
    ultimaMutare.y1=-1;
    ultimaMutare.y2=-1;
    history.push(ultimaMutare);
    generare(tablou);
    desen(tablou, height, width);
startJoc:
    do
    {
        mutareCorecta=false;
        if(ismouseclick(WM_LBUTTONDOWN) && (inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height)||meniuInJoc(width,height,x,y)||undoInJoc(width,height,x,y)))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            if(meniuInJoc(width,height,x,y))
            {
                goto inapoi;
            }
            if(undoInJoc(width,height,x,y))
            {
                if(history.top().x1!=-1)
                {
                    ultimaMutare=history.top();
                    history.pop();
                    stergePiesa(ultimaMutare.x2,ultimaMutare.y2,width,height);
                    deseneazaPiesa((ultimaMutare.x1+ultimaMutare.x2)/2,(ultimaMutare.y1+ultimaMutare.y2)/2,temaCulori.piesa,width,height);
                    deseneazaPiesa(ultimaMutare.x1,ultimaMutare.y1,temaCulori.piesa,width,height);
                    tablou[ultimaMutare.x2][ultimaMutare.y2]=0;
                    tablou[ultimaMutare.x1][ultimaMutare.y1]=1;
                    tablou[(ultimaMutare.x1+ultimaMutare.x2)/2][(ultimaMutare.y1+ultimaMutare.y2)/2]=1;
                    scor--;
                    goto startJoc;
                }
            }

            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
            if (tablou[linia1][coloana1]==1)
            {
                deseneazaPiesa(linia1,coloana1,temaCulori.select,width,height);
                do
                {

                    if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(meniuInJoc(width,height,x,y))
                        {
                            goto inapoi;
                        }
                        if(undoInJoc(width,height,x,y))
                        {
                            if(history.top().x1!=-1)
                            {
                                deseneazaPiesa(linia1,coloana1,temaCulori.piesa,width,height);
                                ultimaMutare=history.top();
                                history.pop();
                                stergePiesa(ultimaMutare.x2,ultimaMutare.y2,width,height);
                                deseneazaPiesa((ultimaMutare.x1+ultimaMutare.x2)/2,(ultimaMutare.y1+ultimaMutare.y2)/2,temaCulori.piesa,width,height);
                                deseneazaPiesa(ultimaMutare.x1,ultimaMutare.y1,temaCulori.piesa,width,height);
                                tablou[ultimaMutare.x2][ultimaMutare.y2]=0;
                                tablou[ultimaMutare.x1][ultimaMutare.y1]=1;
                                tablou[(ultimaMutare.x1+ultimaMutare.x2)/2][(ultimaMutare.y1+ultimaMutare.y2)/2]=1;
                                scor--;
                                goto startJoc;
                            }
                        }



                        linia2=(y-sus)/latura+1;
                        coloana2=(x-stanga)/latura+1;
                        if (mutareValida(linia1,coloana1,linia2,coloana2))
                        {
                            mutareCorecta=true;
                            tablou[linia1][coloana1]=0;
                            tablou[(linia1+linia2)/2][(coloana1+coloana2)/2]=0;
                            tablou[linia2][coloana2]=1;
                            stergePiesa(linia1,coloana1,width,height);
                            stergePiesa((linia1+linia2)/2,(coloana1+coloana2)/2,width,height);
                            deseneazaPiesa(linia2,coloana2,temaCulori.piesa,width,height);
                            ultimaMutare.x1=linia1;
                            ultimaMutare.x2=linia2;
                            ultimaMutare.y1=coloana1;
                            ultimaMutare.y2=coloana2;
                            history.push(ultimaMutare);
                            scor++;
                        }
                        else
                        {
                            deseneazaPiesa(linia1,coloana1,temaCulori.piesa,width,height);
                            mutareCorecta=true;
                        }
                    }
                }
                while (!mutareCorecta);
            }

        }
    }
    while (!terminat(tablou));
    if(castigat(tablou))
    {
        return 1;
    }
    return 0;
inapoi:
    return 2;
}
int desenInstructiuni2(int tablou[8][8],int width,int height);
void desenInstructiuni1(int tablou[8][8],int width,int height)
{
startprogram:
    setbkcolor(temaCulori.fundal);
    clearviewport();
    setcolor(temaCulori.general);
    int i,j, x, y;
    int iesit=0;
    int latura=width/7;
    int marimeText=width/150;
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    setbkcolor(temaCulori.fundal);
    clearviewport();
    setcolor(temaCulori.general);
    setfillstyle(SOLID_FILL,temaCulori.piesa);
    for (int i=1; i<=7; i++)
        for (int j=1; j<=7; j++)
        {
            if(!afara(i,j))
            {
                rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
            }
            if(tablou[i][j]==1&&!(i==4&&j==2))
            {
                fillellipse(stanga+latura*(i-0.5),sus+latura*(j-0.5),18,18);
            }
            else if(i==4&&j==2)
            {
                setfillstyle(SOLID_FILL,temaCulori.select);
                fillellipse(stanga+latura*(i-0.5),sus+latura*(j-0.5),18,18);
                setfillstyle(SOLID_FILL,temaCulori.piesa);
            }


        }
    setlinestyle(0,0,6);
    setcolor(temaCulori.sageata);
    line(stanga+latura*(4-0.5),sus+latura*(2-0.5)+latura*1.5,stanga+latura*(4-0.5),sus+latura*(4-0.5));
    line(stanga+latura*(4-0.5),sus+latura*(4-0.5),stanga+latura*(4-0.5)-(latura/2)*0.6,sus+latura*(4-0.5)-(latura/2)*0.6);
    line(stanga+latura*(4-0.5),sus+latura*(4-0.5),stanga+latura*(4-0.5)+(latura/2)*0.6,sus+latura*(4-0.5)-(latura/2)*0.6);
    line(stanga+latura*(4-0.5),sus+latura*(2-0.5)+latura*0.3,stanga+latura*(4-0.5),sus+latura*(4-0.5));
    setcolor(temaCulori.general);
    setlinestyle(0,0,0);
    rectangle(stanga-latura*0.2,sus+latura*5.8,stanga+latura*1.7,sus+latura*6.5);
    rectangle(stanga+latura*5.2,sus+latura*5.8,stanga+latura*7.3,sus+latura*6.5);
    settextjustify(1,1);
    outtextxy(stanga+latura*0.75,sus+latura*6.15,"MENIU");
    outtextxy(stanga+latura*6.25,sus+latura*6.15,"NEXT");

    int ok=1;
    do
    {
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

        if(x>=stanga-latura*0.2&& x<=stanga+latura*1.7 && y>=sus+latura*5.8&&y<=sus+latura*6.5)
        {
            iesit=1;
        }
        if(x>=stanga+latura*5.2&& x<=stanga+latura*7.3 && y>=sus+latura*5.8&&y<=sus+latura*6.5)
        {
            iesit=2;
        }



    }
    while(iesit==0);
    if(iesit==2)
    {
        if(desenInstructiuni2(tablou,width,height)==1)
        {
            goto startprogram;
        }
    }

}
int desenInstructiuni2(int tablou[8][8],int width,int height)
{
startprogram:
    setbkcolor(temaCulori.fundal);
    clearviewport();
    setcolor(temaCulori.general);
    int i,j, x, y;
    int iesit=0;
    int latura=width/7;
    int marimeText=width/150;
    int sus=(getmaxy()-width)/2;
    int stanga=(getmaxx()-height)/2;
    setbkcolor(temaCulori.fundal);
    clearviewport();
    setcolor(temaCulori.general);
    setfillstyle(SOLID_FILL,temaCulori.piesa);
    for (int i=1; i<=7; i++)
        for (int j=1; j<=7; j++)
        {
            if(!afara(i,j))
            {
                rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
            }
            if((i==4&&j==4)||(tablou[i][j]==1&&!(i==4&&(j==2||j==3))))
            {
                fillellipse(stanga+latura*(i-0.5),sus+latura*(j-0.5),18,18);
            }




        }

    rectangle(stanga-latura*0.2,sus+latura*5.8,stanga+latura*1.7,sus+latura*6.5);
    rectangle(stanga+latura*5.2,sus+latura*5.8,stanga+latura*7.3,sus+latura*6.5);
    settextjustify(1,1);
    outtextxy(stanga+latura*0.75,sus+latura*6.15,"BACK");
    outtextxy(stanga+latura*6.25,sus+latura*6.15,"MENIU");

    int ok=1;
    do
    {
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

        if(x>=stanga-latura*0.2&& x<=stanga+latura*1.7 && y>=sus+latura*5.8&&y<=sus+latura*6.5)
        {
            iesit=1;
        }
        if(x>=stanga+latura*5.2&& x<=stanga+latura*7.3 && y>=sus+latura*5.8&&y<=sus+latura*6.5)
        {
            iesit=2;
        }



    }
    while(iesit==0);
    return iesit;
}
