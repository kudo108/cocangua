#ifndef _MUSIC_HELPER_H_
#define _MUSIC_HELPER_H_

#define BG_MUSIC 1
#define GP_MUSIC 2

class MusicHelper
{
public:
	static void setVolume(int _v);
	static void setIsBgMusicPlaying(bool _bg);
	static void setIsGameplayMusicPlaying(bool _gp);
	static void setIsSFXEffectPlaying(bool _SFX);
	static void setIdDice(int _id);
	static void setIdButton(int _id);
	static void setIdGameOver(int _id);
	static void setIdGameWin(int _id);
	static void setHasTurnOffMusic(bool _music);

	static bool getIsBgMusicPlaying();
	static bool getIsGameplayMusicPlaying();
	static bool getIsSFXEffectPlaying();
	static bool getHasTurnOffMusic();
	static int getVolume();
	static int getIdDice();
	static int getIdButton();
	static int getIdGameOver();
	static int getIdGameWin();

	static void playBackgroundMusic(const char* _bgMusic, int type);
	static void stopBackgroundMusic();
	static void pauseBackgroundMusic();
	static void resumeBackgroundMusic();
	static int playEffect(const char* _sfx, bool loop);
	static void stopEffect(int id);
	static void stopAllEffect();

	const static char* backgroundMusic;
	const static char* gameplayMusic;
	const static char* sfxButton;
	const static char* sfxDice;
	const static char* sfxGameOver;
	const static char* sfxGameWin;
	const static char* sfxFireworks;

	const static char* animal0_die_sound;
	const static char* animal1_die_sound;
	const static char* animal2_die_sound;
	const static char* animal3_die_sound;
	
	const static char* animal0_move_sound;
	const static char* animal1_move_sound;
	const static char* animal2_move_sound;
	const static char* animal3_move_sound;

	const static char* animal0_select_sound;
	const static char* animal1_select_sound;
	const static char* animal2_select_sound;
	const static char* animal3_select_sound;

	const static char* animal_born_sound;
	const static char* animal_finish_sound;
	const static char* animal_kick_sound;

	const static char* btSkip;
	const static char* btWrong;
	const static char* moreTurn;

private:
	static bool isBgMusicPlaying;
	static bool isGameplayMusicPlaying;
	static bool hasTurnOffMusic;
	static bool isSFXEffectPlaying;
	static int volume;
	static int idDice;
	static int idButton;
	static int idGameOver;
	static int idGameWin;


};

#endif