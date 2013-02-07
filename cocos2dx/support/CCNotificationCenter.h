/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Erawppa
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCNOTIFICATIONCENTER_H__
#define __CCNOTIFICATIONCENTER_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"

NS_CC_BEGIN

class CC_DLL CCNotificationCenter : public CCObject
{
public:
    /** CCNotificationCenter constructor */
    CCNotificationCenter();

    /** CCNotificationCenter destructor */
    ~CCNotificationCenter();
    
    /** Gets the single instance of CCNotificationCenter. */
    static CCNotificationCenter *sharedNotificationCenter(void);

    /** Destroys the single instance of CCNotificationCenter. */
    static void purgeNotificationCenter(void);

    /** @brief Adds an observer for the specified target.
     *  @param target The target which wants to observe notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    void addObserver(CCObject *target, 
                     SEL_NoteHandler selector,
                     const char *name,
                     CCObject *obj);

    /** @brief Removes the observer by the specified target and name.
     *  @param target The target of this notification.
     *  @param name The name of this notification. 
     */
    void removeObserver(CCObject *target,const char *name);
	void removeObserver(CCObject *target);
    
    /** @brief Registers one hander for script binding.
     *  @note Only supports Lua Binding now.
     *  @param handler The lua handler.
     */
    void registerScriptObserver(int handler);

    /** Unregisters script observer */
    void unregisterScriptObserver(void);
    
    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     */
    void postNotification(const char *name);

    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     *  @param object The extra parameter.
     */
    void postNotification(const char *name, CCObject *object);
    
	/** @brief Posts one notification event by name.
     *  @param name The name of this notification.
	 *  @param params The dictionary of parameters sent to each receiver.
     *  @param object The extra parameter.
     */
    void postNotification(const char *name, CCDictionary* params, CCObject *object);
	
    /** @brief Gets script handler.
     *  @note Only supports Lua Binding now.
     *  @return The script handle.
     */
    inline int getScriptHandler() { return m_scriptHandler; };
private:
    // internal functions

    // Check whether the observer exists by the specified target and name.
    bool observerExisted(CCObject *target,const char *name);
    
    // variables
    //
    CCArray *m_observers;
    int     m_scriptHandler;
};

class CC_DLL CCNotificationObserver : public CCObject
{
public:
    /** @brief CCNotificationObserver constructor
     *  @param target The target which wants to observer notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    CCNotificationObserver(CCObject *target, 
                           SEL_NoteHandler selector,
                           const char *name,
                           CCObject *obj);

    /** CCNotificationObserver destructor function */
    ~CCNotificationObserver();      
    
    /** Invokes the callback function of this observer */
	void performSelector(const char* noteName, CCDictionary* params);
	
private:
    CC_PROPERTY_READONLY(CCObject *, m_target, Target);
    CC_PROPERTY_READONLY(SEL_NoteHandler, m_selector, Selector);
    CC_PROPERTY_READONLY(char *, m_name, Name);
    CC_PROPERTY_READONLY(CCObject *, m_object, Object);
};

NS_CC_END

#endif//__CCNOTIFICATIONCENTER_H__