//
//  PlayerController.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_PlayerController_h
#define FreshApp_PlayerController_h

#include "Essentials.h"
#include "FreshPlayerController.h"

namespace ld
{
	class Character;
	
	class PlayerController : public fr::FreshPlayerController
	{
		FRESH_DECLARE_CLASS( PlayerController, fr::FreshPlayerController );
	public:
		
		Character& character() const;
		
		bool onAddressedBy( SmartPtr< Character > other );
		void onConversationEnding();

	private:
		
	};
	
}

#endif
