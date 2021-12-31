#include <stdio.h>
#include <stdlib.h>

int wBin(FILE *fPointer, int x1, int x2, int N, int delta);
void rBin(FILE *fPointer, unsigned int n, int x1, int x2);
int wTxt(FILE *fPointer, int x1, int x2, int N, int delta);
void rTxt(FILE *fPointer, unsigned int n, int x1, int x2);


int main()
{
    //my func F(x) = x*2
    //Bin file size 88 byte
    //Txt file size 69 byte
    //To view the bin file, I used "BinaryViewer"
    unsigned int N, delta, n;
    int x1, x2;
    char grupa[50];
    FILE *fInput, *fReadTxt, *fWriteTxt, *fReadBin, *fWriteBin;

    if(fopen("input.dat", "r") != NULL)
    {
        fInput=fopen("input.dat", "r");
    }
    else
    {
        printf("Can't open file\n");
        getchar();
        return 0;
    }
    fscanf(fInput, "%s %d %d %u %u", &grupa, &x1, &x2, &N, &delta);
    fclose(fInput);

    if(N==0)
    {
        N = delta;
    }
    printf("grupa = %s\n",grupa);
    printf("x1 = %d\n",x1);
    printf("x2 = %d\n",x2);
    printf("N = %u\n",N);
    printf("delta = %u\n",delta);

    fWriteTxt = fopen("result.txt", "w");
    n = wTxt(fWriteTxt,x1,x2,N,delta);
    fclose(fWriteTxt);

    fReadTxt  = fopen("result.txt", "r");
    rTxt(fReadTxt,n,x1,x2);
    fclose(fReadTxt);

    fWriteBin = fopen("result.bin", "wb");
    n = wBin(fWriteBin,x1,x2,N,delta);
    fclose(fWriteBin);

    fReadBin  = fopen("result.bin", "rb");
    rBin(fReadBin,n,x1,x2);
    fclose(fReadBin);

    fReadTxt  = fopen("result.txt", "r");
    saveResultToArray(fReadTxt,n);
    fclose(fReadTxt);

    return 0;
}

int wBin(FILE *fPointer,int x1,int x2,int N,int delta)
{
    int i, y, n = 0;

    for(i = 0;i <= N;i++)
    {
        n++;
        y = 3*x1;
        fwrite(&x1, sizeof(int), 1, fPointer);
        fwrite(&y, sizeof(int), 1, fPointer);

        if(x1 >= x2)
        {
            break;
        }
        x1+= delta;
    }
   return n;
}

void rBin(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i, x, y;

    printf("\n \n(result.bin) : \n");
    printf("X1: %d\nX2: %d\nn: %u\n", x1, x2, n);
    printf("*************************************************\n");
    printf("*       N       *       X       *     F (X)     *\n");
    printf("*************************************************\n");

    for(i = 1;i < n+1;i++)
    {
        fread(&x, sizeof(int), 1, fPointer);
        fread(&y, sizeof(int), 1, fPointer);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n", i, x, y);
        printf("+---------------+---------------+---------------+\n");
    }
}

int wTxt(FILE *fPointer, int x1, int x2, int N, int delta)
{
    int i, y, n = 0;

    for(i = 0;i <= N;i++)
    {
        n++;
        y = 3*x1;

        fprintf(fPointer, "%d %d\n", x1, y);

        if(x1 >= x2)
        {
            return n;
        }
        x1+= delta;
    }
    return n;
}

void rTxt(FILE *fPointer, unsigned int n, int x1, int x2)
{
    int i, x, y;

    printf("\n \n(result.txt) : \n");
    printf("X1: %d\nX2: %d\nn: %u\n", x1, x2, n);
    printf("*************************************************\n");
    printf("*       N       *       X       *     F (X)     *\n");
    printf("*************************************************\n");

    for(i = 1;i < n+1;i++)
    {
        fscanf(fPointer,"%d", &x);
        fscanf(fPointer,"%d", &y);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n", i, x, y);
        printf("+---------------+---------------+---------------+\n");
    }
}

int ** memoryAllocation(int rows, int cols)
{
    int i = 0;
    int **matrix = (int **)malloc(rows*sizeof(int *));

    for( i = 0; i < rows; i++)
    {
      matrix[i] = (int *)malloc(cols*sizeof(int));
    }

    return matrix;
}

void saveResultToArray(FILE *fPointer, int n)
{
   int i, j, k;
   int **z = (int **)malloc(n*sizeof(int*));

   for( i = 0; i < n; i++)
   {
      z[i] = (int *)malloc(2*sizeof(int));
   }

   printf("Array content :\n");

   for(i = 0;i < n;i++)
   {
       for(j = 0;j < 2;j++)
       {
           fscanf(fPointer, "%d", &k);
           z[i][j] = k;
       }
   }

   for(i = 0;i < n;i++)
   {
       for(j = 0;j < 1;j++)
       {
            printf("x: %d \ty: %d\n", z[i][j], z[i][j+1]);
       }
   }

   for(i = 0; i < n;i++)
    {
        free(z[i]);
    }
    free(z);
}
