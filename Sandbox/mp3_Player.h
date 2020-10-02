
/*
	-------------------------------------------------
	File:  MP3_Player
	-------------------------------------------------
	
	Description:
		Defines the mp3 player object.
	-------------------------------------------------
*/



#ifndef mp3_player_h
#define mp3_player_h

/*
	-------------------------------------------------
	Constant declarations
	-------------------------------------------------	
*/
		
	#define mp3_max_volume_level 10
	#define mp3_min_volume_level 1
		

/*
	-------------------------------------------------
	Type declarations
	-------------------------------------------------
*/

/*
	-------------------------------------------------
	Variable declarations
	-------------------------------------------------
*/


/*
	-------------------------------------------------
	Prototypes
	-------------------------------------------------
*/

/*
This class is for MP3_Player object.
*/

class MP3_Player 
{
/*
	-------------------------------------------------
	Constant declarations
	-------------------------------------------------	
*/



//
/*
	-------------------------------------------------
	Type declarations
	-------------------------------------------------
*/
	public:
		enum mp3_play_state_type 
		{
			INITIALIZING,
			STOPPED,
			PLAYING,	
			PAUSED
		};
/*
	-------------------------------------------------
	Variable declarations
	-------------------------------------------------
*/
	private:
		mp3_play_state_type 	m_state;
		int 						m_volume; // the current mp3 volume rng 1..10
												 // -1 = not initialized
		int						m_mp3_ser_volume; // the current mp3 serial volume  (i.e. 
														   // in units of mp3 volume +/- cmds
															// -1 = not initialized
		
/*
	-------------------------------------------------
	Prototypes
	-------------------------------------------------
*/
		
	public:
	/*
	-------------------------------------------------
	Function: MP3_Player
	-------------------------------------------------
	   Description:
		   Constuctor for MP3 Player.  

		Parameters: None
	-------------------------------------------------
	*/
	MP3_Player();
	
	/*
	-------------------------------------------------
	Function: Initialize
	-------------------------------------------------
	   Description:
			Initializes the MP3 player for operation.
		   Puts the player in the stopped state.
		   Initialize should be called before any other operations are performed
		Parameters
			volume  (in): The initial volume to set the player output to.
							  Range: 0 - 10 (0 is min, 10 is max volume)
	-------------------------------------------------
	*/
	void Initialize(unsigned int volume);
	
	/*
	-------------------------------------------------
	Function: Play
	-------------------------------------------------
	   Description:
	   	Start playing mp3 with the indicated file name.  
	   	File will continuously loop until stopped or paused

		Parameters
			mp3file  (in):  this is the Root name and is currently limited to "001" to "199"
								 mp3 is the assumed file extension.
	   Restrictions:  Currently no checking is done to determine if name is valid ("001" to "199")
	-------------------------------------------------
	*/
	void Play(char * mp3file_name);
	
	/*
	-------------------------------------------------
	Function: Stop
	-------------------------------------------------
	   Description:
			Stop playing the file that is currently playing.
		Parameters: None
			
	-------------------------------------------------
	*/
	void Stop();
	
	/*
	-------------------------------------------------
	Function: Pause
	-------------------------------------------------
	   Description:
			Pauses the currently playing mp3 file
		Parameters: None
			
	-------------------------------------------------
	*/
	void Pause();
	
	/*
	-------------------------------------------------
	Function: Resume_Play
	-------------------------------------------------
	   Description:
			Resumes playing a paused file.
			If the file is not paused this command has no effect.
		Parameters: None
			
	-------------------------------------------------
	*/
	void Resume_Play();
	
   /*
	-------------------------------------------------
	Function: Set_Volume
	-------------------------------------------------
	   Description:
			Resumes playing a paused file.
		Parameters:
			volume  (in): The volume to set the player output to.
							  Range: 1 - 10 (1 is min, 10 is max volume)
			
	-------------------------------------------------
	*/
	void Set_Volume(unsigned int volume);
	
};

#endif // mp3_player_h