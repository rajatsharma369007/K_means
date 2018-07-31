// Description of code: this is a C code to implement the kmeans cluster to cluster two classes.
// Date of release: february, 2018
// Author's name: Rajat Sharma


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int count=0;

//fuction defintion
void kmean(int, float [], float []);

main(){

    FILE *fp = fopen("data.txt","r");
    int arr[10][2], i=0, j=0;
    char line[20],line1[20],c;

    //to count the number of data points
    while((c=fgetc(fp)) != EOF)
    {
        if(c=='\n')
            count++;
    }
    count++;
    rewind(fp);     //to bring the pointer at the beginning

    float sdx, sdy, meanx, meany, tempx=0, tempy=0;
    float datax[count], datay[count], sumx=0, sumy=0;

    printf("\n---------------Original Data------------------\n\n");
    printf(" X feature | Y feature\n\t   |\n");
    //retrieving data from file
    while(!feof(fp))
    {
        fscanf(fp,"%s %s",line,line1);          //retrieving the data from file
        datax[i] = atof(line);                  //conversion of text to float
        datay[i] = atof(line1);
        printf(" %f | %f\n",datax[i],datay[i]);
        sumx += datax[i];                       //sumx, sumy to be used in mean calulation
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

    //function call
    kmean(count, datax, datay);

}

kmean(int count , float datax[], float datay[])
{
    int cluster[count], cluster1[count], cluster2[count], k, l=0, i, j=0, flag=0;
    float tempx=0, tempy=0, tempx1=0, tempy1=0;

    printf("the value of k : 2\n\n");
    k=2;
  //  scanf("%d",&k);   implemented for two clusters  

    float mean[k][2], mean1[k][2], mean2[k][2], prev_mean[k][2];

    //for taking first two data points as centroids
    for(i=0;i<k;i++)
    {
        mean[i][0] = datax[i];          //centroid points for euclidean measure
        mean[i][1] = datay[i];
        mean1[i][0] = mean[i][0];       //centroid points for manhattan measure
        mean1[i][1] = mean[i][1];
        mean2[i][0] = mean[i][0];       //centroid points for minkwoski measure
        mean2[i][1] = mean[i][1];
    }

    //loop for preparing the cluster
    while(!flag)
    {
        //using Eucledian distance
        for(i=0;i<count;i++)
        {
            if(sqrt((pow(mean[0][0]-datax[i],2))+(pow(mean[0][1]-datay[i],2))) < sqrt((pow(mean[1][0]-datax[i],2))+(pow(mean[1][1]-datay[i],2))))
                cluster[i]=0;
            else
                cluster[i]=1;
        }

        //using manhattan distance
        for(i=0;i<count;i++)
        {
            if((fabs(pow(mean1[0][0]-datax[i],1))+fabs(pow(mean1[0][1]-datay[i],1))) < (fabs(pow(mean1[1][0]-datax[i],1))+fabs(pow(mean1[1][1]-datay[i],1))))
                cluster1[i]=0;
            else
                cluster1[i]=1;
        }

        //using minkwoski distance
        for(i=0;i<count;i++)
        {
            if(sqrt(sqrt((pow(mean2[0][0]-datax[i],4))+(pow(mean2[0][1]-datay[i],4)))) < sqrt(sqrt((pow(mean2[1][0]-datax[i],4))+(pow(mean2[1][1]-datay[i],4)))))
                cluster2[i]=0;
            else
                cluster2[i]=1;
        }

        //prev_mean is used for stopping the loop when previous and current mean are equal
        prev_mean[0][0]=mean[0][0];
        prev_mean[0][1]=mean[0][1];
        prev_mean[1][0]=mean[1][0];
        prev_mean[1][1]=mean[1][1];

        tempx=tempy=tempx1=tempy1=0;
        j=0;
        //for Euclidean distance measure
        for(i=0;i<count;i++)
        {
            if(cluster[i]==0)
            {
                tempx += datax[i];      //tempx, tempy is used to calculate the centroid of cluster0
                tempy += datay[i];
                j++;                    //to get the number of data points in cluster 0
            }
            else
            {
                tempx1 += datax[i];     //tempx1, tempy1 is used to calculate the centroid of cluster1
                tempy1 += datay[i];
            }
        }

        //new centroid calculation for both the clusters 
        mean[0][0] = tempx/j;
        mean[0][1] = tempy/j;
        mean[1][0] = tempx1/(count-j);
        mean[1][1] = tempy1/(count-j);

        //printing the calculated centroid of cluster 0 and cluster 1
        printf("------------Euclidean distance---------\n");
        printf("%f %f, %f %f---------------------%2d %2d\n",mean[0][0], mean[0][1], mean[1][0], mean[1][1],j, count-j);

        tempx=tempy=tempx1=tempy1=0;
        j=0;
        //for Manhattan distance measure
        for(i=0;i<count;i++)
        {
            if(cluster1[i]==0)
            {
                tempx += datax[i];      //tempx, tempy is used to calculate the centroid of cluster0
                tempy += datay[i];
                j++;                    //to get the number of datapoints in cluster 0
            }
            else
            {
                tempx1 += datax[i];     //tempx1, tempy1 is used to calculate the centroid of cluster1
                tempy1 += datay[i];
            }
        }
        
        //new centroid calculation for both the clusters
        mean1[0][0] = tempx/j;
        mean1[0][1] = tempy/j;
        mean1[1][0] = tempx1/(count-j);
        mean1[1][1] = tempy1/(count-j);
        
        //printing the calculated centroid of cluster 0 and cluster 1
        printf("------------Manhattan distance----------\n");
        printf("%f %f, %f %f---------------------%2d %2d\n",mean1[0][0], mean1[0][1], mean1[1][0], mean1[1][1],j, count - j);

        tempx=tempy=tempx1=tempy1=0;
        j=0;
        //for Minkwoski distance measure
        for(i=0;i<count;i++)
        {
            if(cluster2[i]==0)
            {
                tempx += datax[i];      //tempx, tempy is used to calculate the centroid of cluster 0
                tempy += datay[i];
                j++;                    //to get the number of datapoints in cluster 0
            }
            else
            {
                tempx1 += datax[i];     //tempx1, tempy1 is used to calculate the centroid of cluster 1
                tempy1 += datay[i];
            }
        }
        
        //new centroid calculation for both the clusters
        mean2[0][0] = tempx/j;
        mean2[0][1] = tempy/j;
        mean2[1][0] = tempx1/(count-j);
        mean2[1][1] = tempy1/(count-j);

        //printing the calculated centroid of cluster 0 and cluster 1
        printf("------------Minkwoski measure------------\n");
        printf("%f %f, %f %f---------------------%2d %2d\n\n",mean2[0][0], mean2[0][1], mean2[1][0], mean2[1][1],j, count-j);
        
        // for printing the cluster
        for(i=0; i<count; i++)
        {
            printf("%d \t %d \t %d\n", cluster[i], cluster1[i], cluster2[i]);
        }
        
        //to break the loop once the previous and current mean are equal
        if(prev_mean[0][0]==mean[0][0] && prev_mean[0][1]==mean[0][1] && prev_mean[1][0]==mean[1][0] && prev_mean[1][1]==mean[1][1])
            flag=1;

        printf("-------%d iteration ---------\n\n",l);
    }
}
