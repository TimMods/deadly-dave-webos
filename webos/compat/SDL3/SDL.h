#pragma once
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SDL_Gamepad SDL_GameController
#define SDL_OpenGamepad SDL_GameControllerOpen
#define SDL_CloseGamepad SDL_GameControllerClose
#define SDL_GetGamepadAxis SDL_GameControllerGetAxis
#define SDL_GetGamepadButton SDL_GameControllerGetButton
#define SDL_GetGamepadID(pad) SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad))
#define SDL_INIT_GAMEPAD SDL_INIT_GAMECONTROLLER
#define SDL_EVENT_GAMEPAD_ADDED SDL_CONTROLLERDEVICEADDED
#define SDL_EVENT_GAMEPAD_REMOVED SDL_CONTROLLERDEVICEREMOVED
#define SDL_EVENT_GAMEPAD_BUTTON_DOWN SDL_CONTROLLERBUTTONDOWN
#define SDL_EVENT_KEY_DOWN SDL_KEYDOWN
#define SDL_EVENT_MOUSE_BUTTON_DOWN SDL_MOUSEBUTTONDOWN
#define SDL_EVENT_MOUSE_MOTION SDL_MOUSEMOTION
#define SDL_EVENT_QUIT SDL_QUIT
#define SDL_GAMEPAD_BUTTON_SOUTH SDL_CONTROLLER_BUTTON_A
#define SDL_GAMEPAD_BUTTON_EAST SDL_CONTROLLER_BUTTON_B
#define SDL_GAMEPAD_BUTTON_WEST SDL_CONTROLLER_BUTTON_X
#define SDL_GAMEPAD_BUTTON_NORTH SDL_CONTROLLER_BUTTON_Y
#define SDL_GAMEPAD_BUTTON_START SDL_CONTROLLER_BUTTON_START
#define SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define SDL_GAMEPAD_BUTTON_DPAD_UP SDL_CONTROLLER_BUTTON_DPAD_UP
#define SDL_GAMEPAD_BUTTON_DPAD_DOWN SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define SDL_GAMEPAD_BUTTON_DPAD_LEFT SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define SDL_GAMEPAD_BUTTON_DPAD_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT
#define SDL_GAMEPAD_AXIS_LEFTX SDL_CONTROLLER_AXIS_LEFTX
#define SDL_GAMEPAD_AXIS_LEFTY SDL_CONTROLLER_AXIS_LEFTY
#define SDL_GAMEPAD_AXIS_RIGHT_TRIGGER SDL_CONTROLLER_AXIS_TRIGGERRIGHT
/* SDL-webOS sends this scancode but omits it from its public enum. */
#define SDL_WEBOS_SCANCODE_BACK ((SDL_Scancode)482)
#define SDL_GetGamepads dd_gamepads
#define SDL_GetRenderWindow SDL_RenderGetWindow
#define SDL_GetCurrentRenderOutputSize SDL_GetRendererOutputSize
#define SDL_RenderTexture SDL_RenderCopyF
#define SDL_SCALEMODE_NEAREST SDL_ScaleModeNearest
#define SDL_ConvertSurface(s,f) SDL_ConvertSurfaceFormat(s,f,0)
#define SDL_DestroySurface SDL_FreeSurface
#define SDL_KMOD_ALT KMOD_ALT
#define SDL_KMOD_GUI KMOD_GUI
#define SDLK_A SDLK_a
#define SDLK_Z SDLK_z
#define SDL_NS_PER_SECOND UINT64_C(1000000000)
#define SDL_GetTicksNS dd_ticks_ns
#define SDL_DelayNS(ns) SDL_Delay((Uint32)(((ns) + 999999) / 1000000))
#define SDL_SyncWindow(window) ((void)(window))
#define SDL_GetBasePath dd_base_path
#define SDL_Init(flags) (SDL_Init(flags) == 0)
#define SDL_InitSubSystem(flags) (SDL_InitSubSystem(flags) == 0)
#define SDL_CreateWindow(title,w,h,flags) SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags)
#define SDL_CreateRenderer(window,name) SDL_CreateRenderer(window, -1, 0)
#define SDL_SetWindowFullscreen(window,enabled) SDL_SetWindowFullscreen(window, (enabled) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0)
#define SDL_WINDOW_FULLSCREEN SDL_WINDOW_FULLSCREEN_DESKTOP
#define SDL_SetRenderVSync(renderer,enabled) (SDL_RenderSetVSync(renderer, enabled) == 0)
#define SDL_LockTexture(texture,rect,pixels,pitch) (SDL_LockTexture(texture, rect, pixels, pitch) == 0)
#define SDL_SaveFile dd_save_file
#define SDL_AUDIO_S16LE AUDIO_S16LSB
#define SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK 0
#define SDL_AudioStream DaveAudio
#define SDL_OpenAudioDeviceStream dd_audio_open
#define SDL_PutAudioStreamData dd_audio_put
#define SDL_LockAudioStream(a) SDL_LockAudioDevice((a)->device)
#define SDL_UnlockAudioStream(a) SDL_UnlockAudioDevice((a)->device)
#define SDL_PauseAudioStreamDevice(a) SDL_PauseAudioDevice((a)->device,1)
#define SDL_ResumeAudioStreamDevice(a) SDL_PauseAudioDevice((a)->device,0)
#define SDL_DestroyAudioStream dd_audio_close

typedef int SDL_DisplayID;
#define SDL_GetDisplayForWindow(window) (SDL_GetWindowDisplayIndex(window) + 1)

const char *dd_base_path(void);
Uint64 dd_ticks_ns(void);
static inline SDL_JoystickID *dd_gamepads(int *count)
{
    int devices = SDL_NumJoysticks();
    *count = 0;
    if (devices <= 0) return NULL;
    SDL_JoystickID *indices = SDL_malloc((size_t)devices * sizeof(*indices));
    if (!indices) return NULL;
    for (int i = 0; i < devices; ++i)
        if (SDL_IsGameController(i)) indices[(*count)++] = i;
    return indices;
}

typedef struct DaveAudio DaveAudio;
typedef void (SDLCALL *DaveAudioCallback)(void *, DaveAudio *, int, int);
struct DaveAudio {
    SDL_AudioDeviceID device;
    DaveAudioCallback callback;
    void *userdata;
    Uint8 *output;
    int remaining;
};

DaveAudio *dd_audio_open(int device, const SDL_AudioSpec *spec, DaveAudioCallback callback, void *userdata);
void dd_audio_put(DaveAudio *audio, const void *data, int size);
void dd_audio_close(DaveAudio *audio);
bool dd_save_file(const char *path, const void *data, size_t size);
#define SDLK_APOSTROPHE SDLK_QUOTE
