#include <Main.hpp>

#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Files/Format/Obj/Obj.hpp>
#include <NordicEngine/Render/Text/Text.hpp>
#include <NordicEngine/Color/Color.hpp>
#include <NordicEngine/Render/Shaders/Loader.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>
#include <NordicEngine/NordicEngine/Render/Shaders/Loader.hpp>

namespace Game {
    void handleException(std::exception_ptr oException) {
        try {
            if (oException) {
                std::rethrow_exception(oException);
            }
        } catch (const std::exception &oEx) {
            printIt(oEx.what());
        }
    }

    int Main() {
        try {    
            // Set the Game Name
            std::string cGameName = "Experiments";

            // Logger Object
            NordicArts::NordicEngine::Logger  oLogger(cGameName);
            NordicArts::NordicEngine::Logger *pLogger = &oLogger;

            // Settings Object
            NordicArts::NordicEngine::Settings  oSettings(pLogger, cGameName);
            NordicArts::NordicEngine::Settings *pSettings = &oSettings;

            /*
            // Model Tester
            std::vector<glm::vec3> vVertex;
            std::vector<glm::vec2> vUV;
            std::vector<glm::vec3> vNormal;
    
            NordicArts::NordicEngine::Files::Obj oObj("GameFiles/Models/suzanne.obj");
            oObj.loadModel(vVertex, vUV, vNormal);
            */

            // Setup settings
            pSettings->setup();

            // Window Object
            NordicArts::NordicEngine::Window  oWindow(pLogger, pSettings);
            NordicArts::NordicEngine::Window *pWindow = &oWindow;

            // Setup the window
            pWindow->setup();
            pWindow->createWindow();
            pWindow->makeContext();
            pWindow->initColor(NordicArts::NordicEngine::Color::Blue);

            unsigned int iVAO;
            glGenVertexArrays(1, &iVAO);
            glBindVertexArray(iVAO);

            unsigned int iVBO;
            glGenBuffers(1, &iVBO);
            glBindBuffer(GL_ARRAY_BUFFER, iVBO);

            float fVertex[] = {
                    0.0f, 0.5f,
                    0.5f, -0.5f,
                    -0.5f, -0.5f
            };

            glBufferData(GL_ARRAY_BUFFER, sizeof(fVertex), fVertex, GL_STATIC_DRAW);

            // Shaders
            NordicArts::NordicEngine::Render::Shaders::Loader  oLoader;
            NordicArts::NordicEngine::Render::Shaders::Loader *pLoader = &oLoader;
            pLoader->addShader("GameFiles/Shaders/tut1.vertex", "VERTEX");
            pLoader->addShader("GameFiles/Shaders/tut1.fragment", "FRAGMENT");
            pLoader->addFragmentData(0, "outColor");
            unsigned int iProgramID = pLoader->buildShader();

            int iPosAttrib = pLoader->getAttrib(iProgramID, "position");
            glEnableVertexAttribArray(iPosAttrib);
            glVertexAttribPointer(iPosAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

            // Text
            NordicArts::NordicEngine::Render::Text oText;
            oText.setup("GameFiles/Textures/Holstein.DDS");

            // Loop the render
            while (pWindow->isWindowOpen()) {
                // Set the color to base color on each refresh
                pWindow->clear();

                glDrawArrays(GL_TRIANGLES, 0, 3);

                // Render Text
                oText.render("Tester", 0, 0, 1);

                // Poll the keys and display to screen
                pWindow->display();
            }

            glDeleteProgram(iProgramID);
            glDeleteBuffers(1, &iVBO);
            glDeleteVertexArrays(1, &iVAO);

            oText.cleanup();
        } catch (std::exception &oException) {
            throw NordicArts::NordicEngine::Exception(oException.what());
        } catch (NordicArts::NordicEngine::Exception &oException) {
            printIt(oException.what());
        } catch ( ... ) {
            handleException(std::current_exception());
        }

        return EXIT_SUCCESS;
    }
};

int main() {
    return Game::Main();
}
