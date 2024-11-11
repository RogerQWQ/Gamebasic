#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase header
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;
GamesEngineeringBase::Window canvas;
int score= 0;
const int TILE_SIZE = 32;  // Each tile is 32x32 pixels
const int SCREEN_WIDTH = 1024;  
const int SCREEN_HEIGHT = 768;  
const int MAP_WIDTH = 42;  // Width of the map in tiles
const int MAP_HEIGHT = 42; // Height of the map in tiles

enum GameState {
    MENU,
    MAP1,
    MAP2,
    PAUSE,
    EXIT
};
class UI {
private:
    float x, y;
    GamesEngineeringBase::Image sprite;
    GamesEngineeringBase::Image heart;
    GamesEngineeringBase::Image skillui;
    GamesEngineeringBase::Image pauseui;

public:
    UI(float _x, float _y){

        sprite.load("Resources/menu.png");
        heart.load("Resources/heart.png");
        skillui.load("Resources/skillui.png");
        pauseui.load("Resources/pause.png");
        x = _x;
        y = _y;
    }
    void draw(GamesEngineeringBase::Window& canvas) {
        int drawX = x - sprite.width  ;  // 
        int drawY = y - sprite.height  ;
        for (unsigned int i = 0; i < sprite.height; i++) {
            if (drawY + i < canvas.getHeight() && drawY + i >= 0) {
                for (unsigned int n = 0; n < sprite.width; n++) {
                    if (drawX + n < canvas.getWidth() && drawX + n >= 0) {
                        if (sprite.alphaAt(n, i) > 200)
                            canvas.draw(drawX + n, drawY + i, sprite.at(n, i));
                    }
                }
            }
        }

    }
    void drawpause(GamesEngineeringBase::Window& canvas) {
        int drawX = x - pauseui.width;  // 
        int drawY = y - pauseui.height;
        for (unsigned int i = 0; i < pauseui.height; i++) {
            if (drawY + i < canvas.getHeight() && drawY + i >= 0) {
                for (unsigned int n = 0; n < pauseui.width; n++) {
                    if (drawX + n < canvas.getWidth() && drawX + n >= 0) {
                        if (pauseui.alphaAt(n, i) > 200)
                            canvas.draw(drawX + n, drawY + i, pauseui.at(n, i));
                    }
                }
            }
        }

    }
    void drawskillui(GamesEngineeringBase::Window& canvas) {
        int drawX = x - skillui.width;  // 
        int drawY = y - skillui.height;
        for (unsigned int i = 0; i < skillui.height; i++) {
            if (drawY + i < canvas.getHeight() && drawY + i >= 0) {
                for (unsigned int n = 0; n < skillui.width; n++) {
                    if (drawX + n < canvas.getWidth() && drawX + n >= 0) {
                        if (skillui.alphaAt(n, i) > 200)
                            canvas.draw(drawX + n, drawY + i, skillui.at(n, i));
                    }
                }
            }
        }

    }

    void drawheart(GamesEngineeringBase::Window& canvas,float x,float y) {
        int drawX = x - heart.width;
        int drawY = y - heart.height;
        for (unsigned int i = 0; i < heart.height; i++) {
            if (drawY + i < canvas.getHeight() && drawY + i >= 0) {
                for (unsigned int n = 0; n < heart.width; n++) {
                    if (drawX + n < canvas.getWidth() && drawX + n >= 0) {
                        if (heart.alphaAt(n, i) > 200)
                            canvas.draw(drawX + n, drawY + i, heart.at(n, i));
                    }
                }
            }
        }

    }
    
};


class xiaoguaibullet {
protected:
    float x, y;
    float dirX, dirY; 
    float speed;
    GamesEngineeringBase::Image sprite;
    int active = 0;
public:
    xiaoguaibullet(int _x, int _y, string filename, int targetX, int targetY) {
        sprite.load(filename);
        x = _x;
        y = _y;

        // Calculate the direction towards the target position (hero)
        float dx = targetX - x;
        float dy = targetY - y;
        float distance = sqrtf(dx * dx + dy * dy);

        // Normalize the direction vector
        dirX = dx / distance;
        dirY = dy / distance;

       
        speed = 500.0f;// Set the speed of the projectile
    }

    void draw(GamesEngineeringBase::Window& canvas, int drawX, int drawY) {
        int startX = drawX - sprite.width / 2;
        int startY = drawY - sprite.height / 2;
        for (unsigned int i = 0; i < sprite.height; i++) {
            if (startY + i < canvas.getHeight() && startY + i >= 0) {
                for (unsigned int n = 0; n < sprite.width; n++) {
                    if (startX + n < canvas.getWidth() && startX + n >= 0) {
                        if (sprite.alphaAt(n, i) > 200)
                            canvas.draw(startX + n, startY + i, sprite.at(n, i));
                    }
                }
            }
        }

    }
    void update(float dt) {
        x += dirX * speed * dt;
        y += dirY * speed * dt;
    }

    float getY() {
        return y;
    }
    float getX() {
        return x;
    }
    unsigned int getWidth() const {
        return sprite.width;
    }

    unsigned int getHeight() const {
        return sprite.height;
    }

    int updateactive() {
        active = 1;

        return active;
    }
    int getact() {
        return active;
    }
};
class plane {
protected:
    float x, y;
    GamesEngineeringBase::Image sprite;
    int health = 1;
    int type = 1;
    float speed = 100.0;
    int paotai = 0;
    int skin = 0;
public:
    plane(int _x, int _y, string filename) {
        sprite.load(filename);
        x = _x;
        y = _y;
    }

    void draw(GamesEngineeringBase::Window& canvas, int drawX, int drawY) {
        int startX = drawX - sprite.width / 2;
        int startY = drawY - sprite.height / 2;
        for (unsigned int i = 0; i < sprite.height; i++) {
            if (startY + i < canvas.getHeight() && startY + i >= 0) {
                for (unsigned int n = 0; n < sprite.width; n++) {
                    if (startX + n < canvas.getWidth() && startX + n >= 0) {
                        if (sprite.alphaAt(n, i) > 200)
                            canvas.draw(startX + n, startY + i, sprite.at(n, i));
                    }
                }
            }
        }
        
    }

    void update(float _x, float _y) {
        x += _x;
        y += _y;
    }

    

    float getY()  {
        return y;
    }
    float getX()  {
        return x;
    }
    float getdistance(float posx,float posy) {
        int enemyX = getX();
        int enemyY = getY();


        float dx = posx - enemyX;
        float dy = posy - enemyY;
        float distance = sqrtf(dx * dx + dy * dy);
        return distance;
    }
    unsigned int getWidth() const {
        return sprite.width;
    }

    unsigned int getHeight() const {
        return sprite.height;
    }

    int gethealth() {
        return health;
    }
    int hit() {
        health = health - 1;
        return health;
    }

    int sethealth(int x) {
        health = x;
        return health;
    }
    float getspeed() {
        return speed;

    }

    float setspeed(float x) {
        speed = x;
        return speed;
    }

    int getpaotai() {
        return paotai;
    }

    int setpaotai() {
        paotai = 1;
        return paotai;
    }
    int getskin() {
        return skin;
    }
    int setskin(int skinnumber) {
        skin = skinnumber;
        return skin;
    }


   

   

};

class PowerUp {
private:
    float x, y;  // Power-up position
    GamesEngineeringBase::Image sprite;  // Power-up image
    bool isActive;  // Powerup active or not
    int type;

public:
    PowerUp(float _x, float _y) {
        x = _x;
        y = _y;
        sprite.load("Resources/powerup.png");
        isActive = true;  
        
    }


    void update(int posx, int posy) {
        if (isActive) {
            // Check if the hero picks up the power-up
            int dx = posx - x;
            int dy = posy - y;
            float distance = sqrtf(dx * dx + dy * dy);

            
            if (distance < 50) {
                isActive = false;  
                cout << "touch" << endl;
                
            }
        }
    }

    
    void draw(GamesEngineeringBase::Window& canvas, int offsetX, int offsetY) {
        int drawX = x - sprite.width / 2 - offsetX;  // 
        int drawY = y - sprite.height / 2- offsetY;
        for (unsigned int i = 0; i < sprite.height; i++) {
            if (drawY + i < canvas.getHeight() && drawY + i >= 0) {
                for (unsigned int n = 0; n < sprite.width; n++) {
                    if (drawX + n < canvas.getWidth() && drawX + n >= 0) {
                        if (sprite.alphaAt(n, i) > 200)
                            canvas.draw(drawX + n, drawY + i, sprite.at(n, i));
                    }
                }
            }
        }

    }

    void applyEffect() {
        
        cout << "timeThreshold = 0.5" << endl;
    }

    
    float getX() {
        return x;
    }

    float getY() {
        return y;
    }

    
    int getType() {
        return type;
    }

    bool getactive() {
        return isActive;
    }
   
};




// Tile class definition
class Tile {
    GamesEngineeringBase::Image sprite;
    bool passable;  // Indicates whether the tile can be traversed
public:
    Tile() : passable(true) {}

    // Load the tile sprite and set whether it is passable
    bool load(const string& filename, bool isPassable) {
        if (sprite.load(filename)) {
            passable = isPassable;
            return true;
        }
        else {
            cout << "Failed to load: " << filename << endl;
            return false;
        }
    }

    void draw(GamesEngineeringBase::Window& canvas, int x, int y) {
        for (unsigned int i = 0; i < sprite.height; i++) {
            for (unsigned int n = 0; n < sprite.width; n++) {
                if ((x + n) >= 0 && (x + n) < canvas.getWidth() &&
                    (y + i) >= 0 && (y + i) < canvas.getHeight()) {
                    canvas.draw(x + n, y + i, sprite.atUnchecked(n, i));
                }
            }
        }
    }

    // Get whether the tile is passable
    bool isPassable() const { 
        return passable; 
    }
};


class Map {
    int tileMap[MAP_HEIGHT*10][MAP_WIDTH*10];  // The grid map representing the tiles
    Tile tiles[24];  // Array to hold all tile types
    int currentMapWidth = MAP_WIDTH;
    int currentMapHeight = MAP_HEIGHT;
    float timeSinceLastAdd = 0.0f;
    
public:
    Map() {
        for (int i = 0; i < 24; ++i) {
            string filename = "Resources/" + to_string(i) + ".png";
            // Set water tiles (IDs 14-22) as impassable
            bool isPassable = (i < 14 || i > 22); //set tiles from number 14 to 22 isnotpassible
            tiles[i].load(filename, isPassable);
        }

        
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                tileMap[y][x] = 0;  
            }
        }
    }

    void loadMap(const string& filename) {
        ifstream infile(filename);
        if (infile.is_open()) {
            string line;

            for (int i = 0; i < 6; ++i) {
                getline(infile, line);
                cout << "Skipping line: " << line << endl;  
            }

            
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                if (!getline(infile, line)) {
                    cout << "Error reading line for row " << y << endl;
                    return;
                }

               
                istringstream lineStream(line);
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    lineStream >> tileMap[y][x];

                    if (lineStream.fail()) {
                        cout << "Error reading tile at (" << y << ", " << x << ")" << endl;
                        return;  
                    }

                    if (x < MAP_WIDTH - 1) {
                        char comma;
                        lineStream >> comma;

                        if (comma != ',') {
                            cout << "Expected comma at (" << y << ", " << x << "), but got: " << comma << endl;
                        }
                    }
                    else {
                        char maybeComma;
                        lineStream >> maybeComma;
                        if (maybeComma == ',') {
                        }
                        else {
                            lineStream.unget();
                        }
                    }

                    cout << tileMap[y][x] << " ";
                }
                cout << endl;
            }

            infile.close();
            cout << "Map loaded successfully" << endl;
        }
        else {
            cout << "Failed to open map file: " << filename << endl;
        }
    }
    void addRowToTop(float dt) {
        timeSinceLastAdd += dt;
        if (timeSinceLastAdd >= 0.25f) {
            
            for (int y = MAP_HEIGHT - 1; y > 0; --y) {
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    tileMap[y][x] = tileMap[y - 1][x];
                }
            }
            
            for (int x = 0; x < MAP_WIDTH; ++x) {
                tileMap[0][x] = rand() % 5;  

            }
            timeSinceLastAdd = 0.0f;
            
        }
    }
    void addRowToBottom(float dt) {
        timeSinceLastAdd += dt;
        if (timeSinceLastAdd >= 0.25f) {
            
            for (int y = 0; y < MAP_HEIGHT - 1; ++y) {
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    tileMap[y][x] = tileMap[y + 1][x];
                }
            }
           
            for (int x = 0; x < MAP_WIDTH; ++x) {
                tileMap[MAP_HEIGHT - 1][x] = rand() % 5;  
            }
            timeSinceLastAdd = 0.0f;
        }
    }

    void addColumnToLeft(float dt) {
        timeSinceLastAdd += dt;
        if (timeSinceLastAdd >= 0.25f) {
            
            for (int x = MAP_WIDTH - 1; x > 0; --x) {
                for (int y = 0; y < MAP_HEIGHT; ++y) {
                    tileMap[y][x] = tileMap[y][x - 1];
                }
            }
            
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                tileMap[y][0] = rand() % 5;  
            }
            timeSinceLastAdd = 0.0f;
        }
    }

    void addColumnToRight(float dt) {
        timeSinceLastAdd += dt;
        if (timeSinceLastAdd >= 0.25f) {
            
            for (int x = 0; x < MAP_WIDTH - 1; ++x) {
                for (int y = 0; y < MAP_HEIGHT; ++y) {
                    tileMap[y][x] = tileMap[y][x + 1];
                }
            }
            
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                tileMap[y][MAP_WIDTH - 1] = rand() % 5;  
            }
            timeSinceLastAdd = 0.0f;
        }
    }
    void saveGame(const std::string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            
            for (int y = 0; y < currentMapHeight; ++y) {
                for (int x = 0; x < currentMapWidth; ++x) {
                    outFile << tileMap[y][x];
                    if (x < currentMapWidth - 1) {
                        outFile << ",";// Separate tile values with a comma
                    }
                }
                outFile << "\n";// End each row with a new line
            }
            outFile.close();
            cout << "Game saved successfully." << endl;
        }
        else {
           cout << "Failed to open file for saving." << endl;
        }
    }

    void loadGame(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            for (int y = 0; y < currentMapHeight; ++y) {
                if (getline(inFile, line)) {
                    istringstream lineStream(line);
                    for (int x = 0; x < currentMapWidth; ++x) {
                        string value;
                        if (getline(lineStream, value, ',')) {
                            tileMap[y][x] = stoi(value);
                        }
                    }
                }
            }
            inFile.close();
            cout << "Game loaded successfully." << endl;
        }
        else {
            cout << "Failed to open file for loading." << endl;
        }
    }
    
    

    void draw(GamesEngineeringBase::Window& canvas, int offsetX, int offsetY) {
        int startTileX = offsetX / TILE_SIZE;
        int startTileY = offsetY / TILE_SIZE;
        
        int endTileX = min(startTileX + SCREEN_WIDTH / TILE_SIZE, currentMapWidth - 1);
        int endTileY = startTileY + SCREEN_HEIGHT / TILE_SIZE;
        
        

        for (int y = startTileY; y <= endTileY; ++y) {
            for (int x = startTileX; x <= endTileX; ++x) {
                if (y >= 0 && y < currentMapHeight && x >= 0 && x < currentMapWidth) {
                    int tileIndex = tileMap[y][x];
                    int drawX = (x * TILE_SIZE) - offsetX;
                    int drawY = (y * TILE_SIZE) - offsetY;
                    tiles[tileIndex].draw(canvas, drawX, drawY);
                }
            }
        }
    }

    bool isPassable(int x, int y) const {
        int tileX = x / TILE_SIZE;
        int tileY = y / TILE_SIZE;
        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
            int tileIndex = tileMap[tileY][tileX];
            return tiles[tileIndex].isPassable();
        }
        return false;
    }
};


// Swarm 类
class Swarm {
    static const unsigned int maxSize = 100;
    
    plane* sarray[maxSize];
    int hittime = 0;
    unsigned int currentSize = 0;
    unsigned int currentBulletSize = 0;
    xiaoguaibullet* xiaoguaibulletsArray[maxSize];
    float timeElapsed = 0.f;
    float timeThreshold = 3.f;// Initial spawn interval
    

    void generatexiaoguaibullet(GamesEngineeringBase::Window& canvas, float dt, int posx, int posy,int playerx,int playery) {
        timeElapsed += dt;
        if (currentBulletSize < maxSize) {
            if (timeElapsed > timeThreshold) {
                int spawnX = posx;
                int spawnY = posy;
                xiaoguaibullet* x = new xiaoguaibullet(spawnX, spawnY, "Resources/xiaoguaibullet.png", playerx, playery);
                xiaoguaibulletsArray[currentBulletSize++] = x;

                timeElapsed = 0.f;
                timeThreshold -= 0.1f;
                timeThreshold = max(2.0f, timeThreshold);
            }
        }
    }




    void generatePlane(GamesEngineeringBase::Window& canvas, float dt,int posx,int posy) {
        timeElapsed += dt;
        if (currentSize < maxSize) {
            if (timeElapsed > timeThreshold) {
                int tileX = rand() % MAP_WIDTH;
                int tileY = rand() % MAP_HEIGHT;
                int spawnX = tileX * TILE_SIZE;
                int spawnY = tileY * TILE_SIZE;
                int xdistance = abs(posx - spawnX);
                int ydistance = abs(posy - spawnY);
                if (xdistance > 300 && ydistance > 300) {
                    plane* p;
                    int randomvalue = rand() % 4;
                    
                    switch (randomvalue) {
                    case 0:
                        p = new plane(spawnX, spawnY, "Resources/xiaoguai.png");
                        sarray[currentSize++] = p;
                        timeElapsed = 0.f;
                        timeThreshold -= 0.1f;
                        timeThreshold = max(2.0f, timeThreshold);
                        p->setspeed(100.0);
                        p->getskin();
                        p->setskin(0);
                        break;
                    case 1:
                        p = new plane(spawnX, spawnY, "Resources/paotai.png");
                        sarray[currentSize++] = p;
                        timeElapsed = 0.f;
                        timeThreshold -= 0.1f;
                        timeThreshold = max(2.0f, timeThreshold);
                        p->sethealth(1);
                        p->setspeed(0);
                        p->setpaotai();
                        p->getskin();
                        p->setskin(1);
                        
                        break;


                   
                    case 2:
                        p = new plane(spawnX, spawnY, "Resources/xiaoguai3.png");
                        sarray[currentSize++] = p;
                        timeElapsed = 0.f;
                        timeThreshold -= 0.1f;
                        timeThreshold = max(2.0f, timeThreshold);
                        p->setspeed(50.0);
                        p->sethealth(2);
                        p->getskin();
                        p->setskin(2);

                        break;

                    case 3:
                        p = new plane(spawnX, spawnY, "Resources/xiaoguai2.png");
                        sarray[currentSize++] = p;
                        timeElapsed = 0.f;
                        timeThreshold -= 0.1f;
                        timeThreshold = max(2.0f, timeThreshold);
                        p->setspeed(25.0);
                        p->sethealth(3);
                        p->getskin();
                        p->setskin(3);
                        break;
                    }
                    

                    
                    
                    
                }
                else {
                    
                }
               
                
            }
        }
    }

   

    void checkDeletePlane(unsigned int i,int nowposx,int nowposy) {
        
        int health = sarray[i]->gethealth();
        
        int distancex = abs(sarray[i]->getX() - nowposx);
        int distancey = abs(sarray[i]->getY() - nowposy);
        if (health == 0) {
            plane* p = sarray[i];
            sarray[i] = nullptr;
            delete p;
            score = score + 1;
        }
        if (distancex<83 && distancey < 115 ) {
            plane* p = sarray[i];
            sarray[i] = nullptr;
            delete p;
            hittime = hittime + 1;
            
           
        }
    }
    
    void checkxiaoguaibullehit(unsigned int i, int nowposx, int nowposy) {
        // Calculate the distance between the projectile and the hero
        int xdistance = abs(xiaoguaibulletsArray[i]->getX() - nowposx);
        int ydistance = abs(xiaoguaibulletsArray[i]->getY() - nowposy);
        float distance = sqrtf(xdistance * xdistance + ydistance * ydistance);
        if (distance < 50) {
            // Collision detected: Remove the projectile and reduce hero health
            delete xiaoguaibulletsArray[i];
            xiaoguaibulletsArray[i] = nullptr;
            hittime = hittime + 1;
        }
    }


    

    

    




public:
    Swarm() {}

    void removeEnemy(plane* enemy) {
        for (unsigned int i = 0; i < currentSize; i++) {
            if (sarray[i] == enemy) {
                
                sarray[i] = nullptr; 
                delete sarray[i];
                
                break;
            }
        }
    }


    void update(GamesEngineeringBase::Window& canvas, float dt, int posx, int posy) {
        generatePlane(canvas, dt,posx,posy);

          
        for (unsigned int i = 0; i < currentSize; i++) {
            if (sarray[i] != nullptr) {
                

                int dx = sarray[i]->getX() - posx;
                int dy = sarray[i]->getY() - posy;

                float distance = sqrtf(dx * dx + dy * dy);

                float normX = dx / distance;
                float normY = dy / distance;

                
                float speed = sarray[i]->getspeed() * dt;
                float moveX = -normX * speed;
                float moveY = -normY * speed;

                // Update NPC position
                sarray[i]->update(moveX, moveY);
                
                getCurrentSize();
                int paotaisatus = sarray[i]->getpaotai();
                
                if (paotaisatus == 1 && distance < 600) {
                    
                    generatexiaoguaibullet(canvas, dt, sarray[i]->getX(), sarray[i]->getY(),posx,posy);
                    
                    
                    
                    
                }
                
                checkDeletePlane(i, posx, posy);
            }
        }

        for (unsigned int i = 0; i < currentBulletSize; i++) {
            if (xiaoguaibulletsArray[i] != nullptr) {
                xiaoguaibulletsArray[i]->update(dt);

                
                if (xiaoguaibulletsArray[i]->getX() > MAP_WIDTH *32) {
                    delete xiaoguaibulletsArray[i];
                    xiaoguaibulletsArray[i] = nullptr;
                    return;
                }
                else if (xiaoguaibulletsArray[i]->getX() < -MAP_WIDTH * 32) {
                    delete xiaoguaibulletsArray[i];
                    xiaoguaibulletsArray[i] = nullptr;
                    return;
                }
                else if (xiaoguaibulletsArray[i]->getY() < -MAP_HEIGHT * 32) {
                    delete xiaoguaibulletsArray[i];
                    xiaoguaibulletsArray[i] = nullptr;
                    return;
                }
                else if (xiaoguaibulletsArray[i]->getY() > MAP_HEIGHT * 32) {
                    delete xiaoguaibulletsArray[i];
                    xiaoguaibulletsArray[i] = nullptr;
                    return;
                }
                checkxiaoguaibullehit(i, posx, posy);
                
                
                
                
                
                
                


                
                
            }
        }
    }


    void draw(GamesEngineeringBase::Window& canvas, int offsetX, int offsetY) {
        for (unsigned int i = 0; i < currentSize; i++) {
            if (sarray[i] != nullptr) {
                int drawX = sarray[i]->getX() - offsetX;
                int drawY = sarray[i]->getY() - offsetY;
                if (drawX + sarray[i]->getWidth() >= 0 && drawX < SCREEN_WIDTH &&
                    drawY + sarray[i]->getHeight() >= 0 && drawY < SCREEN_HEIGHT) {
                    sarray[i]->draw(canvas, drawX, drawY);
                    
                }
            }
        }

        for (unsigned int i = 0; i < currentBulletSize; i++) {
            if (xiaoguaibulletsArray[i] != nullptr) {
                int drawX = xiaoguaibulletsArray[i]->getX() - offsetX;
                int drawY = xiaoguaibulletsArray[i]->getY() - offsetY;
                if (drawX + xiaoguaibulletsArray[i]->getWidth() >= 0 && drawX < SCREEN_WIDTH &&
                    drawY + xiaoguaibulletsArray[i]->getHeight() >= 0 && drawY < SCREEN_HEIGHT) {
                    xiaoguaibulletsArray[i]->draw(canvas, drawX, drawY);
                }
            }
        }
    }

    void saveEnemyStatus(const std::string& filename) {
        ofstream outFile(filename);

        if (outFile.is_open()) {
            for (unsigned int i = 0; i < currentSize; ++i) {
                if (sarray[i] != nullptr) {
                    
                    int id = i;
                    float x = sarray[i]->getX();
                    float y = sarray[i]->getY();
                    int health = sarray[i]->gethealth();
                    int skin = sarray[i]->getskin();

                    
                    outFile << id << " " << x << " " << y << " " << health << " " << skin <<endl;
                }
            }

            outFile.close();
            cout << "Enemy status saved to " << filename << endl;
        }
        else {
            cout << "Error opening file to save enemy status." << endl;
        }
    }

    void loadEnemyStatus(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                istringstream iss(line);
                int id;
                float x, y;
                int health;
                int skin;
                

                if (iss >> id >> x >> y >> health >> skin) {
                    
                    if (currentSize < maxSize) {
                        if (skin == 0) {
                            plane*p = new plane(x, y, "Resources/xiaoguai.png");
                            sarray[currentSize++] = p;
                            timeElapsed = 0.f;
                            timeThreshold -= 0.1f;
                            timeThreshold = max(2.0f, timeThreshold);
                            p->setspeed(100.0);
                            p->getskin();
                            p->setskin(0);
                            p->sethealth(health);
                            cout << "enemy0" << endl;
                        }
                        if (skin == 1) {
                            plane* p = new plane(x, y, "Resources/paotai.png");
                            sarray[currentSize++] = p;
                            timeElapsed = 0.f;
                            timeThreshold -= 0.1f;
                            timeThreshold = max(2.0f, timeThreshold);
                            p->sethealth(health);
                            p->setspeed(0);
                            p->setpaotai();
                            p->getskin();
                            p->setskin(1);
                            cout << "enemy1" << endl;

                        }
                        if (skin == 2) {
                            plane* p = new plane(x, y, "Resources/xiaoguai3.png");
                            sarray[currentSize++] = p;
                            timeElapsed = 0.f;
                            timeThreshold -= 0.1f;
                            timeThreshold = max(2.0f, timeThreshold);
                            p->setspeed(50.0);
                            p->sethealth(health);
                            p->getskin();
                            p->setskin(2);
                            cout << "enemy2" << endl;
                        }
                        if (skin == 3) {
                            plane*p = new plane(x, y, "Resources/xiaoguai2.png");
                            sarray[currentSize++] = p;
                            timeElapsed = 0.f;
                            timeThreshold -= 0.1f;
                            timeThreshold = max(2.0f, timeThreshold);
                            p->setspeed(25.0);
                            p->sethealth(health);
                            p->getskin();
                            p->setskin(3);
                            cout << "enemy3" << endl;

                        }
                        
                    }
                    else {
                        cout << "Error: Max size reached, cannot load more enemies." << endl;
                    }
                }
                else {
                    cout << "Error reading enemy status from line: " << line << endl;
                }
            
            }
            inFile.close();
            cout << "Enemy status loaded from " << filename << endl;
        }

    }
    unsigned int getCurrentSize() const {
        return currentSize;
    }

    plane* getEnemy(unsigned int index)  const {
        if (index < currentSize) {
            return sarray[index];
        }
        return nullptr;  
    }

    void checkEnemiesPosition(const Swarm& enemySwarm) {
        for (unsigned int i = 0; i < enemySwarm.getCurrentSize(); ++i) {
            plane* enemy = enemySwarm.getEnemy(i);
            if (enemy != nullptr) {
                
                int enemyX = enemy->getX();
                int enemyY = enemy->getY();

                
            }
        }
    }

    void checkEnemiesHealth(const Swarm& enemySwarm) {
        for (unsigned int i = 0; i < enemySwarm.getCurrentSize(); ++i) {
            plane* enemy = enemySwarm.getEnemy(i);
            if (enemy != nullptr) {

                int enemyhealth = enemy->gethealth();
                


            }
        }
    }

    int gethittime() {
        
        return hittime;
    }
    int sethittime() {
        hittime = 0;
        return hittime;
    }
    

    
};



class Bullet {
protected:
    float x, y;
    float dirX, dirY;
    GamesEngineeringBase::Image sprite;
    int active = 0;
public:
    Bullet(int _x, int _y, string filename, float _dirX, float _dirY) {
        sprite.load(filename);
        x = _x;
        y = _y;
        dirX = _dirX;
        dirY = _dirY;
    }

    void draw(GamesEngineeringBase::Window& canvas, int drawX, int drawY) {
        int startX = drawX - sprite.width / 2;
        int startY = drawY - sprite.height / 2;
        for (unsigned int i = 0; i < sprite.height; i++) {
            if (startY + i < canvas.getHeight() && startY + i >= 0) {
                for (unsigned int n = 0; n < sprite.width; n++) {
                    if (startX + n < canvas.getWidth() && startX + n >= 0) {
                        if (sprite.alphaAt(n, i) > 200)
                            canvas.draw(startX + n, startY + i, sprite.at(n, i));
                    }
                }
            }
        }

    }
    void update(float speed) {
        x += dirX * speed;
        y += dirY * speed;
    }

    float getY()  {
        return y;
    }
    float getX()  {
        return x;
    }
    unsigned int getWidth() const {
        return sprite.width;
    }

    unsigned int getHeight() const {
        return sprite.height;
    }

    int updateactive(){
        active = 1;

        return active;
    }
    int getact() {
        return active;
    }

    int setdirx(int x){
        dirX = x;
        return dirX;

    }
    int setdiry(int y) {
        dirY = y;
        return dirY;

    }
};

class Shoot {
    static const unsigned int maxSize = 1000;
    Bullet* bulletsArray[maxSize];
    unsigned int currentSize = 0;
    float timeElapsed = 0.f;
    
    plane** enemiesArray;
    unsigned int enemyCount;



    void generateBullet(GamesEngineeringBase::Window& canvas, float dt, int posx, int posy, plane* targetEnemy) {
        timeElapsed += dt;
        if (currentSize < maxSize) {
            if (timeElapsed > timeThreshold ) {
                float dirX, dirY;
                if (targetEnemy != nullptr) {
                    // Calculate direction vector to the closest enemy
                    int targetX = targetEnemy->getX();
                    int targetY = targetEnemy->getY();
                    float dx = static_cast<float>(targetX - posx);
                    float dy = static_cast<float>(targetY - posy);
                    float distance = sqrtf(dx * dx + dy * dy);

                    // Normalize direction
                    dirX = dx / distance;
                    dirY = dy / distance;
                }else {
                    // Default direction when no target available (upwards)
                    dirX = 0;
                    dirY = -1;
                }
                
                // Create and add a new bullet
                Bullet* b = new Bullet(posx, posy, "Resources/bullet.png", dirX, dirY);
                bulletsArray[currentSize++] = b;
                timeElapsed = 0.f;// Reset the timer for the next attack
            }
        }
    }


    plane* findClosestEnemy(const Swarm& enemySwarm, int heroX, int heroY) {
        plane* closestEnemy = nullptr;
        float minDistance = 580;

        for (unsigned int i = 0; i < enemySwarm.getCurrentSize(); ++i) {
            plane* enemy = enemySwarm.getEnemy(i);
            if (enemy != nullptr) {
                int enemyX = enemy->getX();
                int enemyY = enemy->getY();

                // Calculate the distance between hero and enemy
                float dx = static_cast<float>(enemyX - heroX);
                float dy = static_cast<float>(enemyY - heroY);
                float distance = sqrtf(dx * dx + dy * dy);

                // Update closest enemy if this one is closer

                if (distance < minDistance) {
                    minDistance = distance;
                    closestEnemy = enemy;
                }
            }
        }

        return closestEnemy;  // Return the closest enemy or nullptr if no enemies are found
    }

    
  
    


   





public:
    Shoot() {}
    float timeThreshold = 1.5f;// Time between attacks
    
    Shoot(plane* enemies[], unsigned int count) {
        enemiesArray = enemies;
        enemyCount = count;
    }

    
    void update(GamesEngineeringBase::Window& canvas, float dt, int posx, int posy, const Swarm&enemySwarm) {
        plane* targetEnemy = findClosestEnemy(enemySwarm, posx, posy);
        generateBullet(canvas, dt, posx, posy, targetEnemy);

        
        float speed = 700.0f * dt; 

        
       
        for (unsigned int i = 0; i < currentSize; i++) {
            
            if (bulletsArray[i] != nullptr &&targetEnemy!=nullptr) {
                int targetX = targetEnemy->getX();
                int targetY = targetEnemy->getY();
                float dx = static_cast<float>(targetX - bulletsArray[i]->getX());
                float dy = static_cast<float>(targetY - bulletsArray[i]->getY());
                float distance = sqrtf(dx * dx + dy * dy);
                float dx1 = static_cast<float>(targetX - posx);
                float dy1 = static_cast<float>(targetY - posy);
                float distance1 = sqrtf(dx1 * dx1 + dy1 * dy1);

                float normX = dx / distance;
                float normY = dy / distance;
                float moveX = normX * speed;
                float moveY = normY * speed;
               
                
                
                if (distance1 < 580 ) {
                    bulletsArray[i]->update(speed);
                    
                    
                }
                if (bulletsArray[i]->getY() < 0) { 
                        Bullet* b = bulletsArray[i];
                        bulletsArray[i] = nullptr;
                        delete b;

                 }

                if (distance < 25) {
                    Bullet* b = bulletsArray[i];
                    bulletsArray[i] = nullptr;
                    delete b;
                    targetEnemy->hit();
           
                }
                
            }
            else if (bulletsArray[i] != nullptr) {
                bulletsArray[i]->update(speed);
                if (bulletsArray[i]->getY() < 0) { 
                    Bullet* b = bulletsArray[i];
                    bulletsArray[i] = nullptr;
                    delete b;

                }
            }
            
            
        }
    }

    void draw(GamesEngineeringBase::Window& canvas, int offsetX, int offsetY) {
        for (unsigned int i = 0; i < currentSize; i++) {
            if (bulletsArray[i] != nullptr) {
                int drawX = bulletsArray[i]->getX() - offsetX;
                int drawY = bulletsArray[i]->getY() - offsetY;
                if (drawX + bulletsArray[i]->getWidth() >= 0 && drawX < SCREEN_WIDTH &&
                    drawY + bulletsArray[i]->getHeight() >= 0 && drawY < SCREEN_HEIGHT) {
                    bulletsArray[i]->draw(canvas, drawX, drawY);
                }
            }
        }
    }

    float setattackspeed(float x) {
        timeThreshold = x;
        return timeThreshold;

    }



};
// 英雄类
class Hero {
    GamesEngineeringBase::Image sprite;
    float x, y;  
    bool isFlashing = false;
    float flashDuration = 1.0f;
    float flashTimeElapsed = 0.0f;
    bool isVisible = true;
    float skillCooldown = 10.0f;
    float skillCooldownRemaining = 0.0f;
    int skillenemynumber = 2;
protected:
    int health = 5;
public:
    bool isSkillReady() {
        return skillCooldownRemaining <= 0.0f;
    }
    Hero(float windowWidth, float windowHeight) {
        sprite.load("Resources/L.png");
        x = (windowWidth - sprite.width) / 2;
        y = (windowHeight - sprite.height) / 2;
    }

    void update(int incX, int incY, const Map& map, float dt) {
        int newX = x + incX;
        int newY = y + incY;

        if (isAreaPassable(newX, y, map)) {
            x = newX;
        }
        if (isAreaPassable(x, newY, map)) {
            y = newY;
        }

        if (isFlashing) {
            flashTimeElapsed += dt;
            if (flashTimeElapsed >= flashDuration) {
                isFlashing = false;
                isVisible = true;
            }
            else {

                if (static_cast<int>(flashTimeElapsed * 20) % 2 == 0) {
                    isVisible = !isVisible;
                }
            }
        }
        if (skillCooldownRemaining > 0.0f) {
            skillCooldownRemaining -= dt;
            if (skillCooldownRemaining < 0.0f) {
                skillCooldownRemaining = 0.0f;
            }
        }



    }



    void draw(GamesEngineeringBase::Window& canvas, int offsetX, int offsetY) {
        int drawX = x - offsetX;
        int drawY = y - offsetY;

        if (isVisible) {
            for (unsigned int i = 0; i < sprite.height; i++) {
                for (unsigned int n = 0; n < sprite.width; n++) {
                    if ((drawX + n) >= 0 && (drawX + n) < canvas.getWidth() &&
                        (drawY + i) >= 0 && (drawY + i) < canvas.getHeight()) {
                        if (sprite.alphaAtUnchecked(n, i) > 210) {
                            canvas.draw(drawX + n, drawY + i, sprite.atUnchecked(n, i));
                        }
                    }
                }
            }
        }
    }
    void saveHeroPosition(const string& filename, int posx, int posy) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "herox: " << posx << endl;
            outFile << "heroy: " << posy << endl;
            outFile << "health: " << health << endl;
            outFile.close();
            cout << "Hero position saved to " << filename << endl;
        }
        else {
            cout << "Error opening file to save hero position." << endl;
        }
    }


    void loadHeroPosition(const string& filename, int& nowposx, int& nowposy, int& health) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;

            
            if (getline(inFile, line)) {
                istringstream iss(line);
                string label;
                iss >> label >> nowposx;
            }

           
            if (getline(inFile, line)) {
                istringstream iss(line);
                string label;
                iss >> label >> nowposy;
            }
            if (getline(inFile, line)) {
                istringstream iss(line);
                string label;
                iss >> label >> health;
            }

            inFile.close();
            cout << "Hero position loaded from " << filename << endl;
        }
        else {
            cout << "Error opening file to load hero position." << endl;
        }
    }


    int getX() {
        return x;
    }
    int setX(int posx) {
        x = posx;
        return x;
    }
    int getY() {
        return y;
    }
    int setY(int posy) {
        y = posy;
        return y;
    }
    int getherohealth() {
        return health;
    }
    int setherohealth(int newhealth) {
        health = newhealth;
        return health;
    }
    void gethurt() {
        health = health - 1;
        isFlashing = true;
        flashTimeElapsed = 0.0f;
        isVisible = true;
        
    }
    int setkillnumber(int x) {
        skillenemynumber = x;
        return skillenemynumber;
    }
    
    static const unsigned int Size = 100;
    void useSpecialSkill(Swarm& swarm, int heroX, int heroY, float attackRange) {
        plane* enemiesInRange[Size];  // Temporary array for enemies within the range
        unsigned int enemiesInRangeCount = 0;
        
        // Find all enemies within attackRange
        for (unsigned int i = 0; i < swarm.getCurrentSize(); i++) {
            plane* enemy = swarm.getEnemy(i);
            if (enemy != nullptr) {
                int enemyX = enemy->getX();
                int enemyY = enemy->getY();

                
                float dx = heroX - enemyX;
                float dy = heroY - enemyY;
                float distance = sqrtf(dx * dx + dy * dy);

                
                if (distance <= attackRange) {
                    enemiesInRange[enemiesInRangeCount++] = enemy;
                }
            }
        }

        
        if (enemiesInRangeCount >= skillenemynumber) {
            // Manual sorting: Sort by Y coordinate from high to low (small Y values ​​are close to the player)
            for (unsigned int i = 0; i < enemiesInRangeCount - 1; i++) {
                for (unsigned int j = i + 1; j < enemiesInRangeCount; j++) {
                    
                    if (enemiesInRange[i]->gethealth() < enemiesInRange[j]->gethealth()) {
                        plane* temp = enemiesInRange[i];
                        enemiesInRange[i] = enemiesInRange[j];
                        enemiesInRange[j] = temp;
                    }
                }
            }
            // Attack the top N enemies
            for (int x = 0; x < skillenemynumber; x++) {
                if (enemiesInRange[x] != nullptr) {
                    delete enemiesInRange[x];  
                    swarm.removeEnemy(enemiesInRange[x]);
                    cout << "Enemy " << x << " has been killed." << endl;
                }
            }
            

           
            
            skillCooldownRemaining = skillCooldown;// Reset cooldown for AOE attack
            cout << "Special skill used! The " << skillenemynumber << "highest enemies have been deleted." << endl;
        }
        else {
            skillCooldownRemaining = skillCooldown;
            
            
        }
    }


private:
    Hero* h;
    
    bool isAreaPassable(int newX, int newY, const Map& map) {
        int left = newX;
        int right = newX + sprite.width;
        int top = newY;
        int bottom = newY + sprite.height;

        return map.isPassable(left, top) &&
            map.isPassable(right - 1, top) &&
            map.isPassable(left, bottom - 1) &&
            map.isPassable(right - 1, bottom - 1) &&
            map.isPassable((left + right) / 2, (top + bottom) / 2);
    }
};
int readMapNumber() {
    
    ifstream inFile("Resources/mapnumber.txt");
    int mapnumber = 0;

    if (inFile.is_open()) {
        string line;
        if (getline(inFile, line)) {
            
            if (line == "1") {
                mapnumber = 1;
                
            }
            else if (line == "2") {
                mapnumber = 2;
            }
            else {
                mapnumber = -1; 
            }
        }
        inFile.close();  
    }
    else {
        mapnumber = -1;  
    }
    cout << mapnumber << endl;

    return mapnumber;
}


int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    GamesEngineeringBase::Window canvas;
    canvas.create(SCREEN_WIDTH, SCREEN_HEIGHT, "Hero");

    bool running = true;
    bool notset = true;
    bool load = false;
    int mapnumber = 0;
    Hero h(SCREEN_WIDTH, SCREEN_HEIGHT);
    PowerUp p(500,500);
    Map map;
    map.loadMap("Resources/tiles.txt");
    UI ui(SCREEN_WIDTH, SCREEN_HEIGHT);
    Swarm swarm;  
    Shoot shoot;
    GamesEngineeringBase::Timer tim;
    GameState currentState = MENU;
    
    bool showSkillEffect = false; 
    float skillEffectTimer = 0.0f;
    float elapsedTime = 0.0f;
    int frameCount = 0;
    int currentFPS = 0;
    int previousState = 0;
    while (running) {
        canvas.clear();
        canvas.checkInput();
        
        
        if (currentState == MENU) {
            ui.draw(canvas);
            h.setherohealth(5);
            if (canvas.keyPressed('1')) {
                ofstream outFile("Resources/mapnumber.txt");
                if (outFile.is_open()) {
                    outFile << "1" << endl;  
                    outFile.close();          
                    cout << "Map number saved to file." << endl;
                }
                else {
                    cout << "Error opening file to save map number." << endl;
                }
                currentState = MAP1;
            }
            if (canvas.keyPressed('2')) {
                ofstream outFile("Resources/mapnumber.txt");
                if (outFile.is_open()) {
                    outFile << "2" << endl;
                    outFile.close();
                    cout << "Map number saved to file." << endl;
                }
                else {
                    cout << "Error opening file to save map number." << endl;
                }
                currentState = MAP2;
            }
            if (canvas.keyPressed('3')) {
                load = true;
                int mapNumber = readMapNumber();
                if (mapNumber == 1) {
                    currentState = MAP1;
                }
                if (mapNumber == 2) {
                    currentState = MAP2;
                }

            }
            if (canvas.keyPressed('Q')) {
                currentState = EXIT;
            }


            canvas.present();
        }
        if (currentState == EXIT) {
            running = false;
        }
        
        if (currentState == MAP2) {
            
            
            float dt = tim.dt();// Get the delta time for the current frame
            elapsedTime += dt;// Add the delta time to the elapsed time
            frameCount++;// Increment the frame count
            // If a second has passed, calculate the FPS
            if (elapsedTime >= 1.0f) {
                currentFPS = frameCount;// The FPS is equal to the number of frames in the last second
                frameCount = 0;// Reset the frame count for the next second
                elapsedTime = 0.0f;// Reset the elapsed time

                cout << "FPS: " << currentFPS <<endl;  
            }
            int moveSpeed = 2;
            int herohealth = h.getherohealth();
            int offsetX = h.getX() - SCREEN_WIDTH / 2 + 42;
            int offsetY = h.getY() - SCREEN_HEIGHT / 2 + 58;
            offsetX = max(0, min(offsetX, MAP_WIDTH * TILE_SIZE - SCREEN_WIDTH));
            offsetY = max(0, min(offsetY, MAP_HEIGHT * TILE_SIZE - SCREEN_HEIGHT));
            int nowposx = h.getX() + 42;
            int nowposy = h.getY() + 58;
            if (load) {
                h.loadHeroPosition("Resources/location.txt", nowposx, nowposy, herohealth);
                h.setX(nowposx);
                h.setY(nowposy);
                h.setherohealth(herohealth);
                map.loadGame("Resources/save.txt");
                load = false;
                swarm.loadEnemyStatus("Resources/enemy.txt");
                cout << "load finish" << endl;
            }
            
            
            
            
            
            if (canvas.keyPressed('A')&&nowposx<=512) {
                map.addColumnToLeft(dt);
                
            }
            else if (canvas.keyPressed('A')) {
                h.update(-moveSpeed, 0, map, dt);
            }

            if (canvas.keyPressed('D')&&nowposx>=790) {
                map.addColumnToRight(dt);
                
            }
            else if (canvas.keyPressed('D')) {
                h.update(moveSpeed, 0, map, dt);

            }

            
            if (canvas.keyPressed('W')&&nowposy <= 384) {
                
                map.addRowToTop(dt);

                

            }
            else if (canvas.keyPressed('W')) {
                h.update(0, -moveSpeed, map, dt);

            }
            

            if (canvas.keyPressed('S')&&nowposy >=920) {
                map.addRowToBottom(dt);
                
            }
            else if (canvas.keyPressed('S')) {
                h.update(0, moveSpeed, map, dt);

            }

            

            

            
            map.draw(canvas, offsetX, offsetY);
           
            
            
            

            swarm.update(canvas, dt, nowposx, nowposy);
            int hittime = swarm.gethittime();

            if (hittime == 1) {
                h.gethurt();
                swarm.sethittime();
            }
            for (int i = 0; i < h.getherohealth(); ++i) {
                ui.drawheart(canvas, 40 + (i * 40), 40);
            }
            if (h.getherohealth() <= 0) {
                cout << "score =" << score << endl;
                score = 0;
                currentState = MENU;
                
            }

            
            
            p.update(nowposx, nowposy);
            bool active = p.getactive();

            if (active) {
                p.draw(canvas, offsetX, offsetY);// Draw power-up if still active

            }
            else if (notset) {
                // Apply the power-up effects once, after pickup
                shoot.setattackspeed(0.5f);
                notset = false;
                h.setkillnumber(4);
                cout << "set" << endl;

            }


            swarm.draw(canvas, offsetX, offsetY);
            shoot.update(canvas, dt, nowposx, nowposy, swarm);
            shoot.draw(canvas, offsetX, offsetY);
            h.update(0, 0, map, dt);
            h.draw(canvas, offsetX, offsetY);
            swarm.checkEnemiesPosition(swarm);
            if (canvas.keyPressed('R') && h.isSkillReady()) {
                h.useSpecialSkill(swarm, nowposx, nowposy, 600.0f);
                showSkillEffect = true;
                skillEffectTimer = 2.0f;

            }
            if (showSkillEffect) {
                
                skillEffectTimer -= dt;

                
                int drawX = h.getX() - offsetX;
                int drawY = h.getY() - offsetY;
                ui.drawskillui(canvas);

                
                if (skillEffectTimer <= 0.0f) {
                    showSkillEffect = false;
                }
            }
            if (canvas.keyPressed(VK_ESCAPE)) {
                map.saveGame("Resources/save.txt");
                swarm.saveEnemyStatus("Resources/enemy.txt");
                h.saveHeroPosition("Resources/location.txt", nowposx, nowposy);
                currentState = PAUSE;
                previousState = 2;
            }
            
           
            canvas.present();
            
        }
        if (currentState == MAP1) {


            float dt = tim.dt();
            elapsedTime += dt;
            frameCount++;
            if (elapsedTime >= 1.0f) {
                currentFPS = frameCount;
                frameCount = 0;
                elapsedTime = 0.0f;

                cout << "FPS: " << currentFPS << endl; 
            }
            int moveSpeed = 2;
            int herohealth = h.getherohealth();
            int offsetX = h.getX() - SCREEN_WIDTH / 2 + 42;
            int offsetY = h.getY() - SCREEN_HEIGHT / 2 + 58;
            offsetX = max(0, min(offsetX, MAP_WIDTH * TILE_SIZE - SCREEN_WIDTH));
            offsetY = max(0, min(offsetY, MAP_HEIGHT * TILE_SIZE - SCREEN_HEIGHT));
            int nowposx = h.getX() + 42;
            int nowposy = h.getY() + 58;
            if (load) {
                h.loadHeroPosition("Resources/location.txt", nowposx, nowposy, herohealth);
                h.setX(nowposx);
                h.setY(nowposy);
                h.setherohealth(herohealth);
                map.loadGame("Resources/save.txt");
                swarm.loadEnemyStatus("Resources/enemy.txt");
                load = false;
                cout << "load finish" << endl;
            }
            



           
            if (canvas.keyPressed('A')) {
                h.update(-moveSpeed, 0, map, dt);
                
            }

         
            if (canvas.keyPressed('D')) {
                h.update(moveSpeed, 0, map, dt);

            }


            if (canvas.keyPressed('W')) {
                h.update(0, -moveSpeed, map, dt);
                



            }
            


            if (canvas.keyPressed('S')) {
                h.update(0, moveSpeed, map, dt);

            }
            






            map.draw(canvas, offsetX, offsetY);




            swarm.update(canvas, dt, nowposx, nowposy);
            int hittime = swarm.gethittime();

            if (hittime == 1) {
                h.gethurt();
                swarm.sethittime();
                cout << "hit" << endl;



            }
            for (int i = 0; i < h.getherohealth(); ++i) {
                ui.drawheart(canvas, 40 + (i * 40), 40);
            }
            if (h.getherohealth() <= 0) {
                cout << "score ="<<score << endl;
                score = 0;
                currentState = MENU;
            }

            h.update(0, 0, map, dt);
            h.draw(canvas, offsetX, offsetY);
            p.update(nowposx, nowposy);
            bool active = p.getactive();

            if (active) {
                p.draw(canvas, offsetX, offsetY);

            }
            else if (notset) {
                shoot.setattackspeed(0.5f);
                notset = false;
                h.setkillnumber(4);
                cout << "set" << endl;

            }


            swarm.draw(canvas, offsetX, offsetY);
            shoot.update(canvas, dt, nowposx, nowposy, swarm);
            shoot.draw(canvas, offsetX, offsetY);
            swarm.checkEnemiesPosition(swarm);
            if (canvas.keyPressed('R') && h.isSkillReady()) {
                h.useSpecialSkill(swarm, nowposx, nowposy, 600.0f);
                showSkillEffect = true;
                skillEffectTimer = 2.0f;

            }
            if (showSkillEffect) {

                skillEffectTimer -= dt;


                int drawX = h.getX() - offsetX;
                int drawY = h.getY() - offsetY;
                ui.drawskillui(canvas);


                if (skillEffectTimer <= 0.0f) {
                    showSkillEffect = false;
                }
            }

            if (canvas.keyPressed(VK_ESCAPE)) {
                map.saveGame("Resources/save.txt");
                swarm.saveEnemyStatus("Resources/enemy.txt");
                h.saveHeroPosition("Resources/location.txt", nowposx, nowposy);
                currentState = PAUSE;
                previousState = 1;
            }

            canvas.present();

        }
        if (currentState == PAUSE) {
            ui.drawpause(canvas);
            if (canvas.keyPressed('A')) {
                if (previousState == 1) {
                    currentState = MAP1;
                }
                if (previousState == 2) {
                    currentState = MAP2;
                }

            }
            if (canvas.keyPressed('B')) {
                currentState = MENU;

            }
            if (canvas.keyPressed('C')) {
                currentState = EXIT;

            }
            canvas.present();

            
        }
    }

    return 0;
}
