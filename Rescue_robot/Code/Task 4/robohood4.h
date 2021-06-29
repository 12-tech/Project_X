#define up 0
#define down 1
#define left 2
#define right 3
#define visited 1
#define notVisited 0

#define north 21
#define east -1
#define south -21
#define west 1

#define land 0
#define water 1

#define moveNorth 1
#define moveEast 2
#define moveSouth 3
#define moveWest 4

#define changeMethod 5

#define destroyNorth 6
#define destroyEast 7
#define destroySouth 8
#define destroyWest 9

static int queue[200];
static int parentNode[200];
static int visitedNode[200];
static int neighbour[] = { -21, 21,-1,1 };
static int path[200];
static int returnPath[200];

static int TargetNode;
static int RobotNode;
static int target = 1, found = 0;
static int counter = 1;
static int currentNode = 0;
static int indexQ = 0;
static int Path = 0;
static int goTarget = 0;
static int goInitial = 0;

static int currentPosition = 0;
static int nextPosition = 0;
static int next = 1;
static int current = 0;
static int direction = 0;

static int currentSurface = 0;//land 1= water

static int map = 0;


void initialize();
void check();
void findReversePath();
void findPath();
int ifObstacle(char obstacle);
int move(char* world, int map_id);
