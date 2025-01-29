# DSP-Projects

Analog Circuit Modeling of MXR MicroAmp Guitar Pedal 🎸🎛️
Overview
This project models the MXR MicroAmp guitar pedal, a renowned clean boost pedal, to simulate, analyze, and digitally replicate its performance. The workflow includes analog circuit simulation, theoretical analysis, digital transformation, and plugin development using JUCE and HISE platforms.

Key Features 📌
Analog Circuit Simulation:
Modeled and simulated the MXR MicroAmp circuit using TINA to analyze its performance and waveforms.
Theoretical Analysis:
Applied Norton’s theorem and Modified Nodal Analysis (MNA) to understand the op-amp and potentiometer behavior, achieving up to 26dB gain with minimal distortion (<0.1%).
Digital Transformation:
Converted transfer functions into OCTAVE scripts, validated the results with simulations, and ensured fidelity in the digital domain.
Plugin Development:
Built a digital audio plugin in JUCE using C++ and integrated it into the HISE platform for seamless performance replication and enhancement.
Workflow ⚙️
1. Analog Circuit Modeling
Modeled the MXR MicroAmp circuit in TINA, simulating the transfer function and verifying the output response.
Analyzed the potentiometer's role in controlling gain and ensuring a clean frequency response.
2. Theoretical Insights
Applied Norton’s theorem to simplify circuit analysis.
Used Modified Nodal Analysis (MNA) to evaluate circuit components like the op-amp and potentiometer.
3. Digital Conversion
Derived transfer functions from the analog model.
Developed OCTAVE scripts to simulate the digital audio response.
Validated functionality through waveform analysis in the digital domain.
4. Plugin Development
Designed a digital audio plugin using JUCE and C++.
Integrated the plugin into the HISE platform, ensuring accurate replication of the analog circuit with enhancements.
Results 🏆
Achieved 26dB clean gain with a distortion margin of <0.1% in the analog model.
Successfully replicated the analog circuit's characteristics in the digital domain.
Delivered a functional digital audio plugin with enhanced usability for musicians and audio engineers.
Tools & Technologies 🛠️
TINA: Analog circuit modeling and simulation.
OCTAVE: Digital transformation and script validation.
JUCE: Plugin development framework.
HISE Platform: Audio plugin integration and performance testing.
Screenshots & Visuals 📸
(Include circuit diagrams, simulation results, plugin interface screenshots, and waveform comparisons between analog and digital models.)

How to Use 🚀
Clone this repository:
bash
Copy
Edit
git clone https://github.com/your-username/mxr-microamp-modeling.git  
Open the JUCE project:
Navigate to the JUCE_Project folder and open the .jucer file.
Build and Run:
Compile and run the project in your preferred IDE.
References 📚
MXR MicroAmp Schematic
JUCE Framework
HISE Platform
