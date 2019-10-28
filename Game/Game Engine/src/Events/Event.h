#pragma once

enum class EventType
{
	None = 0,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	Collision
};




class Event
{
public:
	bool Handled = false;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;

};


class KeyEvent : public Event
{
public:
	int GetKeyCode() const { return keyCode;}
protected:
	KeyEvent(int keycode)
		:keyCode(keycode)
	{
	}
	int keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode)
		:KeyEvent(keycode)
	{

	}

	EventType GetEventType() { return EventType::KeyPressed; }
};