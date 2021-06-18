#include "Trackable.h"
#include "Vector2D.h"
#include <vector>

class Unit;
class Animation;
class GraphicsSystem;

class UnitManager : public Trackable
{

public:
    UnitManager();
    ~UnitManager();

    int getNumOfUnits() { return mUnits.size(); }

    Unit* createUnit(Animation* anim, Vector2D loc = Vector2D::Zero());
    Unit* createAndManageUnit(Animation* anim, Vector2D loc = Vector2D::Zero());

    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);
    void removeAndDeleteUnit(Unit* unit);

    void deleteUnit(Unit* unit);

    int find(Unit* unit);
    Unit* getUnitAt(int index);

    void draw(GraphicsSystem* gs);

    void clear();

private:
    std::vector<Unit*> mUnits;

};