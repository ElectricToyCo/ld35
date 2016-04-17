//
//  DisplayObjectProxy.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "DisplayObjectProxy.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( DisplayObjectProxy )
	DEFINE_VAR( DisplayObjectProxy, fr::DisplayObject::wptr, m_object );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( DisplayObjectProxy )
	
	void DisplayObjectProxy::drawChildren( TimeType relativeFrameTime, RenderInjector* injector )
	{
		if( m_object )
		{
			m_object->draw( relativeFrameTime, injector );
		}
		
		Super::drawChildren( relativeFrameTime, injector );
	}
	
}

