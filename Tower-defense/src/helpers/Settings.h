#pragma once

/**
* @brief Singleton class with settings
*/
class Settings {
private:
	// Disallow creating an instance of this object
	Settings() {};
public:
	static bool FULLSCREEN;
};