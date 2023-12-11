#pragma once
#include "UIElement.h"
#include "EventListener.h"

struct Rect
{
	Vector2D lower;
	Vector2D upper;
};

class UIScrollElement : public UIElement
{
public:
	UIScrollElement(Vector2D indentDistance, float scrollSpeed, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	UIScrollElement();
	~UIScrollElement();

	Rect getBounds();
	float getScrollSpeed() { return mScrollSpeed; }

private:
	class UIScrollListener : public EventListener
	{
	public:
		UIScrollListener(UIScrollElement* scrollElement);
		~UIScrollListener();

		void handleEvent(const Event&) override;

	private:
		UIScrollListener() = delete;

		UIScrollElement* mpScrollElement;
	};

	Vector2D mSize;
	UIScrollListener* mpListener;
	Vector2D mOriginalLoc;

	float mScrollSpeed;
};