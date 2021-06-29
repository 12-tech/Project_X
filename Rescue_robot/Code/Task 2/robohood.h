#define north 1
#define south 3
#define east 2
#define west 4 
#define CHANGE 1
#define change 5


static int moveLeft = 0, moveRight = 0;
static int moveUp = 0, moveDown = 0;

static vLock = 0, hLock = 0;

static onWater = 0, onLand = 1;//the robot start on land

static int avoid[200];
static int counter = 0;

void Avoid(int avoidLocation);
int AvoidLocationChecker(int location);
int move(char* world);
int  ifToChange(char nextSurface);





