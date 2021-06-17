#define up 0
#define down 1
#define left 2
#define right 3
#define visited 1
#define notVisited 0
static int queue[200];
static int parentNode[200];
static int visitedNode[200];
static int neighbour[] = {-21, 21,-1,1};
static int path[200];
static int returnPath[200];

static int TargetNode;
static int RobotNode;
static int target=1, found=0;
static int counter=1;
static int currentNode = 0 ;
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

void initialize();
void check();
void findReversePath ();
void findPath();
int ifToChange(char *world);
