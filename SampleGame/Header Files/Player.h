#include "GameObject2D.h"
#include "Vector2D.h"

class Player : public GameObject2D
{
public:
    Player();
    Player(Animation* anim, float moveSpeed, Vector2D loc = Vector2D::Zero());
    ~Player();

    void update(float deltaTime) override;
    void setMoveDirection(Vector2D dir);

private:
    float mSpeed;
    Vector2D mMoveDir;
};