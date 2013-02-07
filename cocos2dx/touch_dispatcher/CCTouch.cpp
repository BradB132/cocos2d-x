/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

#include "support/CCPointExtension.h"
#include "CCTouch.h"
#include "CCDirector.h"

NS_CC_BEGIN

// returns the current touch location in screen coordinates
CCPoint CCTouch::getLocationInView() const 
{ 
    return m_point; 
}

// returns the current previous location in screen coordinates
CCPoint CCTouch::getPreviousLocationInView() const 
{ 
    return m_prevPoint; 
}

// returns the current touch location in OpenGL coordinates
CCPoint CCTouch::getLocation() const
{ 
    return CCDirector::sharedDirector()->convertToGL(m_point); 
}

// returns the previous touch location in OpenGL coordinates
CCPoint CCTouch::getPreviousLocation() const
{ 
    return CCDirector::sharedDirector()->convertToGL(m_prevPoint);  
}

// returns the delta position between the current location and the previous location in OpenGL coordinates
CCPoint CCTouch::getDelta() const
{     
    return ccpSub(getLocation(), getPreviousLocation()); 
}

//NoPL integration
NoPL_FunctionValue CCTouch::evaluateFunction(const char* functionName, const NoPL_FunctionValue* argv, unsigned int argc)
{
	NoPL_FunctionValue returnVal;
	returnVal.type = NoPL_DataType_Uninitialized;
	
	if(argc == 0)
	{
		if(!strcmp(functionName, "x"))
		{
			returnVal.numberValue = getLocation().x;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "y"))
		{
			returnVal.numberValue = getLocation().y;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "prevX"))
		{
			returnVal.numberValue = getPreviousLocation().x;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "prevY"))
		{
			returnVal.numberValue = getPreviousLocation().y;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "dx"))
		{
			returnVal.numberValue = getLocation().x - getPreviousLocation().x;
			returnVal.type = NoPL_DataType_Number;
		}
		else if(!strcmp(functionName, "dy"))
		{
			returnVal.numberValue = getLocation().y - getPreviousLocation().y;
			returnVal.type = NoPL_DataType_Number;
		}
	}
	
	if(returnVal.type == NoPL_DataType_Uninitialized)
		return CCObject::evaluateFunction(functionName, argv, argc);
	return returnVal;
}

NS_CC_END