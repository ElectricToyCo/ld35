//
//  TutorialManager.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/17/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "TutorialManager.h"
#include "World.h"
#include "HUD.h"
#include "Character.h"
#include "AppStage.h"
using namespace fr;

namespace ld
{
	FRESH_DEFINE_CLASS( TutorialStep )
	DEFINE_VAR( TutorialStep, WeakPtr< World >, m_world );
	DEFINE_DVAR( TutorialStep, TimeType, m_preDelay );
	DEFINE_DVAR( TutorialStep, TimeType, m_postDelay );
	DEFINE_VAR( TutorialStep, std::string, m_message );
	DEFINE_DVAR( TutorialStep, TimeType, m_startTime );
	DEFINE_DVAR( TutorialStep, TimeType, m_completionTime );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( TutorialStep )

	World& TutorialStep::world() const
	{
		ASSERT( m_world );
		return *m_world;
	}

	AppStage& TutorialStep::ldStage() const
	{
		return world().ldStage();
	}
	
	HUD& TutorialStep::hud() const
	{
		return world().ldStage().hud();
	}
	
	Character& TutorialStep::player() const
	{
		return world().player();
	}
	
	TimeType TutorialStep::now() const
	{
		return world().time();
	}
	
	bool TutorialStep::completed() const
	{
		return isMarkedCompleted() && now() >= m_completionTime + m_postDelay;
	}
	
	bool TutorialStep::isMarkedCompleted() const
	{
		return m_completionTime >= 0.0;
	}
	
	void TutorialStep::markCompleted()
	{
		if( !isMarkedCompleted() )
		{
			m_completionTime = now();
		}
	}
	
	bool TutorialStep::conditionCompleted() const
	{
		// Override in subclasses.
		return false;
	}
	
	void TutorialStep::begin( WeakPtr< World > world )
	{
		REQUIRES( world );
		m_world = world;

		m_startTime = now();
		m_completionTime = -1;
	}

	void TutorialStep::reallyBegin()
	{
		// Override in subclasses.
		if( !m_message.empty() )
		{
			showMessage( m_message );
		}
	}
	
	void TutorialStep::update()
	{
		if( !isMarkedCompleted() )
		{
			if( conditionCompleted() )
			{
				markCompleted();
				end();
			}
			else if( m_startTime >= 0 && now() >= m_startTime + m_preDelay )
			{
				m_startTime = -1.0;
				reallyBegin();
			}
		}
	}
	
	void TutorialStep::end()
	{
		hideMessage();
		// Override in subclasses.
	}

	
	void TutorialStep::showMessage( const std::string& message )
	{
		world().ldStage().hud().showTutorialMessage( message );
	}
	
	void TutorialStep::hideMessage()
	{
		world().ldStage().hud().hideTutorialMessage();
	}

	//////////////////////////////////////////////////////////////////

	FRESH_DEFINE_CLASS( TutorialManager )
	DEFINE_VAR( TutorialManager, WeakPtr< World >, m_world );
	DEFINE_DVAR( TutorialManager, size_t, m_currentStep );
	DEFINE_VAR( TutorialManager, std::vector< TutorialStep::ptr >, m_steps );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( TutorialManager )

	World& TutorialManager::world() const
	{
		ASSERT( m_world );
		return *m_world;
	}

	void TutorialManager::setup( WeakPtr< World > world )
	{
		REQUIRES( world );
		m_world = world;
		beginStep( 0 );
	}
	
	void TutorialManager::update()
	{
		if( auto currentStep = m_currentStep < m_steps.size() ? m_steps[ m_currentStep ] : TutorialStep::ptr{} )
		{
			currentStep->update();
			
			if( currentStep->completed() )
			{
				advanceStep();
			}
		}
	}
	
	bool TutorialManager::completed() const
	{
		return m_currentStep >= m_steps.size();
	}
	
	void TutorialManager::beginStep( size_t step )
	{
		m_currentStep = step;
		
		if( completed() )
		{
			return;
		}
		
		// Show step message if there is one.
		//
		if( m_currentStep < m_steps.size() )
		{
			auto step = m_steps[ m_currentStep ];
			ASSERT( step );
			step->begin( m_world );
		}
		
		onStepBeginning( m_currentStep );
	}
	
	void TutorialManager::onStepBeginning( size_t step )
	{
		// Override in subclasses.
	}
	
	void TutorialManager::endStep( size_t step )
	{
		if( step < m_steps.size() )
		{
			m_steps[ step ]->end();
		}
	}
	
	void TutorialManager::advanceStep()
	{
		gotoStep( m_currentStep + 1 );
	}
	
	void TutorialManager::gotoStep( size_t step )
	{
		endStep( m_currentStep );
		beginStep( step );
	}
}

