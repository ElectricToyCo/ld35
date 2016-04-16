//
//  CharacterController.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_CharacterController_h
#define FreshApp_CharacterController_h

#include "Essentials.h"
#include "FreshActorController.h"

namespace ld
{
	class Actor;
	
	class CharacterController : public fr::FreshActorController
	{
		FRESH_DECLARE_CLASS( CharacterController, FreshActorController );
	public:
	
		Actor& actor() const;
		
		virtual void update() override;
		
	private:
		
	};
	
}

#endif
