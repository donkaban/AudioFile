#include <iostream>
#include <vector>
#include <string>
#include <alsa/asoundlib.h>

class AudioFile
{
public: 
    using raw_buf = std::vector<char>;

    static void initAudioSystem();
    static void closeAudioSystem();

    AudioFile(const std::string &);
    virtual ~AudioFile();
    void play();
   
private:

    raw_buf  _buffer;
    static uint _rate;
    static uint _ch;
    static snd_pcm_t    * pcm_hdl;
    static snd_pcm_hw_params_t * params;
 };