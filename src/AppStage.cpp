//
//  AppStage.cpp
//  ld35
//
//  Created by Jeff Wofford on 12/2/14.
//  Copyright (c) 2014 Jeff Wofford. All rights reserved.
//

#include "AppStage.h"
#include "World.h"
#include "SimpleButton.h"
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
	DEFINE_VAR( AppStage, std::vector< ClassInfo::cptr >, m_worldClasses );
	DEFINE_DVAR( AppStage, size_t, m_currentWorldIndex );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( AppStage )
	
	HUD& AppStage::hud() const
	{
		return getExpectedDescendant< HUD >( *this );
	}

	void AppStage::update()
	{
		Super::update();
	
		if( m_pendingWorldIndex != -1 )
		{
			if( worldHost().isFullyHidden() )
			{
				onWorldTransitionDone();
			}
		}
	}
	
	void AppStage::onStageLoaded()
	{
		if( name() == "It isn't this." )
		{
			useStuff();
		}

		Super::onStageLoaded();
		
		beginWorld( m_currentWorldIndex );
	}
	
	void AppStage::onWorldFinished( Mission::Status result )
	{
		if( result == Mission::Status::Failed )
		{
			// HUD. TODO
			
			restartWorldWithTransition();
		}
		else
		{
			nextWorldWithTransition();
		}
	}
	
	UIPopup& AppStage::worldHost() const
	{
		auto popup = getChildAt( 0 )->as< UIPopup >();
		ASSERT( popup );
		return *popup;
	}
	
	void AppStage::beginWorldWithTransition( size_t world )
	{
		ASSERT( world < m_worldClasses.size() );
		
		m_pendingWorldIndex = world;
		worldHost().hide();
	}
	
	void AppStage::nextWorldWithTransition()
	{
		const auto nextWorldIndex = m_currentWorldIndex + 1;
		if( nextWorldIndex < m_worldClasses.size() )
		{
			beginWorldWithTransition( nextWorldIndex );
		}
		else
		{
			endCampaign();
		}
	}
	
	void AppStage::restartWorldWithTransition()
	{
		beginWorldWithTransition( m_currentWorldIndex );
	}
	
	void AppStage::onWorldTransitionDone()
	{
		beginWorld( m_pendingWorldIndex );
		m_pendingWorldIndex = -1;
	}
	
	void AppStage::beginWorld( size_t world )
	{
		REQUIRES( world < m_worldClasses.size() );
		
		if( m_world )
		{
			worldHost().host()->removeChild( m_world );
			m_world = nullptr;
		}
		
		const auto worldClass = m_worldClasses[ world ];
		ASSERT( worldClass );
		
		m_world = createObject< World >( *worldClass );
		worldHost().host()->addChild( m_world );
		worldHost().show();
	}

	void AppStage::endCampaign()
	{
		// TODO!!!
		beginWorldWithTransition( 0 );
	}
}

