#include <Main.hpp>

#include <NordicEngine/Window/Window.hpp>
#include <NordicEngine/Logger/Logger.hpp>
#include <NordicEngine/Settings/Settings.hpp>
#include <NordicEngine/Renderer/Renderer.hpp>
#include <NordicEngine/Files/Format/Obj/Obj.hpp>

#include <NordicEngine/ThirdParty/glm/glm/glm.hpp>

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
            std::vector<glm::vec3> vUV;
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
            NordicArts::NordicEngine::Renderer *pRenderer = &oRenderer;
            
            while (pWindow->isWindowOpen()) {

                // Poll the keys and display to screen
                pWindow->display();
            }
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
