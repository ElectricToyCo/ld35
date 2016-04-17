//
//  AppStage.cpp
//  ld35
//
//  Created by Jeff Wofford on 12/2/14.
//  Copyright (c) 2014 Jeff Wofford. All rights reserved.
//

#include "AppStage.h"
#include "SimpleButton.h"
#include "UIPopup.h"
#include "TextField.h"
using namespace fr;

namespace
{
	template< typename T >
	void use()
	{
		auto object = createObject< T >();		// TODO
	}
	
	void useStuff()
	{
		use< SimpleButton >();
		use< UIPopup >();
		use< ld::HUD >();
	}
}

namespace ld
{	
	FRESH_DEFINE_CLASS( AppStage )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( AppStage )
	
	HUD& AppStage::hud() const
	{
		return getExpectedDescendant< HUD >( *this );
	}
	
	void AppStage::onStageLoaded()
	{
		Super::onStageLoaded();
		
		if( name() == "It isn't this." )
		{
			useStuff();
		}
	}
}

