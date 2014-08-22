//
//  Settings.cpp
//  ValkyrieEngine
//
//  Created by Max Hooton on 06/11/2013.
//  Copyright (c) 2013 NordicArts.net. All rights reserved.
//

// Includes
#include "./Settings.hpp"
#include <NordicOS/ExceptionHandler/ExceptionHandler.hpp>

// Static pointer
namespace NordicArts {
    namespace GameNS {
        static Settings* g_pSettings = nullptr;

        Settings* const Settings::get() {
            if (g_pSettings == nullptr) {
                char cError[1024];
                std::sprintf(cError, "%s Failed to use Settings", __FUNCTION__);

                throw ExceptionHandler(cError);
            }

            return g_pSettings;
        }

        // Constructor
        Settings::Settings() : Singleton(TYPE_SETTINGS), m_iPhysicsRefreshRate(100), m_bWindowMode(true), m_lRandomNumberSeed(0), m_bStatsLogging(false), m_vResolution(1024, 768), m_fFOV(45.0f), m_bVSync(true), m_vOpenGL(3, 3), m_iFSAA(0), m_bMobile(false), m_iOpenGLES(2) {
            g_pSettings = this;
        }

        Settings::~Settings() {
            g_pSettings = nullptr;
        }

        // Game Name
        void Settings::setGameName(std::string cGameName) {
            m_cGameName = cGameName;
        }
        std::string Settings::getGameName() const {
            return m_cGameName;
        }

        // Set the random seed
        void Settings::setRandomSeed(unsigned long lSeed) {
            m_lRandomNumberSeed = lSeed;
        }

        // Window display mode
        void Settings::setWindowMode(bool bWindowed) {
            m_bWindowMode = bWindowed;
        }
        bool Settings::isWindowed() const {
            return m_bWindowMode;
        }

        // Stats
        void Settings::setStats(bool bStats) {
            m_bStatsLogging = bStats;
        }
        bool Settings::isStatsEnabled() const {
            return m_bStatsLogging;
        }

        // Physics
        double Settings::getPhysicsRefresh() const {
            return (1.0 / static_cast<double>(m_iPhysicsRefreshRate));
        }

        // Summary
        std::string Settings::showSummary() const {
            int iLength = 57;

            std::ostringstream cReturn;

            cReturn << "Settings: " << std::endl;

            // Random number seed and value
            cReturn << std::setfill(' ') << std::setw(iLength) << "Seed: " << m_lRandomNumberSeed << std::endl;

            // Window Mode
            cReturn << std::setfill(' ') << std::setw(iLength) << "Windowed: " << (m_bWindowMode ? "Yes" : "No") << std::endl;

            // Physics Refresh
            cReturn << std::setfill(' ') << std::setw(iLength) << "Physics Refresh: " << m_iPhysicsRefreshRate << "Hz" << std::endl;

            // Logging
            cReturn << std::setfill(' ') << std::setw(iLength) << "Stats Logging: " << (m_bStatsLogging ? "Yes" : "No") << std::endl;

            // Resolution
            cReturn << std::setfill(' ') << std::setw(iLength) << "Resolution: " << m_vResolution.x  <<  "x" << m_vResolution.y << std::endl;

            // FOV
            cReturn << std::setfill(' ') << std::setw(iLength) << "FOV 1x: " << m_fFOV << std::endl;
            cReturn << std::setfill(' ') << std::setw(iLength) << "FOV 2x: " << (m_fFOV * 2) << std::endl;

            // VSync
            cReturn << std::setfill(' ') << std::setw(iLength) << "VSync: " << (m_bVSync ? "On" : "Off") << std::endl;

            // OpenGL
            cReturn << std::setfill(' ') << std::setw(iLength) << "OpenGL Version: " << m_vOpenGL.x << "." << m_vOpenGL.y << std::endl;

            // FSAA
            cReturn << std::setfill(' ') << std::setw(iLength) << "FSAA: " << m_iFSAA << std::endl;

            // Send back
            return cReturn.str();
        }

        // Resolution
        void Settings::setResolution(const glm::uvec2 &vResolution) {
            m_vResolution = glm::uvec2(glm::clamp(vResolution.x, 800U, 2560U), glm::clamp(vResolution.y, 600U, 2048U));
        }
        const glm::uvec2 Settings::getResolution() const {
            return m_vResolution;
        }

        // FOV
        void Settings::setFOV(float fFOV) {
            m_fFOV = fFOV;
        }
        float Settings::getFOV() const {
            return m_fFOV;
        }

        // VSync
        void Settings::setVSync(bool bVSync) {
            m_bVSync = bVSync;
        }
        bool Settings::getVSync() const {
            return m_bVSync;
        }

        // OpenGL
        void Settings::setOpenGL(const glm::uvec2 &vOpenGL) {
            m_vOpenGL = glm::uvec2(glm::clamp(vOpenGL.x, 3U, 4U), glm::clamp(vOpenGL.y, 0U, 9U));
        }
        const glm::uvec2 Settings::getOpenGL() const {
            return m_vOpenGL;
        }

        // OpenGL ES
        void Settings::setOpenGLES(int8_t iOpenGL) {
            m_iOpenGLES = iOpenGL;
        }
        int8_t Settings::getOpenGLES() const {
            return m_iOpenGLES;
        }

        // Mobile
        void Settings::setMobile(bool bMobile) {
            m_bMobile = bMobile;
        }
        bool Settings::getMobile() const {
            return m_bMobile;
        }

        // FSAA
        void Settings::setFSAA(int8_t iFSAA) {
            m_iFSAA = iFSAA;
        }
        int8_t Settings::getFSAA() const {
            return m_iFSAA;
        }
    };
};
