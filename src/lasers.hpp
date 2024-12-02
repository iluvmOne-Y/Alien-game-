
#include <raylib.h>
#include <vector>

class Laser
{
private:
  Vector2 position;
  int speed;
  int speed_x;
  Color color; // will always be 0, in some case there will be -3 or 3, may  be another number but not for now
public:
  Laser(Vector2 position, int speed, int x_speed, Color color);
  void Draw();
  void Update();
  bool active;
  Rectangle GetRectangle();
};