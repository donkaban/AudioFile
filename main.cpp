
#include "AudioFile.h"


int main() 
{
    try
    {
        AudioFile::initAudioSystem();

        AudioFile t1("test1.wav");
        AudioFile t2("test2.wav");


        t1.play();
        t2.play();
        


        AudioFile::closeAudioSystem();
        
        return 0;
    }
    catch(const std::exception &e)
    {
        std::cout << "error! " << e.what() << std::endl;

    }

}