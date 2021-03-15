#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight};
  
    Character();
    void Update();

  private:
    bool isAlive_;
    Direction direction = Direction::kUp;
    float head_x, head_y;
    float speed;

};

#endif