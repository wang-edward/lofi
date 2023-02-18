#pragma once

#include "core/Plugin.hpp"
#include "plugins/Keyboard.hpp"
#include "plugins/SineEnv.hpp"

#include "utils/Utils.h"

namespace lofi {

class Keyboard : public Plugin {

public:

    Keyboard();
    void onProcess(al::AudioIOData &io);
    void onProcess(al::Graphics& g);
    void onTriggerOn(const al::Keyboard &k);
    void onTriggerOff(const al::Keyboard &k);

private:
    SynthGUIManager<SineEnv> synthManager{"SineEnv_Piano"};
};

} // namespace lofi