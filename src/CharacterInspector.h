//
//  CharacterInspector.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_CharacterInspector_h
#define FreshApp_CharacterInspector_h

#include "Essentials.h"

namespace ld
{
	class Character;
	
	class CharacterInspector : public fr::DisplayObjectContainer
	{
		FRESH_DECLARE_CLASS( CharacterInspector, DisplayObjectContainer );
	public:
		
		void inspectCharacter( SmartPtr< Character > character );
		
	private:
		
		SmartPtr< Character > m_character;
		
	};
	
}

#endif
