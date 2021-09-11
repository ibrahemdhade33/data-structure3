#include <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#define  strsize 100
#include <stdbool.h>
//define the struct for the graph
struct graph{
    int dis;
    char nameoftheroad [strsize];
};/*
 *
 *
 *
 *
 *
 *
 */
//define array of the graph struct
struct graph **adjarray;
int size=0;
/*
 *
 *
 *
 *
 *
 */
//define struct for stack
struct stack {
    char path[strsize];
    int dis;
    struct stack *next;

};
/*
 *
 *
 *
 *
 *
 */
//push function for stack
struct stack *push (struct stack *t,char path[strsize],int dis){

    struct stack *newnode=(struct stack *) malloc(sizeof (struct stack));
    strcpy(newnode->path,path);
newnode->dis=dis;
    if(t==NULL){
        newnode->next=NULL;
        t=newnode;
    }
    else {
        newnode->next=t;
        t=newnode;
    }
    return t;
}
/*
 *
 *
 *
 *
 *
 */
//print stack function to print the path
void printstack(struct stack *top,int dis,int s ) {
FILE *out = fopen("route.txt","a+");
    fprintf(out,"-----------------------------------------------------------------------------------------------\n");
    fprintf(out,"the path from the %d to %d is : \n",s,dis);
    struct stack *temp =top ;
    while (temp !=NULL){
        if(temp->next==NULL)
            fprintf(out," %d KM,,%s", temp->dis, temp->path);
        else{
            fprintf(out," %d KM,,%s ----> ", temp->dis, temp->path);
        }
            temp = temp->next;
    }
    fprintf(out,"\n-----------------------------------------------------------------------------------------------\n");
    fclose(out);
}
/*
 *
 *
 *
 *
 *
 *
 *
 *
 */
//function that find the path
void findthepath(int distination ,int parent[size],int source){

    struct stack *top =NULL;
    int p=distination;
    loop :   while(parent[distination]!=-1){
top = push(top,adjarray[parent[distination]][distination].nameoftheroad,adjarray[parent[distination]][distination].dis);
distination=parent[distination];
       goto loop;
    }
    printstack(top ,p,source);
}
/*
 *
 *
 *
 *
 *
 */
//find the min vertix of the distance array
int selectMinVertex(int distance[size],bool processed[size])
{
int minimum = INT_MAX;
int vertex;
for(int i=0;i<size;++i)
{
if(processed[i]==false && distance[i]<minimum)
{
vertex = i;
minimum = distance[i];
}
}
return vertex;
}
/*
 *
 *
 *
 *
 *
 */
//find the size of the graph by reading the file
int findsizeofdraph(){
    int max=0;
    char str[strsize]="",*token;
    FILE *fp= fopen("segments.txt", "r");
    if (fp == NULL) {
        printf("Could not open file segments.txt");
    }
    while (fgets(str,strsize,fp)!= NULL)
    {
        token = strtok(str, " ");
        int i= atoi(token);
        if(i>max)
            max=i;
        token = strtok(NULL, " ");
        int y = atoi(token);
        if(y>max)
            max=y;
    }
    return max;
}
/*
 *
 *
 *
 *
 */
//create the graph using the size from the file
void craetgraph (){
    size=findsizeofdraph()+1;
    adjarray=(struct graph **) malloc((size +1)* sizeof(struct graph *));
    for (int i = 0; i <=size ; ++i) {

        adjarray[i]= (struct graph*)malloc((size+1)   * sizeof(struct graph));
    }
    for (int i = 0; i <size ; ++i) {
        for (int j = 0; j < size; ++j) {
            adjarray[i][j].dis=0;
        }
    }
}
/*
 *
 *
 *
 *
 *
 *
 */
int *parent;
int distination =1;
/*
 *
 *
 *
 *
 *
 */
//dijkistra function that calculate the shortest path
void dijkstra(int source , int distination)
{
    parent=(int *) malloc(size *sizeof (int));
    int distance[size];
    bool processed[size];

    for (int i = 0; i < size; i++)
        distance[i] = INT_MAX, processed[i] = false,parent[i]=-1;

    distance[source] = 0;

    //Include (V-1) edges to cover all V-vertices
    for(int i=0;i<size-1;++i)
    {
        //Select best Vertex by applying greedy method
        int U = selectMinVertex(distance,processed);
        processed[U] = true;	//Include new Vertex in shortest Path Graph

        //Relax adjacent vertices (not yet included in shortest path graph)
        for(int j=0;j<size;++j)
        {
            if(adjarray[U][j].dis!=0 && processed[j]==false && distance[U]!=INT_MAX
               && (distance[U]+adjarray[U][j].dis < distance[j]))
            {
                distance[j] = distance[U]+adjarray[U][j].dis;
                parent[j] = U;
            }
        }
    }
    if(distance[distination]==INT_MAX)
        printf("there is no connection between source node and the destination node\n");
    else
    printf("the shortes path cost : %d KM\n",distance[distination]);
}
/*
 *
 *
 *
 *
 *
 */
//if you want to print the graph
void printgraph() {
    for (int i = 0; i < size; ++i) {
        printf(" from town %d to ----> ", i);
        for (int j = 0; j < size; ++j) {
            if (adjarray[i][j].dis!=0)
                printf(" %d ,, %d,name of the road  : %s ----> ", j, adjarray[i][j].dis,
                       adjarray[i][j].nameoftheroad);
        }
        printf("NULL \n");
    }
}
/*
 *
 *
 *
 *
 *
 */
//read the file and fill the graph
void readfile(){
    char str[strsize],*token;
    FILE *fp= fopen("segments.txt", "r");
    if (fp == NULL) {
        printf("Could not open file segments.txt");
    }
    while(fgets(str,strsize,fp)!=NULL){
        char r[10]="",c[10]="",dis[10]="";
        int r1=0,c1=0,dis1=0;
        char road[strsize]="";
        int count=0;
        int i=0;
        while (str[count]!=' '){
                r[i]=str[count];
                i++;
                count++;
            }
            count++;
            r1= atoi(r);
            i=0;
            while (str[count]!=' '){
                c[i]=str[count];
                i++;
                count++;
            }
            count++;
            i=0;
        c1= atoi(c);
        while (str[count] <'0' || str [count] > '9'){
            road[i]=str[count];
            i++;
            count++;
        }
        i=0;
        while(str[count]!= '\n' && str[count]!='\0'){
            dis[i]=str[count];
            i++;
            count++;
        }
        dis1= atoi(dis);
        adjarray[r1][c1].dis=dis1;
        adjarray[c1][r1].dis=dis1;
        strcpy(adjarray[r1][c1].nameoftheroad,road);
        strcpy(adjarray[c1][r1].nameoftheroad,road);
    }
}
/*
 *
 *
 *
 *
 *
 */
//the main function
int main() {
    int todo,flag=0,source=1;
    printf("-----------------------------------------------------------------------------\n");
    printf("please chose from the menu : \n"
           "1-Read the file segments.txt and load the data \n"
           "2-Enter 2 points to compute the shortest path between them\n"
           "3-Print the route of the shortest distance to a file called “route.txt”\n"
           "4-exit from the system\n");
    scanf("%d",&todo);
    while (todo!=4){
        switch (todo) {
            case 1:

                flag=1;
                craetgraph();
                readfile();
                //printgraph();
                printf("the file has been redden successfully (:(:\n");
                break;
            case 2 :
                printf(" please enter the source city : \n");
                scanf("%d",&source);
                printf("please enter the distination city : \n");
                scanf("%d",&distination);
                if(flag==0)
                    printf("please read the file first ):):):\n\n");
                else if(source <1 || source >size || distination <1 || distination >size )
                    printf("please enter a city between 1 and %d ):):):\n",size);
                    else {
                        dijkstra(source,distination);
                    }
                break;
            case 3:
                if(flag==0)
                    printf("please read the file first ):):):\n\n");
                else if(source <1 || source >size || distination <1 || distination >size )
                    printf("please enter a city between 1 and %d ):):):\n",size);
                    else {
                printf("the path is :  \n");
                findthepath(distination,parent,source);
                    printf("the road saved to file successfully (:(:(:\n");
                    }

                    break;

            default:
                printf("out of range ):):):\n");
                break;

        }
        printf("-----------------------------------------------------------------------------\n");
        printf("please chose from the menu : \n"
               "1-Read the file segments.txt and load the data \n"
               "2-Enter 2 points to compute the shortest path between them\n"
               "3-Print the route of the shortest distance to a file called “route.txt”\n"
               "4-exit from the system\n");
        scanf("%d",&todo);

    }
    if (todo==4)
    {
        printf("thanks for using our simple map.....bye bye (:(:(:\n");
        exit(5);
    }
    return 0;
}
/*
 IBRAHEM DUHAIDI 1190283
 DR.AHMAD ABU SNINA
 IT WAS A VERY INTERESTING COURSE WITH YOU DOCTOR, I HOPE TO SEE YOU IN ANOTHER COURSES,,WITH ALL MY RESPECT <3<3<3<3<3<3 (:(:
 */
