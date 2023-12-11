#include "UIManager.h"
#include "GraphicsSystem.h"
#include "UIScrollElement.h"

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
	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		delete *it;
	}
	mUIElements.clear();
}

UIElement* UIManager::createAndAddUIElement(string spriteTextureFilepath, string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location, Vector2D scale, GameObject2D* parent, bool animateOnHover)
{
	UIElement* obj = new UIElement(spriteTextureFilepath, objectKey, animationDirection, distanceToMove, speed, location, scale, parent, animateOnHover);

	mUIElements.push_back(obj);

	return obj;
}

UIElement* UIManager::createAndAddUIElement(string spriteTextureFilepath, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
{
	UIElement* obj = new UIElement(spriteTextureFilepath, objectKey, location, scale, parent);

	mUIElements.push_back(obj);

	return obj;
}

UIElement* UIManager::createAndAddUIElement(string textureFilepath, string objectKey, int animationColumns, int animationRows, Vector2D location, bool animateOnHover)
{
	UIElement* obj = new UIElement(textureFilepath, objectKey, animationColumns, animationRows, location, animateOnHover);

	mUIElements.push_back(obj);

	return obj;
}

UIElement* UIManager::createAndAddUIElement(Sprite* sprite, Vector2D location, Vector2D scale, GameObject2D* parent)
{
	UIElement* obj = new UIElement(sprite, location, scale, parent);

	mUIElements.push_back(obj);

	return obj;
}

UIScrollElement* UIManager::createAndAddUIScrollElement(Vector2D indentDistance, float scrollSpeed, string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
{
	UIScrollElement* obj = new UIScrollElement(indentDistance, scrollSpeed, objectKey, location, scale, parent);

	mUIElements.push_back(obj);

	return obj;
}

void UIManager::removeAndDeleteUIElement(int id)
{
	int i = 0;

	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		if (i++ == id)
		{
			delete *it;
			mUIElements.erase(it);
			break;
		}
	}
}

void UIManager::removeAndDeleteUIElement(UIElement* element)
{
	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		if (*it == element)
		{
			delete *it;
			mUIElements.erase(it);
			break;
		}
	}
}

UIElement* UIManager::getUIElement(int id)
{
	return mUIElements.at(id);
}

void UIManager::update(float deltaTime)
{
	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		(*it)->update(deltaTime);
	}
}

void UIManager::updateCursorPosition(Vector2D mousePos)
{
	if(mCursor)
		mCursor->update(mousePos);
}

void UIManager::draw()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		gs->drawUI(*it);
	}

	if(mCursor)
		gs->drawUI(mCursor);
}

void UIManager::onMouseHover(Vector2D mousePos)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		UIElement* element = (*it);

		if (!element->mAnimateOnHover)
			continue;

		Vector2D elementHalfSize = gs->convertToScreenCoordinates(element->getSize() / 2.0f);

		Vector2D elementLowerBound = element->getLoc() - elementHalfSize;
		Vector2D elementUpperBound = element->getLoc() + elementHalfSize;

		element->setAnimating(Vector2D::IsPointWithinBounds(mousePos, elementLowerBound, elementUpperBound));
	}
}

bool UIManager::onClick(Vector2D mousePos)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	for (vector<UIElement*>::iterator it = mUIElements.begin(); it != mUIElements.end(); it++)
	{
		UIElement* element = (*it);

		Vector2D elementHalfSize = gs->convertToScreenCoordinates(element->getSize() / 2.0f);

		Vector2D elementLowerBound = element->getLoc() - elementHalfSize;
		Vector2D elementUpperBound = element->getLoc() + elementHalfSize;

		if (Vector2D::IsPointWithinBounds(mousePos, elementLowerBound, elementUpperBound))
		{
			element->onClick(mousePos);

			if (UIElement* parent = element->getParent())
			{
				parent->setAnimating(!parent->getIsAnimating());
				
			}
			
			return true;
		}
	}

	return false;
}

void UIManager::setCursorImage(Sprite* sprite)
{
	mCursor->setImage(sprite);

	GraphicsSystem::getInstance()->setCursorHidden(sprite);
}

void UIManager::addUIElement(UIElement* element)
{
	mUIElements.push_back(element);
}