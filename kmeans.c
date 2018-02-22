#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int count=0;

void kmean(int, float [], float []);

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

    kmean(count, datax, datay);

}

kmean(int count , float datax[], float datay[])
{
    int cluster[count], k, l=0, i, j=0, flag=0;
    float tempx=0, tempy=0, tempx1=0, tempy1=0;

    printf("\nenter the value of k : ");
    scanf("%d",&k);

    float mean[k][2], prev_mean[k][2];

    for(i=0;i<k;i++)
    {
        mean[i][0] = datax[i];
        mean[i][1] = datay[i];
    }

    while(l<=30)
    {
        for(i=0;i<count;i++)
        {
            if(sqrt((pow(mean[0][0]-datax[i],2))+(pow(mean[0][1]-datay[i],2))) < sqrt((pow(mean[1][0]-datax[i],2))+(pow(mean[1][1]-datay[i],2))))
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
               // printf("%f %f\n",tempx, tempy);
                j++;
            }
            else
            {
                tempx1 += datax[i];
                tempy1 += datay[i];
               // printf("%f %f\n",tempx1, tempy1);
            }
        }

        for(i=0; i<count; i++)
        {
            printf("%d\n", cluster[i]);
        }

        prev_mean[0][0] = mean[0][0];
        prev_mean[0][1] = mean[0][1];
        prev_mean[1][0] = mean[1][0];
        prev_mean[1][1] = mean[1][1];

        mean[0][0] = tempx/j;
        mean[0][1] = tempy/j;
        mean[1][0] = tempx1/(count-j);
        mean[1][1] = tempy1/(count-j);

        if(prev_mean[0][0] == mean[0][0] && prev_mean[1][0] == mean[1][0] && prev_mean[1][0] == mean[1][0] && prev_mean[1][1] == mean[1][1])
            flag=1;
        printf("-------%d iteration ---------\n",l);
        l++;
    }
}
