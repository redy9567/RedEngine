#include "UIManager.h"
#include "GraphicsSystem.h"

using namespace std;

UIManager* UIManager::mspInstance = nullptr;

UIManager* UIManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new UIManager();

	return mspInstance;
}

void UIManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

void UIManager::init()
{

}

void UIManager::cleanup()
{
	for (unordered_map<string, UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		delete it->second;
	}
	mUIElements.clear();
}

UIElement* UIManager::createAndAddUIElement(string key, string spriteTextureFilepath, string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location, Vector2D scale, GameObject2D* parent, bool animateOnHover)
{
	UIElement* obj = new UIElement(spriteTextureFilepath, objectKey, animationDirection, distanceToMove, speed, location, scale, parent, animateOnHover);

	mUIElements.emplace(key, obj);

	return obj;
}

UIElement* UIManager::createAndAddUIElement(std::string key, string textureFilepath, string objectKey, int animationColumns, int animationRows, Vector2D location, bool animateOnHover)
{
	UIElement* obj = new UIElement(textureFilepath, objectKey, animationColumns, animationRows, location, animateOnHover);

	mUIElements.emplace(key, obj);

	return obj;
}

void UIManager::removeAndDeleteUIElement(string key)
{
	UIElement* obj = mUIElements.at(key);

	if (obj)
	{
		delete obj;
		mUIElements.erase(key);
	}
}

UIElement* UIManager::getUIElement(string key)
{
	return mUIElements.at(key);
}

void UIManager::update(float deltaTime)
{
	for (unordered_map<string, UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		it->second->update(deltaTime);
	}
}

void UIManager::draw()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (unordered_map<string, UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		gs->drawUI(it->second);
	}
}

void UIManager::onMouseHover(Vector2D mousePos)
{
	for (unordered_map<string, UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		UIElement* element = it->second;

		if (!element->mAnimateOnHover)
			continue;

		Vector2D elementHalfSize = element->getSize() / 2.0f;

		Vector2D elementLowerBound = element->getLoc() - elementHalfSize;
		Vector2D elementUpperBound = element->getLoc() + elementHalfSize;

		element->setAnimating(Vector2D::IsPointWithinBounds(mousePos, elementLowerBound, elementUpperBound));
	}
}

bool UIManager::onClick(Vector2D mousePos)
{
	for (unordered_map<string, UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		UIElement* element = it->second;

		Vector2D elementHalfSize = element->getSize() / 2.0f;

		Vector2D elementLowerBound = element->getLoc() - elementHalfSize;
		Vector2D elementUpperBound = element->getLoc() + elementHalfSize;

		if (Vector2D::IsPointWithinBounds(mousePos, elementLowerBound, elementUpperBound))
		{
			if (UIElement* parent = element->getParent())
			{
				parent->setAnimating(!parent->getIsAnimating());
				return true;
			}
			else
				return false;
		}
	}

	return false;
}