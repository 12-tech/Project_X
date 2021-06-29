#include <stdio.h>

int leftHistory = 0, rightHistory = 0;
int rightLock = 0, leftLock = 0;

int upHistory = 0, downHistory = 0;
int upLock = 0, downLock = 0;
int verticalLock = 0, horizontalLock = 0;


int moveOld(char* world)
{
    int TLocation = 0;
    int RLocation = 0;
    int horizontalTLocation;
    int verticalTLocation;
    int horizontalRLocation;
    int verticalRLocation;


    //get T location
    for (; world[TLocation] != 'T'; TLocation++) {}

    //get R location
    for (; world[RLocation] != 'R'; RLocation++) {}


    //calculate horizontal T position
    horizontalTLocation = TLocation % 21;
    //calculate vertical T distance
    verticalTLocation = (TLocation / 21) + 2;

    //calculate horizontal R position
    horizontalRLocation = RLocation % 21;
    //calculate vertical R distance
    verticalRLocation = (RLocation / 21) + 2;


    //find horizontal direction
    if ((horizontalRLocation - horizontalTLocation) > 0)
    {
        return 4;
    }
    if ((horizontalRLocation - horizontalTLocation) < 0)
    {
        return 2;
    }

    //find vertical direction
    if ((verticalRLocation - verticalTLocation) < 0)
    {
        return 3;
    }
    if ((verticalRLocation - verticalTLocation) > 0)
    {
        return 1;
    }
    
    return 0;
}

int move(char* world)//warning : (world[robot_index] = 'O') need to be changed;
{
    int TLocation = 0;
    int RLocation = 0;
    int horizontalTLocation;
    int verticalTLocation;
    int horizontalRLocation;
    int verticalRLocation;
    

    //get T location
    for (; world[TLocation] != 'T'; TLocation++) {}

    //get R location
    for (; world[RLocation] != 'R'; RLocation++) {}


    //calculate horizontal T position
    horizontalTLocation = TLocation % 21;
    //calculate vertical T distance
    verticalTLocation = (TLocation / 21) + 2;

    //calculate horizontal R position
    horizontalRLocation = RLocation % 21;
    //calculate vertical R distance
    verticalRLocation = (RLocation / 21) + 2;

    restart:

    //find vertical direction
    if (((verticalRLocation - verticalTLocation) > 0) && verticalLock == 0)//north
    {
        if ((world[RLocation - 21] == '#'|| world[RLocation - 21] == 'x' ))
        {
            //need to move down
            if ((world[RLocation - 1] == '#' || world[RLocation - 1] == 'x') && (world[RLocation + 1] == '#' || world[RLocation - 1] == 'x'))
            {
                world[RLocation] = 'x';//dummy wall
                //reset
                leftHistory = 0;
                rightHistory = 0;
                rightLock = 0;
                leftLock = 0;
                return 3;//south

            }
            //stuck at left coner
            if (world[RLocation - 1] == '#' && world[RLocation + 1] == 'O' && rightHistory == 0)
            {
                rightHistory = 1;//countinue moving to right for next step
                leftHistory = 0;
                world[RLocation] = 'x';//dummy wall
                leftLock = 1;// dont move to the left for the next step
                rightLock = 0;// only moving to right is 
            }
            //stuck at right coner
            if (world[RLocation + 1] == '#' && world[RLocation - 1] == 'O'&& leftHistory == 0)
            {
                leftHistory = 1;//countinue moving to left for next step
                rightHistory = 0;
                world[RLocation] = 'x';//dummy wall
                rightLock = 1;// dont move to the right for the next step
                leftLock = 0;// only moving to left is 
            }
            //move to left or right
            if (leftHistory == 0 && rightLock == 0)
            {
                rightHistory = 1;
                return 2;//east
            }
            if (rightHistory == 0 && leftLock == 0)
            {
                leftHistory = 1;
                return 4;
            }
        }
        leftHistory = rightHistory = 0;
        
    }
    else if ((verticalRLocation - verticalTLocation) < 0 && verticalLock == 0)//south
    {
        if ((world[RLocation + 21] == '#' || world[RLocation + 21] == 'x'))
        {
            //need to move up
            if ((world[RLocation - 1] == '#' || world[RLocation - 1] == 'x') && (world[RLocation + 1] == '#' || world[RLocation + 1] == 'x'))
            {
                world[RLocation] = 'x';//dummy wall
                //reset
                leftHistory = 0;
                rightHistory = 0;
                rightLock = 0;
                leftLock = 0;
                return 1;//north


            }
            //stuck at left coner
            if (world[RLocation - 1] == '#' && world[RLocation + 1] == 'O' && rightHistory == 0)
            {
                rightHistory = 1;//countinue moving to right for next step
                leftHistory = 0;
                world[RLocation] = 'x';//dummy wall
                leftLock = 1;// dont move to the left for the next step
                rightLock = 0;// only moving to right is 
            }
            //stuck at right coner
            if (world[RLocation + 1] == '#' && world[RLocation - 1] == 'O' && leftHistory == 0)
            {
                leftHistory = 1;//countinue moving to left for next step
                rightHistory = 0;
                world[RLocation] = 'x';//dummy wall
                rightLock = 1;// dont move to the right for the next step
                leftLock = 0;// only moving to left is 
            }
            //move to left or right
            if (leftHistory == 0 && rightLock == 0)
            {
                rightHistory = 1;
                return 2;//east

            }
            if (rightHistory == 0 && leftLock == 0)
            {
                leftHistory = 1;
                return 4;
            }
        }
        leftHistory = rightHistory = 0;
        return 3;//south
    }
    else if (verticalLock&&horizontalLock)
    {
        horizontalLock = 0;
    }
    else
    {
        verticalLock = 1;
        printf("lock");
    }
    
   
    
    //find horizontal direction
    if ((horizontalRLocation - horizontalTLocation) < 0&&horizontalLock==0)//east
    {
        if (world[RLocation + 1] == '#' || world[RLocation + 1] == 'x')
        {
            //need to move to west
            if ((world[RLocation - 21] == '#' || world[RLocation - 21] == 'x') && (world[RLocation + 21] == '#' || world[RLocation - 21] == 'x'))
            {
                world[RLocation] = 'x';//dummy wall
                //reset
                upHistory = 0;
                downHistory = 0;
                upLock = 0;
                downLock = 0;
                printf("need to move to west");
                return 2;//east
               

            }
            //notes are not updated after copy
            //stuck at upper coner
            if (world[RLocation - 21] == '#' && world[RLocation + 21] == 'O' && downHistory == 0)
            {
                downHistory = 1;//countinue moving to 
                upHistory = 0;
                world[RLocation] = 'x';//dummy wall
                upLock = 1;// dont move to the 
                downLock = 0;// only moving to 
                printf("stuck at upper right conner");
            }
            //stuck at lower coner
            if (world[RLocation + 21] == '#' && world[RLocation - 21] == 'O' && leftHistory == 0)
            {
                upHistory = 1;//countinue moving to 
                downHistory = 0;
                world[RLocation] = 'x';//dummy wall
                downLock = 1;// dont move to 
                upLock = 0;// only moving to 
                printf("stuck at down right conner");
            }
            //move to left or right
            if (upHistory == 0 && downLock == 0)
            {
                downHistory = 1;
                printf("move downward ");
                return 3;//south
            }
            if (downHistory == 0 && upLock == 0)
            {
                upHistory = 1;
                printf("move upward ");
                return 1;//north
            }
        }
        upHistory = downHistory = 0;
        printf("move east ");
        return 2;//east
    }
    else if ((horizontalRLocation - horizontalTLocation) > 0&&horizontalLock == 0)//west
    {
        if (world[RLocation - 1] == '#' || world[RLocation - 1] == 'x')
        {
            //need to move to west
            if ((world[RLocation - 21] == '#' || world[RLocation - 21] == 'x') && (world[RLocation + 21] == '#' || world[RLocation - 21] == 'x'))
            {
                world[RLocation] = 'x';//dummy wall
                //reset
                upHistory = 0;
                downHistory = 0;
                upLock = 0;
                downLock = 0;
                return 2;//east

            }
            //notes are not updated after copy
            //stuck at upper coner
            if (world[RLocation - 21] == '#' && world[RLocation + 21] == 'O' && downHistory == 0)
            {
                downHistory = 1;//countinue moving to 
                upHistory = 0;
                world[RLocation] = 'x';//dummy wall
                upLock = 1;// dont move to the 
                downLock = 0;// only moving to 
            }
            //stuck at lower coner
            if (world[RLocation + 21] == '#' && world[RLocation - 21] == 'O' && leftHistory == 0)
            {
                upHistory = 1;//countinue moving to 
                downHistory = 0;
                world[RLocation] = 'x';//dummy wall
                downLock = 1;// dont move to the 
                upLock = 0;// only moving to 
            }
            //
            if (upHistory == 0 && downLock == 0)
            {
                downHistory = 1;
                return 3;//south
            }
            if (downHistory == 0 && upLock == 0)
            {
                upHistory = 1;
                return 11;//north
            }
        }
        upHistory = downHistory = 0;
        return 4;//west
    }
    else
    {
        verticalLock = 0;
        horizontalLock = 1;
        goto restart;
    }

}



