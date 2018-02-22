#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int count=0;

//function for preparing the cluster
void kmean(int, float [], float []);

main(){

    FILE *fp = fopen("data.txt","r");
    int arr[10][2], i=0, j=0;
    char line[20],line1[20],c;

    //while loop to get number of data points in the file
    while((c=fgetc(fp)) != EOF)
    {
        if(c=='\n')
            count++;
    }
    count++;
    rewind(fp);     //to bring the file pointer at the beginning

    float sdx, sdy, meanx, meany, tempx=0, tempy=0;
    float datax[count], datay[count], sumx=0, sumy=0;

    printf("\n---------------Original Data------------------\n\n");
    printf(" X feature | Y feature\n\t   |\n");
    //retrieving data from file
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",line,line1);          //retrieving the data points from the file
        datax[i] = atof(line);                  //conversion of text to number
        datay[i] = atof(line1);
        printf(" %f | %f\n",datax[i],datay[i]); //printing the data points
        sumx += datax[i];                       //sumx, sumy to be used in meanx, meany calculation
        sumy += datay[i];
        i++;
    }

    //mean of x and y feature
    meanx = sumx/count;
    meany = sumy/count;

    //calculation of summation(data-mean)^2, to be used in standard deviation calculation
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

    //calling the function
    kmean(count, datax, datay);

}

kmean(int count , float datax[], float datay[])
{
    int cluster[count], k, l=0, i, j=0, flag=0;
    float tempx=0, tempy=0, tempx1=0, tempy1=0;

    //number of clusters
    printf("\nenter the value of k : ");
    scanf("%d",&k);

    float mean[k][2], prev_mean[k][2];

    //to choose the first two data points as centroid, as k=2
    for(i=0;i<k;i++)
    {
        mean[i][0] = datax[i];
        mean[i][1] = datay[i];
    }

    //for 30 iterations, we prepare the cluster
    while(l<=30)
    {
        for(i=0;i<count;i++)
        {
            //comparing the distance of the two centroids from a data points 
            if(sqrt((pow(mean[0][0]-datax[i],2))+(pow(mean[0][1]-datay[i],2))) < sqrt((pow(mean[1][0]-datax[i],2))+(pow(mean[1][1]-datay[i],2))))
                cluster[i]=0;       //if data point is closer to first centroid 
            else
                cluster[i]=1;       //if data point is closer to second centroid
        }

        //after dividing the data points in clusters, we again compute mean of the two clusters
        for(i=0;i<count;i++)
        {
            if(cluster[i]==0)
            {
                tempx += datax[i];
                tempy += datay[i];
                j++;                  //to get the number of data points in first cluster
            }
            else
            {
                tempx1 += datax[i];
                tempy1 += datay[i];
            }
        }

        //printing the index of data points in the two clusters| this is the result
        for(i=0; i<count; i++)
        {
            printf("%d\n", cluster[i]);
        }

        //calculating the mean of two clusters, in every iteration
        mean[0][0] = tempx/j;
        mean[0][1] = tempy/j;
        mean[1][0] = tempx1/(count-j);
        mean[1][1] = tempy1/(count-j);

        printf("-------%d iteration ---------\n",l);
        l++;
    }
}
