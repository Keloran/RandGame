#ifndef NordicArts_NordicOS_Window_WindowStyle_H
#define NordicArts_NordicOS_Window_WindowStyle_H

namespace NordicArts {
    namespace NordicOS {
        namespace Style {
            enum {
                None            = 0,
                TitleBar        = 1 << 0,
                Resize          = 1 << 1,
                Close           = 1 << 2,
                FullScreen      = 1 << 3,

                Default         = (TitleBar | Resize | Close)
            };
        };
    };
};

#endif
