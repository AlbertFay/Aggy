#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
  public:
    enum class Direction {kUp, kDown, kLeft, kRight};
    float pos_x = 0, pos_y = 0;
  
    Character();
    void Update(Direction direction);

  private:
    bool isAlive_;
    Direction direction = Direction::kUp;
    float speed = 2;

};

#endif