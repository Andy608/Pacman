#include "AssetManager.h"

AssetManager::AssetManager(SettingsFile& mainSettingsFile) :
	mMainSettingsFile(mainSettingsFile),
	mIsLoaded(false)
{

}

GraphicsBuffer* AssetManager::getBuffer(std::string key) const
{
	try
	{
		return mBufferContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Sprite* AssetManager::getSprite(std::string key) const
{
	try
	{
		return mSpriteContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

SpriteSheet* AssetManager::getSpriteSheet(std::string key) const
{
	try
	{
		return mSpriteSheetContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

float* AssetManager::getValue(std::string key) const
{
	try
	{
		return mValueContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Color* AssetManager::getColor(std::string key) const
{
	try
	{
		return mColorContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Sound* AssetManager::getSound(std::string key) const
{
	try
	{
		return mSoundContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Font* AssetManager::getFont(std::string key) const
{
	try
	{
		return mFontContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Vector2D* AssetManager::getVector2D(std::string key) const
{
	try
	{
		return mVector2DContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

bool AssetManager::loadAssets()
{
	bool success;

	if (!mIsLoaded)
	{
		try
		{
			loadValues();
			loadBuffers();
			loadSprites();
			loadSpriteSheets();
			loadColors();
			loadSounds();
			loadFonts();
			loadVector2Ds();
			success = true;
		}
		catch (const std::exception& e)
		{
			success = false;
			std::cout << "Unable to load asset from file. Error: " << e.what() << std::endl;
		}

		if (success)
		{
			mIsLoaded = true;
		}
	}

	return success;
}

void AssetManager::loadBuffers()
{
	mBufferContainer.addAsset("level_map", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("level_map_buffer")));
	mBufferContainer.addAsset("player_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("player_buffer")));
	mBufferContainer.addAsset("candy_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("candy_buffer")));
	mBufferContainer.addAsset("coin_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("coin_buffer")));
	
	mBufferContainer.addAsset("enemy_attack_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("enemy_attack_buffer")));
	mBufferContainer.addAsset("enemy_flee_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("enemy_flee_buffer")));
	mBufferContainer.addAsset("enemy_idle_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("enemy_idle_buffer")));

	mBufferContainer.addAsset("background_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("background_buffer")));
}

void AssetManager::loadSprites()
{
	mSpriteContainer.addAsset("player_sprite", new Sprite(*mBufferContainer.getAsset("player_buffer")));
	mSpriteContainer.addAsset("candy_sprite", new Sprite(*mBufferContainer.getAsset("candy_buffer")));
	mSpriteContainer.addAsset("coin_sprite", new Sprite(*mBufferContainer.getAsset("coin_buffer")));
	
	mSpriteContainer.addAsset("enemy_attack_sprite", new Sprite(*mBufferContainer.getAsset("enemy_attack_buffer")));
	mSpriteContainer.addAsset("enemy_flee_sprite", new Sprite(*mBufferContainer.getAsset("enemy_flee_buffer")));
	mSpriteContainer.addAsset("enemy_idle_sprite", new Sprite(*mBufferContainer.getAsset("enemy_idle_buffer")));
}

void AssetManager::loadSpriteSheets() {}

void AssetManager::loadValues()
{
	mValueContainer.addAsset("eat_enemy_score", new float(std::stof(mMainSettingsFile.getSettingFromKey("eat_enemy_score"))));
	mValueContainer.addAsset("eat_candy_score", new float(std::stof(mMainSettingsFile.getSettingFromKey("eat_candy_score"))));
	mValueContainer.addAsset("eat_coin_score", new float(std::stof(mMainSettingsFile.getSettingFromKey("eat_coin_score"))));

	mValueContainer.addAsset("enemy_respawn_time", new float(std::stof(mMainSettingsFile.getSettingFromKey("enemy_respawn_time"))));
	mValueContainer.addAsset("enemy_flee_time", new float(std::stof(mMainSettingsFile.getSettingFromKey("enemy_flee_time"))));

	mValueContainer.addAsset("title_color_r", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_color_r"))));
	mValueContainer.addAsset("title_color_g", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_color_g"))));
	mValueContainer.addAsset("title_color_b", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_color_b"))));

	mValueContainer.addAsset("text_color_r", new float(std::stof(mMainSettingsFile.getSettingFromKey("text_color_r"))));
	mValueContainer.addAsset("text_color_g", new float(std::stof(mMainSettingsFile.getSettingFromKey("text_color_g"))));
	mValueContainer.addAsset("text_color_b", new float(std::stof(mMainSettingsFile.getSettingFromKey("text_color_b"))));

	mValueContainer.addAsset("button_press_color_r", new float(std::stof(mMainSettingsFile.getSettingFromKey("button_press_color_r"))));
	mValueContainer.addAsset("button_press_color_g", new float(std::stof(mMainSettingsFile.getSettingFromKey("button_press_color_g"))));
	mValueContainer.addAsset("button_press_color_b", new float(std::stof(mMainSettingsFile.getSettingFromKey("button_press_color_b"))));

	mValueContainer.addAsset("title_font_size", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_font_size"))));
	mValueContainer.addAsset("subtitle_font_size", new float(std::stof(mMainSettingsFile.getSettingFromKey("subtitle_font_size"))));
	mValueContainer.addAsset("gui_font_size", new float(std::stof(mMainSettingsFile.getSettingFromKey("gui_font_size"))));

	mValueContainer.addAsset("title_scene_menu_title_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_title_y"))));
	mValueContainer.addAsset("title_scene_menu_subtitle_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_subtitle_y"))));
	mValueContainer.addAsset("title_scene_menu_start_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_start_y"))));
	mValueContainer.addAsset("title_scene_menu_options_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_options_y"))));
	mValueContainer.addAsset("title_scene_menu_exit_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_exit_y"))));

	mValueContainer.addAsset("options_scene_menu_title_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_title_y"))));
	mValueContainer.addAsset("options_scene_menu_back_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_back_y"))));
	mValueContainer.addAsset("options_scene_menu_sound_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_sound_y"))));
	mValueContainer.addAsset("options_scene_menu_sound_on_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_sound_on_y"))));
	mValueContainer.addAsset("options_scene_menu_sound_off_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_sound_off_y"))));

	mValueContainer.addAsset("options_scene_menu_languages_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_languages_y"))));
	mValueContainer.addAsset("options_scene_menu_english_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_english_y"))));
	mValueContainer.addAsset("options_scene_menu_french_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_french_y"))));
	mValueContainer.addAsset("options_scene_menu_spanish_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_spanish_y"))));

	mValueContainer.addAsset("end_scene_outcome_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_outcome_y"))));

	mValueContainer.addAsset("end_scene_menu_title_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_menu_title_y"))));
	mValueContainer.addAsset("end_scene_menu_subtitle_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_menu_subtitle_y"))));
	mValueContainer.addAsset("end_scene_menu_back_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_menu_back_y"))));
}

void AssetManager::loadColors()
{
	mColorContainer.addAsset("title_color", new Color((unsigned char)*getValue("title_color_r"),
		(unsigned char)*getValue("title_color_g"), (unsigned char)*getValue("title_color_b")));

	mColorContainer.addAsset("text_color", new Color((unsigned char)*getValue("text_color_r"),
		(unsigned char)*getValue("text_color_g"), (unsigned char)*getValue("text_color_b")));

	mColorContainer.addAsset("button_press_color", new Color((unsigned char)*getValue("button_press_color_r"),
		(unsigned char)*getValue("button_press_color_g"), (unsigned char)*getValue("button_press_color_b")));
}

void AssetManager::loadSounds()
{
	mSoundContainer.addAsset("balloon_sound", new Sound(mMainSettingsFile.getSettingFromKey("balloon_sound_filename"), true));
	mSoundContainer.addAsset("balloon_music", new Sound(mMainSettingsFile.getSettingFromKey("balloon_music_filename"), false));
}

void AssetManager::loadFonts()
{
	mFontContainer.addAsset("title_font", new Font(mMainSettingsFile.getSettingFromKey("font_src"), (int)*getValue("title_font_size")));
	mFontContainer.addAsset("subtitle_font", new Font(mMainSettingsFile.getSettingFromKey("font_src"), (int)*getValue("subtitle_font_size")));
	mFontContainer.addAsset("gui_font", new Font(mMainSettingsFile.getSettingFromKey("font_src"), (int)*getValue("gui_font_size")));
}

void AssetManager::loadVector2Ds() {}