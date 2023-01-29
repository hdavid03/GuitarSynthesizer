# GuitarSynthesizer
> A simple C++ acoustic guitar synthesizer software
---
## About this project
The project is based on university studies and involves roughly two semesters of research work. This includes learning about the JUCE framework, which is great and really useful for building audio applications in C++. My goal was to create a real-time guitar synthesizer application that can also used by an _audio editing program_ as a VST plugin.
I measured an acoustic guitar body and became acquainted with digital filters. The development continued with implementation of the string model.
As a string model, I implemented a digital waveguide, which I had to add a fractional delay filter to accurately determine the fundamental frequency, and a loss filter to adjust the decay times of the components of the guitar sounds. In addition, I implemented the guitar body with a 480th-order warped IIR filter.
As a next step, I supplemented the synthesizer with a volume control and an effect to sustain the sound after releasing a key.
You can find information [here](https://ccrma.stanford.edu/~jos/pasp/Digital_Waveguide_Model.html) about the waveguide modeling and [here](https://www.ee.columbia.edu/~dpwe/papers/KarjHLH97-warp.pdf) about the warped filters.
## Installation on Linux
1. `cd Builds/LinuxMakefile/`
2. run `make all` to compile the source code
## Running standalone application
1. `cd Builds/LinuxMakefile/build/`
> You can find also here the VST plugin
2. `./GuitarSynthesizer`

