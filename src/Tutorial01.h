//
//  Tutorial01.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/17/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_Tutorial01_h
#define FreshApp_Tutorial01_h

#include "Essentials.h"
#include "TutorialManager.h"
#include "World.h"
#include "HUD.h"
#include "Character.h"

namespace ld
{
	
	class TutorialStep01_01 : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_01, TutorialStep );
	public:
		
		virtual void begin( WeakPtr< World > world ) override
		{
			Super::begin( world );
			
			m_playerStartPos = player().position();
		}
		
		virtual bool conditionCompleted() const override
		{
			return distance( player().position(), m_playerStartPos ) > 2.0f * UNITS_PER_TILE;
		}
		
	private:
		
		vec2 m_playerStartPos;
		
	};

	class TutorialStep01_02 : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_02, TutorialStep );
	public:
		
		virtual bool conditionCompleted() const override
		{
			return hud().isInspectorShowing();
		}
		
	};

}

#endif
