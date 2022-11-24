#include <dwmapi.h>

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>

namespace {
// use OpenGL 3.3
static constexpr int GL_MAJOR = 3;
static constexpr int GL_MINOR = 3;
static constexpr const char *GLSL_VERSION = "#version 330";
} // namespace

#undef main
int main(HINSTANCE, HINSTANCE, PSTR, int) {
  // setup SDL
  SDL_Init(SDL_INIT_VIDEO);

  // note: do this after SDL_Init
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  const auto window =
      SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_OPENGL);

  // creating the OpenGL context for the window
  const auto gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // use v-sync

  // get window HWND
  SDL_SysWMinfo info;
  SDL_VERSION(&info.version);
  SDL_GetWindowWMInfo(window, &info);

  // make window transparent
  MARGINS margins = {-1};
  SetWindowLong(info.info.win.window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
  if (FAILED(DwmExtendFrameIntoClientArea(info.info.win.window, &margins))) {
    throw;
  }

  // load OpenGL 3.3 functions
  // gladLoadGLLoader(SDL_GL_GetProcAddress);

  // init imgui for SDL
  // IMGUI_CHECKVERSION();
  // ImGui::CreateContext();
  // ImGuiIO &io = ImGui::GetIO();
  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  // ImGui_ImplOpenGL3_Init(GLSL_VERSION);

  // render loop
  bool running = true;
  int last_w = -1, last_h = -1;
  while (running) {
    // poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      // ImGui_ImplSDL2_ProcessEvent(&event);

      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window)) {
        running = false;
      }
    }

    // new imgui frame
    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplSDL2_NewFrame();
    // ImGui::NewFrame();

    // ImGui::Render();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // update and render additional platform windows
    // auto backup_current_window = SDL_GL_GetCurrentWindow();
    // auto backup_current_context = SDL_GL_GetCurrentContext();
    // ImGui::UpdatePlatformWindows();
    // ImGui::RenderPlatformWindowsDefault();
    // SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    SDL_GL_SwapWindow(window);
  }

  if (glGetError() != GL_NO_ERROR) {
    throw;
  }

  // teardown and free resources
  // ImGui_ImplOpenGL3_Shutdown();
  // ImGui_ImplSDL2_Shutdown();
  // ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
