#ifndef NordicArts_NordicOS_Window_Mouse_H
#define NordicArts_NordicOS_Window_Mouse_H

#include <glm/glm.hpp>

namespace NordicArts {
    namespace NordicOS {
        class Window;

        class Mouse {
        // Variables
        public:
            enum Button {
                Left,
                Right,
                Middle,
                XButton1,
                XButton2,

                ButtonCount
            };

        protected:
        private:    

        // Methods
        public:
            static bool isButtonPressed(Button eButton);

            static glm::vec2 getPosition();
            static glm::vec2 getPosition(const Window &oWindow);
            
            static void setPosition(const glm::vec2 &vPosition);
            static void setPosition(const glm::vec2 &vPosition, const Window &oWindow);

        protected:
        private:

        };
    };
};

#endif
