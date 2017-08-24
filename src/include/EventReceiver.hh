#ifndef EVENT_RECEIVER_HH
#define EVENT_RECEIVER_HH

#include <irrlicht.h>

class EventReceiver : public irr::IEventReceiver
{
public:
    virtual bool OnEvent(const irr::SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    	{
                if ((KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown))
    	      KeyReleased[event.KeyInput.Key] = false;
    	    else
    	      KeyReleased[event.KeyInput.Key] = true;
    	}
        else if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
        {
            _joystickState = event.JoystickEvent;
        }

        return false;
    }

    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    virtual bool IsKeyReleased(irr::EKEY_CODE keyCode) const
    {
      return KeyReleased[keyCode];
    }

    irr::SEvent::SJoystickEvent const& getJoystickState(void) const
    {
        return (_joystickState);
    }

   	EventReceiver()
    {
        for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
        for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            KeyReleased[i] = true;
    }

private:
  bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  bool KeyReleased[irr::KEY_KEY_CODES_COUNT];
  irr::SEvent::SJoystickEvent     _joystickState;

};

#endif // EVENT_RECEIVER_HH
