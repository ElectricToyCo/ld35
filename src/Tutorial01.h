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
#include "PlayerConversationPanel.h"

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
			return distance( player().position(), m_playerStartPos ) > 1.5f * UNITS_PER_TILE;
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
	
	class TutorialStep01_03 : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_03, TutorialStep );
	public:
		
		virtual bool conditionCompleted() const override
		{
			return hud().isPlayerConversationPanelShowing();
		}
		
	};
	
	class TutorialStep01_04 : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_04, TutorialStep );
	public:
		
		virtual void begin( WeakPtr< World > world ) override
		{
			Super::begin( world );
			// TODO!!! Disable non-opinion conversations?
		}
		
		virtual bool conditionCompleted() const override
		{
			return hud().playerConversationPanel().chosenType() >= 0;
		}
		
	};
	
	class TutorialStep01_05 : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_05, TutorialStep );
	public:
		
		virtual bool conditionCompleted() const override
		{
			return hud().playerConversationPanel().opinionTopic() != TopicType::Undecided;
		}
		
	};
	
	class TutorialStep01_06 : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_06, TutorialStep );
	public:
		
		virtual bool conditionCompleted() const override
		{
			return hud().playerConversationPanel().opinionValue() != Value::Undecided;
		}
	};
	
	class TutorialStep01_Decision : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_Decision, TutorialStep );
	public:

		Value tiffanyValue() const
		{
			return world().characterAt( 1 )->valueForTopic( std::make_pair( TopicType::Sports, -1 )) ;
		}

		virtual size_t nextStep() const override
		{
			return tiffanyValue() >= Value::Like ? 7 : 8;
		}
		
		virtual bool conditionCompleted() const override
		{
			return true;
		}
	};
	
	class TutorialStep01_Correct : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_Correct, TutorialStep );
	public:
		
		virtual size_t nextStep() const override
		{
			return 9;
		}
		
		virtual bool conditionCompleted() const override
		{
			return age() > 4.0;
		}
	};
	
	class TutorialStep01_Incorrect : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_Incorrect, TutorialStep );
	public:
		
		virtual size_t nextStep() const override
		{
			return 3;
		}
		
		virtual bool conditionCompleted() const override
		{
			return hud().isPlayerConversationPanelShowing();
		}
		
	};
	
	class TutorialStep01_Done : public TutorialStep
	{
		FRESH_DECLARE_CLASS( TutorialStep01_Done, TutorialStep );
	public:
		
		virtual bool conditionCompleted() const override
		{
			return age() > 6.0;
		}
	};
	
	
}

#endif
