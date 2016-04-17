//
//  PlayerConversationPanel.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/17/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_PlayerConversationPanel_h
#define FreshApp_PlayerConversationPanel_h

#include "Essentials.h"
#include "EventKeyboard.h"

namespace ld
{
	class Character;
	
	class PlayerConversationPanel : public fr::UIPopup
	{
		FRESH_DECLARE_CLASS( PlayerConversationPanel, UIPopup );
	public:
		
		void beginPlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character );
		void togglePlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character );
		
		virtual void onAddedToStage() override;

	protected:
		
		void chooseConversationType( int type );
		
	private:
		
		SmartPtr< Character > m_player;
		SmartPtr< Character > m_conversant;
		
		int m_chosenType = -1;

		FRESH_DECLARE_CALLBACK( PlayerConversationPanel, onStageKeyUp, fr::EventKeyboard );

		FRESH_DECLARE_CALLBACK( PlayerConversationPanel, onConversationTypeChosen, fr::EventTouch );
		FRESH_DECLARE_CALLBACK( PlayerConversationPanel, onConversationTypeOpinionTopicChosen, fr::EventTouch );
		FRESH_DECLARE_CALLBACK( PlayerConversationPanel, onConversationTypeOpinionValueChosen, fr::EventTouch );
		FRESH_DECLARE_CALLBACK( PlayerConversationPanel, onConversationTypeSendCharacterChosen, fr::EventTouch );
		FRESH_DECLARE_CALLBACK( PlayerConversationPanel, onConversationTypeSendTopicChosen, fr::EventTouch );

	};
	
}

#endif
