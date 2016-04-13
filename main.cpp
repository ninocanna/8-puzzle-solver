#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<iostream>
using namespace std;

#define SIZE 3

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


struct Puzzle
{
    int A[SIZE][SIZE];
    int fa[SIZE][SIZE];
    int g,h;

    void input()
    {
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                scanf("%d",&A[i][j]);
            }
        }
    }

    void output()
    {
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                printf("%d ",A[i][j]);
            }
            printf("\n");
        }
    }

    friend bool operator< (Puzzle n1, Puzzle n2)
    {
        return n1.g+n1.h > n2.g+n2.h;
    }

} Initstate;

queue<Puzzle> Q;
priority_queue<Puzzle> PQ;

int lenOfQueue =0;

bool judgeComplete(Puzzle candidate)
{
    if(
        candidate.A[0][0] == 1 &&candidate.A[0][1] == 2 &&candidate.A[0][2] == 3 &&
        candidate.A[1][0] == 4 &&candidate.A[1][1] == 5 &&candidate.A[1][2] == 6 &&
        candidate.A[2][0] == 7 &&candidate.A[2][1] == 8 &&candidate.A[2][2] == 0)
    {
        return true;
    }
    else return false;
}

bool tranform(int direction,Puzzle &puzzle)
{
    int row,col;
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            if(puzzle.A[i][j]==0)
            {
                row=i;
                col=j;
                break;
            }
        }
    }


    if(direction == LEFT)
    {
        if(col-1>=0)
        {
            swap(puzzle.A[row][col],puzzle.A[row][col-1]);
            return true;
        }
        else return false;
    }
    if(direction == RIGHT)
    {
        if(col+1<SIZE)
        {
            swap(puzzle.A[row][col],puzzle.A[row][col+1]);
            return true;
        }
        else return false;
    }
    if(direction == UP)
    {
        if(row-1>=0)
        {
            swap(puzzle.A[row][col],puzzle.A[row-1][col]);
            return true;
        }
        else return false;
    }
    if(direction == DOWN)
    {
        if(row+1<SIZE)
        {
            swap(puzzle.A[row][col],puzzle.A[row+1][col]);
            return true;
        }
        else return false;
    }
}

bool judgeSame(Puzzle a,Puzzle b)
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            if(a.A[i][j]!=b.fa[i][j])return false;
        }
    }

    return true;
}

void giveFatherValue(Puzzle &puzzle, Puzzle father)
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            puzzle.fa[i][j] = father.A[i][j];
        }
    }
}

void outputExpanding(Puzzle puzzle)
{
    printf("The best state to expand is ...:\n");
    puzzle.output();
    printf("Expanding this node..\n");

}


void UniformCostSearch()
{
    int stateNum=0;
    while(!Q.empty())Q.pop();

    Q.push(Initstate);

    printf("Expanding state:\n");
    Initstate.output();

    while(!Q.empty())
    {
        stateNum++;
        Puzzle queueFront = Q.front();
        Q.pop();
        outputExpanding(queueFront);
        //getchar();
        if(judgeComplete(queueFront))
        {
            break;
        }
        else
        {
            Puzzle tPuzzle = queueFront;
            if(tranform(LEFT,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                giveFatherValue(tPuzzle,queueFront);
                Q.push(tPuzzle);
            }
            tPuzzle = queueFront;
            if(tranform(RIGHT,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                giveFatherValue(tPuzzle,queueFront);
                Q.push(tPuzzle);
            }
            tPuzzle = queueFront;
            if(tranform(UP,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                giveFatherValue(tPuzzle,queueFront);
                Q.push(tPuzzle);
            }
            tPuzzle = queueFront;
            if(tranform(DOWN,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                giveFatherValue(tPuzzle,queueFront);
                Q.push(tPuzzle);
            }
        }
    }
    printf("%d\n",stateNum);

}

int getMisplacedNum(Puzzle p)
{
    int cnt=0;
    if(p.A[0][0]!=1)cnt++;
    if(p.A[0][1]!=2)cnt++;
    if(p.A[0][2]!=3)cnt++;
    if(p.A[1][0]!=4)cnt++;
    if(p.A[1][1]!=5)cnt++;
    if(p.A[1][2]!=6)cnt++;
    if(p.A[2][0]!=7)cnt++;
    if(p.A[2][1]!=8)cnt++;
    return cnt;
}


void AwithTheMisplacedTileHeuristic()
{

    int stateNum = 0;
    while(!PQ.empty())PQ.pop();

    Initstate.g=0;
    Initstate.h=getMisplacedNum(Initstate);

    PQ.push(Initstate);

    printf("Expanding state:\n");
    Initstate.output();


    while (!PQ.empty())
    {
        if(PQ.size()>lenOfQueue){
            lenOfQueue = PQ.size();
        }


        Puzzle queueFront = PQ.top();
        PQ.pop();

        printf("g(n)=%d  " ,queueFront.g);
        printf("h(n)=%d  ",queueFront.h);
        outputExpanding(queueFront);

        if(judgeComplete(queueFront))
        {
            break;
        }
        else
        {
            Puzzle tPuzzle = queueFront;
            if(tranform(LEFT,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getMisplacedNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
            tPuzzle = queueFront;
            if(tranform(RIGHT,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getMisplacedNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
            tPuzzle = queueFront;
            if(tranform(UP,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getMisplacedNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
            tPuzzle = queueFront;
            if(tranform(DOWN,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getMisplacedNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
        }
    }
    printf("%d\n",stateNum);


}




int getManhattanDistanceNum(Puzzle p)
{
    int distance = 0;
    int i, j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)  // iterate over all tiles
        {
            if(p.A[i][j]==0)continue;

            int x = (p.A[i][j]-1)/SIZE;
            int y = (p.A[i][j]-1)%SIZE;
            distance += (abs(i-x)+abs(j-y));
        }
    }

    return distance;
}






void AwithTheManhattanDistanceHeuristic()
{

    int stateNum = 0;
    while(!PQ.empty())PQ.pop();

    Initstate.g=0;
    Initstate.h=getManhattanDistanceNum(Initstate);

    PQ.push(Initstate);

    printf("Expanding state:\n");
    Initstate.output();


    while (!PQ.empty())
    {
        if(PQ.size()>lenOfQueue){
            lenOfQueue = PQ.size();
        }

        stateNum++;
        Puzzle queueFront = PQ.top();
        PQ.pop();

        printf("g(n)=%d  " ,queueFront.g);
        printf("h(n)=%d  ",queueFront.h);
        outputExpanding(queueFront);

        if(judgeComplete(queueFront))
        {
            break;
        }
        else
        {
            Puzzle tPuzzle = queueFront;
            if(tranform(LEFT,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getManhattanDistanceNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
            tPuzzle = queueFront;
            if(tranform(RIGHT,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getManhattanDistanceNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
            tPuzzle = queueFront;
            if(tranform(UP,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getManhattanDistanceNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
            tPuzzle = queueFront;
            if(tranform(DOWN,tPuzzle)&&!judgeSame(tPuzzle,queueFront))
            {
                tPuzzle.g = queueFront.g+1;
                tPuzzle.h = getManhattanDistanceNum(tPuzzle);
                giveFatherValue(tPuzzle,queueFront);
                PQ.push(tPuzzle);
                stateNum++;
            }
        }
    }
    printf("%d\n",stateNum);


}



bool isValidPuzzle()
{

    int a[SIZE*SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            a[i * SIZE + j] = Initstate.A[i][j];
        }
    }


    int nCount = 0;
    int i, j;
    for(i=0; i<SIZE*SIZE; i++)
        for(j=i+1; j<SIZE*SIZE; j++)
            if (a[i]!=0&&a[j]!=0&&a[i]>a[j])
                nCount++;

    if(nCount&1)
    {
        printf("Invalid puzzle!\n");
        return false;
    }
    else return true;
}

void welcome()
{
    printf("Please enter the initial state:\n");
    Initstate.input();
    Initstate.output();

    if(!isValidPuzzle())return;

    printf("Please enter your choice:\n");
    printf("1.Uniform:\n");
    printf("2.A*MisplaceTileHeuristic:\n");
    printf("3.A*ManhattanDistanceHeuristic:\n");
    int choice;

    lenOfQueue = 0;

    scanf("%d",&choice);
    if(choice==1)
    {
        UniformCostSearch();
    }
    else if(choice==2)
    {
        AwithTheMisplacedTileHeuristic();
    }
    else
    {
        AwithTheManhattanDistanceHeuristic();
    }
    printf("Max length of queue is %d\n",lenOfQueue);
    printf("Goal!!!!!\n");

}

int main()
{
    welcome();
}
