#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>
#include <string>      // std::rand, std::srand
using namespace std;

void K_Means( const char *, int K, int NUM);// num is the number of data point 

int main()
{
    const char Input[]="Input.txt";
     K_Means(Input,4,73);

}
void K_Means( const char *str,int K, int NUM)
{

    int k = K;
    const int MAX =100;// Max number of data point in each cluster
    struct Clust
    {
     double x;
     double y;
    };

    Clust  clust[NUM];
    struct Clust1
   {
     double x[MAX];
     double y[MAX];
   };

   Clust1 clusters[NUM];
   Clust  centroid [NUM];
   Clust  Newcentroid [NUM];


    int l =0;
    double n,m;
    ifstream read(str);
    while(read>>n>>m)
    {
      clust[l].x=n;
      clust[l].y=m;
      l++;
    }

    int  random[l];
    int  count[l];
    int  NewCount[l];
    srand((unsigned)time(NULL));
    for(int j = 0 ; j<=l; j++)
    {
        random[j]=j;
    }

    random_shuffle(random, random+l);
    for (int i = 0 ; i <k ; i++)
    {
         centroid[i].x = clust[random[i]].x;
         centroid[i].y = clust[random[i]].y;
         count[i]=0;
         NewCount[i]=0;

    }

    int lowest;
    bool no_change ;
    do
    {
        for(int n = 0 ; n < k; n++)
        {
             Newcentroid[n].x=centroid[n].x;
             Newcentroid[n].y=centroid[n].y;
             NewCount[n] = count[n];
             count[n]=0;
        }
        no_change = false;
        for(int i = 0; i<l;i++)
        {
            int X;
            int Y;
            int dist[l];
            lowest = 0;
            for(int t = 0 ; t < k; t++)
            {
                X=Y=0;
                X =(clust[i].x)-(centroid[t].x);
                Y =(clust[i].y)-(centroid[t].y);
                dist[t] = sqrt(pow(X,2)+ pow(Y,2));
                if(dist[t]<dist[lowest])
                {
                    lowest = t;
                }
            }

            int index = count[lowest];
            clusters[lowest].x[index]= clust[i].x;
            clusters[lowest].y[index]= clust[i].y;
            count[lowest]++;
            int temp1 =0;
            int temp2=0;
            for(int j =0 ; j <count[lowest]; j++)
            {
                temp1= (clusters[lowest].x[j] + temp1);
                temp2= (clusters[lowest].y[j] + temp2);
            }
            centroid[lowest].x=temp1/count[lowest];
            centroid[lowest].y=temp2/count[lowest];


        }

        for(int L = 0 ; L<k;L++)
        {
            if(count[L] != 0)
            {

                if( Newcentroid[L].x == centroid[L].x && Newcentroid[L].y == centroid[L].y && NewCount[L]==count[L])
                {
                    no_change=true;
                }

            }


        }

    }while(no_change == false);

    ofstream myfile("Output.txt");
    if (myfile.is_open())
    {
      for(int g = 0 ; g<k ;g++)
      {
        int index2 = count[g];
       for(int f = 0; f<index2;f++)
        {
           myfile <<clusters[g].x[f]<<setw(5)<<clusters[g].y[f]<<setw(5)<<g+1<<endl;

        }

      }
      myfile.close();

    }

}
