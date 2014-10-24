#include <iostream>
#include <vector>
#include <string>
#include <alsa/asoundlib.h>

class AudioFile
{
public: 
    using raw_buf = std::vector<char>;

   
    AudioFile(const std::string &);
    virtual ~AudioFile();
    void play();
   
private:

    void init();
    void close();
    uint getChannels();
    uint getRate();

    std::string _filename;
    raw_buf  _buffer;
    uint _rate;
    uint _ch;
    snd_pcm_t    * pcm_hdl;
    snd_pcm_hw_params_t * params;
 };