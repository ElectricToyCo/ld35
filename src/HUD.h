//
//  HUD.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_HUD_h
#define FreshApp_HUD_h

#include "Essentials.h"

namespace ld
{
	class Character;
	class PlayerConversationPanel;
	
	class HUD : public fr::MovieClip
	{
		FRESH_DECLARE_CLASS( HUD, MovieClip );
	public:
		
		void inspectCharacter( SmartPtr< Character > character );
		void toggleCharacterInspection( SmartPtr< Character > character );
		bool isInspectorShowing() const;
		
		void showTutorialMessage( const std::string& message );
		void hideTutorialMessage();

		PlayerConversationPanel& playerConversationPanel() const;
		
		bool isPlayerConversationPanelShowing() const;
		void beginPlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character );
		void togglePlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character );
		
		void announceMission( const std::string& heading, const std::string& message );
	};
	
}

#endif
