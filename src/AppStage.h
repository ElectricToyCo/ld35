//
//  AppStage.h
//  ld35
//
//  Created by Jeff Wofford on 12/2/14.
//  Copyright (c) 2014 Jeff Wofford. All rights reserved.
//

#ifndef ld35_AppStage_h
#define ld35_AppStage_h

#include "Essentials.h"
#include "Stage.h"
#include "HUD.h"

namespace ld
{
	
	class AppStage : public fr::Stage
	{
		FRESH_DECLARE_CLASS( AppStage, Stage );
	public:
		
		HUD& hud() const;
		
	private:
		
	};
	
}

#endif
