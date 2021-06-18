#include "UnitManager.h"
#include "Unit.h"
#include "Animation.h"
#include "GraphicsSystem.h"

using namespace std;

UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
    if(!mUnits.empty())
    {
        clear();
    }
}

Unit* UnitManager::createUnit(Animation* anim, Vector2D loc)
{
    return new Unit(anim, loc);
}

Unit* UnitManager::createAndManageUnit(Animation* anim, Vector2D loc)
{
    Unit* unit = new Unit(anim, loc);
    mUnits.push_back(unit);
    return unit;
}

void UnitManager::addUnit(Unit* unit)
{
    mUnits.push_back(unit);
}

void UnitManager::removeUnit(Unit* unit)
{
    for(vector<Unit*>::iterator i = mUnits.begin(); i != mUnits.end(); i++)
    {
        if(*i == unit)
        {
            mUnits.erase(i);
            return;
        }
    }
}

void UnitManager::removeAndDeleteUnit(Unit* unit)
{
    for(vector<Unit*>::iterator i = mUnits.begin(); i != mUnits.end(); i++)
    {
        if(*i == unit)
        {
            delete *i;
            mUnits.erase(i);
            return;
        }
    }
}

void UnitManager::deleteUnit(Unit* unit)
{
    delete unit;
}

int UnitManager::find(Unit* unit)
{
    int index = 0;
    for(vector<Unit*>::iterator i = mUnits.begin(); i != mUnits.end(); i++)
    {
        if(*i == unit)
        {
            return index;
        }
        index++;
    }
    return -1;
}

Unit* UnitManager::getUnitAt(int index)
{
    int ind = 0;
    for(vector<Unit*>::iterator i = mUnits.begin(); i != mUnits.end(); i++)
    {
        if(ind != index)
        {
            ind++;
            continue;
        }

        return *i;
    }
    return nullptr;
}

void UnitManager::draw(GraphicsSystem* gs)
{
    for(vector<Unit*>::iterator i = mUnits.begin(); i != mUnits.end(); i++)
    {
        (*i)->draw(gs);
    }
}

void UnitManager::clear()
{

    if(mUnits.size() > 0)
    {
        for(vector<Unit*>::iterator i = mUnits.begin(); i != mUnits.end(); i++)
        {
            delete (*i);
        }
    }

    mUnits.clear();

}