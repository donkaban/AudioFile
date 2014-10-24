
#include <thread>
#include "AudioFile.h"


int main() 
{
    try
    {
   
        std::thread player([&]()
        {
            AudioFile t1("harp.wav");

            while(true)
            { 
                t1.play();
                std::chrono::milliseconds dura(2000);
                std::this_thread::sleep_for(dura);
            }
        });
        player.join();   

        return 0;
    }
    catch(const std::exception &e)
    {
        std::cout << "error! " << e.what() << std::endl;

    }

}