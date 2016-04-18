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
#include "Mission.h"
#include "HUD.h"

namespace ld
{
	class World;
	
	class AppStage : public fr::Stage
	{
		FRESH_DECLARE_CLASS( AppStage, Stage );
	public:
		
		HUD& hud() const;
		
		virtual void update() override;
		virtual void onStageLoaded() override;
		
		void onWorldFinished( Mission::Status result );
		
		virtual void onTouchBegin( const fr::EventTouch& event ) override;
		virtual void onKeyUp( const fr::EventKeyboard& event ) override;
		
	protected:
		
		void maybeAdvanceIntro();
		
		fr::UIPopup& worldHost() const;
		
		void beginWorldWithTransition( size_t world );
		void nextWorldWithTransition();
		void restartWorldWithTransition();

		void onWorldTransitionDone();
		
		void beginWorld( size_t world );

		void endCampaign();
		
	private:
		
		VAR( std::vector< ClassInfo::cptr >, m_worldClasses );
		DVAR( size_t, m_currentWorldIndex, 0 );

		size_t m_introStep = 0;
		
		size_t m_pendingWorldIndex = -1;
		
		SmartPtr< World > m_world;
		
	};
	
}

#endif
