////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2010 Marco Antognini (antognini.marco@gmail.com), 
//                         Laurent Gomila (laurent.gom@gmail.com), 
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_WINDOWIMPLCOCOA_HPP
#define SFML_WINDOWIMPLCOCOA_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowImpl.hpp>

////////////////////////////////////////////////////////////
/// Predefine OBJC classes
////////////////////////////////////////////////////////////
#ifdef __OBJC__

#import <SFML/Window/OSX/WindowImplDelegateProtocol.h>
typedef id<WindowImplDelegateProtocol,NSObject> WindowImplDelegateRef;

@class NSAutoreleasePool;
typedef NSAutoreleasePool* NSAutoreleasePoolRef;

@class NSOpenGLContext;
typedef NSOpenGLContext* NSOpenGLContextRef;

#else // If C++

typedef void* WindowImplDelegateRef;
typedef void* NSAutoreleasePoolRef;
typedef void* NSOpenGLContextRef;

#endif

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Mac OS X (Cocoa) implementation of WindowImpl
///
////////////////////////////////////////////////////////////
class WindowImplCocoa : public WindowImpl
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Construct the window implementation from an existing control
	///
	/// \param handle Platform-specific handle of the control
	///
	////////////////////////////////////////////////////////////
	WindowImplCocoa(WindowHandle handle);
	
	////////////////////////////////////////////////////////////
	/// \brief Create the window implementation
	///
	/// \param mode  Video mode to use
	/// \param title Title of the window
	/// \param style Window style (resizable, fixed, or fullscren)
	///
	////////////////////////////////////////////////////////////
	WindowImplCocoa(VideoMode mode, const std::string& title, unsigned long style);
	
	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~WindowImplCocoa();
	
	/// Events
	void WindowClosed(void);
	void WindowResized(unsigned int width, unsigned int height);
	void WindowLostFocus(void);
	void WindowGainedFocus(void);
	void MouseDownAt(Mouse::Button button, int x, int y);
	void MouseUpAt(Mouse::Button button, int x, int y);
	void MouseMovedAt(int x, int y);
	void MouseWheelScrolledAt(float delta, int x, int y);
	void MouseMovedIn(void);
	void MouseMovedOut(void);
	void KeyDown(unsigned short keycode, unsigned int modifierFlags);
	void KeyUp(unsigned short keycode, unsigned int modifierFlags);
	void TextEntred(Uint32 charcode);
	
	static Key::Code NSKeyCodeToSFMLKeyCode(unsigned short rawchar);
	
	////////////////////////////////////////////////////////////
	/// 
	////////////////////////////////////////////////////////////
	void ApplyContext(NSOpenGLContextRef context) const;
	
private:
	////////////////////////////////////////////////////////////
	/// \brief Process incoming events from the operating system
	///
	/// \param block Use true to block the thread until an event arrives
	///
	////////////////////////////////////////////////////////////
	virtual void ProcessEvents(bool block);
	
	////////////////////////////////////////////////////////////
	/// \brief Get the OS-specific handle of the window
	///
	/// \return Handle of the window
	///
	////////////////////////////////////////////////////////////
	virtual WindowHandle GetSystemHandle() const;
	
	////////////////////////////////////////////////////////////
	/// \brief Show or hide the mouse cursor
	///
	/// \param show True to show, false to hide
	///
	////////////////////////////////////////////////////////////
	virtual void ShowMouseCursor(bool show);
	
	////////////////////////////////////////////////////////////
	/// \brief Change the position of the mouse cursor
	///
	/// \param x Left coordinate of the cursor, relative to the window
	/// \param y Top coordinate of the cursor, relative to the window
	///
	////////////////////////////////////////////////////////////
	virtual void SetCursorPosition(unsigned int x, unsigned int y);
	
	////////////////////////////////////////////////////////////
	/// \brief Change the position of the window on screen
	///
	/// \param x Left position
	/// \param y Top position
	///
	////////////////////////////////////////////////////////////
	virtual void SetPosition(int x, int y);
	
	////////////////////////////////////////////////////////////
	/// \brief Change the size of the rendering region of the window
	///
	/// \param width  New width
	/// \param height New height
	///
	////////////////////////////////////////////////////////////
	virtual void SetSize(unsigned int width, unsigned int height);
	
	////////////////////////////////////////////////////////////
	/// \brief Change the title of the window
	///
	/// \param title New title
	///
	////////////////////////////////////////////////////////////
	virtual void SetTitle(const std::string& title);
	
	////////////////////////////////////////////////////////////
	/// \brief Show or hide the window
	///
	/// \param show True to show, false to hide
	///
	////////////////////////////////////////////////////////////
	virtual void Show(bool show);
	
	////////////////////////////////////////////////////////////
	/// \brief Enable or disable automatic key-repeat
	///
	/// \param enabled True to enable, false to disable
	///
	////////////////////////////////////////////////////////////
	virtual void EnableKeyRepeat(bool enabled);
	
	////////////////////////////////////////////////////////////
	/// \brief Change the window's icon
	///
	/// \param width  Icon's width, in pixels
	/// \param height Icon's height, in pixels
	/// \param pixels Pointer to the pixels in memory, format must be RGBA 32 bits
	///
	////////////////////////////////////////////////////////////
	virtual void SetIcon(unsigned int width, unsigned int height, const Uint8* pixels);
	
	////////////////////////////////////////////////////////////
	/// \brief Construct the pool after ensuring NSApp is valid.
	////////////////////////////////////////////////////////////
	void SetUpPoolAndApplication(void);
	
	////////////////////////////////////////////////////////////
	/// \brief Change the type of the current process to become a full GUI app.
	////////////////////////////////////////////////////////////
	static void SetUpProcessAsApplication(void);
	
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	WindowImplDelegateRef myDelegate; ///< Implementation in Obj-C.
	NSAutoreleasePoolRef  myPool;			///< Memory manager for this class.
};
	
} // namespace priv
	
} // namespace sf


#endif // SFML_WINDOWIMPLCOCOA_HPP
