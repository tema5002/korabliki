#pragma once

typedef struct jukebox_t {
    openmpt_module* module;
    SDL_AudioDeviceID audio_device;
    SDL_AudioStream* audio_stream;
    int16_t* buffer;
    size_t buffer_len;
    int32_t sample_rate;
    pthread_t thread;
    pthread_mutex_t mutex;
} jukebox_t;

static void libopenmpt_example_logfunc( const char * message, void * userdata ) {
    (void)userdata;
    if ( message ) {
        fprintf( stderr, "openmpt: %s\n", message );
    }
}

static int libopenmpt_example_errfunc( int error, void * userdata ) {
    (void)userdata;
    (void)error;
    return OPENMPT_ERROR_FUNC_RESULT_DEFAULT & ~OPENMPT_ERROR_FUNC_RESULT_LOG;
}

static void libopenmpt_example_print_error( const char * func_name, int mod_err, const char * mod_err_str ) {
    if ( !func_name ) {
        func_name = "unknown function";
    }
    if ( mod_err == OPENMPT_ERROR_OUT_OF_MEMORY ) {
        mod_err_str = openmpt_error_string( mod_err );
        if ( !mod_err_str ) {
            fprintf( stderr, "Error: %s\n", "OPENMPT_ERROR_OUT_OF_MEMORY" );
        } else {
            fprintf( stderr, "Error: %s\n", mod_err_str );
            openmpt_free_string( mod_err_str );
            mod_err_str = NULL;
        }
    } else {
        if ( !mod_err_str ) {
            mod_err_str = openmpt_error_string( mod_err );
            if ( !mod_err_str ) {
                fprintf( stderr, "Error: %s failed.\n", func_name );
            } else {
                fprintf( stderr, "Error: %s failed: %s\n", func_name, mod_err_str );
            }
            openmpt_free_string( mod_err_str );
            mod_err_str = NULL;
        }
        fprintf( stderr, "Error: %s failed: %s\n", func_name, mod_err_str );
    }
}

static jukebox_t jukebox = {0};

static void mod_audio_callback(void* userdata, SDL_AudioStream* stream, int additional_amount, int total_amount) {
    (void)userdata; (void)additional_amount; (void)total_amount;

    pthread_mutex_lock(&jukebox.mutex);

    if (!jukebox.module) {
        pthread_mutex_unlock(&jukebox.mutex);
        return;
    }

    const size_t samples_read = openmpt_module_read_interleaved_stereo(
        jukebox.module, jukebox.sample_rate,
        jukebox.buffer_len, jukebox.buffer
    );

    if (samples_read > 0) {
        const size_t bytes = samples_read * sizeof(int16_t) * 2;
        SDL_PutAudioStreamData(stream, jukebox.buffer, bytes);
    }

    pthread_mutex_unlock(&jukebox.mutex);
}

static int mod_init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    if (pthread_mutex_init(&jukebox.mutex, NULL) != 0) {
        SDL_Quit();
        return 0;
    }
    jukebox.buffer_len = 1024;
    jukebox.sample_rate = 44100;
    jukebox.buffer = safe_malloc(sizeof(int16_t) * jukebox.buffer_len * 2);

    const SDL_AudioSpec spec = {
        .freq = jukebox.sample_rate,
        .format = SDL_AUDIO_S16,
        .channels = 2
    };

    jukebox.audio_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    if (!jukebox.audio_device) {
        return 0;
    }

    jukebox.audio_stream = SDL_OpenAudioDeviceStream(jukebox.audio_device, &spec, mod_audio_callback, NULL);
    if (!jukebox.audio_stream) {
        return 0;
    }
    SDL_ResumeAudioStreamDevice(jukebox.audio_stream);
    return 1;
}

static int mod_load_from_file(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    const size_t size = ftell(f);
    rewind(f);

    void* data = safe_malloc(size);
    fread(data, 1, size, f);
    fclose(f);

    int mod_err; char* mod_err_str;
    jukebox.module = openmpt_module_create_from_memory2(
        data, size,
        libopenmpt_example_logfunc, NULL,
        libopenmpt_example_errfunc, NULL,
        &mod_err, &mod_err_str,
        NULL
    );
    free(data);

    if (!jukebox.module) {
        libopenmpt_example_print_error("openmpt_module_create_from_memory2()", mod_err, mod_err_str);
        openmpt_free_string(mod_err_str);
        mod_err_str = NULL;
        return 0;
    }
    openmpt_module_set_repeat_count(jukebox.module, -1);
    return 1;
}