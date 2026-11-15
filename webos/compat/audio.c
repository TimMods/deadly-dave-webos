#include <SDL3/SDL.h>

static void SDLCALL fill_audio(void *userdata, Uint8 *output, int size)
{
    DaveAudio *audio = userdata;
    SDL_memset(output, 0, size);
    audio->output = output;
    audio->remaining = size;
    audio->callback(audio->userdata, audio, size, size);
}

DaveAudio *dd_audio_open(int device, const SDL_AudioSpec *spec, DaveAudioCallback callback, void *userdata)
{
    (void)device;
    DaveAudio *audio = SDL_calloc(1, sizeof(*audio));
    if (!audio) return NULL;
    audio->callback = callback;
    audio->userdata = userdata;
    SDL_AudioSpec request = *spec;
    request.samples = 1024;
    request.callback = fill_audio;
    request.userdata = audio;
    audio->device = SDL_OpenAudioDevice(NULL, 0, &request, NULL, 0);
    if (audio->device) return audio;
    SDL_free(audio);
    return NULL;
}

void dd_audio_put(DaveAudio *audio, const void *data, int size)
{
    if (size <= 0 || size > audio->remaining) return;
    SDL_memcpy(audio->output, data, size);
    audio->output += size;
    audio->remaining -= size;
}

void dd_audio_close(DaveAudio *audio)
{
    if (!audio) return;
    SDL_CloseAudioDevice(audio->device);
    SDL_free(audio);
}

bool dd_save_file(const char *path, const void *data, size_t size)
{
    FILE *file = fopen(path, "wb");
    if (!file) return false;
    bool written = fwrite(data, 1, size, file) == size;
    return fclose(file) == 0 && written;
}
