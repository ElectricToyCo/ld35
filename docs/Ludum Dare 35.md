Ludum Dare 35
=============

Theme: Shapeshift

Strengths of the theme:
	Shape
	change
	doppelganger
	metamorphosis
	transition
	shape in the geometric sense
	shape - animal form
	shape - clay, molding
	shape - life, time of life
	shift - the keyboard key
	shift - change
	shift - drift
	shift - adjustment

Directions:
	Abstract, geometric
	sci-fi/fantasy, doppelganger
	Shape a shift key
	shape as a verb: shape a "shift" (noun?)
	Shape in geometric but looser forms: 
		military command (parade)
		body shape
		clay
	soft body dynamics

sitting down for a think

I. 		Discrete shapes that move (e.g. shape chess)
II. 	Geometric shape(s) that change(s)
		A.	Discretely, e.g. player triangle becomes square becomes circle etc.
		B.	Free-form
			1.	Slicing
			2.	Drawing
			3.	Soft body
			4.	...
III.	Doppelgangers
		A.	Werewolf
		B.	Whatever
IV.		Shapes in a more real-life setting
		A.	Cloud painter
		B.	Home designer
		C.	Constellations
		D.	Body
		E.	Mountain
		F.	Sculpture
		G.	Pottery
        H.  Snow
        I.  Bicycle/Car
        J.  Face

Sitting down for a think (8:33PM)
Grabbing coffee (8:54PM)
Back from coffee (9:06PM). Who thought of this stupid theme?

* Asteroid racer/chaser
* Luftrausers-style game with cloud obscurations
* Soft body/inflation platformer

What about more story based?
        ...more text based?

Social engineer doppelganger
Motorcycle designer

Designing social engineering and motorcycle games (9:50pm)

Going to the store to get eggs for my wife. (10:01pm)
Back. Liking the social engineering game. Needs lots of design though. (10:34pm)

EMMA: TEEN DOPPELGANGER

Tasks
-----

Characters (8)
    Animations
        Idle    (+Work/sleep?)
        Walk
        Talk
    Close-ups
        Facial expressions
            Love
            Like
            Neutral
            Dislike
            Hate
            Panic
    Behaviors
        Wander
        Sleep/Work/Idle?
        Talk
            Choose who to talk to
            Choose conversation type
            Choose topic/subject
        Avoid
        Panic
    Agendas (antagonist characters)
        Desired mission
    Mental Model

Non-Character Topics (Art)
    Food (apple)
    Sports (soccer ball)
    Music (violin; guitar)

UI
    Character inspector
    Conversation type choice
    Talking choice - topical
    Talking choice - query
    Talking choice - directive (You should talk about <topic> with <person>.)
    3rd-party conversation display
    Mission reminder display
    Tutorial elements
    Mission introduction
    Mission complete
    Logo
    Intro/Tutorial text
    Doppelganger transform selection
    Overall relationship overlay?

Audio
    Conversation amplification
    Footsteps
    Environment ambient
    UI button clicks
    Doppelganger transform
    Music

Tile-based environment with pathfinding
    Floors
    Walls
    Furniture/Props (plants etc.)

Mission sequence
    Maybe 6–8 missions
    Convince liking character to like a topic
    Convince a disliking character to like you by talking about a shared topic, then like a topic
    Convince a disliking character to like a topic by getting a character they like to talk to them
    Convince a liking character to like another character by getting them to talk about something they both like
    Use shapeshifting to become a character that can do what you can't do otherwise
    Use more than one character to influence a character doubly
    ... and so on with greater levels of indirection (i.e. influence a character to influence a character to influence the target character, through more than one channel, sometimes foiled by an antithesis character or characters)

Walking around to think and wake up (11:12pm)

# Task sequence
##   First playable
-   Basic environment with empty/solid tile designations, no art
-   Basic character; possibly prototype art, but at most one character
-   Character pathfinding, wandering
-   Player control (arrow keys/WASD)
-   Player collision
-   Begin conversation (space bar?)
        Choose type
        Topical:
            choose topic, value
        Query:
            choose topic
        Directive
            choose object character, topic
-   Character psychology        
-   Character inspector   (useful for debugging)      
-   Relationships overlay (useful for debugging)
-   (Mission reminder)

##   Expansion
-   Mission completion
-   Shapeshifting
-   Character avoidance behavior
-   Character panic
-   Character art
-   Issue art
-   Environment art
-   Music
-   Overall game sequence
-   Mission sequence
-   Tutorials
-   SFX


4 AM. Taking a little break.

5:10 AM. Not a bad stopping point. Time to sleep.

9:25 AM Saturday. Up!

4:20 PM Saturday. Time for a break.

5:04 PM. Back.

1:05 AM Sunday morning. To sleep, perchance to dream.

7:37 AM Sunday morning. Up and at 'em. Concerned about time.

# Tutorial Sequence

## Intro Text

IntroText "Your name is EMMA. You're a not-particularly popular girl at a not-particularly interesting school. But you have a little secret: you're a SHAPESHIFTER. You can take on the form of your fellow students.\n\nAnd this is handy, because all they ever do is talk, talk, talk about what they LOVE and what they HATE. Sometimes they LOVE the wrong things; sometimes they HATE the wrong things. But by SHAPESHIFTING, you can join in the conversation and CHANGE THEIR MINDS.\n\nInfluencing people to see things (and each other!) the way YOU want them to see them: THAT is your special gift."

TutorialPlayerCharacter "This is Emma. Use WASD to move."

TutorialInspection "This is Tiffany. Get close to her and hit SPACE to see what she's thinking."

TutorialMission "Tiffany is indifferent to SPORTS. That's too bad. You should help her appreciate SPORTS.\n\nHit the Z key to talk to Tiffany."

TutorialTalk "Pick the SPORTS topic."

TutorialValue "Tell Tiffany you LOVE this topic."

TutorialCorrectResult "You just changed Tiffany's opinion! Because Tiffany LIKES you, she listened to what you said about SPORTS and now LIKES them too."

TutorialIncorrectResult "Oops. You need to tell Tiffany you LOVE SPORTS. Hit the Z key to talk to her again."

8:44 AM Sunday Time for Church!

10:34 AM Back to work

11:51 AM Designing the big one: The Player Conversation Interface