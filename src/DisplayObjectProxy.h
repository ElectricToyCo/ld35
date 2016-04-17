//
//  DisplayObjectProxy.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_DisplayObjectProxy_h
#define FreshApp_DisplayObjectProxy_h

#include "Essentials.h"

namespace ld
{
	class DisplayObjectProxy : public fr::Sprite
	{
		FRESH_DECLARE_CLASS( DisplayObjectProxy, Sprite );
	public:
		
		SYNTHESIZE( fr::DisplayObject::wptr, object )

		virtual void drawChildren( TimeType relativeFrameTime, RenderInjector* injector );
	private:
		
		VAR( fr::DisplayObject::wptr, m_object );
		
	};
	
}

#endif
