#include <stdio.h>

#define DIM 3

void stampa(int m[DIM][DIM])
{
    int i,j;
    printf("\n --------------------------------------\n");
    for(i=0;i<DIM;i++)
    {
        for(j=0;j<DIM;j++)
        {
            printf("|\t%d\t",m[i][j]);
        }
        printf("|\n --------------------------------------\n");
    }
    printf("\n");
}

int tris(int v[DIM])
{
    int i;
    for (i=0; i<DIM-1; i++)
    {
        if(v[i]==0 || v[i]!=v[i+1])
            return 0;
    }
    return v[0];
}

int vincente(int m[DIM][DIM])
{
    int i, j, risultato, temp[DIM];
    
    for(i=0;i<DIM;i++)
    {
        risultato=tris(m[i]);
        if(risultato!=0)
            return risultato;
        for(j=0;j<DIM;j++)
            temp[j]=m[j][i];
        risultato=tris(temp);
        if(risultato!=0)
            return risultato;
    }
    
    for(i=0;i<DIM;i++)
        temp[i]=m[i][i];
    risultato=tris(temp);
    if(risultato!=0)
        return risultato;
    
    for(i=0;i<DIM;i++)
        temp[i]=m[i][DIM-1-i];
    risultato=tris(temp);
    if(risultato!=0)
        return risultato;
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
            if(m[i][j]==0)
                return -1;
    
    return 0;
}

int mossa_mia(int m[DIM][DIM], int giocatore, int a, int b);

int mossa_avversario(int m[DIM][DIM], int giocatore, int a, int b)
{
    int risultato,i,j,m_temp[DIM][DIM];
    
    if(m[a][b]!=0)
        return -2;
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
            m_temp[i][j]=m[i][j];
    
    m_temp[a][b]=giocatore;
    
    risultato=vincente(m_temp);
    
    if(risultato==giocatore)
        return -1;
    
    if(risultato==0)
        return 0;
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
        {
            risultato=mossa_mia(m_temp,3-giocatore,i,j);
            if(risultato==1)
                return 1;
        }
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
        {
            risultato=mossa_mia(m_temp,3-giocatore,i,j);
            if(risultato==0)
                return 0;
        }

    return -1;
}

int mossa_mia(int m[DIM][DIM], int giocatore, int a, int b)
{
    int risultato,i,j,m_temp[DIM][DIM];
    
    if(m[a][b]!=0)
        return -2;
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
            m_temp[i][j]=m[i][j];
    
    m_temp[a][b]=giocatore;
    
    risultato=vincente(m_temp);
    
    if(risultato==giocatore)
        return 1;
    
    if(risultato==0)
        return 0;
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
        {
            risultato=mossa_avversario(m_temp,3-giocatore,i,j);
            if(risultato==-1)
                return -1;
        }
    
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
        {
            risultato=mossa_avversario(m_temp,3-giocatore,i,j);
            if(risultato==0)
                return 0;
        }
    return 1;
}

void mossa(int m[DIM][DIM], int giocatore)
{
    int i,j;
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
            if(mossa_mia(m,giocatore,i,j)==1)
            {
                m[i][j]=giocatore;
                return ;
            }
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
            if(mossa_mia(m,giocatore,i,j)==0)
            {
                m[i][j]=giocatore;
                return ;
            }
    for(i=0;i<DIM;i++)
        for(j=0;j<DIM;j++)
            if(m[i][j]==0)
            {
                m[i][j]=giocatore;
                return ;
            }
}

int main(int argc, const char * argv[])
{
    int turno,x,y,m[DIM][DIM]={{0,0,0},{0,0,0},{0,0,0}};
    
    turno=2;
    
    while(vincente(m)==-1)
    {
        /*for(i=0;i<DIM;i++)
            for(j=0;j<DIM;j++)
                printf("La mossa (%d,%d) è vincente? Risposta: %d\n", i, j, mossa_mia(m, turno, i, j));*/
        stampa(m);
        if (turno==1) {
            do
            {
                printf("Inserisci le coordinate della tua mossa (<x y>): ");
                scanf("%d %d",&x,&y);
            }while(m[x][y]!=0 || vincente(m)==0);
            if(m[x][y]==0)
                m[x][y]=turno;
        }
        else mossa(m,turno);
        turno=3-turno;
    }
    
    printf("Ha vinto %d! :D\n", vincente(m));
    
    printf("\n");
    
    return 0;
}
