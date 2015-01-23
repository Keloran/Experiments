#include <Main.hpp>

#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Renderer/Renderer.hpp>
#include <NordicEngine/Files/Format/Obj/Obj.hpp>
#include <NordicEngine/Render/Text/Text.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>
#include <NordicEngine/Color/Color.hpp>

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

            // Model Tester
            std::vector<glm::vec3> vVertex;
            std::vector<glm::vec2> vUV;
            std::vector<glm::vec3> vNormal;
    
            NordicArts::NordicEngine::Files::Obj oObj("GameFiles/Models/suzanne.obj");
            oObj.loadModel(vVertex, vUV, vNormal);

            // Setup settings
            pSettings->setup();

            // Window Object
            NordicArts::NordicEngine::Window  oWindow(pLogger, pSettings);
            NordicArts::NordicEngine::Window *pWindow = &oWindow;

            // Setup the window
            pWindow->setup();
            pWindow->createWindow();
            pWindow->makeContext();

            // Renderer
            NordicArts::NordicEngine::Renderer  oRenderer(pLogger, pWindow);
            oRenderer.setColor(NordicArts::NordicEngine::Color::Blue);

            // Text
            NordicArts::NordicEngine::Render::Text oText;
            oText.setup("GameFiles/Textures/Holstein.DDS");
            
            while (pWindow->isWindowOpen()) {
                oRenderer.clear();

                oText.render("Tester", 0, 0, 1);

                // Poll the keys and display to screen
                pWindow->display();
            }

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
