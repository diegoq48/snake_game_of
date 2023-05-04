#include "Snake.h"
#include "ofMain.h"

Snake::Snake(int segmentSize, int boardSizeW, int boardSizeH)
{
    body.push_back({8, 9});
    body.push_back({9, 9});
    body.push_back({10, 9});
    body.push_back({11, 9});
    this->speed = 1;
    this->score = 0;
    this->goal = 200;
    this->direction = LEFT;
    this->crashed = false;
    this->segmentSize = segmentSize;
    this->boardSizeWidth = boardSizeW;
    this->boardSizeHeight = boardSizeH;
}

Snake::~Snake()
{
    // TODO Auto-generated destructor stub
}

void Snake::update() {
    if (this->isGod) {
        // skip update if snake is in god mode and hits the wall
        if ((this->direction == LEFT && this->body[0][0] == 0) ||
            (this->direction == DOWN && this->body[0][1] == boardSizeHeight - 1) ||
            (this->direction == RIGHT && this->body[0][0] == boardSizeWidth - 1) ||
            (this->direction == UP && this->body[0][1] == 0)) {
            return;
        }
    }
    else {
        // check for wall collision
        vector<int> oldHead = this->getHead();
        if (oldHead[0] == -1 || oldHead[0] == boardSizeWidth || oldHead[1] == -1 || oldHead[1] == boardSizeHeight) {
            crashed = true;
            return;
        }

        // update body position
        vector<int> prevPos = this->body[0];
        this->body[0][0] += this->direction == LEFT ? -speed : this->direction == RIGHT ? speed : 0;
        this->body[0][1] += this->direction == UP ? -speed : this->direction == DOWN ? speed : 0;
        for (int i = 1; i < this->body.size(); i++) {
            vector<int> temp = this->body[i];
            this->body[i][0] = prevPos[0];
            this->body[i][1] = prevPos[1];
            prevPos = temp;
        }
    }

    // check for self-crash
    checkSelfCrash();
}

void Snake::draw()
{
    for (int i = 0; i < body.size(); i++)
    {
        int curX = this->body[i][0];
        int curY = this->body[i][1];
        ofSetColor(146, 159, 164);
        // draw the head red and the tail green
        if (i == 0)
            ofSetColor(154, 259, 131);
        if (i == body.size() - 1)
            ofSetColor(171, 232, 252);
        ofDrawRectangle(curX * segmentSize, curY * segmentSize, segmentSize, segmentSize);
    }
}

void Snake::changeDirection(Direction d)
{

    if (this->direction == LEFT and d == RIGHT)
        return;
    if (this->direction == RIGHT and d == LEFT)
        return;
    if (this->direction == UP and d == DOWN)
        return;
    if (this->direction == DOWN and d == UP)
        return;

    this->direction = d;
}

void Snake::checkSelfCrash()
{
    std::vector<std::vector<int>> snake = this->body;
    vector<int> head = snake[0];
    for (int i = 1; i < snake.size(); i++)
    {
        if (head[0] == snake[i][0] and head[1] == snake[i][1])
        {
            crashed = true;
            return;
        }
    }
}

void Snake::grow()
{
    vector<int> newSegment = this->getTail();
    this->body.push_back(newSegment);
}

void Snake::removeSection(int numOfSections, int recursionDepth)
{
    if (recursionDepth == numOfSections)
    {
        return;
    }
    else
    {
        this->body.pop_back();
        removeSection(numOfSections, recursionDepth + 1);
    }
}