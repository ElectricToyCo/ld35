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
	
	class CharacterInspector : public fr::UIPopup
	{
		FRESH_DECLARE_CLASS( CharacterInspector, UIPopup );
	public:
		
		void inspectCharacter( SmartPtr< Character > character );
		void toggleCharacterInspection( SmartPtr< Character > character );

		virtual void hideWithDuration( TimeType duration, bool deleteWhenHidden = false, TimeType queueIfShowingWithDelay = -1.0 ) override;
		
	private:
		
		SmartPtr< Character > m_character;
		
	};
	
}

#endif
