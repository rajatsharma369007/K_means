#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int count=0;

void kmean(int [][10], int, int [], int []);

main(){

    FILE *fp = fopen("data.txt","r");
    int arr[10][2], i=0, j=0;
    char line[20],line1[20],c;

    while((c=fgetc(fp)) != EOF)
    {
        if(c=='\n')
            count++;
    }
    count++;
    rewind(fp);

    float sdx, sdy, meanx, meany, tempx=0, tempy=0;
    float datax[count], datay[count], sumx=0, sumy=0;

    printf("\n---------------Original Data------------------\n\n");
    printf(" X feature | Y feature\n\t   |\n");
    //retrieving data from file
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",line,line1);
        datax[i] = atof(line);
        datay[i] = atof(line1);
        printf(" %f | %f\n",datax[i],datay[i]);
        sumx += datax[i];
        sumy += datay[i];
        i++;
    }

    //mean of x and y feature
    meanx = sumx/count;
    meany = sumy/count;

    //calculation of summation(data-mean)^2
    i=0;
    while(i<count)
    {
        tempx += pow(abs(datax[i] - meanx), 2);
        tempy += pow(abs(datay[i] - meany), 2);
        i++;
    }

    //standard deviation of x, y feature
    sdx = sqrt(tempx/(count-1));
    sdy = sqrt(tempy/(count-1));

    //preparing the standardized data
    i=0;
    while(i<count)
    {
        datax[i] = (datax[i]-meanx)/sdx;
        datay[i] = (datay[i]-meany)/sdy;
        i++;
    }

    printf("\n---------------Standardised Data----------------\n\n");
    printf(" X feature | Y feature\n\t   |\n");
    //printing the standardized data
    i=0;
    while(i<count)
    {
        printf(" %f | %f\n",datax[i], datay[i]);
        i++;
    }

    //calculation of dissimilarity matrix using euclidean distance
    float matrix[count][count];
    for(i=0;i<count;i++)
    {
        for(j=0;j<=i;j++)
        {
            matrix[i][j] = sqrt(pow(datax[i]-datax[j],2) + pow(datay[i]-datay[j],2));
            matrix[j][i] = matrix[i][j];
        }
    }

    printf("\n---------------Dissimilarity matrix-------------\n\n");
    //for printing the matrix
    for(i=0;i<count;i++)
    {
        for(j=0;j<count;j++)
        {
            printf(" %f ",matrix[i][j]);
        }
        printf("\n\n");
    }

    kmean(matrix, count, datax, datay);

}

kmean(int matrix[][count], int count , int datax[], int datay[])
{
    int cluster[count], k, i, j=0,tempx=0, tempy=0, tempx1=0, tempy1=0;

    printf("enter the value of k : ");
    scanf("%d",&k);

    int mean[k][2];

    for(i=0;i<k;i++)
    {
        mean[i][0] = datax[i];
        mean[i][1] = datay[i];
    }



    for(i=0;i<count;i++)
    {
        if(matrix[][0]<=matrix[i][1])
            cluster[i]=0;
        else
            cluster[i]=1;
    }

    for(i=0;i<count;i++)
    {
        if(cluster[i]==0)
        {
            tempx += datax[i];
            tempy += datay[i];
            j++;
        }
        else
        {
            tempx1 += datax[i];
            tempy1 += datay[i];
        }
    }
/*
    for(i=0; i<count; i++)
    {
        printf("%d %d %d\n", cluster[i], j, count-j);
    }
*/
    mean[0][0] = tempx/j;
    mean[0][1] = tempy/j;
    mean[1][0] = tempx1/(count-j);
    mean[1][1] = tempx1/(count-j);




}

