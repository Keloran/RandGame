#include "./Context.hpp"
#include "../Window/WindowOS/WindowOS.hpp"
#include "../../ExceptionHandler/Errors.hpp"

#import "../Wrapper/AutoReleasePool.hpp"

namespace NordicArts {
    namespace NordicOS {
        NAContext::NAContext(NAContext *pShared) : m_view(0), m_window(0) {
            retainPool();

            createContext(pShared, VideoMode::getDesktopMode().m_iBitsPerPixel, ContextSettings(0, 0, 0));
        }

        NAContext::NAContext(NAContext *pShared, const ContextSettings &oSettings, const WindowImp *pOwner, unsigned int iBitsPerPixel) : m_view(0), m_window(0) {
            retainPool();
        
            createContext(pShared, iBitsPerPixel, oSettings);

            const WindowOS *pWindowOS = static_cast<const WindowOS *>(pOwner);
            pWindowOS->applyContext(m_context);
        }

        NAContext::NAContext(NAContext *pShared, const ContextSettings &oSettings, unsigned int iWidth, unsigned int iHeight) : m_view(0), m_window(0) { 
            WindowOS::setUpProcess();
        
            retainPool();
            
            createContext(pShared, VideoMode::getDesktopMode().m_iBitsPerPixel, oSettings);

            m_window    = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, iWidth, iHeight) styleMask:NSBorderlessWindowMask backing:NSBackingStoreBuffered defer:NO];
            m_view      = [[NSOpenGLView alloc] initWithFrame:NSMakeRect(0, 0, iWidth, iHeight)];
        
            [m_window setContentView:m_view];
            [m_view setOpenGLContext:m_context];
            [m_context setView:m_view];
        }

        NAContext::~NAContext() {
            [m_context clearDrawable];
            [m_context release];

            [m_view release];
            [m_window release];

            releasePool();
        }

        bool NAContext::makeCurrent() {
            [m_context makeCurrentContext];
        
            return (m_context == [NSOpenGLContext currentContext]);
        }

        void NAContext::display() {
            [m_context flushBuffer];
        }

        void NAContext::setVerticalSyncEnabled(bool bEnabled) {
            GLint swapInterval = (bEnabled ? 1 : 0);
            [m_context setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
        }

        void NAContext::createContext(NAContext *pShared, unsigned int iBitsPerPixel, const ContextSettings &oSettings) {
            std::vector<NSOpenGLPixelFormatAttribute> attrs;
            attrs.reserve(20);


            attrs.push_back(NSOpenGLPFAClosestPolicy);
            attrs.push_back(NSOpenGLPFADoubleBuffer);

            if (iBitsPerPixel > 24) {
                attrs.push_back(NSOpenGLPFAAlphaSize);
                attrs.push_back((NSOpenGLPixelFormatAttribute)8);
            }

            attrs.push_back(NSOpenGLPFADepthSize);
            attrs.push_back((NSOpenGLPixelFormatAttribute)oSettings.iDepthBits);
            attrs.push_back(NSOpenGLPFAStencilSize);
            attrs.push_back((NSOpenGLPixelFormatAttribute)oSettings.iStencilBits);

            if (oSettings.iAntiAliasingLevel > 0) {
                attrs.push_back(NSOpenGLPFAMultisample);
                attrs.push_back(NSOpenGLPFASampleBuffers);
                attrs.push_back((NSOpenGLPixelFormatAttribute)1);
                attrs.push_back(NSOpenGLPFASamples);
                attrs.push_back((NSOpenGLPixelFormatAttribute)oSettings.iAntiAliasingLevel);
                attrs.push_back(NSOpenGLPFAAccelerated);
            }

            bool bLegacy = (oSettings.iMajorVersion < 3);
            attrs.push_back(NSOpenGLPFAOpenGLProfile);

            if (bLegacy) {
                attrs.push_back(NSOpenGLProfileVersionLegacy);
            } else {
                attrs.push_back(NSOpenGLProfileVersion3_2Core);
            }

            attrs.push_back((NSOpenGLPixelFormatAttribute)0);

            NSOpenGLPixelFormat *pixFmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:&attrs[0]];
            if (pixFmt == nil) {
                Errors() << "not a good pixle format" << std::endl;
                
                return;
            }

            NSOpenGLContext *sharedContext = (pShared != NULL ? pShared->m_context: nil);
            
            m_context = [[NSOpenGLContext alloc] initWithFormat:pixFmt shareContext:sharedContext];
            if (m_context == nil) {
                Errors() << "trying without shared context" << std::endl;
        
                m_context = [[NSOpenGLContext alloc] initWithFormat:pixFmt shareContext:nil];
                if (m_context == nil) {
                    Errors() << "cant create context" << std::endl;
                } else {
                    Errors() << "cant create context without shared context" << std::endl;
                }
            }

            [pixFmt release];

            m_Settings = oSettings;
        }
    };
};
