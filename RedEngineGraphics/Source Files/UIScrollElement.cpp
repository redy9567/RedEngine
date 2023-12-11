#include "UIScrollElement.h"
#include "MouseEvent.h"
#include "EventSystem.h"
#include "GraphicsSystem.h"

UIScrollElement::UIScrollElement(Vector2D indentDistance, float scrollSpeed, std::string objectKey, Vector2D location, Vector2D scale, GameObject2D* parent)
	: UIElement(objectKey, location, scale, parent)
{
	Vector2D parentScreenSize = GraphicsSystem::getInstance()->convertToScreenCoordinates(parent->getSize());

	mSize = Vector2D((parentScreenSize.getX() - indentDistance.getX()) * parent->getScale().getX(),
		(parentScreenSize.getY() - indentDistance.getY()) * parent->getScale().getY());
	mOriginalLoc = location;
	mScrollSpeed = scrollSpeed;

	mpListener = new UIScrollListener(this);

	EventSystem::getInstance()->addListener(Event::MOUSE_EVENT, mpListener);
}

UIScrollElement::UIScrollElement()
	: UIElement()
{
	mSize = Vector2D::Zero();
}

UIScrollElement::~UIScrollElement()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(mpListener);

	delete mpListener;
	mpListener = nullptr;
}

Rect UIScrollElement::getBounds()
{
	Vector2D halfSize = mSize / 2.0f;

	Rect rect;
	rect.lower = mOriginalLoc + mParent->getLoc() - halfSize;
	rect.upper = mOriginalLoc + mParent->getLoc() + halfSize;

	return rect;
}

UIScrollElement::UIScrollListener::UIScrollListener(UIScrollElement* scrollElement)
{
	mpScrollElement = scrollElement;
}

UIScrollElement::UIScrollListener::~UIScrollListener()
{

}

void UIScrollElement::UIScrollListener::handleEvent(const Event& event)
{
	if (event.getType() == Event::EventType::MOUSE_EVENT)
	{
		Rect scrollBounds = mpScrollElement->getBounds();

		const MouseEvent& ms = (const MouseEvent&)event;
		if (ms.getMouseAction() == MouseAction::Scroll && Vector2D::IsPointWithinBounds(ms.getMousePosition(), scrollBounds.lower, scrollBounds.upper))
		{
			mpScrollElement->setLoc(mpScrollElement->getLocalLoc() + ms.getScrollOffset() * mpScrollElement->getScrollSpeed());
		}
	}
}