#pragma once
#include <unordered_map>
#include <string>
#include <Vector2D.h>
#include "UIElement.h"
#include "Cursor.h"

class UIScrollElement;

class UIManager : public Trackable
{
public:
	friend class Game;

private:
	static UIManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();
	void update(float deltaTime);
	void draw();

	void onMouseHover(Vector2D mousePos);
	bool onClick(Vector2D mousePos);

	UIElement* createAndAddUIElement(std::string spriteTextureFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr, bool animateOnHover = false);
	UIElement* createAndAddUIElement(std::string spriteTextureFilepath, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	UIElement* createAndAddUIElement(std::string textureFilepath, std::string objectKey, int animationColumns, int animationRows, Vector2D location = Vector2D::Zero(), bool animateOnHover = false);
	UIElement* createAndAddUIElement(Sprite* sprite, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	UIScrollElement* createAndAddUIScrollElement(Vector2D indentDistance, float scrollSpeed, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	void addUIElement(UIElement* element);

	void removeAndDeleteUIElement(int id);
	void removeAndDeleteUIElement(UIElement* element);

	UIElement* getUIElement(int id);
	void setCursor(Cursor* cursor) { mCursor = cursor; }
	Cursor* getCursor() { return mCursor; }
	void setCursorImage(Sprite* sprite);
	void updateCursorPosition(Vector2D mousePos);


	UIManager();
	virtual ~UIManager();

	static UIManager* mspInstance;

	std::vector<UIElement*> mUIElements;
	Cursor* mCursor;
};