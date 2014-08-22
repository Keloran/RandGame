//
//  Settings.h
//  ValkyrieEngine
//
//  Created by Max Hooton on 06/11/2013.
//  Copyright (c) 2013 NordicArts.net. All rights reserved.
//

#ifndef NORDICARTS_GAME_SETTINGS_H
#define NORDICARTS_GAME_SETTINGS_H

// Prefix
#include "../Includes.hpp"

// Includes
#include <NordicOS/Singleton/Singleton.hpp>

// Namespace
namespace NordicArts {

	// Class
	class Settings final : public Singleton {
    // Variables
	public:
	protected:
	private:
        unsigned        m_iPhysicsRefreshRate;
        int8_t          m_iFSAA;
        int8_t          m_iOpenGLES;
        
        unsigned long   m_lRandomNumberSeed;
        
        bool            m_bWindowMode;
        bool            m_bStatsLogging;
        bool            m_bVSync;
        bool            m_bMobile;
        
        glm::uvec2      m_vResolution;
        glm::uvec2      m_vOpenGL;
        
        std::string     m_cGameName;
        
        float           m_fFOV;
        
	// Methods
	public:
        // Singeton
        static Settings* const get();
        
        // Constructor
		Settings();
		virtual ~Settings();
        
        void setRandomSeed(unsigned long lSeed);
        std::string showSummary() const;
        
        // Display
        void setWindowMode(bool bWindow);
        bool isWindowed() const;
        
        // Stats
        void setStats(bool bStats);
        bool isStatsEnabled() const;
        
        // Refresh
        double getPhysicsRefresh() const;
        
        // Resolution
        void setResolution(const glm::uvec2 &vResolution);
        const glm::uvec2 getResolution() const;
        
        // Game Name
        void setGameName(std::string cName);
        std::string getGameName() const;
        
        // FOV
        void setFOV(float fFOV);
        float getFOV() const;
        
        // VSync
        void setVSync(bool bVSync);
        bool getVSync() const;

        // OpenGL
        void setOpenGL(const glm::uvec2 &vOpenGL);
        const glm::uvec2 getOpenGL() const;

        // OpenGL ES
        void setOpenGLES(int8_t iOpenGL);
        int8_t getOpenGLES() const;

        // Mobile
        void setMobile(bool bMobile);
        bool getMobile() const;

        // FSAA
        void setFSAA(int8_t iFSAA);
        int8_t getFSAA() const;
        
	protected:
	private:
        
	};
}

#endif 
