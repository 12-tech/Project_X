#include <stdio.h>
#include "robohood.h"

void Avoid(int avoidLocation)
{
    avoid[counter] = avoidLocation; //mark location that surrounded by obstacle
    counter++;
}

int AvoidLocationChecker(int location)
{
    for (int count = 0; avoid[count] != '\0'; count++)
    {
        if (location == avoid[count])
        {
            return 1;//(cannot go to the location)
        }
    }
    return 0;
}

int  ifToChange(char nextSurface)
{
    
    if (nextSurface == '~'&& onLand == 1 )//change to move on water mood
    {
        onLand = 0;
        onWater = 1;
        return CHANGE;
    }
    if (nextSurface == 'O' && onWater == 1 )//change to move on land mood
    {
        onLand = 1;
        onWater = 0;
        return CHANGE;
    }
    return 0;//no change
}

int move(char* world)
{

    int TLocation = 0;
    int RLocation = 0;
    int horizontalTLocation;
    int verticalTLocation;
    int horizontalRLocation;
    int verticalRLocation;
    //get T and R location
    for (; world[TLocation] != 'T'; TLocation++) {}
    for (; world[RLocation] != 'R'; RLocation++) {}

    //calculate horizontal and vertical T position
    horizontalTLocation = TLocation % 21;
    verticalTLocation = (TLocation / 21) + 2;

    //calculate horizontal and vertical R position
    horizontalRLocation = RLocation % 21;
    verticalRLocation = (RLocation / 21) + 2;

    //find vertical direction
    //north direction
    start: 
    if (((verticalRLocation - verticalTLocation) > 0) && vLock == 0)//north
    {
        printf("north\n");
        if (world[RLocation - 21] == '#' || AvoidLocationChecker(RLocation - 21))//if there is obstacle infront
        {
            //need to move down
            if ((world[RLocation - 1] == '#' || AvoidLocationChecker(RLocation - 1)) && (world[RLocation + 1] == '#' || AvoidLocationChecker(RLocation + 1)))
            {
                Avoid(RLocation);//mark the location as avoid location
                //reset
                moveLeft = 0;
                moveRight = 0;
                //check for method change
                if (ifToChange(world[RLocation + 21]))
                {
                    return 5;
                }
                printf(" down\n");
                return south;

            }
            //stuck at left coner
            else if ((world[RLocation - 1] == '#' || AvoidLocationChecker(RLocation - 1)) && (world[RLocation + 1] == 'O'|| world[RLocation + 1] == '~'))
            {
                moveRight = 1;//countinue moving to right for next step
                moveLeft = 0;
                Avoid(RLocation);//mark the location as avoid location
            }
            //stuck at right coner
            else if ((world[RLocation + 1] == '#' || AvoidLocationChecker(RLocation + 1)) && (world[RLocation - 1] == 'O'|| world[RLocation - 1] == '~'))
            {
                moveLeft = 1;//countinue moving to left for next step
                moveRight = 0;
                Avoid(RLocation);//mark location as void location
            }
            //move left option
            else if (world[RLocation - 1] != '#' || AvoidLocationChecker(RLocation - 1) != 1) 
            {
                moveLeft = 1;
            }
            //move right option
            else if (world[RLocation + 1] != '#' || AvoidLocationChecker(RLocation + 1) != 1) 
            {
                moveRight = 1;
            }

            //action(left or right)
            if (moveRight == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation + 1]))
                {
                    return 5;
                }
                printf(" right\n");
                return east;
            }
            else if (moveLeft == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation - 1]))
                {
                    return 5;
                }
                printf(" left\n");
                return west;
            }
        }
        //default when there is no obstacle
        hLock = 0;
        moveLeft = 0;
        moveRight = 0;
        //check for method change
        if (ifToChange(world[RLocation - 21]))
        {
            return 5;
        }
        printf(" up\n");
        return north;
    }

    //moving south
    else if ((verticalRLocation - verticalTLocation) < 0 && vLock == 0)//south
    {
        printf("south\n");
        if (world[RLocation + 21] == '#' || AvoidLocationChecker(RLocation + 21))//if there is obstacle at bottom
        {

            //need to move up
            if ((world[RLocation + 1] == '#' || AvoidLocationChecker(RLocation + 1)) && (world[RLocation - 1] == '#' || AvoidLocationChecker(RLocation - 1)))
            {
                Avoid(RLocation);//mark location as void location
                //reset
                moveLeft = 0;
                moveRight = 0;
                //check for method change
                if (ifToChange(world[RLocation - 21]))
                {
                    return 5;
                }
                return north;

            }
            //stuck at left coner
            else if ((world[RLocation + 1] == '#' || AvoidLocationChecker(RLocation + 1)) && (world[RLocation - 1] == 'O' || world[RLocation - 1] == '~'))
            {
                moveRight = 0;//countinue moving to right for next step
                moveLeft = 1;
                Avoid(RLocation);//mark location as void location
            }
            //stuck at right coner
            else if ((world[RLocation - 1] == '#' || AvoidLocationChecker(RLocation - 1)) && (world[RLocation + 1] == 'O' || world[RLocation + 1] == '~'))
            {
                moveLeft = 0;//countinue moving to left for next step
                moveRight = 1;
                Avoid(RLocation);//mark location as void location
            }
            //move right option
            else if (world[RLocation + 1] != '#' || AvoidLocationChecker(RLocation + 1) != 1) 
            {
                moveRight = 1;
            }
            //move left option
            else if (world[RLocation - 1] != '#' || AvoidLocationChecker(RLocation - 1) != 1) 
            {
                moveLeft = 1;
            }

            //action
            if (moveRight == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation + 1]))
                {
                    return 5;
                }
                return east;

            }
            else if (moveLeft == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation - 1]))
                {
                    return 5;
                }
                return west;
            }
        }
        //default when there is no obstacle
        moveLeft = 0;
        moveRight = 0;
        hLock = 0;
        //check for method change
        if (ifToChange(world[RLocation +21]))
        {
            return 5;
        }
        return south;
    }
    //temporary lock for vertical movement algorithm
    else
    {
        vLock = 1;
    }


    //find horizontal direction
    //move to right
    if ((horizontalRLocation - horizontalTLocation) < 0 && hLock == 0)//east
    {
        printf("east\n");
        if (world[RLocation + 1] == '#' || AvoidLocationChecker(RLocation + 1))//if there is obstacle on right
        {
            //need to move left
            if ((world[RLocation - 21] == '#' || AvoidLocationChecker(RLocation - 21)) && (world[RLocation + 21] == '#' || AvoidLocationChecker(RLocation + 21)))
            {
                Avoid(RLocation);//mark location as void location
                //reset
                moveUp = 0;
                moveDown = 0;
                //check for method change
                if (ifToChange(world[RLocation - 1 ]))
                {
                    return 5;
                }
                return west;

            }
            //stuck at upper right conner
            else if ((world[RLocation - 21] == '#' || AvoidLocationChecker(RLocation - 21)) && (world[RLocation +21] == 'O' || world[RLocation +21] == '~'))
            {
                moveDown = 1;//countinue moving down for next step
                moveUp = 0;
                Avoid(RLocation);//mark location as void location
            }
            //stuck at lower right coner
            else if ((world[RLocation + 21] == '#' || AvoidLocationChecker(RLocation + 21)) && (world[RLocation - 21] == 'O' || world[RLocation - 21] == '~'))
            {
                moveUp = 1;//countinue moving up for next step
                moveDown = 0;
                Avoid(RLocation);//mark location as void location
            }
            //move up option
            else if (world[RLocation + 21] != '#' || AvoidLocationChecker(RLocation + 21) != 1)
            {
                moveUp = 1;
            }
            //move down option
            else if (world[RLocation - 21] != '#' || AvoidLocationChecker(RLocation - 21) != 1)
            {
                moveDown = 1;
            }

            //action
            if (moveDown == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation + 21]))
                {
                    return 5;
                }
                return south;
            }
            else if (moveUp == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation - 21]))
                {
                    return 5;
                }
                return north;
            }
        }
        //default when there is no obstacle
        moveUp = 0;
        moveDown = 0;
        vLock = 0;
        //check for method change
        if (ifToChange(world[RLocation + 1]))
        {
            return 5;
        }
        return east;
    }
    //move to left
    else if ((horizontalRLocation - horizontalTLocation) > 0 && hLock == 0)//west
    {
        printf("west\n");
        if (world[RLocation - 1] == '#' || AvoidLocationChecker(RLocation - 1))//if there is obstacle on left
        {
            //need to move right
            if ((world[RLocation - 21] == '#' || AvoidLocationChecker(RLocation - 21)) && (world[RLocation + 21] == '#' || AvoidLocationChecker(RLocation + 21)))
            {
                Avoid(RLocation);//mark location as void location
                //reset
                moveUp = 0;
                moveDown = 0;
                //check for method change
                if (ifToChange(world[RLocation + 1]))
                {
                    return 5;
                }
                return east;

            }
            //stuck at upper left conner
            else if ((world[RLocation - 21] == '#' || AvoidLocationChecker(RLocation - 21)) && (world[RLocation + 21] == 'O' || world[RLocation + 21] == '~'))
            {
                moveDown = 1;//countinue moving down for next step
                moveUp = 0;
                Avoid(RLocation);//mark location as void location
            }
            //stuck at lower left coner
            else if ((world[RLocation + 21] == '#' || AvoidLocationChecker(RLocation + 21)) && (world[RLocation - 21] == 'O' || world[RLocation - 21] == '~'))
            {
                moveUp = 1;//countinue moving up for next step
                moveDown = 0;
                Avoid(RLocation);//mark location as void location
            }
            //move down option
            else if (world[RLocation + 21] != '#' || AvoidLocationChecker(RLocation + 21) != 1)
            {
                moveDown = 1;
            }
            //move up option
            else if (world[RLocation - 21] != '#' || AvoidLocationChecker(RLocation - 21) != 1)
            {
                moveUp = 1;
            }
            if (moveDown == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation + 21]))
                {
                    return 5;
                }
                return south;
            }
            else if (moveUp == 1)
            {
                //check for method change
                if (ifToChange(world[RLocation - 21]))
                {
                    return 5;
                }
                return north;
            }
        }
        //default when there is no obstacle
        moveUp = 0;
        moveDown = 0;
        vLock = 0;
        //check for method change
        if (ifToChange(world[RLocation - 1]))
        {
            return 5;
        }
        return west;
    }
    //temporary lock for horizontal move algorithm
    else
    {
        hLock = 1;
    }

    //if deadlock occur
    if (vLock == 1 && hLock == 1 )
    {
        printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        vLock = 0;
        hLock = 0;
        moveLeft = 0;
        moveRight = 0;
        moveUp = 0;
        moveDown = 0;
        goto start;
    }
}